#ifndef DEEP_LIB_MEMORY_MANAGER_HPP
#define DEEP_LIB_MEMORY_MANAGER_HPP

#include "deep_lib_export.h"
#include "../DeepCore/types.hpp"
#include "../DeepCore/memory.hpp"
#include "mem_ptr.hpp"
#include "buffer_ptr.hpp"

#include <new>
#include <utility>

namespace deep
{
    class DEEP_LIB_API memory_manager
    {
      public:
        memory_manager() = delete;
        memory_manager(void *internal_context);

        template <typename Type, typename... Args>
        mem_ptr<Type> alloc(Args &&...args);

        template <typename Type>
        buffer_ptr<Type> alloc(usize number_of_elements);

        template <typename Type>
        bool realloc(buffer_ptr<Type> &buffer, usize number_of_elements);

        template <typename Type>
        bool dealloc(mem_ptr<Type> &data);

        template <typename Type>
        bool dealloc(buffer_ptr<Type> &buffer);

      private:
        friend class lib;

        void *m_internal_context;
    };

    template <typename Type, typename... Args>
    inline mem_ptr<Type> memory_manager::alloc(Args &&...args)
    {
        Type *obj = (Type *) core_mem::alloc(m_internal_context, sizeof(Type));

        if (obj == nullptr)
        {
            return mem_ptr<Type>();
        }

        new (obj) Type(std::forward<Args>(args)...);

        return mem_ptr<Type>(this, obj);
    }

    template <typename Type>
    inline buffer_ptr<Type> memory_manager::alloc(usize number_of_elements)
    {
        Type *obj = (Type *) core_mem::alloc(m_internal_context, sizeof(Type) * number_of_elements);

        if (obj == nullptr)
        {
            return buffer_ptr<Type>();
        }

        return buffer_ptr<Type>(this, obj);
    }

    template <typename Type>
    inline bool memory_manager::realloc(buffer_ptr<Type> &buffer, usize number_of_elements)
    {
        Type *ptr = static_cast<Type *>(core_mem::realloc(m_internal_context, buffer.get(), sizeof(Type) * number_of_elements));

        if (ptr == nullptr)
        {
            return false;
        }

        buffer.set(ptr);

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

        // TODO: utiliser mem::dealloc plutôt que core_mem::dealloc
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

        buffer.set(nullptr);

        return true;
    }

    template <typename Type>
    inline bool mem_ptr<Type>::destroy()
    {
        if (m_memory_manager == nullptr)
        {
            return false;
        }

        return m_memory_manager->dealloc(*this);
    }

    template <typename Type>
    inline bool buffer_ptr<Type>::destroy()
    {
        if (m_memory_manager == nullptr)
        {
            return false;
        }

        return m_memory_manager->dealloc(*this);
    }
} // namespace deep

#endif
