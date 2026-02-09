#ifndef DEEP_LIB_STRING_BASE_HPP
#define DEEP_LIB_STRING_BASE_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/memory/ref_counted.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/object.hpp"

namespace deep
{
    template <typename Derived, typename Type>
    class string_base : public object
    {
      public:
        string_base();
        string_base(const ref<ctx> &context);
        string_base(const ref<ctx> &context, const Type *str);
        string_base(const ref<ctx> &context, Type *str, usize bytes_size, usize length);

        static usize calc_bytes_size(const Type *str);
        static usize calc_length(const Type *str);

        static Derived from(const ref<ctx> &context, bool value);
        static Derived from(const ref<ctx> &context, int64 value);
        static Derived from(const ref<ctx> &context, uint64 value);
        static Derived from(const ref<ctx> &context, double value, int16 digits);

        static bool equals(const Type *first, const Type *second);

        bool append(Type character);
        bool append(const Type *str);

        bool insert(Type character);
        bool insert(const Type *str);

        bool shrink(usize length) noexcept;

        bool find(Type character, usize *index) noexcept;
        bool find_from_end(Type character, usize *index) noexcept;

        bool equals(const string_base &other) const;
        bool equals(const Type *str) const;

        Derived &operator+=(const Type *str);

        Type *operator*() const;
        const Type operator[](usize index) const;

        bool is_valid() const;
        bool is_null() const;

        usize get_bytes_size() const;
        usize get_length() const;

        const ref<buffer_primitive<Type>> &get_ref() const;

      protected:
        ref<buffer_primitive<Type>> m_data;
        usize m_length;

      private:
        bool realloc(usize new_bytes_size);
    };

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base()
            : object(), m_length(0)
    {
    }

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base(const ref<ctx> &context)
            : object(context), m_length(0)
    {
    }

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base(const ref<ctx> &context, const Type *str)
            : object(context), m_length(0)
    {
        usize bytes_size = calc_bytes_size(str);
        usize length     = calc_length(str);

        Type *ptr = mem::alloc<Type>(context.get(), bytes_size + sizeof(Type));
        if (ptr == nullptr)
        {
            return;
        }

        memcpy(ptr, str, bytes_size);
        *((Type *) (((uint8 *) ptr) + bytes_size)) = static_cast<Type>('\0');

        m_data.set(context.get(), mem::alloc_type<buffer_primitive<Type>>(context.get(), context.get(), ptr, bytes_size + sizeof(Type)), sizeof(buffer_primitive<Type>));
        m_data->take();

        m_length = length;
    }

