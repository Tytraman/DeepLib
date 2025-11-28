#ifndef DEEP_LIB_EVENT_HPP
#define DEEP_LIB_EVENT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_LIB_API event
    {
      public:
        event(bool manual_reset = false, bool initial_state = false);

        bool set();
        bool reset();
        void wait(uint32 milliseconds);

        bool get_manual_reset() const;
        bool get_state() const;

        bool is_valid() const;

      private:
        handle m_handle;
        bool m_manual_reset;
        bool m_state;
    };

    inline bool event::get_manual_reset() const
    {
        return m_manual_reset;
    }

    inline bool event::get_state() const
    {
        return m_state;
    }

    inline bool event::is_valid() const
    {
        return m_handle != nullptr;
    }
} // namespace deep

#endif
