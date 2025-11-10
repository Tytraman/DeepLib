#ifndef DEEP_LIB_MANAGED_PTR_HPP
#define DEEP_LIB_MANAGED_PTR_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory_manager.hpp"

namespace deep
{

    /**
     * @brief Classe qui utilise le CRTP (Curiously Recurring Template Pattern) afin de créer une interface statique pour la gestion des pointeurs.
     * @tparam Derived
     * @tparam Type
     */
    template <typename Derived, typename Type>
    class managed_ptr
    {
      public:
        managed_ptr();
        managed_ptr(ctx *context, Type *ptr, usize bytes_size);
        managed_ptr(const ctx *context, const Type *ptr, usize bytes_size);
        managed_ptr(memory_manager *manager, Type *ptr, usize bytes_size);
        managed_ptr(const memory_manager *manager, const Type *ptr, usize bytes_size);

        bool destroy();

        bool is_valid() const;
        bool is_null() const;

        Type *get();
        const Type *get() const;
        memory_manager *get_memory_manager();
        const memory_manager *get_memory_manager() const;
        usize get_bytes_size() const;

        void set(ctx *context, Type *ptr, usize bytes_size);
        void set(Type *ptr, usize bytes_size);
        void set(memory_manager *manager);

      protected:
        ~managed_ptr() = default;

      protected:
        memory_manager *m_memory_manager;
        Type *m_ptr;
        usize m_bytes_size;
    };

    template <typename Derived, typename Type>
    inline managed_ptr<Derived, Type>::managed_ptr()
            : m_memory_manager(nullptr), m_ptr(nullptr), m_bytes_size(0)
    {
    }

    template <typename Derived, typename Type>
    inline managed_ptr<Derived, Type>::managed_ptr(ctx *context, Type *ptr, usize bytes_size)
            : m_memory_manager(nullptr), m_ptr(ptr), m_bytes_size(bytes_size)
    {
        if (context != nullptr)
        {
            m_memory_manager = context->get_memory_manager();
        }
    }

    template <typename Derived, typename Type>
    inline managed_ptr<Derived, Type>::managed_ptr(const ctx *context, const Type *ptr, usize bytes_size)
            : m_memory_manager(nullptr), m_ptr(const_cast<Type *>(ptr)), m_bytes_size(bytes_size)
    {
        if (context != nullptr)
        {
            m_memory_manager = const_cast<ctx *>(context)->get_memory_manager();
        }
    }

    template <typename Derived, typename Type>
    inline managed_ptr<Derived, Type>::managed_ptr(memory_manager *manager, Type *ptr, usize bytes_size)
            : m_memory_manager(manager), m_ptr(ptr), m_bytes_size(bytes_size)
    {
    }

    template <typename Derived, typename Type>
    inline managed_ptr<Derived, Type>::managed_ptr(const memory_manager *manager, const Type *ptr, usize bytes_size)
            : m_memory_manager(const_cast<memory_manager *>(manager)), m_ptr(const_cast<Type *>(ptr)), m_bytes_size(bytes_size)
    {
    }

    template <typename Derived, typename Type>
    inline bool managed_ptr<Derived, Type>::destroy()
    {
        return static_cast<Derived *>(this)->destroy_impl();
    }

    template <typename Derived, typename Type>
    inline bool managed_ptr<Derived, Type>::is_valid() const
    {
        return m_ptr != nullptr;
    }

    template <typename Derived, typename Type>
    inline bool managed_ptr<Derived, Type>::is_null() const
    {
        return m_ptr == nullptr;
    }

    template <typename Derived, typename Type>
    inline Type *managed_ptr<Derived, Type>::get()
    {
        return m_ptr;
    }

    template <typename Derived, typename Type>
    inline const Type *managed_ptr<Derived, Type>::get() const
    {
        return m_ptr;
    }

    template <typename Derived, typename Type>
    inline memory_manager *managed_ptr<Derived, Type>::get_memory_manager()
    {
        return m_memory_manager;
    }

    template <typename Derived, typename Type>
    inline const memory_manager *managed_ptr<Derived, Type>::get_memory_manager() const
    {
        return m_memory_manager;
    }

    template <typename Derived, typename Type>
    inline usize managed_ptr<Derived, Type>::get_bytes_size() const
    {
        return m_bytes_size;
    }

    template <typename Derived, typename Type>
    inline void managed_ptr<Derived, Type>::set(ctx *context, Type *ptr, usize bytes_size)
    {
        if (context != nullptr)
        {
            m_memory_manager = context->get_memory_manager();
        }

        m_ptr        = ptr;
        m_bytes_size = bytes_size;
    }

    template <typename Derived, typename Type>
    inline void managed_ptr<Derived, Type>::set(Type *ptr, usize bytes_size)
    {
        m_ptr        = ptr;
        m_bytes_size = bytes_size;
    }

    template <typename Derived, typename Type>
    inline void managed_ptr<Derived, Type>::set(memory_manager *manager)
    {
        m_memory_manager = manager;
    }
} // namespace deep

#endif
