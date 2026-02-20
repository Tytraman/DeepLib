#ifndef DEEP_LIB_LIST_HPP
#define DEEP_LIB_LIST_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/collection/collection.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"

#include <string.h>

namespace deep
{
    template <typename Type>
    class list : public collection<Type>
    {
      public:
        list(const ref<ctx> &context, uint32 capacity_step = 10);
        list(ctx *context, uint32 capacity_step = 10);
        virtual ~list() override;

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

        bool is_empty() const;

        Type &get_first() const;
        Type &get_last() const;

        usize get_capacity() const;
        usize get_capacity_step() const;

        Type &operator[](usize index) const;

        Type *get_data();
        Type *get_data() const;

        void set_count(usize count);
        void set_capacity_step(usize size);

      protected:
        buffer_ptr<Type> m_buffer;

        /**
         * @brief Le nombre d'éléments que la liste peut stocker avec la mémoire allouée actuellement.
         */
        usize m_capacity;

        /**
         * @brief La valeur à ajouter à la capacité quand elle est atteinte.
         */
        usize m_capacity_step;

        bool grow_if_needed();
        bool grow_if_needed(usize index, usize count);
    };

    template <typename Type>
    inline list<Type>::list(const ref<ctx> &context, uint32 capacity_step)
            : collection<Type>(), m_buffer(context.get(), nullptr, 0), m_capacity(0), m_capacity_step(capacity_step)
    {
    }

    template <typename Type>
    list<Type>::list(ctx *context, uint32 capacity_step)
            : collection<Type>(), m_buffer(context, nullptr, 0), m_capacity(0), m_capacity_step(capacity_step)
    {
    }

    template <typename Type>
    list<Type>::~list()
    {
        if (m_buffer.is_valid())
        {
            if (!is_trivially_destructible<Type>)
            {
                usize len = this->m_number_of_elements;
                usize i;

                for (i = 0; i < len; ++i)
                {
                    (this->m_buffer.get() + i)->~Type();
                }
            }

            free();
        }
    }

    template <typename Type>
    void list<Type>::init(uint32 capacity_step)
    {
        this->m_buffer.set(nullptr);
        this->m_capacity           = 0;
        this->m_capacity_step      = capacity_step;
        this->m_number_of_elements = 0;
    }

    template <typename Type>
    bool list<Type>::add()
    {
        if (!grow_if_needed())
        {
            return false;
        }

        this->m_number_of_elements++;

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
        this->m_buffer.get()[this->m_number_of_elements] = element;
        this->m_number_of_elements++;

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
        this->m_buffer.get()[this->m_number_of_elements] = rvalue_cast(element);
        this->m_number_of_elements++;

        return true;
    }

    template <typename Type>
    bool list<Type>::set(const Type *buffer, usize index, usize count)
    {
        if (!grow_if_needed(index, count))
        {
            return false;
        }

        memcpy(this->m_buffer.get() + index, buffer, count * sizeof(Type));

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
            memcpy(m_buffer.get() + index + i, &value, sizeof(Type));
        }

        return true;
    }

    template <typename Type>
    bool list<Type>::remove(usize index)
    {
        usize diff;
        usize size;
        usize number_of_bytes_to_move;

        if (index >= this->m_number_of_elements)
        {
            return false;
        }

        // Obtient le nombre d'éléments pour atteindre la fin de la liste.
        diff                    = this->m_number_of_elements - index - 1;
        size                    = sizeof(Type);
        number_of_bytes_to_move = diff * size;

        Type *data = this->m_buffer.get();
        memmove(data + index, data + (index + 1), number_of_bytes_to_move);

        this->m_number_of_elements--;

        return true;
    }

    template <typename Type>
    size_t list<Type>::find(const Type &to_search) const
    {
        // Pointeur vers le tableau des éléments de la liste.
        uint8 *ptr               = (uint8 *) m_buffer.get();
        usize number_of_elements = this->m_number_of_elements;
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
        if (number_of_elements == this->m_number_of_elements)
        {
            return true;
        }

        size_t new_capacity = (number_of_elements / m_capacity_step + 1) * m_capacity_step;

        if (!mem::realloc(this->m_buffer, new_capacity))
        {
            return false;
        }

        this->m_capacity           = new_capacity;
        this->m_number_of_elements = number_of_elements;

        return true;
    }

    template <typename Type>
    void list<Type>::fill_with_byte(uint8 value)
    {
        memset(this->m_buffer.get(), value, this->m_number_of_elements * sizeof(Type));
    }

    template <typename Type>
    void list<Type>::empty()
    {
        this->m_buffer.set(nullptr, 0);
        this->m_number_of_elements = 0;
        this->m_capacity           = 0;
    }

    template <typename Type>
    bool list<Type>::free()
    {
        this->m_buffer.destroy();

        this->m_number_of_elements = 0;
        this->m_capacity           = 0;

        return true;
    }

    template <typename Type>
    inline bool list<Type>::is_empty() const
    {
        return this->m_number_of_elements == 0;
    }

    template <typename Type>
    Type &list<Type>::get_first() const
    {
        return operator[](DEEP_U64(0));
    }

    template <typename Type>
    Type &list<Type>::get_last() const
    {
        usize index = this->m_number_of_elements > 0 ? this->m_number_of_elements - 1 : 0;

        return operator[](index);
    }

    template <typename Type>
    usize list<Type>::get_capacity() const
    {
        return this->m_capacity;
    }

    template <typename Type>
    usize list<Type>::get_capacity_step() const
    {
        return this->m_capacity_step;
    }

    template <typename Type>
    Type &list<Type>::operator[](usize index) const
    {
        return this->m_buffer.get()[index];
    }

    template <typename Type>
    bool list<Type>::grow_if_needed()
    {
        // Si le nombre d'éléments présents dans la liste est supérieur à la capacité,
        // on augmente celle-ci du pas attribué.
        if (this->m_number_of_elements >= this->m_capacity)
        {
            usize new_capacity = this->m_number_of_elements + this->m_capacity;
            usize mul          = (new_capacity / this->m_capacity_step) + 1;

            new_capacity = mul * this->m_capacity_step;

            if (!mem::realloc(this->m_buffer, new_capacity * sizeof(Type)))
            {
                return false;
            }

            this->m_capacity = new_capacity;
        }

        return true;
    }

    template <typename Type>
    bool list<Type>::grow_if_needed(usize index, usize count)
    {
        if (index >= this->m_number_of_elements)
        {
            usize number_of_elements = this->m_number_of_elements;
            usize diff               = index + count - number_of_elements;

            this->m_number_of_elements += diff;

            if (!grow_if_needed())
            {
                this->m_number_of_elements = number_of_elements;

                return false;
            }
        }

        return true;
    }

    template <typename Type>
    inline Type *list<Type>::get_data()
    {
        return this->m_buffer.get();
    }

    template <typename Type>
    inline Type *list<Type>::get_data() const
    {
        return this->m_buffer.get();
    }

    template <typename Type>
    inline void list<Type>::set_count(usize count)
    {
        this->m_number_of_elements = count;
    }

    template <typename Type>
    inline void list<Type>::set_capacity_step(usize size)
    {
        this->m_capacity_step = size;
    }
} // namespace deep

#endif
