#ifndef DEEP_LIB_FILESYSTEM_HPP
#define DEEP_LIB_FILESYSTEM_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/string/string_native.hpp"

namespace deep
{
    class DEEP_LIB_API fs
    {
      public:
        static string_native get_cwd(const ref<ctx> &context);
    };
} // namespace deep

#endif
