#include "event.hpp"
#include "DeepCore/event.hpp"

namespace deep
{
    event::event(bool manual_reset, bool initial_state)
            : m_handle(core_event::create(manual_reset, initial_state)), m_manual_reset(manual_reset), m_state(initial_state)
    {
    }

    bool event::set()
    {
        if (!core_event::set(m_handle))
        {
            return false;
        }

        m_state = true;

        return true;
    }

    bool event::reset()
    {
        if (!core_event::reset(m_handle))
        {
            return false;
        }

        m_state = false;

        return true;
    }

    void event::wait(uint32 milliseconds)
    {
        core_event::wait(m_handle, milliseconds);

        if (!m_manual_reset)
        {
            m_state = false;
        }
    }
} // namespace deep
