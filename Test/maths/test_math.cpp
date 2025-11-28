#include "DeepLib/lib.hpp"
#include "DeepLib/maths/math.hpp"
#include "DeepLib/maths/limit.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    deep::uint32 a1 = deep::math::abs(-25);

    if (a1 != 25)
    {
        return 2;
    }

    deep::uint32 a2 = deep::math::abs(64);

    if (a2 != 64)
    {
        return 3;
    }

    deep::uint32 a3   = deep::math::abs(deep::limit::MIN_INT32);
    deep::uint32 max1 = DEEP_U32(deep::limit::MAX_INT32) + 1;

    if (a3 != max1)
    {
        return 4;
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
