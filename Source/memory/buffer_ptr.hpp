#ifndef DEEP_LIB_BUFFER_PTR_HPP
#define DEEP_LIB_BUFFER_PTR_HPP

#include "../context.hpp"

namespace deep
{
    class memory_manager;

    template <typename Type>
    class buffer_ptr
    {
      public:
        buffer_ptr();
        buffer_ptr(ctx *context, Type *ptr);
        buffer_ptr(memory_manager *manager, Type *ptr);

        buffer_ptr(const buffer_ptr &)            = delete;
        buffer_ptr &operator=(const buffer_ptr &) = delete;

        bool destroy();

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
    inline buffer_ptr<Type>::buffer_ptr()
            : m_memory_manager(nullptr), m_ptr(nullptr)
    {
    }

    template <typename Type>
    inline buffer_ptr<Type>::buffer_ptr(ctx *context, Type *ptr)
            : m_memory_manager(nullptr), m_ptr(ptr)
    {
        if (context != nullptr)
        {
            m_memory_manager = context->get_memory_manager();
        }
    }

    template <typename Type>
    inline buffer_ptr<Type>::buffer_ptr(memory_manager *manager, Type *ptr)
            : m_memory_manager(manager), m_ptr(ptr)
    {
    }

    template <typename Type>
    inline bool buffer_ptr<Type>::is_valid() const
    {
        return m_ptr != nullptr;
    }

    template <typename Type>
    inline bool buffer_ptr<Type>::is_null() const
    {
        return m_ptr == nullptr;
    }

    template <typename Type>
    inline Type *buffer_ptr<Type>::get()
    {
        return m_ptr;
    }

    template <typename Type>
    inline Type *buffer_ptr<Type>::get_const() const
    {
        return m_ptr;
    }

    template <typename Type>
    inline memory_manager *buffer_ptr<Type>::get_memory_manager()
    {
        return m_memory_manager;
    }

    template <typename Type>
    inline memory_manager *buffer_ptr<Type>::get_memory_manager_const() const
    {
        return m_memory_manager;
    }

    template <typename Type>
    inline void buffer_ptr<Type>::set(Type *ptr)
    {
        m_ptr = ptr;
    }
} // namespace deep

#endif
