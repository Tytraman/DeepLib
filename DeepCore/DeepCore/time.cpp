#include "time.hpp"

namespace deep
{
    uint64 core_time::get_tick_count() noexcept
    {
        return core_time_get_tick_count();
    }

    uint64 core_time::get_current_time_millis() noexcept
    {
        return core_time_get_current_time_millis();
    }
} // namespace deep
