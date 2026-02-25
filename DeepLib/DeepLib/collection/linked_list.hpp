#ifndef DEEP_LIB_LINKED_LIST_HPP
#define DEEP_LIB_LINKED_LIST_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/maths/math.hpp"

#include <utility>

namespace deep
{
    template <typename Type>
    class linked_list;

    template <typename Type>
    class linked_list_element
    {
      public:
        template <typename... Args>
        linked_list_element(Args &&...args) noexcept;

      private:
        Type m_value;
        linked_list_element<Type> *m_next;

      public:
        friend linked_list;
    };

    template <typename Type>
    template <typename... Args>
    inline linked_list_element<Type>::linked_list_element(Args &&...args) noexcept
            : m_value(std::forward<Args>(args)...),
              m_next(nullptr)
    {
    }

    template <typename Type>
    class linked_list
    {
      public:
        linked_list(const ref<ctx> &context) noexcept;

        template <typename... Args>
        bool add(Args &&...args) noexcept;

        bool remove(usize index) noexcept;

        bool swap(usize first, usize second) noexcept;

        usize count() const noexcept;

        Type *get_last() noexcept;

        Type *operator[](usize index) noexcept;

      protected:
        ref<ctx> m_context;
        linked_list_element<Type> *m_root;
    };

    template <typename Type>
    inline linked_list<Type>::linked_list(const ref<ctx> &context) noexcept
            : m_context(context),
              m_root(nullptr)
    {
    }

    template <typename Type>
    template <typename... Args>
    inline bool linked_list<Type>::add(Args &&...args) noexcept
    {
        linked_list_element<Type> *lle = mem::alloc_type<linked_list_element<Type>>(m_context.get(), std::forward<Args>(args)...);

        if (lle == nullptr)
        {
            return false;
        }

        linked_list_element<Type> *last = m_root;

        if (last == nullptr)
        {
            m_root = lle;

            return true;
        }

        while (last->m_next != nullptr)
        {
            last = last->m_next;
        }

        last->m_next = lle;

        return true;
    }

    template <typename Type>
    inline bool linked_list<Type>::remove(usize index) noexcept
    {
        linked_list_element<Type> *previous;
        linked_list_element<Type> *to_delete = m_root;

        if (to_delete == nullptr)
        {
            return false;
        }

        if (index == 0)
        {
            linked_list_element<Type> *next = to_delete->m_next;

            if (!mem::dealloc_type(m_context->get_memory_manager(), to_delete))
            {
                return false;
            }

            m_root = next;

            return true;
        }

        usize counter = 1;
        previous      = m_root;
        to_delete     = previous->m_next;

        while (counter != index)
        {
            if (to_delete->m_next == nullptr)
            {
                return false;
            }

            previous  = to_delete;
            to_delete = to_delete->m_next;

            counter++;
        }

        linked_list_element<Type> *next = to_delete->m_next;

        if (!mem::dealloc_type(m_context->get_memory_manager(), to_delete))
        {
            return false;
        }

        previous->m_next = next;

        return true;
    }

    template <typename Type>
    inline bool linked_list<Type>::swap(usize first, usize second) noexcept
    {
        if (first == second)
        {
            return true;
        }

        if (first > second)
        {
            usize temp = first;
            first      = second;
            second     = temp;
        }

        usize counter;

        linked_list_element<Type> *previous_A = nullptr, *node_A = m_root;
        linked_list_element<Type> *previous_B = nullptr, *node_B = m_root;

        for (counter = 0; counter < first && node_A != nullptr; ++counter)
        {
            previous_A = node_A;
            node_A     = node_A->m_next;
        }

        previous_B = previous_A;
        node_B     = node_A;

        for (counter = first; counter < second && node_B != nullptr; ++counter)
        {
            previous_B = node_B;
            node_B     = node_B->m_next;
        }

        if (node_A == nullptr || node_B == nullptr)
        {
            return false;
        }

        if (previous_A == nullptr)
        {
            m_root = node_B;
        }
        else
        {
            previous_A->m_next = node_B;
        }

        if (previous_B != nullptr && previous_B != node_A)
        {
            previous_B->m_next = node_A;
        }

        linked_list_element<Type> *temp_next = node_B->m_next;
        if (node_A->m_next == node_B)
        {
            node_B->m_next = node_A;
        }
        else
        {
            node_B->m_next = node_A->m_next;
        }
        node_A->m_next = temp_next;

        return true;
    }

    template <typename Type>
    inline usize linked_list<Type>::count() const noexcept
    {
        usize counter                   = 1;
        linked_list_element<Type> *last = m_root;

        if (last == nullptr)
        {
            return 0;
        }

        while (last->m_next != nullptr)
        {
            last = last->m_next;
            counter++;
        }

        return counter;
    }

    template <typename Type>
    inline Type *linked_list<Type>::get_last() noexcept
    {
        linked_list_element<Type> *last = m_root;

        if (last == nullptr)
        {
            return nullptr;
        }

        while (last->m_next != nullptr)
        {
            last = last->m_next;
        }

        return &last->m_value;
    }

    template <typename Type>
    inline Type *linked_list<Type>::operator[](usize index) noexcept
    {
        linked_list_element<Type> *last = m_root;

        if (last == nullptr)
        {
            return nullptr;
        }

        usize counter = 0;

        while (counter != index)
        {
            if (last->m_next == nullptr)
            {
                return nullptr;
            }

            last = last->m_next;

            counter++;
        }

        return &last->m_value;
    }

} // namespace deep

#if defined(_MSC_VER)

#define DEEP_LINKED_LIST(__type, __var_name)  \
    __pragma(warning(push))                   \
            __pragma(warning(disable : 4251)) \
                    deep::linked_list<__type> \
                            __var_name;       \
    __pragma(warning(pop))

#endif

#endif
