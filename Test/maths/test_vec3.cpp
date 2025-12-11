#include "DeepLib/lib.hpp"
#include "DeepLib/maths/vec.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::ivec3 vec = deep::ivec3(1, 2, 3);

    vec += 5;

    if (vec != deep::ivec3(6, 7, 8))
    {
        return 2;
    }

    deep::ivec3 v1 = vec * 2;

    if (v1 != deep::ivec3(12, 14, 16))
    {
        return 3;
    }

    return 0;
}
