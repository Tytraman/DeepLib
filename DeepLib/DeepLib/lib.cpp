#include "DeepCore/context.hpp"
#include "DeepCore/memory.hpp"
#include "DeepCore/error.hpp"
#include "DeepLib/lib.hpp"
#include "DeepLib/memory/memory_manager.hpp"

#include <new>

namespace deep
{
    const char *lib::get_version()
    {
        return DEEP_LIB_VERSION;
    }

    ref<ctx> lib::create_ctx()
    {
        void *raw = core_mem::alloc(nullptr, sizeof(ctx));
        if (raw == nullptr)
        {
            return ref<ctx>();
        }

        ctx *context = new (raw) ctx();

        if (!context->init())
        {
            core_mem::dealloc(nullptr, raw);

            return ref<ctx>();
        }

        return ref<ctx>(context, context);
    }

    bool lib::destroy_ctx(ctx *context)
    {
        if (context == nullptr)
        {
            return false;
        }

        if (!core_mem::dealloc(context->get_internal_ctx(), context->get_memory_manager()))
        {
            return false;
        }

        if (!core_ctx::destroy_internal_ctx(context->get_internal_ctx()))
        {
            return false;
        }

        return core_mem::dealloc(nullptr, context);
    }
} // namespace deep
