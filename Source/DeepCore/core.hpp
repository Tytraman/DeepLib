#ifndef DEEP_CORE_CORE_HPP
#define DEEP_CORE_CORE_HPP

#include "deep_core_export.h"
#include "system.hpp"

namespace deep
{
    class DEEP_CORE_API core
    {
      public:
        /**
         * @brief Sélectionne le système d'exploitation sur lequel la librairie
         * est utilisée.
         *
         * @return Le système utilisé.
         */
        DEEP_CORE_API static system get_current_system();
    };
} // namespace deep

#endif
