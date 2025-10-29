#include "unicode.hpp"

namespace deep
{
    usize core_unicode::calc_bytes_size(const wchar *str)
    {
        return calc_length(str) * sizeof(wchar);
    }

    usize core_unicode::calc_length(const wchar *str)
    {
        usize length = 0;

        const wchar *current = str;

        while (*current != L'\0')
        {
            length++;
            current++;
        }

        return length;
    }
} // namespace deep
