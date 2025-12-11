#include "DeepLib/lib.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    constexpr deep::usize bytes_size_1 = sizeof(int) * 100;
    constexpr deep::usize bytes_size_2 = sizeof(int) * 100;

    deep::buffer_ptr<int> buffer = deep::buffer_ptr<int>(context.get(), deep::mem::alloc<int>(context.get(), bytes_size_1), bytes_size_1);

    if (!buffer.is_valid())
    {
        return 1;
    }

    if (!deep::mem::realloc(buffer, bytes_size_2))
    {
        deep::mem::dealloc(buffer);

        return 2;
    }

    if (!deep::mem::dealloc(buffer))
    {
        return 3;
    }

    return 0;
}
