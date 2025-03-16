#ifndef DEEP_LIB_CONTEXT_HPP
#define DEEP_LIB_CONTEXT_HPP

#include "DeepCore/types.hpp"
#include "deep_lib_export.h"
#include "memory/memory_manager.hpp"

namespace deep
{
    /**
     * @class ctx
     * @brief Contient des données internes propres à chaque système
     * d'exploitation supporté par la librairie.
     *
     */
    struct DEEP_LIB_API ctx
    {
        /**
         * @brief Pointeur vers une zone de données contenant les données
         * internes propres au système d'exploitation.
         */
        void *internal_data;
        memory_manager *mem;
    };
} // namespace deep

#endif
