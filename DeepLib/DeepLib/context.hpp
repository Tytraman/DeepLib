#ifndef DEEP_LIB_CONTEXT_HPP
#define DEEP_LIB_CONTEXT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/memory/ref_counted.hpp"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/stream/text_writer.hpp"

namespace deep
{
    class memory_manager;

    template class DEEP_LIB_API ref<stream>;
    template class DEEP_LIB_API ref<text_writer>;

    /**
     * @class ctx
     * @brief Contient des données internes propres à chaque système
     * d'exploitation supporté par la librairie.
     * @remark Hérite de ref_counted pour permettre l'utilisation de ref<ctx>.
     */
    class DEEP_LIB_API ctx : public ref_counted
    {
      public:
        ctx();
        ~ctx();

        static constexpr void *get_internal_ctx(ctx *from);

        static constexpr memory_manager *get_memory_manager(ctx *from);

        bool destroy_internal_ctx();

        text_writer &out();
        text_writer &err();

        void *get_internal_ctx();
        void *get_internal_ctx() const;
        memory_manager *get_memory_manager();

      protected:
        bool init();

      private:
        friend class lib;

        /**
         * @brief Pointeur vers une zone de données contenant les données
         * internes propres au système d'exploitation.
         */
        void *m_internal_data;
        memory_manager *m_mem;
        ref<stream> m_stdout;
        ref<stream> m_stderr;
        ref<text_writer> m_stdout_writer;
        ref<text_writer> m_stderr_writer;
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
            return from->m_mem;
        }

        return nullptr;
    }

    inline void *ctx::get_internal_ctx()
    {
        return m_internal_data;
    }

    inline void *ctx::get_internal_ctx() const
    {
        return m_internal_data;
    }

    inline memory_manager *ctx::get_memory_manager()
    {
        return m_mem;
    }
} // namespace deep

#endif
