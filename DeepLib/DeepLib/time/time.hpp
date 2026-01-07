#ifndef DEEP_LIB_TIME_HPP
#define DEEP_LIB_TIME_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_LIB_API time
    {
      public:
        static uint64 get_tick_count() noexcept;
        static uint64 get_current_time_millis() noexcept;
    };
} // namespace deep

#endif
