#include "lib.hpp"
#include "memory/memory.hpp"
#include "memory/owned_ptr.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    {
        constexpr int value = 2002;

        deep::owned_ptr<int> owned_1 = deep::owned_ptr<int>(context, deep::mem::alloc_type<int>(context, value), sizeof(int));
        if (!owned_1.is_valid())
        {
            return 2;
        }

        deep::owned_ptr<int> owned_2 = deep::move(owned_1);
        if (!owned_2.is_valid())
        {
            return 3;
        }

        if (owned_1.is_valid())
        {
            return 4;
        }

        if (owned_1.get_bytes_size() != 0)
        {
            return 5;
        }

        if (*owned_2 != value)
        {
            return 6;
        }

        if (owned_2.get_bytes_size() != sizeof(value))
        {
            return 7;
        }
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
