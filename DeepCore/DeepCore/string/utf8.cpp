#include "utf8.hpp"

namespace deep
{
    usize core_utf8::calc_bytes_size(const char *str)
    {
        usize length = 0;

        const char *current = str;

        while (*current != '\0')
        {
            length++;
            current++;
        }

        return length;
    }

    usize core_utf8::calc_length(const char *str)
    {
        const uint8 *byte = reinterpret_cast<const uint8 *>(str);
        usize length      = 0;

        while (*byte != '\0')
        {
            length++;

            if (*byte < 0x80) // Caractère ASCII
            {
                // Un caractère ASCII est TOUJOURS sur 1 seul octet.
                byte += 1;
            }
            else if ((*byte & 0xE0) == 0xC0) // Début de séquence de 2 octets.
            {
                byte += 2;
            }
            else if ((*byte & 0xF0) == 0xE0) // Début de séquence de 3 octets.
            {
                byte += 3;
            }
            else if ((*byte & 0xF8) == 0xF0) // Début de séquence de 4 octets.
            {
                byte += 4;
            }
            else // Séquence invalide.
            {
                byte += 1;
            }
        }

        return length;
    }
} // namespace deep
