#ifndef DEEP_LIB_MEMORY_HPP
#define DEEP_LIB_MEMORY_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/memory.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/mem_ptr.hpp"
#include "DeepLib/memory/buffer_ptr.hpp"
#include "DeepLib/memory/managed_ptr.hpp"
#include "DeepLib/memory/memory_manager.hpp"

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
        static Type *alloc(ctx *context, usize bytes_size);

        template <typename Type>
        static Type *alloc(memory_manager *manager, usize bytes_size);

        template <typename Type>
        static buffer_ptr<Type> alloc_buffer(ctx *context, usize number_of_elements);

        template <typename Type>
        static Type **alloc_table(ctx *context, usize number_of_elements);

        template <typename Type>
        static Type **alloc_table(memory_manager *manager, usize number_of_elements);

        template <typename Type>
        static Type *realloc(memory_manager *manager, Type *address, usize bytes_size);

        template <typename Type>
        static bool realloc(buffer_ptr<Type> &buffer, usize bytes_size);

        template <typename Type>
        static Type **realloc_table(memory_manager *manager, Type **address, usize new_number_of_elements) noexcept;

        template <typename Type>
        static bool dealloc(memory_manager *manager, Type *address) noexcept;

        template <typename Type>
        static bool dealloc(ctx *context, Type *address);

        template <typename Type>
        static bool dealloc(buffer_ptr<Type> &buffer);

        template <typename Type>
        static bool dealloc_buffer(buffer_ptr<Type> &buffer);

        template <typename Type, typename... Args>
        static Type *alloc_type(ctx *context, Args &&...args);

        template <typename Type, typename... Args>
        static Type *alloc_type(memory_manager *manager, Args &&...args);

        template <typename Type>
        static bool dealloc_type(memory_manager *manager, Type *address);

        template <typename Type>
        static bool dealloc_type(mem_ptr<Type> &data);
    };

    template <typename Type>
    inline Type *mem::alloc(ctx *context, usize bytes_size)
    {
        if (context == nullptr)
        {
            return nullptr;
        }

        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return nullptr;
        }

        return mem->alloc<Type>(bytes_size);
    }

    template <typename Type>
    inline Type *mem::alloc(memory_manager *manager, usize bytes_size)
    {
        if (manager == nullptr)
        {
            return nullptr;
        }

        return manager->alloc<Type>(bytes_size);
    }

    template <typename Type>
    inline buffer_ptr<Type> mem::alloc_buffer(ctx *context, usize number_of_elements)
    {
        if (context == nullptr)
        {
            return buffer_ptr<Type>();
        }

        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return buffer_ptr<Type>();
        }

        usize bytes_size = number_of_elements * sizeof(Type);
        Type *ptr        = mem->alloc<Type>(bytes_size);

        if (ptr == nullptr)
        {
            return buffer_ptr<Type>();
        }

        return buffer_ptr<Type>(mem, ptr, bytes_size);
    }

    template <typename Type>
    inline Type **mem::alloc_table(ctx *context, usize number_of_elements)
    {
        if (context == nullptr)
        {
            return nullptr;
        }

        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return nullptr;
        }

        return mem->alloc_table<Type>(number_of_elements);
    }

    template <typename Type>
    inline Type **mem::alloc_table(memory_manager *manager, usize number_of_elements)
    {
        if (manager == nullptr)
        {
            return nullptr;
        }

        return manager->alloc_table<Type>(number_of_elements);
    }

    template <typename Type>
    inline Type *mem::realloc(memory_manager *manager, Type *address, usize bytes_size)
    {
        if (manager == nullptr)
        {
            return nullptr;
        }

        return manager->realloc(address, bytes_size);
    }

    template <typename Type>
    inline bool mem::realloc(buffer_ptr<Type> &buffer, usize bytes_size)
    {
        memory_manager *mem = buffer.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->realloc(buffer, bytes_size);
    }

    template <typename Type>
    inline Type **mem::realloc_table(memory_manager *manager, Type **address, usize new_number_of_elements) noexcept
    {
        if (manager == nullptr)
        {
            return nullptr;
        }

        return manager->realloc_table<Type>(address, new_number_of_elements);
    }

    template <typename Type>
    inline bool mem::dealloc(memory_manager *manager, Type *address) noexcept
    {
        if (manager == nullptr)
        {
            return false;
        }

        return manager->dealloc(address);
    }

    template <typename Type>
    inline bool mem::dealloc(ctx *context, Type *address)
    {
        if (context == nullptr)
        {
            return false;
        }

        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->dealloc(address);
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

    template <typename Type>
    inline bool mem::dealloc_buffer(buffer_ptr<Type> &buffer)
    {
        memory_manager *mem = buffer.get_memory_manager();
        if (mem == nullptr)
        {
            return false;
        }

        return mem->dealloc(buffer);
    }

    template <typename Type, typename... Args>
    inline Type *mem::alloc_type(ctx *context, Args &&...args)
    {
        memory_manager *mem = context->get_memory_manager();
        if (mem == nullptr)
        {
            return nullptr;
        }

        return mem->alloc<Type>(std::forward<Args>(args)...);
    }

    template <typename Type, typename... Args>
    inline Type *mem::alloc_type(memory_manager *manager, Args &&...args)
    {
        if (manager == nullptr)
        {
            return nullptr;
        }

        return manager->alloc<Type>(std::forward<Args>(args)...);
    }

    template <typename Type>
    inline bool mem::dealloc_type(memory_manager *manager, Type *address)
    {
        if (manager == nullptr)
        {
            return false;
        }

        return manager->dealloc(address);
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
