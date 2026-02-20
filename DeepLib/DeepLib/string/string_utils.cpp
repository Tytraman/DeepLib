#include "DeepLib/string/string_utils.hpp"
#include "DeepCore/string/utf8.hpp"

namespace deep
{
    uint64 string_utils::hash(const char *utf8_str)
    {
        uint64 val       = 5381;
        usize bytes_size = core_utf8::calc_bytes_size(utf8_str);
        usize index;

        for (index = 0; index < bytes_size; ++index)
        {
            val = ((val << 5) + val) + make_unsigned<char>(utf8_str[index]);
        }

        return val;
    }
} // namespace deep
