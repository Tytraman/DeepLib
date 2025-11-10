#ifndef DEEP_LIB_CONTEXT_HPP
#define DEEP_LIB_CONTEXT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class memory_manager;

    /**
     * @class ctx
     * @brief Contient des données internes propres à chaque système
     * d'exploitation supporté par la librairie.
     *
     */
    class DEEP_LIB_API ctx
    {
      public:
        ctx();

        static constexpr void *get_internal_ctx(ctx *from);
        static constexpr memory_manager *get_memory_manager(ctx *from);

        bool destroy_internal_ctx();

        void *get_internal_ctx();
        memory_manager *get_memory_manager();

      private:
        friend class lib;

        /**
         * @brief Pointeur vers une zone de données contenant les données
         * internes propres au système d'exploitation.
         */
        void *internal_data;
        memory_manager *mem;
    };

    inline constexpr void *ctx::get_internal_ctx(ctx *from)
    {
        if (from != nullptr)
        {
            return from->get_internal_ctx();
        }

        return nullptr;
    }

    inline constexpr memory_manager *ctx::get_memory_manager(ctx *from)
    {
        if (from != nullptr)
        {
            return from->mem;
        }

        return nullptr;
    }

    inline void *ctx::get_internal_ctx()
    {
        return internal_data;
    }

    inline memory_manager *ctx::get_memory_manager()
    {
        return mem;
    }
} // namespace deep

#endif
