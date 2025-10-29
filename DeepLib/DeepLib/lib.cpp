#include "DeepCore/context.hpp"
#include "DeepCore/memory.hpp"
#include "DeepCore/error.hpp"
#include "DeepLib/lib.hpp"
#include "DeepLib/memory/memory_manager.hpp"

namespace deep
{
    const char *lib::get_version()
    {
        return DEEP_LIB_VERSION;
    }

    ctx *lib::create_ctx()
    {
        ctx *context = static_cast<ctx *>(core_mem::alloc(nullptr, sizeof(ctx)));
        if (context == nullptr)
        {
            return nullptr;
        }

        context->internal_data = core_ctx::create_internal_ctx();
        if (context->internal_data == nullptr)
        {
            core_mem::dealloc(nullptr, context);

            return nullptr;
        }

        context->mem = static_cast<memory_manager *>(core_mem::alloc(nullptr, sizeof(memory_manager)));
        if (context->mem == nullptr)
        {
            core_ctx::destroy_internal_ctx(context->internal_data);
            core_mem::dealloc(nullptr, context);

            return nullptr;
        }
        context->mem->m_internal_context = context->internal_data;

        return context;
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
