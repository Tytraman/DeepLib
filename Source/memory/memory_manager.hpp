#ifndef DEEP_LIB_MEMORY_MANAGER_HPP
#define DEEP_LIB_MEMORY_MANAGER_HPP

#include "deep_lib_export.h"
#include "../DeepCore/types.hpp"
#include "../DeepCore/memory.hpp"
#include "mem_ptr.hpp"

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
        bool realloc(mem_ptr<Type> &data, usize size);

        template <typename Type>
        bool dealloc(mem_ptr<Type> &data);

      private:
        friend class lib;

        void *m_internal_context;
    };

    template <typename Type, typename... Args>
    inline mem_ptr<Type> memory_manager::alloc(Args &&...args)
    {
        // TODO: utiliser mem::alloc plutôt que core_mem::alloc
        Type *obj = (Type *) core_mem::alloc(m_internal_context, sizeof(Type));

        if (obj == nullptr)
        {
            return mem_ptr<Type>();
        }

        new (obj) Type(std::forward<Args>(args)...);

        return mem_ptr<Type>(this, obj);
    }

    template <typename Type>
    inline bool memory_manager::realloc(mem_ptr<Type> &data, usize size)
    {
        Type *ptr = static_cast<Type *>(core_mem::realloc(m_internal_context, data.get(), size));

        if (ptr == nullptr)
        {
            return false;
        }

        data.set(ptr);

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
    inline bool mem_ptr<Type>::destroy()
    {
        if (m_memory_manager == nullptr)
        {
            return false;
        }

        return m_memory_manager->dealloc(*this);
    }
} // namespace deep

#endif
