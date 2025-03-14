#ifndef DEEP_LIB_MEMORY_HPP
#define DEEP_LIB_MEMORY_HPP

#include "../DeepCore/memory.hpp"
#include "deep_lib_export.h"

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
        // TODO: static void *realloc(void *address, usize size);
        // TODO: static bool dealloc(void *address);

        template <typename Type, typename... Args>
        static Type *alloc_type(Args &&...args);

        template <typename Type>
        static bool dealloc_type(Type *ptr);
    };

    template <typename Type, typename... Args>
    inline Type *mem::alloc_type(Args &&...args)
    {
        // TODO: utiliser mem::alloc plutôt que core::mem::alloc
        Type *obj = (Type *) core::mem::alloc(sizeof(Type));

        if (obj == nullptr)
        {
            return nullptr;
        }

        new (obj) Type(std::forward<Args>(args)...);

        return obj;
    }

    template <typename Type>
    inline bool mem::dealloc_type(Type *ptr)
    {
        // Si l'objet a un destructeur défini, l'appelle.
        if (!is_trivially_destructible<Type>)
        {
            ptr->~Type();
        }

        // TODO: utiliser mem::dealloc plutôt que core::mem::dealloc
        return core::mem::dealloc(ptr);
    }
} // namespace deep

#endif
