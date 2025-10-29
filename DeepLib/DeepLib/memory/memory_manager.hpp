#ifndef DEEP_LIB_MEMORY_MANAGER_HPP
#define DEEP_LIB_MEMORY_MANAGER_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepCore/memory.hpp"

#include <new>
#include <utility>

namespace deep
{
    template <typename Type>
    class mem_ptr;

    template <typename Type>
    class buffer_ptr;

    class DEEP_LIB_API memory_manager
    {
      public:
        memory_manager() = delete;
        memory_manager(void *internal_context);

        template <typename Type, typename... Args>
        Type *alloc(Args &&...args);

        template <typename Type>
        Type *alloc(usize bytes_size);

        template <typename Type>
        Type *realloc(Type *address, usize bytes_size);

        template <typename Type>
        bool realloc(buffer_ptr<Type> &buffer, usize bytes_size);

        template <typename Type>
        bool dealloc(Type *ptr);

        template <typename Type>
        bool dealloc(mem_ptr<Type> &data);

        template <typename Type>
        bool dealloc(buffer_ptr<Type> &buffer);

      private:
        friend class lib;

        void *m_internal_context;
    };

    template <typename Type, typename... Args>
    inline Type *memory_manager::alloc(Args &&...args)
    {
        Type *obj = (Type *) core_mem::alloc(m_internal_context, sizeof(Type));

        if (obj == nullptr)
        {
            return nullptr;
        }

        new (obj) Type(std::forward<Args>(args)...);

        return obj;
    }

    template <typename Type>
    inline Type *memory_manager::alloc(usize bytes_size)
    {
        Type *obj = (Type *) core_mem::alloc(m_internal_context, bytes_size);

        if (obj == nullptr)
        {
            return nullptr;
        }

        return obj;
    }

    template <typename Type>
    inline Type *memory_manager::realloc(Type *address, usize bytes_size)
    {
        Type *ptr = static_cast<Type *>(core_mem::realloc(m_internal_context, address, bytes_size));

        if (ptr == nullptr)
        {
            return nullptr;
        }

        return ptr;
    }

    template <typename Type>
    inline bool memory_manager::realloc(buffer_ptr<Type> &buffer, usize bytes_size)
    {
        Type *ptr = static_cast<Type *>(core_mem::realloc(m_internal_context, buffer.get(), bytes_size));

        if (ptr == nullptr)
        {
            return false;
        }

        buffer.set(ptr, bytes_size);

        return true;
    }

    template <typename Type>
    inline bool memory_manager::dealloc(Type *ptr)
    {
        if (!is_trivially_destructible<Type>)
        {
            ptr->~Type();
        }

        if (!core_mem::dealloc(m_internal_context, ptr))
        {
            return false;
        }

        return true;
    }

    template <typename Type>
    inline bool memory_manager::dealloc(mem_ptr<Type> &data)
    {
        Type *ptr = data.get();

        // Si l'objet a un destructeur défini, l'appelle.
        if (!is_trivially_destructible<Type>)
        {
            ptr->~Type();
        }

        if (!core_mem::dealloc(m_internal_context, ptr))
        {
            return false;
        }

        data.set(nullptr);

        return true;
    }

    template <typename Type>
    inline bool memory_manager::dealloc(buffer_ptr<Type> &buffer)
    {
        Type *ptr = buffer.get();

        if (!core_mem::dealloc(m_internal_context, ptr))
        {
            return false;
        }

        buffer.set(nullptr, 0);

        return true;
    }
} // namespace deep

#endif
