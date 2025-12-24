#ifndef DEEP_LIB_QUEUE_HPP
#define DEEP_LIB_QUEUE_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/collection/list.hpp"

#include <queue>

namespace deep
{
    template <typename Type>
    class queue
    {
      public:
        queue(ctx *context, uint32 capacity_step = 10) noexcept;

        bool add(const Type &element) noexcept;
        bool add(Type &&element) noexcept;

        bool pop() noexcept;

        void empty() noexcept;

        Type &get_front() const;
        Type &get_back() const;

        bool is_empty() const;

        usize count() const;

      protected:
        list<Type> m_data;
    };

    template <typename Type>
    inline queue<Type>::queue(ctx *context, uint32 capacity_step) noexcept
            : m_data(context, capacity_step)
    {
    }

    template <typename Type>
    inline bool queue<Type>::add(const Type &element) noexcept
    {
        return m_data.add(element);
    }

    template <typename Type>
    inline bool queue<Type>::add(Type &&element) noexcept
    {
        return m_data.add(element);
    }

    template <typename Type>
    inline bool queue<Type>::pop() noexcept
    {
        return m_data.remove(0);
    }

    template <typename Type>
    inline void queue<Type>::empty() noexcept
    {
        return m_data.empty();
    }

    template <typename Type>
    inline Type &queue<Type>::get_front() const
    {
        return m_data.get_first();
    }

    template <typename Type>
    inline Type &queue<Type>::get_back() const
    {
        return m_data.get_last();
    }

    template <typename Type>
    inline bool queue<Type>::is_empty() const
    {
        return m_data.is_empty();
    }

    template <typename Type>
    inline usize queue<Type>::count() const
    {
        return m_data.count();
    }
} // namespace deep

#endif
