#ifndef DEEP_CORE_MEMORY_HPP
#define DEEP_CORE_MEMORY_HPP

#include "context.hpp"
#include "deep_core_export.h"
#include "types.hpp"

namespace deep
{
    class DEEP_CORE_API mem
    {
      public:
        static constexpr uint8 ProtNone  = 0x00;
        static constexpr uint8 ProtRead  = 0x01;
        static constexpr uint8 ProtWrite = 0x02;
        static constexpr uint8 ProtExec  = 0x04;

      public:
        DEEP_CORE_API static void *alloc(ctx &context, usize size,
                                         uint8 protection);
        DEEP_CORE_API static bool dealloc(ctx &context, void *address,
                                          usize size);
    };

    extern void *core_alloc(ctx &context, usize size, uint8 protection);
    extern bool core_dealloc(ctx &context, void *address, usize size);
} // namespace deep

#endif
