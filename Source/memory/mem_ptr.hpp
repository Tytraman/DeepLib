#ifndef DEEP_LIB_MEM_PTR_HPP
#define DEEP_LIB_MEM_PTR_HPP

#include "deep_lib_export.h"
#include "../context.hpp"

namespace deep
{
    class memory_manager;

    template <typename Type>
    class mem_ptr
    {
      public:
        mem_ptr();
        mem_ptr(ctx *context, Type *ptr);
        mem_ptr(memory_manager *manager, Type *ptr);

        mem_ptr(const mem_ptr &)            = delete;
        mem_ptr &operator=(const mem_ptr &) = delete;

        bool destroy();

        Type *operator->();

        bool is_valid() const;
        bool is_null() const;

        Type *get();
        Type *get_const() const;
        memory_manager *get_memory_manager();
        memory_manager *get_memory_manager_const() const;

        void set(Type *ptr);

      private:
        memory_manager *m_memory_manager;
        Type *m_ptr;
    };

    template <typename Type>
    inline mem_ptr<Type>::mem_ptr()
            : m_memory_manager(nullptr), m_ptr(nullptr)
    {
    }

    template <typename Type>
    inline mem_ptr<Type>::mem_ptr(ctx *context, Type *ptr)
            : m_memory_manager(nullptr), m_ptr(ptr)
    {
        if (context != nullptr)
        {
            m_memory_manager = context->get_memory_manager();
        }
    }

    template <typename Type>
    inline mem_ptr<Type>::mem_ptr(memory_manager *manager, Type *ptr)
            : m_memory_manager(manager), m_ptr(ptr)
    {
    }

    template <typename Type>
    inline Type *mem_ptr<Type>::operator->()
    {
        return m_ptr;
    }

    template <typename Type>
    inline bool mem_ptr<Type>::is_valid() const
    {
        return m_ptr != nullptr;
    }

    template <typename Type>
    inline bool mem_ptr<Type>::is_null() const
    {
        return m_ptr == nullptr;
    }

    template <typename Type>
    inline Type *mem_ptr<Type>::get()
    {
        return m_ptr;
    }

    template <typename Type>
    inline Type *mem_ptr<Type>::get_const() const
    {
        return m_ptr;
    }

    template <typename Type>
    inline memory_manager *mem_ptr<Type>::get_memory_manager()
    {
        return m_memory_manager;
    }

    template <typename Type>
    inline memory_manager *mem_ptr<Type>::get_memory_manager_const() const
    {
        return m_memory_manager;
    }

    template <typename Type>
    inline void mem_ptr<Type>::set(Type *ptr)
    {
        m_ptr = ptr;
    }
} // namespace deep

#endif
