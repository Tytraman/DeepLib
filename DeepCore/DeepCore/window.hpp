#ifndef DEEP_CORE_WINDOW_HPP
#define DEEP_CORE_WINDOW_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_window
    {
      public:
        static window_handle create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height);

        static void show(window_handle win);
        static void hide(window_handle win);

        static bool process_message(void *internal_context, window_handle win);
    };

    extern window_handle core_window_create(void *internal_context, const native_char *class_name, const native_char *title, int32 x, int32 y, int32 width, int32 height);
    extern void core_window_show(window_handle win);
    extern void core_window_hide(window_handle win);
    extern bool core_window_process_message(void *internal_context, window_handle win);
} // namespace deep

#endif
