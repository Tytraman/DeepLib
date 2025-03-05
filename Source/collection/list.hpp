#ifndef DEEP_LIB_LIST_HPP
#define DEEP_LIB_LIST_HPP

#include "DeepCore/core.hpp"
#include "DeepCore/memory.hpp"
#include "DeepCore/types.hpp"
#include "collection.hpp"

#include <string.h>

namespace deep
{
    template <typename Type>
    class list : public collection<Type>
    {
      public:
        list(uint32 capacity_step = 10);
        ~list();

        void init(uint32 capacity_step = 10);

        bool add() override;
        bool add(const Type &element) override;
        bool add(Type &&element) override;

        bool set(const Type *buffer, usize index, usize count);
        bool set(const Type &value, usize index, usize count);

        bool remove(usize index) override;

        usize find(const Type &to_search) const override;

        bool reserve(usize number_of_elements) override;
        void fill_with_byte(uint8 value);

        void empty() override;
        bool free() override;

        usize get_capacity() const;
        uint32 get_capacity_step() const;

        Type &operator[](usize index);

        Type *get_data() const;

        void set_count(usize count);
        void set_capacity_step(usize size);

      protected:
        Type *m_data;
        size_t m_capacity;
        uint32_t m_capacity_step;

        bool grow_if_needed();
        bool grow_if_needed(usize index, usize count);
    };

    template <typename Type>
    list<Type>::list(uint32 capacity_step)
            : collection<Type>(), m_data(nullptr), m_capacity(0), m_capacity_step(capacity_step)
    {
    }

    template <typename Type>
    list<Type>::~list()
    {
        if (m_data != nullptr)
        {
            if (!is_trivially_destructible<Type>)
            {
                usize len = m_number_of_elements;
                usize i;

                for (i = 0; i < len; ++i)
                {
                    (m_data + i)->~Type();
                }
            }

            free();
        }
    }

    template <typename Type>
    void list<Type>::init(uint32 capacity_step)
    {
        m_data               = nullptr;
        m_capacity           = 0;
        m_capacity_step      = capacity_step;
        m_number_of_elements = 0;
    }

    template <typename Type>
    bool list<Type>::add()
    {
        if (!grow_if_needed())
        {
            return false;
        }

        m_number_of_elements++;

        return true;
    }

    template <typename Type>
    bool list<Type>::add(const Type &element)
    {
        // Augmente la taille du buffer si nécessaire.
        if (!grow_if_needed())
        {
            return false;
        }

        // Déplace ou copie l'élément dans la case mémoire.
        m_data[m_number_of_elements] = element;
        m_number_of_elements++;

        return true;
    }

    template <typename Type>
    bool list<Type>::add(Type &&element)
    {
        // Augmente la taille du buffer si nécessaire.
        if (!grow_if_needed())
        {
            return false;
        }

        // Déplace ou copie l'élément dans la case mémoire.
        m_data[m_number_of_elements] = rvalue_cast(element);
        m_number_of_elements++;

        return true;
    }

    template <typename Type>
    bool list<Type>::set(const Type *buffer, usize index, usize count)
    {
        if (!grow_if_needed(index, count))
        {
            return false;
        }

        memcpy(m_data + index, buffer, count * sizeof(Type));

        return true;
    }

    template <typename Type>
    bool list<Type>::set(const Type &value, usize index, usize count)
    {
        usize i;

        if (!grow_if_needed(index, count))
        {
            return false;
        }

        for (i = 0; i < count; ++i)
        {
            memcpy(m_data + index + i, &value, sizeof(Type));
        }

        return true;
    }

    template <typename Type>
    bool list<Type>::remove(usize index)
    {
        usize diff;
        usize size;
        usize number_of_bytes_to_move;

        if (index >= m_number_of_elements)
        {
            return false;
        }

        // Obtient le nombre d'éléments pour atteindre la fin de la liste.
        diff                    = m_number_of_elements - index - 1;
        size                    = sizeof(Type);
        number_of_bytes_to_move = diff * size;

        memmove(m_data + index, m_data + (index + 1), number_of_bytes_to_move);

        m_number_of_elements--;

        return true;
    }

