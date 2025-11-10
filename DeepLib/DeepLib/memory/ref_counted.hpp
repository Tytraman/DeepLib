#ifndef DEEP_LIB_REF_COUNTED_HPP
#define DEEP_LIB_REF_COUNTED_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/memory/managed_ptr.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"
#include "DeepCore/types.hpp"

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
        virtual ~ref_counted() = default;

        /**
         * @brief Ajoute 1 au compteur.
         */
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

    inline ref_counted::ref_counted()
            : m_count(0)
    {
    }

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
    class buffer_primitive : public ref_counted
    {
        static_assert(is_primitive<Type>, "Type must be primitive");

      public:
        buffer_primitive(ctx *context, Type *ptr, usize bytes_size);

        buffer_ptr<Type> &get_buffer();
        const buffer_ptr<Type> &get_buffer() const;

      protected:
        buffer_ptr<Type> m_buffer;
    };

    template <typename Type>
    class ref : public managed_ptr<ref<Type>, Type>
    {
      public:
        ref() = default;
        ref(ctx *context, Type *ptr);

        /**
         * @brief Crée une nouvelle référence vers l'objet et ajoute 1 à son compteur.
         * @param other L'objet à référencer.
         */
        ref(const ref<Type> &other);

        /**
         * @brief Destructeur qui appelle la méthode \ref unreference afin de retirer 1 au compteur de l'objet référencé.
         */
        ~ref();

        bool destroy_impl();

        /**
         * @brief Change l'objet référencé et ajoute 1 à son compteur.
         * @remark Retire 1 au compteur de l'objet déjà référencé avant de changer la référence.
         * @param from Le nouvel objet à référencer.
         */
        void reference(const ref &from);

        void unreference();

        ref<Type> &operator=(ref<Type> &other);
        ref<Type> &operator=(const ref<Type> &other);

        Type *operator->();
        const Type *operator->() const;
        Type &operator*();

        bool operator==(const Type *ptr) const;
        bool operator!=(const Type *ptr) const;
        bool operator==(const ref<Type> &other) const;
        bool operator!=(const ref<Type> &other) const;
    };

    template <typename Type>
    inline ref<Type>::ref(ctx *context, Type *ptr)
            : managed_ptr<ref<Type>, Type>(context, ptr, sizeof(Type))
    {
        if (is_valid())
        {
            m_ptr->take();
        }
    }

    template <typename Type>
    inline ref<Type>::ref(const ref<Type> &other)
            : managed_ptr<ref<Type>, Type>(other.get_memory_manager(), other.get(), other.get_bytes_size())
    {
        if (is_valid())
        {
            m_ptr->take();
        }
    }

    template <typename Type>
    inline ref<Type>::~ref()
    {
        unreference();
    }

    template <typename Type>
    inline bool ref<Type>::destroy_impl()
    {
        if (m_memory_manager == nullptr)
        {
            return false;
        }

        if (!m_memory_manager->dealloc(m_ptr))
        {
            return false;
        }

        m_ptr = nullptr;

        return true;
    }

    template <typename Type>
    inline void ref<Type>::reference(const ref &from)
    {
        if (m_ptr == from.m_ptr)
        {
            return;
        }

        unreference();

        set(from.m_ptr, from.m_bytes_size);
        if (is_valid())
        {
            m_ptr->take();
        }
    }

    template <typename Type>
    inline void ref<Type>::unreference()
    {
        if (is_valid() && m_ptr->drop())
        {
            destroy();
        }
    }

    template <typename Type>
    ref<Type> &ref<Type>::operator=(ref<Type> &other)
    {
        reference(other);

        return *this;
    }

    template <typename Type>
    ref<Type> &ref<Type>::operator=(const ref<Type> &other)
    {
        reference(other);

        return *this;
    }

    template <typename Type>
    Type *ref<Type>::operator->()
    {
        return m_ptr;
    }

    template <typename Type>
    inline const Type *ref<Type>::operator->() const
    {
        return m_ptr;
    }

    template <typename Type>
    Type &ref<Type>::operator*()
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

    template <typename Type, typename Kype>
    inline Type *ref_cast(const Kype &to_cast)
    {
        return reinterpret_cast<Type *>(to_cast.get());
    }

    template <typename Type>
    inline buffer_primitive<Type>::buffer_primitive(ctx *context, Type *ptr, usize bytes_size)
            : m_buffer(context, ptr, bytes_size)
    {
    }

    template <typename Type>
    inline buffer_ptr<Type> &buffer_primitive<Type>::get_buffer()
    {
        return m_buffer;
    }

    template <typename Type>
    inline const buffer_ptr<Type> &buffer_primitive<Type>::get_buffer() const
    {
        return m_buffer;
    }

} // namespace deep

#endif
