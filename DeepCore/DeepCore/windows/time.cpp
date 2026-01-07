#include "../time.hpp"

namespace deep
{
    uint64 core_time_get_tick_count() noexcept
    {
        return GetTickCount64();
    }

    uint64 core_time_get_current_time_millis() noexcept
    {
        FILETIME t;
        uint64 millis;
        GetSystemTimeAsFileTime(&t);
        millis = (DEEP_U64(t.dwLowDateTime) + (DEEP_U64(t.dwHighDateTime) << 32)) / 10000;

        return millis;
    }
} // namespace deep
