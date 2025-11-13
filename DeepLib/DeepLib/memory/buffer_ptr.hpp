#ifndef DEEP_LIB_BUFFER_PTR_HPP
#define DEEP_LIB_BUFFER_PTR_HPP

#include "DeepLib/memory/mem_ptr.hpp"

namespace deep
{

    template <typename Type>
    class buffer_ptr : public mem_ptr<Type>
    {
      public:
        using mem_ptr<Type>::mem_ptr;

        Type operator[](usize index) const;
        Type &operator[](usize index);

      private:
        friend memory_manager;
    };

    template <typename Type>
    inline Type buffer_ptr<Type>::operator[](usize index) const
    {
        return m_ptr[index];
    }

    template <typename Type>
    inline Type &buffer_ptr<Type>::operator[](usize index)
    {
        return m_ptr[index];
    }
} // namespace deep

#endif
