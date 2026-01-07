#ifndef DEEP_CORE_TIME_HPP
#define DEEP_CORE_TIME_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_time
    {
      public:
        static uint64 get_tick_count() noexcept;
        static uint64 get_current_time_millis() noexcept;
    };

    extern uint64 core_time_get_tick_count() noexcept;
    extern uint64 core_time_get_current_time_millis() noexcept;
} // namespace deep

#endif
