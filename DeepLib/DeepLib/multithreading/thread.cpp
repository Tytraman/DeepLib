#include "thread.hpp"
#include "DeepCore/thread.hpp"

namespace deep
{
    thread thread::create(ctx *context, thread_callback callback, void *args, bool paused)
    {
        thread t;

        static core_thread::native_args native_args;
        native_args.callback = callback;
        native_args.args     = args;

        t.m_context   = context;
        t.m_suspended = paused;
        t.m_handle    = core_thread::create(ctx::get_internal_ctx(context), core_native_thread, &native_args, paused);

        return t;
    }

    bool thread::suspend()
    {
        if (m_suspended)
        {
            return true;
        }

        m_suspended = core_thread::suspend(ctx::get_internal_ctx(m_context), m_handle);

        return m_suspended;
    }

    bool thread::resume()
    {
        if (!m_suspended)
        {
            return true;
        }

        if (!core_thread::resume(ctx::get_internal_ctx(m_context), m_handle))
        {
            return false;
        }

        m_suspended = false;

        return true;
    }

    void thread::wait(uint32 milliseconds)
    {
        core_thread::wait(m_handle, milliseconds);
    }
} // namespace deep
