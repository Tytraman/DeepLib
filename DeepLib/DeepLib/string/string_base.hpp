#ifndef DEEP_LIB_STRING_BASE_HPP
#define DEEP_LIB_STRING_BASE_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/memory/ref_counted.hpp"
#include "DeepLib/memory/memory.hpp"

namespace deep
{
    template <typename Derived, typename Type>
    class string_base
    {
      public:
        string_base();
        string_base(ctx *context, const Type *str);

        static usize calc_bytes_size(const Type *str);
        static usize calc_length(const Type *str);

        bool append(const Type *str);
        Derived &operator+=(const Type *str);

        const Type *operator*() const;

        bool is_valid() const;
        bool is_null() const;

        usize get_bytes_size() const;
        usize get_length() const;

        const ref<buffer_primitive<Type>> &get_ref() const;

      protected:
        ref<buffer_primitive<Type>> m_data;
        usize m_length;
    };

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base()
            : m_length(0)
    {
    }

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base(ctx *context, const Type *str)
            : m_length(0)
    {
        usize bytes_size = calc_bytes_size(str);
        usize length     = calc_length(str);

        Type *ptr = mem::alloc<Type>(context, bytes_size + sizeof(Type));
        if (ptr == nullptr)
        {
            return;
        }

        memcpy(ptr, str, bytes_size);
        *((Type *) (((uint8 *) ptr) + bytes_size)) = static_cast<Type>('\0');

        m_data.set(context, mem::alloc_type<buffer_primitive<Type>>(context, context, ptr, bytes_size + sizeof(Type)), sizeof(buffer_primitive<Type>));
        m_data->take();

        m_length = length;
    }

    template <typename Derived, typename Type>
    inline usize string_base<Derived, Type>::calc_bytes_size(const Type *str)
    {
        return Derived::calc_bytes_size_impl(str);
    }

    template <typename Derived, typename Type>
    inline usize string_base<Derived, Type>::calc_length(const Type *str)
    {
        return Derived::calc_length_impl(str);
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::append(const Type *str)
    {
        usize bytes_size         = calc_bytes_size(str);
        usize length             = calc_length(str);
        usize current_bytes_size = m_data->get_buffer().get_bytes_size();
        usize new_bytes_size     = current_bytes_size + bytes_size;

        if (!mem::realloc<Type>(m_data->get_buffer(), new_bytes_size))
        {
            return false;
        }

        memcpy(((uint8 *) m_data->get_buffer().get()) + current_bytes_size - sizeof(Type), str, bytes_size);
        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type))) = static_cast<Type>('\0');

        m_length += length;

        return true;
    }

    template <typename Derived, typename Type>
    inline Derived &string_base<Derived, Type>::operator+=(const Type *str)
    {
        append(str);

        return *static_cast<Derived *>(this);
    }

    template <typename Derived, typename Type>
    inline const Type *string_base<Derived, Type>::operator*() const
    {
        return m_data.get()->get_buffer().get();
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::is_valid() const
    {
        return m_data.is_valid();
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::is_null() const
    {
        return m_data.is_null();
    }

    template <typename Derived, typename Type>
    inline usize string_base<Derived, Type>::get_bytes_size() const
    {
        return m_data->get_buffer().get_bytes_size();
    }

    template <typename Derived, typename Type>
    inline usize string_base<Derived, Type>::get_length() const
    {
        return m_length;
    }
    template <typename Derived, typename Type>
    inline const ref<buffer_primitive<Type>> &string_base<Derived, Type>::get_ref() const
    {
        return m_data;
    }
} // namespace deep

#endif
