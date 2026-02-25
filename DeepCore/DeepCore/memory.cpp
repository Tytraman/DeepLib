#include "memory.hpp"

namespace deep
{
    void *core_mem::alloc(void *internal_context, usize size)
    {
        return core_alloc(internal_context, size);
    }

    void *core_mem::realloc(void *internal_context, void *address, usize size)
    {
        return core_realloc(internal_context, address, size);
    }

    bool core_mem::dealloc(void *internal_context, void *address)
    {
        return core_dealloc(internal_context, address);
    }

    core_buffer_ptr::core_buffer_ptr() noexcept
            : m_ptr(nullptr),
              m_size(0)
    {
    }

    bool core_buffer_ptr::grow(usize new_size) noexcept
    {
        if (new_size <= m_size)
        {
            return true;
        }

        void *new_ptr = core_mem::realloc(nullptr, m_ptr, new_size);

        if (new_ptr == nullptr)
        {
            return false;
        }

        m_ptr  = new_ptr;
        m_size = new_size;

        return true;
    }

    void *core_buffer_ptr::get() noexcept
    {
        return m_ptr;
    }

    const void *core_buffer_ptr::get() const noexcept
    {
        return m_ptr;
    }
} // namespace deep
