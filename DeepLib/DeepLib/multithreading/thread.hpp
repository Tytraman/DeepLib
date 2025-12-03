#ifndef DEEP_LIB_THREAD_HPP
#define DEEP_LIB_THREAD_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/context.hpp"

namespace deep
{
    class DEEP_LIB_API thread
    {
      public:
        static thread create(ctx *context, thread_callback callback, void *args, bool paused);

        bool suspend();
        bool resume();
        void wait(uint32 milliseconds = infinite);

        bool is_valid() const;
        bool is_suspended() const;

      protected:
        thread() = default;

      private:
        ctx *m_context;
        handle m_handle;
        bool m_suspended;
    };

    inline bool thread::is_valid() const
    {
        return m_handle != nullptr;
    }

    inline bool thread::is_suspended() const
    {
        return m_suspended;
    }
} // namespace deep

#endif
