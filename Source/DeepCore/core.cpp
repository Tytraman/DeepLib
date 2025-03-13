#include "core.hpp"
#include "error.hpp"
#include "memory.hpp"

namespace deep
{
    ctx *core::g_current_context = nullptr;

    bool core::create_context(ctx &context)
    {
        // TODO: initialiser les données interne du contexte

        if (g_current_context == nullptr)
        {
            g_current_context = &context;
        }

        context.result = error::NoError;

        return true;
    }

    bool core::destroy_context(ctx &context)
    {
        // TODO: libérer les données interne du contexte

        context.result = error::NoError;

        return true;
    }
} // namespace deep
