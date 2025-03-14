#ifndef DEEP_LIB_REF_COUNTED_HPP
#define DEEP_LIB_REF_COUNTED_HPP

#include "../DeepCore/memory.hpp"
#include "../DeepCore/types.hpp"
#include "deep_lib_export.h"

namespace deep
{
    /**
     * @class ref_counted
     * @brief Compte le nombre de références faites vers l'objet.
     * @remark Pour que les objets instanciés d'une classe puisse être comptés, celle-ci doit hériter de \ref ref_counted.
     */
    class DEEP_LIB_API ref_counted
    {
      public:
        ref_counted();

        /// Ajoute 1 au compteur.
        void take() const;

        /**
         * @brief Retire 1 au compteur.
         * @return \c true si le compteur atteint 0 et que l'objet doit être détruit.
         */
        bool drop() const;

        /**
         * @return Le nombre de références vers l'objet.
         */
        usize get_ref_count() const;

      private:
        mutable usize m_count;
    };

    inline void ref_counted::take() const
    {
        m_count++;
    }

    inline bool ref_counted::drop() const
    {
        // TODO: assert m_count > 0

        m_count--;

        return m_count == 0;
    }

    inline usize ref_counted::get_ref_count() const
    {
        return m_count;
    }

    template <typename Type>
    class ref
    {
      public:
        ref();
        ref(Type *ptr);

        /**
         * @brief Crée une nouvelle référence vers l'objet et ajoute 1 à son compteur.
         * @param other L'objet à référencer.
         */
        ref(const ref<Type> &other);

        /**
         * @brief Destructeur qui appelle la méthode \ref unreference afin de retirer 1 au compteur de l'objet référencé.
         */
        ~ref();

        /**
         * @brief Change l'objet référencé et ajoute 1 à son compteur.
         * @remark Retire 1 au compteur de l'objet déjà référencé avant de changer la référence.
         * @param from Le nouvel objet à référencer.
         */
        void reference(const ref &from);

        void unreference();

        ref<Type> &operator=(const ref<Type> &other);

        Type *operator->() const;
        Type &operator*() const;

        bool operator==(const Type *ptr) const;
        bool operator!=(const Type *ptr) const;
        bool operator==(const ref<Type> &other) const;
        bool operator!=(const ref<Type> &other) const;

        bool is_valid() const;
        bool is_null() const;

        Type *get() const;

      private:
        Type *m_ptr;
    };

    template <typename Type>
    inline ref<Type>::ref()
            : m_ptr(nullptr)
    {
    }

    template <typename Type>
    inline ref<Type>::ref(Type *ptr)
            : m_ptr(ptr)
    {
        static_assert(is_base_of<ref_counted, Type>, "The specified class needs to inherit from class ref_counted.");

        if (ptr != nullptr)
        {
            ptr->take();
        }
    }

    template <typename Type>
    inline ref<Type>::ref(const ref<Type> &other)
            : m_ptr(other.m_ptr)
    {
        if (other.m_ptr != nullptr)
        {
            other.m_ptr->take();
        }
    }

    template <typename Type>
    inline ref<Type>::~ref()
    {
        unreference();
    }

    template <typename Type>
    inline void ref<Type>::reference(const ref &from)
    {
        if (m_ptr == from.m_ptr)
        {
            return;
        }

        unreference();

        m_ptr = from.m_ptr;
        if (m_ptr != nullptr)
        {
            m_ptr->take();
        }
    }

    template <typename Type>
    inline void ref<Type>::unreference()
    {
        if (is_valid() && m_ptr->drop())
        {
            mem::dealloc_type(m_ptr);
        }
    }

    template <typename Type>
    ref<Type> &ref<Type>::operator=(const ref<Type> &other)
    {
        reference(other);

        return *this;
    }

    template <typename Type>
    Type *ref<Type>::operator->() const
    {
        return m_ptr;
    }

    template <typename Type>
    Type &ref<Type>::operator*() const
    {
        return *m_ptr;
    }

    template <typename Type>
    inline bool ref<Type>::operator==(const Type *ptr) const
    {
        return m_ptr == ptr;
    }

    template <typename Type>
    inline bool ref<Type>::operator!=(const Type *ptr) const
    {
        return m_ptr != ptr;
    }

    template <typename Type>
    bool ref<Type>::operator==(const ref<Type> &other) const
    {
        return m_ptr == other.m_ptr;
    }

    template <typename Type>
    inline bool ref<Type>::operator!=(const ref<Type> &other) const
    {
        return m_ptr != other.m_ptr;
    }

    template <typename Type>
    inline bool ref<Type>::is_valid() const
    {
        return m_ptr != nullptr;
    }

    template <typename Type>
    inline bool ref<Type>::is_null() const
    {
        return m_ptr == nullptr;
    }

    template <typename Type>
    Type *ref<Type>::get() const
    {
        return m_ptr;
    }

    template <typename Type, typename Kype>
    inline Type *ref_cast(const Kype &to_cast)
    {
        return reinterpret_cast<Type *>(to_cast.get());
    }

} // namespace deep

#endif
