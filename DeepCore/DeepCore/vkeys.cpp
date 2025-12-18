#include "vkeys.hpp"

namespace deep
{
    const char *vkeys::get_name(vkey key)
    {
#define DEEP_GEN_CASE(__name, __value) \
    case __value:                      \
        return #__name;

        switch (key)
        {
            default:
                return "UNKNOWN";
                DEEP_VKEYS_LIST(DEEP_GEN_CASE)
        }

#undef DEEP_GEN_CASE
    }
} // namespace deep
