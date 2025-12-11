#include "DeepLib/lib.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/memory/owned_ptr.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    constexpr int value = 2002;

    deep::owned_ptr<int> owned_1 = deep::owned_ptr<int>(context.get(), deep::mem::alloc_type<int>(context.get(), value), sizeof(int));
    if (!owned_1.is_valid())
    {
        return 10;
    }

    deep::owned_ptr<int> owned_2 = deep::move(owned_1);
    if (!owned_2.is_valid())
    {
        return 11;
    }

    if (owned_1.is_valid())
    {
        return 12;
    }

    if (owned_1.get_bytes_size() != 0)
    {
        return 13;
    }

    if (*owned_2 != value)
    {
        return 14;
    }

    if (owned_2.get_bytes_size() != sizeof(value))
    {
        return 15;
    }

    return 0;
}
