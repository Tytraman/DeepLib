#ifndef DEEP_LIB_MEMORY_HPP
#define DEEP_LIB_MEMORY_HPP

#include "deep_lib_export.h"
#include "../context.hpp"
#include "mem_ptr.hpp"
#include "memory_manager.hpp"
#include "../DeepCore/memory.hpp"

#include <new>
#include <utility>

namespace deep
{
    /**
     * @class mem
     * @brief Permet de gérer la mémoire de manière sécurisée grâce au gestionnaire de mémoire interne.
     */
    class DEEP_LIB_API mem
    {
      public:
        // TODO: static void *alloc(usize size);

        template <typename Type>
        static bool realloc(mem_ptr<Type> &data, usize size);

        // TODO: static bool dealloc(void *address);

        template <typename Type, typename... Args>
        static mem_ptr<Type> alloc_type(ctx *context, Args &&...args);

        template <typename Type>
        static bool dealloc_type(mem_ptr<Type> &data);
    };

    template <typename Type>
    inline bool mem::realloc(mem_ptr<Type> &data, usize size)
    {
        memory_manager *mem = data.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->realloc(data, size);
    }

    template <typename Type, typename... Args>
    inline mem_ptr<Type> mem::alloc_type(ctx *context, Args &&...args)
    {
        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return mem_ptr<Type>();
        }

        return mem->alloc<Type>(std::forward<Args>(args)...);
    }

    template <typename Type>
    inline bool mem::dealloc_type(mem_ptr<Type> &data)
    {
        memory_manager *mem = data.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->dealloc(data);
    }
} // namespace deep

#endif
