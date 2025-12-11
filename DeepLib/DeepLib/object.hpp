#ifndef DEEP_LIB_OBJECT_HPP
#define DEEP_LIB_OBJECT_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepLib/memory/ref_counted.hpp"
#include "DeepLib/context.hpp"

namespace deep
{
    template class DEEP_LIB_API ref<ctx>;

    /**
     * @class object
     * @brief Classe de base pour tous les objets nécessitant un contexte.
     * @remark Hérite de ref_counted pour permettre l'utilisation de ref<object>.
     */
    class DEEP_LIB_API object : public ref_counted
    {
      public:
        object();
        explicit object(const ref<ctx> &context);
        virtual ~object() = default;

        const ref<ctx> &get_context() const;
        ctx *get_context_ptr();
        ctx *get_context_ptr() const;

      protected:
        ref<ctx> m_context;
    };
} // namespace deep

#endif
