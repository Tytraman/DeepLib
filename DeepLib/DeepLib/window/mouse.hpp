#ifndef DEEP_LIB_MOUSE_HPP
#define DEEP_LIB_MOUSE_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/maths/vec.hpp"

#include <queue>

namespace deep
{
    class window;
    class mouse;

    class DEEP_LIB_API mouse_event
    {
      public:
        enum class action
        {
            Invalid,
            LeftPress,
            LeftRelease,
            RightPress,
            RightRelease,
            MiddlePress,
            MiddleRelease,
            WheelUp,
            WheelDown,
            Move,
            Enter,
            Leave
        };

      public:
        mouse_event() noexcept;
        mouse_event(action a, const mouse &parent) noexcept;
        mouse_event(action a, const mouse &parent, int32 x, int32 y) noexcept;

        bool is_press() const noexcept;
        bool is_release() const noexcept;
        bool is_valid() const noexcept;

        action get_action() const noexcept;
        ivec2 get_position() const noexcept;
        int32 get_position_x() const noexcept;
        int32 get_position_y() const noexcept;

      private:
        action m_action;
        int32 m_x;
        int32 m_y;
        bool m_is_left_pressed;
        bool m_is_right_pressed;
        bool m_is_middle_pressed;
    };

    struct raw_mouse_delta
    {
        int32 x;
        int32 y;
    };

    class DEEP_LIB_API mouse
    {
      public:
        using event = mouse_event;

        friend window;
        friend event;

      public:
        mouse() noexcept;

        mouse(const mouse &)            = delete;
        mouse &operator=(const mouse &) = delete;

        event read() noexcept;
        bool is_empty() const noexcept;

        raw_mouse_delta read_raw_delta() noexcept;
        bool is_raw_delta_empty() const noexcept;

        ivec2 get_position() const noexcept;
        int32 get_position_x() const noexcept;
        int32 get_position_y() const noexcept;

        bool is_left_pressed() const noexcept;
        bool is_right_pressed() const noexcept;
        bool is_middle_pressed() const noexcept;
        bool is_in_window() const noexcept;

      private:
        bool on_mouse_move(int32 x, int32 y, window *win) noexcept;
        bool on_left_pressed(int32 x, int32 y, window *win) noexcept;
        bool on_left_released(int32 x, int32 y, window *win) noexcept;
        bool on_right_pressed(int32 x, int32 y, window *win) noexcept;
        bool on_right_released(int32 x, int32 y, window *win) noexcept;
        bool on_middle_pressed(int32 x, int32 y, window *win) noexcept;
        bool on_middle_released(int32 x, int32 y, window *win) noexcept;
        bool on_wheel_up(int32 x, int32 y, window *win) noexcept;
        bool on_wheel_down(int32 x, int32 y, window *win) noexcept;
        bool on_wheel_delta(int32 x, int32 y, int32 delta, window *win) noexcept;
        bool on_raw_delta(int32 x, int32 y, window *win) noexcept;
        bool on_leave(window *win) noexcept;
        bool on_enter(window *win) noexcept;

        template <typename Type>
        static void trim_buffer(std::queue<Type> &buffer) noexcept;

      private:
        static constexpr uint8 BufferSize = 16;

        int32 m_x;
        int32 m_y;
        bool m_is_left_pressed;
        bool m_is_right_pressed;
        bool m_is_middle_pressed;
        bool m_is_in_window;
        int32 m_wheel_delta_carry;
        std::queue<event> m_event_buffer;
        std::queue<raw_mouse_delta> m_raw_delta;
    };

    template <typename Type>
    inline void mouse::trim_buffer(std::queue<Type> &buffer) noexcept
    {
        while (buffer.size() > BufferSize)
        {
            buffer.pop();
        }
    }
} // namespace deep

#endif
