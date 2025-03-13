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
        static void *alloc(usize size);
        static void *realloc(void *address, usize size);
        static bool dealloc(void *address);
    };

    extern void *core_alloc(uint64 *result, usize size);
    extern void *core_realloc(uint64 *result, void *address, usize size);
    extern bool core_dealloc(uint64 *result, void *address);
} // namespace deep

#endif
