#include "event.hpp"

namespace deep
{
    handle core_event::create(bool manual_reset, bool initial_state)
    {
        return core_create_event(manual_reset, initial_state);
    }

    bool core_event::set(handle ev)
    {
        return core_set_event(ev);
    }

    bool core_event::reset(handle ev)
    {
        return core_reset_event(ev);
    }

    void core_event::wait(handle ev, uint32 milliseconds)
    {
        return core_event_wait(ev, milliseconds);
    }
} // namespace deep
