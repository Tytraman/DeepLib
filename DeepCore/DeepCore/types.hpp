#ifndef DEEP_CORE_TYPES_HPP
#define DEEP_CORE_TYPES_HPP

#include <stdint.h>

/*
 *  La librairie utilise les types primitifs suivants :
 *  - int8_d, uint8_d
 *  - int16_d, uint16_d
 *  - int32_d, uint32_d
 *  - int64_d, uint64_d
 *  - size_d, usize_d
 *  - bool_d
 *  Ils sont tous redéfinissables, pour cela il faut créer
 *  la macro correspondante avant d'inclure "types.hpp".
 */

#ifndef int8_d
#define int8_d int8_t
#endif

#ifndef uint8_d
#define uint8_d uint8_t
#endif

#ifndef int16_d
#define int16_d int16_t
#endif

#ifndef uint16_d
#define uint16_d uint16_t
#endif

#ifndef int32_d
#define int32_d int32_t
#endif

#ifndef uint32_d
#define uint32_d uint32_t
#endif

#ifndef int64_d
#define int64_d int64_t
#endif

#ifndef uint64_d
#define uint64_d uint64_t
#endif

#ifndef wchar_d
#define wchar_d wchar_t
#endif

namespace deep
{
    using null_ptr = decltype(nullptr);

    /**
     * @brief Vérifie à la compilation si le type passé est une énumération.
     *
     * @tparam Type
     */
    template <typename Type>
    inline constexpr bool is_enum = __is_enum(Type);

    template <typename Type>
    using underlying_type = __underlying_type(Type);

    template <typename Enum>
    inline constexpr underlying_type<Enum> to_utype(Enum e)
    {
        return static_cast<underlying_type<Enum>>(e);
    }

    /**
     * @brief Vérifie à la compilation si un type hérite bien du type spécifié.
     *
     * @tparam Base
     * @tparam Derived
     */
    template <typename Base, typename Derived>
    inline constexpr bool is_base_of = __is_base_of(Base, Derived);

    template <typename Type>
    inline constexpr bool is_trivially_destructible =
            __is_trivially_destructible(Type);

    /**
     * @brief Vérifie à la compilation qu'un type soit bien une classe.
     * @tparam Type Le type à vérifier.
     */
    template <typename Type>
    inline constexpr bool is_class = __is_class(Type);

    /**
     * @brief Vérifie à la compilation que deux types soient les mêmes.
     * @tparam Le premier type à vérifier.
     * @tparam Le deuxième type à vérifier.
     */
    template <typename, typename>
    inline constexpr bool is_same = false;

    template <typename Type>
    inline constexpr bool is_same<Type, Type> = true;

    /**
     * @brief Vérifie à la compilation qu'un type est void.
     * @tparam Type Le type de donnée à vérifier.
     */
    template <typename Type>
    inline constexpr bool is_void = is_same<rm_const_volatile<Type>, void>;

    template <typename Type>
    inline constexpr bool is_nullptr = is_same<rm_const_volatile<Type>, null_ptr>;

    template <typename Type, typename... Types>
    inline constexpr bool is_any_of = (is_same<Type, Types> || ...);

    template <uint64_d>
    struct mk_signed;

    template <>
    struct mk_signed<1>
    {
        using type = int8_d;
    };

    template <>
    struct mk_signed<2>
    {
        using type = int16_d;
    };

    template <>
    struct mk_signed<4>
    {
        using type = int32_d;
    };

    template <>
    struct mk_signed<8>
    {
        using type = int64_d;
    };

    /**
     * @brief Crée une version signée d'un type non signé.
     *
     * @tparam Type
     */
    template <typename Type>
    using make_signed = typename mk_signed<sizeof(Type)>::type;

    template <typename Type>
    struct rm_ref_s
    {
        using type  = Type;
        using ctype = const Type;
    };

    template <typename Type>
    struct rm_ref_s<Type &>
    {
        using type  = Type;
        using ctype = const Type;
    };

    template <typename Type>
    struct rm_ref_s<Type &&>
    {
        using type  = Type;
        using ctype = const Type;
    };

    /**
     * @brief Retire la référence d'un type.
     * @tparam Type
     */
    template <class Type>
    using rm_ref = typename rm_ref_s<Type>::type;

    template <typename Type>
    constexpr rm_ref<Type> &&rvalue_cast(Type &&value) noexcept
    {
        return static_cast<rm_ref<Type> &&>(value);
    }

    template <typename Type>
    struct rm_const_s
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_const_s<const Type>
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_volatile_s
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_volatile_s<volatile Type>
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_const_volatile_s
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_const_volatile_s<const Type>
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_const_volatile_s<volatile Type>
    {
        using type = Type;
    };

    template <typename Type>
    struct rm_const_volatile_s<const volatile Type>
    {
        using type = Type;
    };

    /**
     * @brief Retire la constance d'un type.
     * @tparam Type
     */
    template <typename Type>
    using rm_const = typename rm_const_s<Type>::type;

    template <typename Type>
    using rm_volatile = typename rm_volatile_s<Type>::type;

