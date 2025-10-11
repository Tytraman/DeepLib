#ifndef DEEP_LIB_COLLECTION_HPP
#define DEEP_LIB_COLLECTION_HPP

#include "../DeepCore/types.hpp"

namespace deep
{

    template <typename Type>
    class collection
    {
      public:
        static constexpr usize nothing = static_cast<usize>(-1);

      public:
        collection();

        virtual bool add()                    = 0;
        virtual bool add(const Type &element) = 0;
        virtual bool add(Type &&element)      = 0;

        virtual bool remove(usize index) = 0;

        virtual usize find(const Type &element) const = 0;

        virtual bool reserve(usize number_of_elements) = 0;

        virtual void empty() = 0;
        virtual bool free()  = 0;

        usize count() const;

      protected:
        usize m_number_of_elements;
    };

    template <typename Type>
    collection<Type>::collection()
            : m_number_of_elements(0)
    {
    }

    template <typename Type>
    usize collection<Type>::count() const
    {
        return m_number_of_elements;
    }
} // namespace deep

#endif
