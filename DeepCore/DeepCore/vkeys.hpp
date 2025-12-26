#ifndef DEEP_CORE_VKEYS_HPP
#define DEEP_CORE_VKEYS_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
#if defined(DEEP_WINDOWS)
    using vkey = WPARAM;

    static constexpr int32 WheelDelta = WHEEL_DELTA;

#define DEEP_VKEYS_LIST(GEN)      \
    GEN(A, 'A')                   \
    GEN(B, 'B')                   \
    GEN(C, 'C')                   \
    GEN(D, 'D')                   \
    GEN(E, 'E')                   \
    GEN(F, 'F')                   \
    GEN(G, 'G')                   \
    GEN(H, 'H')                   \
    GEN(I, 'I')                   \
    GEN(J, 'J')                   \
    GEN(K, 'K')                   \
    GEN(L, 'L')                   \
    GEN(M, 'M')                   \
    GEN(N, 'N')                   \
    GEN(O, 'O')                   \
    GEN(P, 'P')                   \
    GEN(Q, 'Q')                   \
    GEN(R, 'R')                   \
    GEN(S, 'S')                   \
    GEN(T, 'T')                   \
    GEN(U, 'U')                   \
    GEN(V, 'V')                   \
    GEN(W, 'W')                   \
    GEN(X, 'X')                   \
    GEN(Y, 'Y')                   \
    GEN(Z, 'Z')                   \
    GEN(Num0, '0')                \
    GEN(Num1, '1')                \
    GEN(Num2, '2')                \
    GEN(Num3, '3')                \
    GEN(Num4, '4')                \
    GEN(Num5, '5')                \
    GEN(Num6, '6')                \
    GEN(Num7, '7')                \
    GEN(Num8, '8')                \
    GEN(Num9, '9')                \
    GEN(Backspace, VK_BACK)       \
    GEN(Tab, VK_TAB)              \
    GEN(Clear, VK_CLEAR)          \
    GEN(Enter, VK_RETURN)         \
    GEN(Shift, VK_SHIFT)          \
    GEN(Control, VK_CONTROL)      \
    GEN(Alt, VK_MENU)             \
    GEN(CapsLock, VK_CAPITAL)     \
    GEN(Escape, VK_ESCAPE)        \
    GEN(Spacebar, VK_SPACE)       \
    GEN(PageUp, VK_PRIOR)         \
    GEN(PageDown, VK_NEXT)        \
    GEN(End, VK_END)              \
    GEN(Home, VK_HOME)            \
    GEN(Left, VK_LEFT)            \
    GEN(Up, VK_UP)                \
    GEN(Right, VK_RIGHT)          \
    GEN(Down, VK_DOWN)            \
    GEN(Select, VK_SELECT)        \
    GEN(Print, VK_PRINT)          \
    GEN(Execute, VK_EXECUTE)      \
    GEN(PrintScreen, VK_SNAPSHOT) \
    GEN(Insert, VK_INSERT)        \
    GEN(Delete, VK_DELETE)        \
    GEN(Help, VK_HELP)            \
    GEN(Numpad0, VK_NUMPAD0)      \
    GEN(Numpad1, VK_NUMPAD1)      \
    GEN(Numpad2, VK_NUMPAD2)      \
    GEN(Numpad3, VK_NUMPAD3)      \
    GEN(Numpad4, VK_NUMPAD4)      \
    GEN(Numpad5, VK_NUMPAD5)      \
    GEN(Numpad6, VK_NUMPAD6)      \
    GEN(Numpad7, VK_NUMPAD7)      \
    GEN(Numpad8, VK_NUMPAD8)      \
    GEN(Numpad9, VK_NUMPAD9)      \
    GEN(Multiply, VK_MULTIPLY)    \
    GEN(Add, VK_ADD)              \
    GEN(Substract, VK_SUBTRACT)   \
    GEN(Divide, VK_DIVIDE)        \
    GEN(F1, VK_F1)                \
    GEN(F2, VK_F2)                \
    GEN(F3, VK_F3)                \
    GEN(F4, VK_F4)                \
    GEN(F5, VK_F5)                \
    GEN(F6, VK_F6)                \
    GEN(F7, VK_F7)                \
    GEN(F8, VK_F8)                \
    GEN(F9, VK_F9)                \
    GEN(F10, VK_F10)              \
    GEN(F11, VK_F11)              \
    GEN(F12, VK_F12)              \
    GEN(NumLock, VK_NUMLOCK)      \
    GEN(Scroll, VK_SCROLL)

#endif

    class DEEP_CORE_API vkeys
    {
      public:
#define DEEP_GEN_CONST(__name, __value) static constexpr vkey __name = __value;
        DEEP_VKEYS_LIST(DEEP_GEN_CONST)
#undef DEEP_GEN_CONST

#if defined(DEEP_WINDOWS)
        static constexpr uint8 KeyCount = 0xFF;
#endif

        static const char *get_name(vkey key);
    };

} // namespace deep

#endif
