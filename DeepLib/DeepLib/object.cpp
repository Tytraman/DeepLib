#include "object.hpp"
#include "context.hpp"

namespace deep
{
    object::object()
            : m_context(ref<ctx>())
    {
    }

    object::object(const ref<ctx> &context)
            : m_context(context)
    {
    }

    const ref<ctx> &object::get_context() const
    {
        return m_context;
    }

    ctx *object::get_context_ptr()
    {
        return m_context.get();
    }

    ctx *object::get_context_ptr() const
    {
        return m_context.get();
    }
} // namespace deep
