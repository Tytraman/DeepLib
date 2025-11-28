#ifndef DEEP_CORE_EVENT_HPP
#define DEEP_CORE_EVENT_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

namespace deep
{
    class DEEP_CORE_API core_event
    {
      public:
        /**
         * @brief
         * @param manual_reset
         * @param initial_state
         * @return `nullptr` en cas d'erreur.
         */
        static handle create(bool manual_reset, bool initial_state);

        static bool set(handle ev);
        static bool reset(handle ev);

        /**
         * @brief
         * @param ev
         * @param milliseconds `infinite` pour attendre à l'infini.
         */
        static void wait(handle ev, uint32 milliseconds);
    };

    extern handle core_create_event(bool manual_reset, bool initial_state);
    extern bool core_set_event(handle ev);
    extern bool core_reset_event(handle ev);
    extern void core_event_wait(handle ev, uint32 milliseconds);
} // namespace deep

#endif
