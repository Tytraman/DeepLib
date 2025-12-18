#ifndef DEEP_LIB_WINDOW_HPP
#define DEEP_LIB_WINDOW_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/object.hpp"
#include "DeepCore/window.hpp"

namespace deep
{
    class DEEP_LIB_API window : public object
    {
      public:
        window() = delete;

        using object::object;

        static ref<window> create(const ref<ctx> &context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height);

        void show();
        void hide();

        bool process_message();

        void set_keydown_callcack(core_window::keydown_callback callback);
        void set_keyup_callback(core_window::keyup_callback callback);
        void set_text_input_callback(core_window::text_input_callback callack);

        bool is_valid() const;

      protected:
        window_handle m_handle;
        core_window::callbacks m_callbacks;
    };

    inline bool window::is_valid() const
    {
        return m_handle != invalid_window_handle;
    }
} // namespace deep

#endif
