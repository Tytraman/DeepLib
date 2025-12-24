#include "DeepLib/lib.hpp"
#include "DeepLib/utils/bitset.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::bitset<256> bits;

    // --- TEST d'initialisation ---

    if (bits.test(0) || bits.test(63) || bits.test(64) || bits.test(127) || bits.test(255))
    {
        return 10;
    }

    // --- TEST de set() ---

    bits.set(0);
    if (!bits.test(0))
    {
        return 20;
    }

    if (bits.test(1))
    {
        return 21;
    }

    // --- TEST des frontières de mots (Word Boundary) ---
    // Bit 63 est la fin du premier uint64, Bit 64 est le début du second.

    bits.set(63);
    bits.set(64);

    if (!bits.test(63))
    {
        return 30;
    }

    if (!bits.test(64))
    {
        return 31;
    }

    if (bits.test(62) || bits.test(65))
    {
        return 32;
    }

    // --- TEST de reset() ---

    bits.reset(64);

    if (bits.test(64))
    {
        return 40;
    }

    // On s'assure que le reset n'a pas touché au bit 63 (qui est dans un autre uint64)
    if (!bits.test(63))
    {
        return 41;
    }

    bits.reset(0);
    if (bits.test(0))
    {
        return 42;
    }

    // --- TEST de la limite haute (Last Bit) ---

    bits.set(255);
    if (!bits.test(255))
    {
        return 50;
    }

    bits.set(256);
    if (!bits.test(255))
    {
        return 51;
    }

    // --- TEST de clear() ---

    bits.clear();

    for (deep::usize i = 0; i < 256; ++i)
    {
        if (bits.test(i))
        {
            return 60;
        }
    }

    return 0;
}
