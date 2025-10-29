#include "../context.hpp"
#include "../memory.hpp"
#include "internal_data.hpp"

namespace deep
{
    void *core_create_internal_ctx()
    {
        uint64 result;

        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(core_alloc(&result, sizeof(*internal_data)));

        if (internal_data == nullptr)
        {
            return nullptr;
        }

        internal_data->result = result;

        return internal_data;
    }

    bool core_destroy_internal_ctx(void *internal_ctx)
    {
        uint64 result;

        if (!core_dealloc(&result, internal_ctx))
        {
            internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_ctx);
            internal_data->result              = result;

            return false;
        }

        return true;
    }

    uint64 core_get_internal_ctx_result(void *internal_context)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        return internal_data->result;
    }

    void core_set_internal_ctx_result(void *internal_context, uint64 result)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        internal_data->result = result;
    }
} // namespace deep