    template <typename Type>
    using rm_const_volatile = typename rm_const_volatile_s<Type>::type;

    template <typename Type>
    constexpr rm_ref<Type> &&move(Type &&value) noexcept
    {
        return static_cast<rm_ref<Type> &&>(value);
    }

    using int8   = int8_d;
    using uint8  = uint8_d;
    using int16  = int16_d;
    using uint16 = uint16_d;
    using int32  = int32_d;
    using uint32 = uint32_d;
    using int64  = int64_d;
    using uint64 = uint64_d;

    using wchar = wchar_d;

    template <typename Type>
    inline constexpr bool is_integral = is_any_of<rm_const_volatile<Type>, bool, char, int8, uint8, int16, uint16, int32, uint32, int64, uint64, wchar>;

    template <typename Type>
    inline constexpr bool is_floating_point = is_any_of<rm_const_volatile<Type>, float, double, long double>;

    template <typename Type>
    inline constexpr bool is_arithmetic = is_integral<Type> || is_floating_point<Type>;

    template <typename Type>
    inline constexpr bool is_primitive = is_arithmetic<Type> || is_void<Type> || is_nullptr<Type>;

    enum class string_encoding
    {
        UTF8,
        Unicode
    };
} // namespace deep

#ifndef isize_d
#include <stddef.h>
#define isize_d deep::make_signed<size_t>;
#endif

#ifndef usize_d
#include <stddef.h>
#define usize_d size_t
#endif

namespace deep
{
    using isize = isize_d;
    using usize = usize_d;
} // namespace deep

// Défini des macros selon le système d'exploitation sur
// lequel la librairie est compilée.
#if !defined(DEEP_WINDOWS) && !defined(DEEP_UNIX) && !defined(DEEP_LINUX)

#if defined(WIN32) || defined(_WIN32)
#define DEEP_WINDOWS 1
#endif // windows

#if defined(unix) || defined(__unix) || defined(__unix__)
#define DEEP_UNIX 1

#if defined(__linux__)
#define DEEP_LINUX 1
#endif // linux

#endif // unix
#endif

#define DEEP_CONCAT_HELPER(__a, __b) __a##__b
#define DEEP_STRINGIFY_HELPER(__value) #__value

#define DEEP_CONCAT(__a, __b) DEEP_CONCAT_HELPER(__a, __b)
#define DEEP_STRINGIFY(__value) DEEP_STRINGIFY_HELPER(__value)

#ifndef native_error_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define native_error_d DWORD
#elif defined(DEEP_UNIX)
#define native_error_d int
#endif
#endif

#ifndef native_char_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#include "string/unicode.hpp"
#define native_char_d WCHAR

#define DEEP_NATIVE_ENCODING deep::string_encoding::Unicode

#define DEEP_TEXT_NATIVE(__value) DEEP_CONCAT(L, __value)

#define DEEP_TEXT_NATIVE_BYTES_SIZE(__str) deep::core_unicode::calc_bytes_size(__str)
#define DEEP_TEXT_NATIVE_LENGTH(__str) deep::core_unicode::calc_length(__str)
#elif defined(DEEP_UNIX)
#include "string/utf8.hpp"
#define native_char_d char

#define DEEP_NATIVE_ENCODING deep::string_encoding::UTF8

#define DEEP_TEXT_NATIVE(__value) __value

#define DEEP_TEXT_NATIVE_BYTES_SIZE(__str) deep::core_utf8::calc_bytes_size(__str)
#define DEEP_TEXT_NATIVE_LENGTH(__str) deep::core_utf8::calc_length(__str)
#endif
#endif

#ifndef DEEP_TEXT_UTF8
#define DEEP_TEXT_UTF8(__value) DEEP_CONCAT(u8, __value)
#endif

#ifndef DEEP_STRING
#define DEEP_STRING(__value) DEEP_TEXT_UTF8(__value)
#endif

#ifndef fd_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define fd_d HANDLE
#define invalid_fd_d INVALID_HANDLE_VALUE
#elif defined(DEEP_UNIX)
#define fd_d int
#define invalid_fd_d -1
#endif
#endif

#ifndef path_str_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define path_char_d WCHAR
#define path_str_d LPWSTR
#define const_path_str_d LPCWSTR
#elif defined(DEEP_UNIX)
#define path_char_d char
#define path_str_d char *
#define const_path_str_d const char *
#endif
#endif

namespace deep
{
    using native_char  = native_char_d;
    using native_error = native_error_d;
    using fd           = fd_d;
#if defined(DEEP_WINDOWS)
    static const fd invalid_fd = invalid_fd_d;
#else
    static constexpr fd invalid_fd = invalid_fd_d;
#endif
    using path_char      = path_char_d;
    using path_str       = path_str_d;
    using const_path_str = const_path_str_d;

    template <typename Type, typename K = Type>
    Type exchange(Type &value, K &&new_value) noexcept
    {
        Type old_value = static_cast<Type &&>(value);

        value = static_cast<K &&>(new_value);

        return old_value;
    }
} // namespace deep

#endif
