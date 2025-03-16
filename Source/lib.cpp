#include "lib.hpp"
#include "DeepCore/core.hpp"
#include "DeepCore/error.hpp"

namespace deep
{
    ctx *lib::g_current_context = nullptr;

    const char *lib::get_version()
    {
        return DEEP_LIB_VERSION;
    }

    bool lib::create_context(ctx &context)
    {
        // 'internal_data' peut être égale à nullptr selon le système.
        context.internal_data = core::create_internal_context();

        if (g_current_context == nullptr)
        {
            set_current_context(context);
        }

        return true;
    }

    bool lib::destroy_context()
    {
        // TODO: libérer la mémoire des autres membres du contexte

        return core::destroy_internal_context();
    }

    uint64 lib::get_context_result()
    {
        return core::get_internal_context_result();
    }
} // namespace deep
