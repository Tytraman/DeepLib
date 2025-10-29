#ifndef DEEP_LIB_HPP
#define DEEP_LIB_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/context.hpp"

namespace deep
{
    class DEEP_LIB_API lib
    {
      public:
        static const char *get_version();

        static ctx *create_ctx();
        static bool destroy_ctx(ctx *context);
    };
} // namespace deep

#endif
