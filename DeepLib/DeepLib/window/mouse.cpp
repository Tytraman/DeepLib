#include "mouse.hpp"
#include "DeepLib/window/window.hpp"

namespace deep
{
    mouse_event::mouse_event() noexcept
            : m_action(action::Invalid),
              m_x(0),
              m_y(0),
              m_is_left_pressed(false),
              m_is_right_pressed(false),
              m_is_middle_pressed(false)
    {
    }

    mouse_event::mouse_event(action a, const mouse &parent) noexcept
            : m_action(a),
              m_x(parent.m_x),
              m_y(parent.m_y),
              m_is_left_pressed(parent.m_is_left_pressed),
              m_is_right_pressed(parent.m_is_right_pressed),
              m_is_middle_pressed(parent.m_is_middle_pressed)
    {
    }

    mouse_event::mouse_event(action a, const mouse &parent, int32 x, int32 y) noexcept
            : m_action(a),
              m_x(x),
              m_y(y),
              m_is_left_pressed(parent.m_is_left_pressed),
              m_is_right_pressed(parent.m_is_right_pressed),
              m_is_middle_pressed(parent.m_is_middle_pressed)
    {
    }

    bool mouse_event::is_valid() const noexcept
    {
        return m_action != action::Invalid;
    }

    mouse_event::action mouse_event::get_action() const noexcept
    {
        return m_action;
    }

    ivec2 mouse_event::get_position() const noexcept
    {
        return ivec2(m_x, m_y);
    }

    int32 mouse_event::get_position_x() const noexcept
    {
        return m_x;
    }

    int32 mouse_event::get_position_y() const noexcept
    {
        return m_y;
    }

    mouse::mouse(const ref<ctx> &context) noexcept
            : m_x(0),
              m_y(0),
              m_is_left_pressed(false),
              m_is_right_pressed(false),
              m_is_middle_pressed(false),
              m_is_in_window(false),
              m_wheel_delta_carry(0),
              m_event_buffer(context)
    {
    }

    mouse::event mouse::read() noexcept
    {
        if (!m_event_buffer.is_empty())
        {
            event e = m_event_buffer.get_front();
            m_event_buffer.pop();

            return e;
        }

        return event();
    }

    bool mouse::is_empty() const noexcept
    {
        return m_event_buffer.is_empty();
    }

    ivec2 mouse::get_position() const noexcept
    {
        return ivec2(m_x, m_y);
    }

    int32 mouse::get_position_x() const noexcept
    {
        return m_x;
    }

    int32 mouse::get_position_y() const noexcept
    {
        return m_y;
    }

    bool mouse::is_left_pressed() const noexcept
    {
        return m_is_left_pressed;
    }

    bool mouse::is_right_pressed() const noexcept
    {
        return m_is_right_pressed;
    }

    bool mouse::is_middle_pressed() const noexcept
    {
        return m_is_middle_pressed;
    }

    bool mouse::is_in_window() const noexcept
    {
        return m_is_in_window;
    }

    bool mouse::on_mouse_move(int32 x, int32 y, window *win) noexcept
    {
        if (win == nullptr)
        {
            return true;
        }

        m_x = x;
        m_y = y;

        int32 width  = win->get_width();
        int32 height = win->get_height();

        // Si le curseur est à l'intérieur de la fenêtre.
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            m_event_buffer.add(event(event::action::Move, *this));

            // Si le curseur vient d'entrer dans la fenêtre.
            if (!m_is_in_window)
            {
                on_enter(win);
            }
        }
        // Si le curseur est en dehors de la fenêtre.
        else
        {
            // Ajoute le "drag capture" à la fenêtre.
            if (m_is_left_pressed || m_is_right_pressed || m_is_middle_pressed)
            {
                m_event_buffer.add(event(event::action::Move, *this));
            }
            else
            {
                if (m_is_in_window)
                {
                    on_leave(win);
                }
            }
        }

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_left_pressed(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_left_pressed = true;

        m_event_buffer.add(event(event::action::LeftPress, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_left_released(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_left_pressed = false;

        m_event_buffer.add(event(event::action::LeftRelease, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_right_pressed(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_right_pressed = true;

        m_event_buffer.add(event(event::action::RightPress, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_right_released(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_right_pressed = false;

        m_event_buffer.add(event(event::action::RightRelease, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_middle_pressed(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_middle_pressed = true;

        m_event_buffer.add(event(event::action::MiddlePress, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_middle_released(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_is_middle_pressed = false;

        m_event_buffer.add(event(event::action::MiddleRelease, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_wheel_up(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_event_buffer.add(event(event::action::WheelUp, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_wheel_down(int32 x, int32 y, window * /*win*/) noexcept
    {
        m_event_buffer.add(event(event::action::WheelDown, *this, x, y));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool mouse::on_wheel_delta(int32 x, int32 y, int32 delta, window *win) noexcept
    {
        m_wheel_delta_carry += delta;

        while (m_wheel_delta_carry >= WheelDelta)
        {
            m_wheel_delta_carry -= WheelDelta;

            on_wheel_up(x, y, win);
        }

        while (m_wheel_delta_carry <= -WheelDelta)
        {
            m_wheel_delta_carry += WheelDelta;

            on_wheel_down(x, y, win);
        }

        return true;
    }

    bool mouse::on_leave(window *win) noexcept
    {
        m_is_in_window = false;

        m_event_buffer.add(event(event::action::Leave, *this));

        if (win != nullptr)
        {
            win->release_capture();
        }

        return true;
    }

    bool mouse::on_enter(window *win) noexcept
    {
        m_is_in_window = true;

        m_event_buffer.add(event(event::action::Enter, *this));

        if (win != nullptr)
        {
            win->set_capture();
        }

        return true;
    }

} // namespace deep
