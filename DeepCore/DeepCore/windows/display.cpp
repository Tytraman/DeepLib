#include "DeepCore/display.hpp"

namespace deep
{
    int32 core_display::get_monitor_count() noexcept
    {
        return core_display_get_monitor_count();
    }

    bool core_display::get_monitor_infos(void *internal_context, uint32 monitor_index, uint32 *width, uint32 *height, uint32 *frequency) noexcept
    {
        return core_display_get_monitor_infos(internal_context, monitor_index, width, height, frequency);
    }

    bool core_display::get_primary_monitor_index(uint32 *monitor_index) noexcept
    {
        return core_display_get_primary_monitor_index(monitor_index);
    }
} // namespace deep
