#ifndef DEEP_CORE_THREAD_HPP
#define DEEP_CORE_THREAD_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_thread
    {
      public:
        struct native_args
        {
            thread_callback callback;
            void *args;
        };

      public:
        static handle create(void *internal_context, native_thread_callback callback, void *args, bool paused);
        static bool suspend(void *internal_context, handle thread);
        static bool resume(void *internal_context, handle thread);
        static void wait(handle thread, uint32 milliseconds);
    };

    extern handle core_create_thread(void *internal_context, native_thread_callback callback, void *args, bool paused);
    extern bool core_suspend_thread(void *internal_context, handle thread);
    extern bool core_resume_thread(void *internal_context, handle thread);
    extern void core_wait_thread(handle thread, uint32 milliseconds);

    extern DEEP_CORE_API DEEP_NATIVE_THREAD;
} // namespace deep

#endif
