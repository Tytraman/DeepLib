#include "context.hpp"
#include "DeepCore/context.hpp"

namespace deep
{
    ctx::ctx()
            : internal_data(nullptr), mem(nullptr)
    {
    }

    bool ctx::destroy_internal_ctx()
    {
        if (!core_ctx::destroy_internal_ctx(internal_data))
        {
            return false;
        }

        internal_data = nullptr;

        return true;
    }
} // namespace deep
