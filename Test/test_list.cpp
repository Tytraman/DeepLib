#include "DeepLib/lib.hpp"
#include "DeepLib/collection/list.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    {
        deep::list<int> test_list = deep::list<int>(context);

        if (!test_list.add(105))
        {
            return 1;
        }

        if (!test_list.add(206))
        {
            return 1;
        }

        if (!test_list.add(307))
        {
            return 1;
        }

        if (test_list[0] != 105)
        {
            return 1;
        }

        if (test_list[1] != 206)
        {
            return 1;
        }

        if (test_list[2] != 307)
        {
            return 1;
        }
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 1;
    }

    return 0;
}
