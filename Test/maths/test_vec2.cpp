#include "DeepLib/lib.hpp"
#include "DeepLib/maths/vec.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::ivec2 vec = deep::ivec2(10, 15);

    vec += 5;

    if (vec != deep::ivec2(15, 20))
    {
        return 2;
    }

    deep::ivec2 v1 = vec * 2;

    if (v1 != deep::ivec2(30, 40))
    {
        return 3;
    }

    return 0;
}
