#ifndef DEEP_LIB_BITMASK_HPP
#define DEEP_LIB_BITMASK_HPP

#include "DeepCore/types.hpp"

namespace deep
{
    template <typename Type>
    class bitmask
    {
        static_assert(is_integral<Type>, "Type must be integral");

      public:
        constexpr bitmask() noexcept;
        constexpr bitmask(Type value) noexcept;

        /**
         * @brief Active le bit en mettant sa valeur à 1.
         * @param position La position du bit à activer.
         */
        constexpr void set(uint8 position) noexcept;

        /**
         * @brief Désactive le bit en mettant sa valeur à 0.
         * @param position La position du bit à désactiver.
         */
        constexpr void reset(uint8 position) noexcept;

        /**
         * @brief Inverse la valeur du bit.
         * @param position Le position du bit à inverser.
         */
        constexpr void flip(uint8 position) noexcept;

        /**
         * @brief Vérifie si le bit est activé.
         * @param position La position du bit à vérifier.
         * @return true si activé.
         */
        constexpr bool test(uint8 position) noexcept;

        constexpr bitmask<Type> operator&(const bitmask<Type> &other) const noexcept;
        constexpr bitmask<Type> &operator&=(const bitmask<Type> &other) noexcept;

        constexpr bitmask<Type> operator|(const bitmask<Type> &other) const noexcept;
        constexpr bitmask<Type> operator|=(const bitmask<Type> &other) noexcept;

        constexpr bitmask<Type> operator^(const bitmask<Type> &other) const noexcept;
        constexpr bitmask<Type> operator^=(const bitmask<Type> &other) noexcept;

        constexpr bitmask<Type> operator~() const noexcept;

        constexpr bool operator==(const bitmask<Type> &other) const noexcept;
        constexpr bool operator!=(const bitmask<Type> &other) const noexcept;

        constexpr Type get_bits() const noexcept;

      private:
        Type m_bits;
    };

    template <typename Type>
    inline constexpr bitmask<Type>::bitmask() noexcept
            : m_bits(static_cast<Type>(0))
    {
    }

    template <typename Type>
    inline constexpr bitmask<Type>::bitmask(Type value) noexcept
            : m_bits(value)
    {
    }

    template <typename Type>
    inline constexpr void bitmask<Type>::set(uint8 position) noexcept
    {
        m_bits |= (static_cast<Type>(1) << position);
    }

    template <typename Type>
    inline constexpr void bitmask<Type>::reset(uint8 position) noexcept
    {
        m_bits &= ~(static_cast<Type>(1) << position);
    }

    template <typename Type>
    inline constexpr void bitmask<Type>::flip(uint8 position) noexcept
    {
        m_bits ^= (static_cast<Type>(1) << position);
    }

    template <typename Type>
    inline constexpr bool bitmask<Type>::test(uint8 position) noexcept
    {
        return (m_bits & (static_cast<Type>(1) << position)) != 0;
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator&(const bitmask<Type> &other) const noexcept
    {
        return bitmask<Type>(m_bits & other.m_bits);
    }

    template <typename Type>
    inline constexpr bitmask<Type> &bitmask<Type>::operator&=(const bitmask<Type> &other) noexcept
    {
        m_bits &= other.m_bits;

        return *this;
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator|(const bitmask<Type> &other) const noexcept
    {
        return bitmask<Type>(m_bits | other.m_bits);
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator|=(const bitmask<Type> &other) noexcept
    {
        m_bits |= other.m_bits;

        return *this;
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator^(const bitmask<Type> &other) const noexcept
    {
        return bitmask<Type>(m_bits ^ other.m_bits);
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator^=(const bitmask<Type> &other) noexcept
    {
        m_bits ^= other.m_bits;

        return *this;
    }

    template <typename Type>
    inline constexpr bitmask<Type> bitmask<Type>::operator~() const noexcept
    {
        return bitmask<Type>(~m_bits);
    }

    template <typename Type>
    inline constexpr bool bitmask<Type>::operator==(const bitmask<Type> &other) const noexcept
    {
        return m_bits == other.m_bits;
    }

    template <typename Type>
    inline constexpr bool bitmask<Type>::operator!=(const bitmask<Type> &other) const noexcept
    {
        return m_bits != other.m_bits;
    }

    template <typename Type>
    inline constexpr Type bitmask<Type>::get_bits() const noexcept
    {
        return m_bits;
    }

    using bitmask8  = bitmask<uint8>;
    using bitmask16 = bitmask<uint16>;
    using bitmask32 = bitmask<uint32>;
    using bitmask64 = bitmask<uint64>;
} // namespace deep

#endif
