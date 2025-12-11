#include "DeepLib/lib.hpp"
#include "DeepLib/utils/bitmask.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::bitmask16 bits;
    if (bits.get_bits() != 0)
    {
        return 10;
    }

    deep::bitmask16 bits_A7 = 0xA7;
    if (bits_A7.get_bits() != 0xA7)
    {
        return 11;
    }

    // --- TEST de set() ---

    bits.set(0);
    if (!bits.test(0))
    {
        return 12;
    }

    if (bits.get_bits() != 1)
    {
        return 13;
    }

    bits.set(15);
    if (!bits.test(15))
    {
        return 14;
    }
    if (!bits.test(0))
    {
        return 15;
    }

    // --- TEST de reset() ---

    bits.reset(0);
    if (bits.test(0))
    {
        return 20;
    }

    if (!bits.test(15))
    {
        return 21;
    }

    bits.reset(15);
    if (bits.test(15))
    {
        return 22;
    }

    // --- TEST de flip() ---

    bits.set(15);

    bits.flip(15);

    if (bits.test(15))
    {
        return 30;
    }

    bits.flip(2);

    if (!bits.test(2))
    {
        return 31;
    }

    // --- TEST des opérateurs binaires ---

    deep::bitmask16 m1 = 0x3;
    deep::bitmask16 m2 = 0x5;

    deep::bitmask16 result_or = m1 | m2;

    if (result_or.get_bits() != 0x7)
    {
        return 40;
    }

    deep::bitmask16 result_and = m1 & m2;

    if (result_and.get_bits() != 0x1)
    {
        return 41;
    }

    deep::bitmask16 result_xor = m1 ^ m2;

    if (result_xor.get_bits() != 0x6)
    {
        return 42;
    }

    // --- TEST des opérateurs d'assignation ---

    deep::bitmask16 assign = 0x1;

    assign |= 0x2;

    if (assign.get_bits() != 0x3)
    {
        return 50;
    }

    assign &= 0x1;

    if (assign.get_bits() != 0x1)
    {
        return 51;
    }

    assign ^= 0x1;

    if (assign.get_bits() != 0x0)
    {
        return 52;
    }

    // --- TEST de l'opérateur NOT ---

    deep::bitmask16 zero;
    if (zero != 0)
    {
        return 60;
    }

    deep::bitmask16 inverted = ~zero;
    if (inverted.get_bits() != 0xFFFF)
    {
        return 61;
    }

    // --- TEST des comparaisons ---

    deep::bitmask16 cmp1 = 100;
    deep::bitmask16 cmp2 = 100;
    deep::bitmask16 cmp3 = 666;

    if (!(cmp1 == cmp2))
    {
        return 70;
    }

    if (cmp1 != cmp2)
    {
        return 71;
    }

    if (cmp1 == cmp3)
    {
        return 72;
    }

    return 0;
}