    template <typename Derived, typename Type>
    inline string_base<Derived, Type>::string_base(const ref<ctx> &context, Type *str, usize bytes_size, usize length)
            : object(context), m_length(length)
    {
        *((Type *) (((uint8 *) str) + length * sizeof(Type))) = static_cast<Type>('\0');

        m_data.set(context.get(), mem::alloc_type<buffer_primitive<Type>>(context.get(), context.get(), str, bytes_size), sizeof(buffer_primitive<Type>));
        m_data->take();
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
    inline Derived string_base<Derived, Type>::from(const ref<ctx> &context, bool value)
    {
        return Derived::from_impl(context, value);
    }

    template <typename Derived, typename Type>
    inline Derived string_base<Derived, Type>::from(const ref<ctx> &context, int64 value)
    {
        return Derived::from_impl(context, value);
    }

    template <typename Derived, typename Type>
    inline Derived string_base<Derived, Type>::from(const ref<ctx> &context, uint64 value)
    {
        return Derived::from_impl(context, value);
    }

    template <typename Derived, typename Type>
    inline Derived string_base<Derived, Type>::from(const ref<ctx> &context, double value, int16 digits)
    {
        return Derived::from_impl(context, value, digits);
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::equals(const Type *first, const Type *second)
    {
        usize bytes_size1 = calc_bytes_size(first);
        usize bytes_size2 = calc_bytes_size(second);

        if (bytes_size1 != bytes_size2)
        {
            return false;
        }

        return memcmp(first, second, bytes_size1) == 0;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::append(Type character)
    {
        usize new_bytes_size = get_bytes_size() + sizeof(character);

        if (new_bytes_size < 2)
        {
            new_bytes_size = 2;
        }

        if (!realloc(new_bytes_size))
        {
            return false;
        }

        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - (sizeof(Type) * 2))) = character;
        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type)))       = static_cast<Type>('\0');

        m_length++;

        return true;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::append(const Type *str)
    {
        usize bytes_size         = calc_bytes_size(str);
        usize length             = calc_length(str);
        usize current_bytes_size = get_bytes_size();
        usize new_bytes_size     = current_bytes_size + bytes_size;

        if (current_bytes_size == 0)
        {
            current_bytes_size += sizeof(Type);
            new_bytes_size += sizeof(Type);
        }

        if (!realloc(new_bytes_size))
        {
            return false;
        }

        memcpy(((uint8 *) m_data->get_buffer().get()) + current_bytes_size - sizeof(Type), str, bytes_size);
        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type))) = static_cast<Type>('\0');

        m_length += length;

        return true;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::insert(Type character)
    {
        usize current_bytes_size = get_bytes_size();
        usize new_bytes_size     = current_bytes_size + sizeof(character);

        if (new_bytes_size < 2)
        {
            new_bytes_size = 2;
        }

        if (!realloc(new_bytes_size))
        {
            return false;
        }

        if (current_bytes_size > 0)
        {
            memmove(m_data->get_buffer().get() + 1, m_data->get_buffer().get(), current_bytes_size - sizeof(Type));
        }

        *((Type *) (((uint8 *) m_data->get_buffer().get())))                                 = character;
        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type))) = static_cast<Type>('\0');

        m_length++;

        return true;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::insert(const Type *str)
    {
        usize bytes_size         = calc_bytes_size(str);
        usize length             = calc_length(str);
        usize current_bytes_size = get_bytes_size();
        usize new_bytes_size     = current_bytes_size + bytes_size;

        if (!realloc(new_bytes_size))
        {
            return false;
        }

        if (current_bytes_size > 0)
        {
            memmove(m_data->get_buffer().get() + bytes_size, m_data->get_buffer().get(), current_bytes_size - sizeof(Type));
        }

        memcpy(m_data->get_buffer().get(), str, bytes_size);
        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type))) = static_cast<Type>('\0');

        m_length += length;

        return true;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::shrink(usize length) noexcept
    {
        if (length >= m_length)
        {
            return false;
        }

        usize new_bytes_size = (length + 1) * sizeof(Type);

        if (!realloc(new_bytes_size))
        {
            return false;
        }

        *((Type *) (((uint8 *) m_data->get_buffer().get()) + new_bytes_size - sizeof(Type))) = static_cast<Type>('\0');

        m_length = length;

        return true;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::find(Type character, usize *index) noexcept
    {
        usize length = m_length;

        for (*index = 0; *index < length; ++(*index))
        {
            if (m_data->get_buffer()[*index] == character)
            {
                return true;
            }
        }

        return false;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::find_from_end(Type character, usize *index) noexcept
    {
        if (m_length == 0)
        {
            return false;
        }

        *index = m_length - 1;

        while (true)
        {
            if (m_data->get_buffer()[*index] == character)
            {
                return true;
            }

            if (*index == 0)
            {
                break;
            }

            (*index)--;
        }

        return false;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::equals(const string_base &other) const
    {
        usize bytes_size = get_bytes_size();

        if (bytes_size != other.get_bytes_size())
        {
            return false;
        }

        const Type *str1 = operator*();
        const Type *str2 = *other;

        return memcmp(str1, str2, bytes_size) == 0;
    }

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::equals(const Type *str) const
    {
        const Type *str1 = operator*();
        const Type *str2 = str;

        usize bytes_size1 = get_bytes_size();
        usize bytes_size2 = calc_bytes_size(str2) + sizeof(Type);

        if (bytes_size1 != bytes_size2)
        {
            return false;
        }

        return memcmp(str1, str2, bytes_size1) == 0;
    }

    template <typename Derived, typename Type>
    inline Derived &string_base<Derived, Type>::operator+=(const Type *str)
    {
        append(str);

        return *static_cast<Derived *>(this);
    }

    template <typename Derived, typename Type>
    inline Type *string_base<Derived, Type>::operator*() const
    {
        return m_data.get()->get_buffer().get();
    }

    template <typename Derived, typename Type>
    inline const Type string_base<Derived, Type>::operator[](usize index) const
    {
        if (!m_data.is_valid())
        {
            return static_cast<Type>('\0');
        }

        return m_data.get()->get_buffer()[index];
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
        if (!m_data.is_valid())
        {
            return 0;
        }

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

    template <typename Derived, typename Type>
    inline bool string_base<Derived, Type>::realloc(usize new_bytes_size)
    {
        if (m_data.is_valid())
        {
            return mem::realloc<Type>(m_data->get_buffer(), new_bytes_size);
        }

        Type *ptr = mem::alloc<Type>(get_context_ptr(), new_bytes_size);
        if (ptr == nullptr)
        {
            return false;
        }

        buffer_primitive<Type> *buffer = mem::alloc_type<buffer_primitive<Type>>(get_context_ptr(), get_context_ptr(), ptr, new_bytes_size);
        if (buffer == nullptr)
        {
            mem::dealloc<Type>(get_context_ptr(), ptr);

            return false;
        }

        m_data.set(get_context_ptr(), buffer, sizeof(buffer_primitive<Type>));
        m_data->take();

        return true;
    }
} // namespace deep

#endif
