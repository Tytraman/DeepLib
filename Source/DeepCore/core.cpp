#include "core.hpp"
#include "system.hpp"
#include "types.hpp"

namespace deep
{
    system core::get_current_system()
    {
#if DEEP_LINUX
        return system::Linux;
#else
#error Current system not supported.
#endif
    }
} // namespace deep
