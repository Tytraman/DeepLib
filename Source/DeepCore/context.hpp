#ifndef DEEP_CORE_CONTEXT_HPP
#define DEEP_CORE_CONTEXT_HPP

#include "deep_core_export.h"
#include "types.hpp"

namespace deep
{
    /**
     * @class ctx
     * @brief Contient des données internes propres à chaque système
     * d'exploitation supporté par la librairie.
     *
     */
    struct DEEP_CORE_API ctx
    {
        /**
         * @brief Pointeur vers une zone de données contenant les données
         * internes propres au système d'exploitation.
         */
        void *internal_data;
        /**
         * @brief Contient le code résultant de chaque procédure de la
         * librairie.
         */
        uint64 result;
    };
} // namespace deep

#endif
