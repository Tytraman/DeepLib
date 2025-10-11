#include "ref_counted.hpp"
#include "memory.hpp"

namespace deep
{
    ref_counted::ref_counted()
            : m_count(0)
    {
    }
} // namespace deep
