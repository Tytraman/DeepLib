#ifndef DEEP_LIB_HASH_MAP_HPP
#define DEEP_LIB_HASH_MAP_HPP

#include "DeepCore/types.hpp"

namespace deep
{
    template <typename Type>
    struct hash_entry
    {
        uint64 key;
        Type value;
        hash_entry<Value> *next;
        hash_entry<Value> *previous;
    };

    template <typename Type>
    class hash_table
    {
      public:
        hash_entry<Type> &insert(const char *key, const Type &value);

      private:
        hash_entry<Type> **m_table;
        usize m_size;
        usize m_number_of_elements;
    };

    template <typename Type>
    inline hash_entry<Type> &hash_table<Type>::insert(const char *key, const Type &value)
    {
        uint64
    }
} // namespace deep

#endif
