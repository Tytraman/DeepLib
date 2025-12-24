#include "DeepLib/lib.hpp"
#include "DeepLib/collection/list.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::list<int> test_list = deep::list<int>(context.get());

    if (!test_list.add(105))
    {
        return 10;
    }

    if (!test_list.add(206))
    {
        return 11;
    }

    if (!test_list.add(307))
    {
        return 12;
    }

    if (test_list[0] != 105)
    {
        return 13;
    }

    if (test_list[1] != 206)
    {
        return 14;
    }

    if (test_list[2] != 307)
    {
        return 15;
    }

    return 0;
}
