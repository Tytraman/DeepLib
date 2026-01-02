#ifndef DEEP_LIB_WINDOW_HPP
#define DEEP_LIB_WINDOW_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/object.hpp"
#include "DeepCore/window.hpp"
#include "DeepLib/window/keyboard.hpp"
#include "DeepLib/window/mouse.hpp"
#include "DeepLib/string/string_native.hpp"

namespace deep
{
    class DEEP_LIB_API window : public object
    {
      public:
        friend memory_manager;

      public:
        window() = delete;
        ~window() noexcept;

        static ref<window> create(const ref<ctx> &context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height) noexcept;

        void show() noexcept;
        void hide() noexcept;

        bool process_message() noexcept;

        void set_capture() noexcept;
        bool release_capture() noexcept;

        bool set_title(const native_char *title) noexcept;
        bool set_title(const string_native &title) noexcept;

        bool is_valid() const noexcept;

        int32 get_width() const noexcept;
        int32 get_height() const noexcept;

        window_handle get_handle() noexcept;

        keyboard &get_keyboard() noexcept;
        mouse &get_mouse() noexcept;

      protected:
        window(const ref<ctx> &context) noexcept;

        static bool keydown_callback(vkey key, bool repeated, void *data) noexcept;
        static bool keyup_callback(vkey key, void *data) noexcept;
        static bool text_input_callback(native_char character, void *data) noexcept;
        static bool lose_focus_callback(void *data) noexcept;
        static bool mouse_button_down_callback(core_window::mouse_button clicked, int32 relative_position_x, int32 relative_position_y, void *data) noexcept;
        static bool mouse_button_up_callback(core_window::mouse_button released, int32 relative_position_x, int32 relative_position_y, void *data) noexcept;
        static bool mouse_move_callback(int32 relative_position_x, int32 relative_position_y, void *data) noexcept;
        static bool mouse_wheel_delta_callback(int32 relative_position_x, int32 relative_position_y, int32 delta, void *data) noexcept;

      protected:
        window_handle m_handle;
        core_window::callbacks m_callbacks;
        keyboard m_keyboard;
        mouse m_mouse;
        int32 m_x;
        int32 m_y;
        int32 m_width;
        int32 m_height;
    };

    inline bool window::is_valid() const noexcept
    {
        return m_handle != invalid_window_handle;
    }
} // namespace deep

#endif
