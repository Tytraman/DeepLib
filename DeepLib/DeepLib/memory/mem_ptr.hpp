#ifndef DEEP_LIB_MEM_PTR_HPP
#define DEEP_LIB_MEM_PTR_HPP

#include "DeepLib/memory/managed_ptr.hpp"

namespace deep
{
    template <typename Type>
    class mem_ptr : public managed_ptr<mem_ptr<Type>, Type>
    {
      public:
        using managed_ptr<mem_ptr<Type>, Type>::managed_ptr;

        bool destroy_impl();

        Type *operator->();
        Type &operator*();
    };

    template <typename Type>
    inline bool mem_ptr<Type>::destroy_impl()
    {
        if (this->m_memory_manager == nullptr)
        {
            return false;
        }

        if (!this->m_memory_manager->dealloc(this->m_ptr))
        {
            return false;
        }

        this->m_ptr        = nullptr;
        this->m_bytes_size = 0;

        return true;
    }

    template <typename Type>
    inline Type *mem_ptr<Type>::operator->()
    {
        return this->m_ptr;
    }

    template <typename Type>
    inline Type &mem_ptr<Type>::operator*()
    {
        return *this->m_ptr;
    }
} // namespace deep

#endif
