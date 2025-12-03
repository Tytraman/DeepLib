#include "DeepLib/lib.hpp"
#include "DeepLib/multithreading/thread.hpp"

static constexpr deep::uint32 NEW_VALUE = 1504;

void thread_callback(void *args)
{
    deep::uint32 *shared_value = static_cast<deep::uint32 *>(args);

    *shared_value = NEW_VALUE;
}

int main(int argc, char *argv[])
{
    deep::ctx *context = deep::lib::create_ctx();

    if (context == nullptr)
    {
        return 1;
    }

    deep::uint32 shared_value = 789;

    deep::thread t = deep::thread::create(context, thread_callback, &shared_value, true);

    if (!t.is_valid())
    {
        return 2;
    }

    if (!t.resume())
    {
        return 3;
    }

    t.wait();

    if (shared_value != NEW_VALUE)
    {
        return 10;
    }

    if (!deep::lib::destroy_ctx(context))
    {
        return 100;
    }

    return 0;
}
