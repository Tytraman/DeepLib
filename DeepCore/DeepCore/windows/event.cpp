#include "../event.hpp"

#include <Windows.h>

namespace deep
{
    handle core_create_event(bool manual_reset, bool initial_state)
    {
        return CreateEventW(nullptr, manual_reset, initial_state, nullptr);
    }

    bool core_set_event(handle ev)
    {
        return SetEvent(ev);
    }

    bool core_reset_event(handle ev)
    {
        return ResetEvent(ev);
    }

    void core_event_wait(handle ev, uint32 milliseconds)
    {
        WaitForSingleObject(ev, milliseconds);
    }
} // namespace deep
