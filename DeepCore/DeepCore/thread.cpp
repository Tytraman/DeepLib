#include "thread.hpp"

namespace deep
{
    handle core_thread::create(void *internal_context, native_thread_callback callback, void *args, bool paused)
    {
        return core_create_thread(internal_context, callback, args, paused);
    }

    bool core_thread::suspend(void *internal_context, handle thread)
    {
        return core_suspend_thread(internal_context, thread);
    }

    bool core_thread::resume(void *internal_context, handle thread)
    {
        return core_resume_thread(internal_context, thread);
    }

    void core_thread::wait(handle thread, uint32 milliseconds)
    {
        core_wait_thread(thread, milliseconds);
    }
} // namespace deep
