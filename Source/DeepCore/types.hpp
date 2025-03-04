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

#ifndef bool_d
#include <stdbool.h>
#define bool_d bool
#endif

#ifndef d_true
#include <stdbool.h>
#define d_true true
#endif

#ifndef d_false
#include <stdbool.h>
#define d_false false
#endif

namespace deep
{
    /**
     * @brief Vérifie statiquement si le type passé est une énumération.
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
     * @brief Vérifie statiquement si un type hérite bien du type spécifié.
     *
     * @tparam Base
     * @tparam Derived
     */
    template <typename Base, typename Derived>
    inline constexpr bool is_base_of = __is_base_of(Base, Derived);

    template <typename Type>
    inline constexpr bool is_trivially_destructible =
        __is_trivially_destructible(Type);

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

    using int8   = int8_d;
    using uint8  = uint8_d;
    using int16  = int16_d;
    using uint16 = uint16_d;
    using int32  = int32_d;
    using uint32 = uint32_d;
    using int64  = int64_d;
    using uint64 = uint64_d;
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

#ifndef native_error_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define native_error_d DWORD
#elif defined(DEEP_UNIX)
#define native_error_d int
#endif
#endif

#ifndef fd_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define fd_d         HANDLE
#define invalid_fd_d INVALID_HANDLE_VALUE
#elif defined(DEEP_UNIX)
#define fd_d         int
#define invalid_fd_d -1
#endif
#endif

#ifndef path_str_d
#if defined(DEEP_WINDOWS)
#include <Windows.h>
#define path_char_d      WCHAR
#define path_str_d       LPWSTR
#define const_path_str_d LPCWSTR
#elif defined(DEEP_UNIX)
#define path_char_d      char
#define path_str_d       char *
#define const_path_str_d const char *
#endif
#endif

namespace deep
{

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
} // namespace deep

#endif
