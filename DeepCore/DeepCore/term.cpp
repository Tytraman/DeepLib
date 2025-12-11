#include "term.hpp"

namespace deep
{
    fd core_term::get_std_handle(void *internal_context, std_handle h)
    {
        return core_term_get_std_handle(internal_context, h);
    }

    bool core_term::set_encoding(void *internal_context, string_encoding encoding)
    {
        return core_term_set_encoding(internal_context, encoding);
    }

    bool core_term::add_mode(void *internal_context, fd std, mode m)
    {
        return core_term_add_mode(internal_context, std, m);
    }
} // namespace deep
