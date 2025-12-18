#ifndef DEEP_CORE_WINDOW_HPP
#define DEEP_CORE_WINDOW_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/vkeys.hpp"

namespace deep
{
    class DEEP_CORE_API core_window
    {
      public:
        using keydown_callback    = bool (*)(vkey key, void *data);
        using keyup_callback      = bool (*)(vkey key, void *data);
        using text_input_callback = bool (*)(native_char character, void *data);

        struct callbacks
        {
            void *data;
            keydown_callback keydown;
            keyup_callback keyup;
            text_input_callback text_input;
        };

      public:
        static window_handle create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height, callbacks *call);

        static void show(window_handle win);
        static void hide(window_handle win);

        static bool process_message(void *internal_context, window_handle win);
    };

    extern window_handle core_window_create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height, core_window::callbacks *call);
    extern void core_window_show(window_handle win);
    extern void core_window_hide(window_handle win);
    extern bool core_window_process_message(void *internal_context, window_handle win);
} // namespace deep

#endif
