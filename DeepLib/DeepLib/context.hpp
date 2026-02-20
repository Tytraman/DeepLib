#ifndef DEEP_LIB_CONTEXT_HPP
#define DEEP_LIB_CONTEXT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/types.hpp"
#include "DeepLib/memory/ref_counted.hpp"
#include "DeepLib/stream/stream.hpp"
#include "DeepLib/stream/text_writer.hpp"
#include "DeepLib/collection/hash_map.hpp"

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
        virtual ~ctx() override;

        static constexpr void *get_internal_ctx(ctx *from);

        static constexpr memory_manager *get_memory_manager(ctx *from);

        bool destroy_internal_ctx();

        text_writer &out() const noexcept;
        text_writer &err() const noexcept;

        void *get_internal_ctx();
        void *get_internal_ctx() const;
        memory_manager *get_memory_manager();

        template <typename Type>
        void set_object(const char *name, const ref<Type> &obj) noexcept;

        template <typename Type>
        ref<Type> get_object(const char *name) noexcept;

      protected:
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
        DEEP_HASHMAP(ref<object>, m_objects)

      protected:
        bool init();

      public:
        friend class lib;
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

    template <typename Type>
    inline void ctx::set_object(const char *name, const ref<Type> &obj) noexcept
    {
        m_objects.insert(name, ref_cast<object>(obj));
    }

    template <typename Type>
    inline ref<Type> ctx::get_object(const char *name) noexcept
    {
        hash_entry<ref<object>> *entry = m_objects[name];

        if (entry == nullptr)
        {
            return ref<Type>();
        }

        return ref_cast<Type>(entry->value);
    }
} // namespace deep

#endif
