#include "collection/list.hpp"
#include "core.hpp"

int main(int argc, char *argv[])
{
    deep::ctx context;

    if (!deep::core::core::create_context(context))
    {
        return 1;
    }

    deep::list<int> test_list;

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

    return 0;
}
