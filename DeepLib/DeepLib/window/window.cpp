#include "window.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory.hpp"

namespace deep
{
    bool window::keydown_callback(vkey key, bool repeated, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_key_pressed(key, repeated, win);
        }

        return true;
    }

    bool window::keyup_callback(vkey key, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_key_released(key, win);
        }

        return true;
    }

    bool window::text_input_callback(native_char character, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_text_input(character, win);
        }

        return true;
    }

    bool window::lose_focus_callback(void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_keyboard.on_lose_focus(win);
        }

        return true;
    }

    bool window::mouse_button_down_callback(core_window::mouse_button clicked, int32 relative_position_x, int32 relative_position_y, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            switch (clicked)
            {
                default:
                    break;
                case core_window::mouse_button::Left:
                    return win->m_mouse.on_left_pressed(relative_position_x, relative_position_y, win);
                case core_window::mouse_button::Right:
                    return win->m_mouse.on_right_pressed(relative_position_x, relative_position_y, win);
                case core_window::mouse_button::Middle:
                    return win->m_mouse.on_middle_pressed(relative_position_x, relative_position_y, win);
            }
        }

        return true;
    }

    bool window::mouse_button_up_callback(core_window::mouse_button released, int32 relative_position_x, int32 relative_position_y, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            switch (released)
            {
                default:
                    break;
                case core_window::mouse_button::Left:
                    return win->m_mouse.on_left_released(relative_position_x, relative_position_y, win);
                case core_window::mouse_button::Right:
                    return win->m_mouse.on_right_released(relative_position_x, relative_position_y, win);
                case core_window::mouse_button::Middle:
                    return win->m_mouse.on_middle_released(relative_position_x, relative_position_y, win);
            }
        }

        return true;
    }

    bool window::mouse_move_callback(int32 relative_position_x, int32 relative_position_y, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_mouse.on_mouse_move(relative_position_x, relative_position_y, win);
        }

        return true;
    }

    bool window::mouse_wheel_delta_callback(int32 relative_position_x, int32 relative_position_y, int32 delta, void *data) noexcept
    {
        window *win = static_cast<window *>(data);

        if (win != nullptr)
        {
            return win->m_mouse.on_wheel_delta(relative_position_x, relative_position_y, delta, win);
        }

        return true;
    }

    window::window(const ref<ctx> &context) noexcept
            : object(context),
              m_handle(invalid_window_handle),
              m_callbacks(),
              m_keyboard(context),
              m_mouse(context),
              m_x(0),
              m_y(0),
              m_width(0),
              m_height(0)
    {
    }

    window::~window() noexcept
    {
        core_window::destroy(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }

    ref<window> window::create(const ref<ctx> &context, const native_char *class_name, const native_char *title, core_window::style s, bool transparent, int32 x, int32 y, int32 width, int32 height) noexcept
    {
        ref<window> win = ref<window>(context, mem::alloc_type<window>(context.get(), context));

        if (!win.is_valid())
        {
            return win;
        }

        win->m_x      = x;
        win->m_y      = y;
        win->m_width  = width;
        win->m_height = height;

        win->m_callbacks                   = { 0 };
        win->m_callbacks.keydown           = keydown_callback;
        win->m_callbacks.keyup             = keyup_callback;
        win->m_callbacks.text_input        = text_input_callback;
        win->m_callbacks.mouse_move        = mouse_move_callback;
        win->m_callbacks.mouse_button_down = mouse_button_down_callback;
        win->m_callbacks.mouse_button_up   = mouse_button_up_callback;
        win->m_callbacks.mouse_wheel_delta = mouse_wheel_delta_callback;
        win->m_callbacks.lose_focus        = lose_focus_callback;
        win->m_callbacks.data              = win.get();

        win->m_handle = core_window::create(ctx::get_internal_ctx(context.get()), class_name, title, s, transparent, x, y, width, height, &win->m_callbacks);

        return win;
    }

    void window::show() noexcept
    {
        core_window::show(m_handle);
    }

    void window::hide() noexcept
    {
        core_window::hide(m_handle);
    }

    bool window::process_message() noexcept
    {
        return core_window::process_message(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }

    void window::set_capture() noexcept
    {
        core_window::set_capture(m_handle);
    }

    bool window::release_capture() noexcept
    {
        return core_window::release_capture(ctx::get_internal_ctx(get_context_ptr()), m_handle);
    }

    bool window::set_title(const native_char *title) noexcept
    {
        return core_window::set_title(ctx::get_internal_ctx(get_context_ptr()), m_handle, title);
    }

    bool window::set_title(const string_native &title) noexcept
    {
        return core_window::set_title(ctx::get_internal_ctx(get_context_ptr()), m_handle, *title);
    }

    int32 window::get_width() const noexcept
    {
        return m_width;
    }

    int32 window::get_height() const noexcept
    {
        return m_height;
    }

    window_handle window::get_handle() noexcept
    {
        return m_handle;
    }

    keyboard &window::get_keyboard() noexcept
    {
        return m_keyboard;
    }

    mouse &window::get_mouse() noexcept
    {
        return m_mouse;
    }
} // namespace deep
