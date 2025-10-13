#ifndef DEEP_LIB_MEMORY_HPP
#define DEEP_LIB_MEMORY_HPP

#include "deep_lib_export.h"
#include "../context.hpp"
#include "mem_ptr.hpp"
#include "buffer_ptr.hpp"
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
        template <typename Type>
        static buffer_ptr<Type> alloc(ctx *context, usize number_of_elements);

        template <typename Type>
        static bool realloc(buffer_ptr<Type> &buffer, usize number_of_elements);

        template <typename Type>
        static bool dealloc(buffer_ptr<Type> &buffer);

        template <typename Type, typename... Args>
        static mem_ptr<Type> alloc_type(ctx *context, Args &&...args);

        template <typename Type>
        static bool dealloc_type(mem_ptr<Type> &data);
    };

    template <typename Type>
    inline buffer_ptr<Type> mem::alloc(ctx *context, usize number_of_elements)
    {
        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return buffer_ptr<Type>();
        }

        return mem->alloc<Type>(number_of_elements);
    }

    template <typename Type>
    inline bool mem::realloc(buffer_ptr<Type> &buffer, usize number_of_elements)
    {
        memory_manager *mem = buffer.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->realloc(buffer, number_of_elements);
    }

    template <typename Type>
    inline bool mem::dealloc(buffer_ptr<Type> &buffer)
    {
        memory_manager *mem = buffer.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->dealloc(buffer);
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
