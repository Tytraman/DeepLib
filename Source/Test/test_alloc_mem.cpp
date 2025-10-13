#include "lib.hpp"
#include "memory/memory.hpp"

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    deep::buffer_ptr<int> buffer = deep::mem::alloc<int>(context, 100);

    if (!buffer.is_valid())
    {
        return 1;
    }

    if (!deep::mem::realloc(buffer, 500))
    {
        deep::mem::dealloc(buffer);

        return 1;
    }

    if (!deep::mem::dealloc(buffer))
    {
        return 1;
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 1;
    }

    return 0;
}