    template <typename Type>
    size_t list<Type>::find(const Type &to_search) const
    {
        // Pointeur vers le tableau des éléments de la liste.
        uint8 *ptr               = (uint8 *) m_data;
        usize number_of_elements = m_number_of_elements;
        usize index              = 0;
        usize element_size       = sizeof(Type);
        const Type *element      = &to_search;

        if (ptr == nullptr)
        {
            return list::nothing;
        }

        // Vérifie pour chaque élément de la liste si la donnée est la même que celle recherchée.
        while (index < number_of_elements)
        {
            if (memcmp(ptr, element, element_size) == 0)
            {
                return index;
            }

            ptr += element_size;
            index++;
        }

        return list::nothing;
    }

    template <typename Type>
    bool list<Type>::reserve(usize number_of_elements)
    {
        ctx *context = core::get_current_context();

        if (context == nullptr)
        {
            return false;
        }

        if (number_of_elements == m_number_of_elements)
        {
            return true;
        }

        size_t new_capacity = (number_of_elements / m_capacity_step + 1) * m_capacity_step;
        void *ptr           = mem::realloc(*context, m_data, new_capacity * sizeof(Type));

        if (ptr == nullptr)
        {
            return false;
        }

        m_data               = static_cast<Type *>(ptr);
        m_capacity           = new_capacity;
        m_number_of_elements = number_of_elements;

        return true;
    }

    template <typename Type>
    void list<Type>::fill_with_byte(uint8 value)
    {
        memset(m_data, value, m_number_of_elements * sizeof(Type));
    }

    template <typename Type>
    void list<Type>::empty()
    {
        m_data               = nullptr;
        m_number_of_elements = 0;
        m_capacity           = 0;
    }

    template <typename Type>
    bool list<Type>::free()
    {
        ctx *context = core::get_current_context();

        if (context == nullptr)
        {
            return false;
        }

        if (m_data != nullptr)
        {
            mem::dealloc(*context, m_data);

            m_data = nullptr;
        }

        m_number_of_elements = 0;
        m_capacity           = 0;

        return true;
    }

    template <typename Type>
    usize list<Type>::get_capacity() const
    {
        return m_capacity;
    }

    template <typename Type>
    uint32 list<Type>::get_capacity_step() const
    {
        return m_capacity_step;
    }

    template <typename Type>
    typename Type &list<Type>::operator[](usize index)
    {
        return m_data[index];
    }

    template <typename Type>
    bool list<Type>::grow_if_needed()
    {
        ctx *context = core::get_current_context();

        if (context == nullptr)
        {
            return false;
        }

        // Si le nombre d'éléments présents dans la liste est supérieur à la capacité,
        // on augmente celle-ci du pas attribué.
        if (m_number_of_elements >= m_capacity)
        {
            void *ptr;
            usize new_capacity = m_number_of_elements + m_capacity;
            usize mul          = (new_capacity / m_capacity_step) + 1;

            new_capacity = mul * m_capacity_step;

            ptr = mem::realloc(*context, m_data, new_capacity * sizeof(Type));

            if (ptr == nullptr)
            {
                return false;
            }

            m_data     = static_cast<Type *>(ptr);
            m_capacity = new_capacity;
        }

        return true;
    }

    template <typename Type>
    bool list<Type>::grow_if_needed(usize index, usize count)
    {
        if (index >= m_number_of_elements)
        {
            usize number_of_elements = m_number_of_elements;
            usize diff               = index + count - number_of_elements;

            m_number_of_elements += diff;

            if (!grow_if_needed())
            {
                m_number_of_elements = number_of_elements;

                return false;
            }
        }

        return true;
    }

    template <typename Type>
    inline Type *list<Type>::get_data() const
    {
        return m_data;
    }

    template <typename Type>
    inline void list<Type>::set_count(usize count)
    {
        m_number_of_elements = count;
    }

    template <typename Type>
    inline void list<Type>::set_capacity_step(usize size)
    {
        m_capacity_step = size;
    }
} // namespace deep

#endif
