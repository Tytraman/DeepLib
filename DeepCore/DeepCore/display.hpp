#ifndef DEEP_CORE_DISPLAY_HPP
#define DEEP_CORE_DISPLAY_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_display
    {
      public:
        static int32 get_monitor_count() noexcept;
        static bool get_monitor_infos(void *internal_context, uint32 monitor_index, uint32 *width, uint32 *height, uint32 *frequency) noexcept;
        static bool get_primary_monitor_index(uint32 *monitor_index) noexcept;
    };

    extern int32 core_display_get_monitor_count() noexcept;
    extern bool core_display_get_monitor_infos(void *internal_context, uint32 monitor_index, uint32 *width, uint32 *height, uint32 *frequency) noexcept;
    extern bool core_display_get_primary_monitor_index(uint32 *monitor_index) noexcept;
} // namespace deep

#endif
