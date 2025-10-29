#ifndef DEEP_CORE_MEMORY_HPP
#define DEEP_CORE_MEMORY_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_mem
    {
      public:
        static constexpr uint8 ProtNone  = 0x00;
        static constexpr uint8 ProtRead  = 0x01;
        static constexpr uint8 ProtWrite = 0x02;
        static constexpr uint8 ProtExec  = 0x04;

      public:
        static void *alloc(void *internal_context, usize size);
        static void *realloc(void *internal_context, void *address, usize size);
        static bool dealloc(void *internal_context, void *address);
    };

    extern void *core_alloc(void *internal_context, usize size);
    extern void *core_realloc(void *internal_context, void *address, usize size);
    extern bool core_dealloc(void *internal_context, void *address);
} // namespace deep

#endif
