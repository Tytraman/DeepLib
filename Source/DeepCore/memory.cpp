#include "memory.hpp"
#include "core.hpp"

namespace deep
{
    namespace core
    {
        void *mem::alloc(usize size)
        {
            return core_alloc(&core::g_current_context->result, size);
        }

        void *mem::realloc(void *address, usize size)
        {
            return core_realloc(&core::g_current_context->result, address, size);
        }

        bool mem::dealloc(void *address)
        {
            return core_dealloc(&core::g_current_context->result, address);
        }
    } // namespace core
} // namespace deep
