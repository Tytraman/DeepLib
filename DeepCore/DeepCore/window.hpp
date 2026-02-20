#ifndef DEEP_CORE_WINDOW_HPP
#define DEEP_CORE_WINDOW_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/vkeys.hpp"

namespace deep
{
    class DEEP_CORE_API core_window
    {
      public:
        enum class style
        {
            Windowed,
            Borderless
        };

        enum class mouse_button
        {
            Left,
            Right,
            Middle
        };

#if defined(DEEP_WINDOWS)
        using pre_callback = LRESULT (*)(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#else
#error Need implementation
#endif

        using keydown_callback           = bool (*)(vkey key, bool repeated, void *data);
        using keyup_callback             = bool (*)(vkey key, void *data);
        using text_input_callback        = bool (*)(native_char character, void *data);
        using mouse_button_down_callback = bool (*)(mouse_button clicked, int32 relative_position_x, int32 relative_position_y, void *data);
        using mouse_button_up_callback   = bool (*)(mouse_button released, int32 relative_position_x, int32 relative_position_y, void *data);
        using mouse_move_callback        = bool (*)(int32 relative_position_x, int32 relative_position_y, void *data);
        using mouse_wheel_delta_callback = bool (*)(int32 relative_position_x, int32 relative_position_y, int32 delta, void *data);
        using lose_focus_callback        = bool (*)(void *data);

        struct callbacks
        {
            void *data;
            pre_callback pre;
            keydown_callback keydown;
            keyup_callback keyup;
            text_input_callback text_input;
            mouse_button_down_callback mouse_button_down;
            mouse_button_up_callback mouse_button_up;
            mouse_move_callback mouse_move;
            mouse_wheel_delta_callback mouse_wheel_delta;
            lose_focus_callback lose_focus;
        };

      public:
        static window_handle create(void *internal_context, const native_char *class_name, const native_char *title, style s, bool transparent, int32 x, int32 y, int32 width, int32 height, callbacks *call) noexcept;
        static bool destroy(void *internal_context, window_handle win) noexcept;

        static void show(window_handle win) noexcept;
        static void hide(window_handle win) noexcept;
        static void set_capture(window_handle win) noexcept;
        static bool release_capture(void *internal_context, window_handle win) noexcept;

        static void hide_cursor() noexcept;
        static void show_cursor() noexcept;

        static bool set_title(void *internal_context, window_handle win, const native_char *title) noexcept;

        static bool process_message(void *internal_context, window_handle win) noexcept;
    };

    extern window_handle core_window_create(void *internal_context, const native_char *class_name, const native_char *title, core_window::style s, bool transparent, int32 x, int32 y, int32 width, int32 height, core_window::callbacks *call);
    extern bool core_window_destroy(void *internal_context, window_handle win);
    extern void core_window_show(window_handle win);
    extern void core_window_hide(window_handle win);
    extern void core_window_set_capture(window_handle win) noexcept;
    extern bool core_window_release_capture(void *internal_context, window_handle win) noexcept;
    extern void core_window_hide_cursor() noexcept;
    extern void core_window_show_cursor() noexcept;
    extern bool core_window_set_title(void *internal_context, window_handle win, const native_char *title) noexcept;
    extern bool core_window_process_message(void *internal_context, window_handle win);
} // namespace deep

#endif
