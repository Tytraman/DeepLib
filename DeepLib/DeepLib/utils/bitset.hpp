#ifndef DEEP_LIB_BITSET_HPP
#define DEEP_LIB_BITSET_HPP

#include "DeepCore/types.hpp"

namespace deep
{
    template <usize Size>
    class bitset
    {
      public:
        static constexpr usize WordCount = (Size + 63) / 64;

        constexpr bitset() noexcept;

        constexpr void set(usize position) noexcept;
        constexpr void reset(usize position) noexcept;

        constexpr bool test(usize position) const noexcept;

        constexpr void clear() noexcept;

      private:
        uint64 m_bits[WordCount];
    };

    template <usize Size>
    inline constexpr bitset<Size>::bitset() noexcept
    {
        for (usize index = 0; index < WordCount; ++index)
        {
            m_bits[index] = 0;
        }
    }

    template <usize Size>
    inline constexpr void bitset<Size>::set(usize position) noexcept
    {
        if (position >= Size)
        {
            return;
        }

        usize word = position / 64;
        uint64 bit = position % 64;

        m_bits[word] |= (DEEP_U64(1) << bit);
    }

    template <usize Size>
    inline constexpr void bitset<Size>::reset(usize position) noexcept
    {
        if (position >= Size)
        {
            return;
        }

        usize word = position / 64;
        uint64 bit = position % 64;

        m_bits[word] &= ~(DEEP_U64(1) << bit);
    }

    template <usize Size>
    inline constexpr bool bitset<Size>::test(usize position) const noexcept
    {
        if (position >= Size)
        {
            return false;
        }

        usize word = position / 64;
        uint64 bit = position % 64;

        return (m_bits[word] & (DEEP_U64(1) << bit)) != 0;
    }

    template <usize Size>
    inline constexpr void bitset<Size>::clear() noexcept
    {
        for (usize index = 0; index < WordCount; ++index)
        {
            m_bits[index] = 0;
        }
    }
} // namespace deep

#endif
