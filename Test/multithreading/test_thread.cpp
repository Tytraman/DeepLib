#include "DeepLib/lib.hpp"
#include "DeepLib/multithreading/thread.hpp"

static constexpr deep::uint32 NEW_VALUE = 1504;

void thread_callback(void *args)
{
    deep::uint32 *shared_value = static_cast<deep::uint32 *>(args);

    *shared_value = NEW_VALUE;
}

int main(int /*argc*/, char * /*argv*/[])
{
    deep::ref<deep::ctx> context = deep::lib::create_ctx();

    if (!context.is_valid())
    {
        return 1;
    }

    deep::uint32 shared_value = 789;

    deep::thread t = deep::thread::create(context.get(), thread_callback, &shared_value, true);

    if (!t.is_valid())
    {
        return 10;
    }

    if (!t.resume())
    {
        return 11;
    }

    t.wait();

    if (shared_value != NEW_VALUE)
    {
        return 12;
    }

    return 0;
}
