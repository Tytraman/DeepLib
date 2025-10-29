#include "string.hpp"

namespace deep
{
    uint64 string::hash(const char *str)
    {
        uint64 val       = 5381;
        usize bytes_size = calc_bytes_size(str);
        usize index;

        for (index = 0; index < bytes_size; ++index)
        {
            val = ((val << 5) + val) + str[index];
        }

        return val;
    }
} // namespace deep
