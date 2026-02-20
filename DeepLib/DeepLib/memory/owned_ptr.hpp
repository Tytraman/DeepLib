#ifndef DEEP_LIB_OWNED_PTR_HPP
#define DEEP_LIB_OWNED_PTR_HPP

#include "managed_ptr.hpp"

namespace deep
{
    template <typename Type>
    class owned_ptr : public managed_ptr<owned_ptr<Type>, Type>
    {
      public:
        owned_ptr() = default;
        /**
         * @brief Instancie un pointeur unique.
         * @param data
         */
        explicit owned_ptr(ctx *context, Type *ptr, usize bytes_size);
        owned_ptr(owned_ptr &&other) noexcept;

        owned_ptr &operator=(owned_ptr &&other) noexcept;

        owned_ptr(const owned_ptr &other)            = delete;
        owned_ptr &operator=(const owned_ptr &other) = delete;

        ~owned_ptr();

        bool destroy_impl();

        Type *operator->();
        Type &operator*();

      private:
        /**
         * @brief Libère la mémoire et réinitialise le pointeur.
         * @return nullptr
         */
        Type *release();
        void reset(owned_ptr &&other);
        void reset(Type *ptr);
    };

    template <typename Type>
    inline owned_ptr<Type>::owned_ptr(ctx *context, Type *ptr, usize bytes_size)
            : managed_ptr<owned_ptr<Type>, Type>(context, ptr, bytes_size)
    {
    }

    template <typename Type>
    inline owned_ptr<Type>::owned_ptr(owned_ptr &&other) noexcept
            : managed_ptr<owned_ptr<Type>, Type>(other.get_memory_manager(), other.release(), other.get_bytes_size())
    {
    }

    template <typename Type>
    inline owned_ptr<Type> &owned_ptr<Type>::operator=(owned_ptr &&other) noexcept
    {
        if (this != &other)
        {
            reset(other.release());
        }

        return *this;
    }

    template <typename Type>
    inline owned_ptr<Type>::~owned_ptr()
    {
        this->destroy();
    }

    template <typename Type>
    inline bool owned_ptr<Type>::destroy_impl()
    {
        if (this->m_memory_manager == nullptr)
        {
            return false;
        }

        if (!this->m_memory_manager->dealloc(this->m_ptr))
        {
            return false;
        }

        this->m_ptr        = nullptr;
        this->m_bytes_size = 0;

        return true;
    }

    template <typename Type>
    inline Type *owned_ptr<Type>::operator->()
    {
        return this->m_ptr;
    }

    template <typename Type>
    Type &owned_ptr<Type>::operator*()
    {
        return *this->m_ptr;
    }

    template <typename Type>
    inline Type *owned_ptr<Type>::release()
    {
        Type *ret = exchange(this->m_ptr, nullptr);

        this->m_bytes_size = 0;

        return ret;
    }

    template <typename Type>
    inline void owned_ptr<Type>::reset(owned_ptr &&other)
    {
        this->destroy();

        this->m_memory_manager = other.m_memory_manager;
        this->m_ptr            = other.m_ptr;
    }

    template <typename Type>
    inline void owned_ptr<Type>::reset(Type *ptr)
    {
        this->destroy();

        this->m_ptr = ptr;
    }
} // namespace deep

#endif
