#include "core.hpp"
#include "memory.hpp"

namespace deep
{
    ctx *core::g_current_context = nullptr;

    ctx *core::create_context()
    {
        uint64 result;

        ctx *context = static_cast<ctx *>(core_alloc(&result, sizeof(*context)));

        if (context == nullptr)
        {
            return nullptr;
        }

        context->result = result;

        // TODO: initialiser les données interne du contexte

        if (g_current_context == nullptr)
        {
            g_current_context = context;
        }

        return context;
    }

    bool core::destroy_context(ctx *context)
    {
        // TODO: libérer les données interne du contexte

        uint64 result;

        return core_dealloc(&result, context);
    }
} // namespace deep
