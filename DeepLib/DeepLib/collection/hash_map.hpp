#ifndef DEEP_LIB_HASH_MAP_HPP
#define DEEP_LIB_HASH_MAP_HPP

#include "DeepCore/types.hpp"
#include "DeepLib/memory/memory.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/memory/memory_manager.hpp"
#include "DeepLib/string/string.hpp"

namespace deep
{
    using hash_function = uint64 (*)(const char *str);

    template <typename Type>
    struct hash_entry
    {
        uint64 key;
        Type value;
        hash_entry<Type> *next;
        hash_entry<Type> *previous;
    };

    /**
     * @brief
     * @tparam Type Le type de donnée à stocker dans la hash_map.
     */
    template <typename Type>
    class hash_map
    {
      public:
        hash_map() = delete;
        hash_map(ctx *context, usize size = 10);

        /**
         * @brief Récupère l'entrée correspondante à la clé spécifiée.
         * @param key La clé à rechercher.
         * @return L'entrée liée à la clé ou `nullptr` si rien n'est trouvé.
         */
        hash_entry<Type> *operator[](const char *key);
        hash_entry<Type> *operator[](uint64 key);

        /**
         * @brief Insère un élément lié à la clé spécifiée. Si une clé existe déjà, remplace sa valeur avec la nouvelle.
         * @param key La clé à laquelle lier l'élément.
         * @param value L'élément à insérer.
         * @return L'entrée insérée ou `nullptr` en cas d'erreur.
         */
        hash_entry<Type> *insert(const char *key, const Type &value);
        hash_entry<Type> *insert(uint64 key, const Type &value);

        /**
         * @brief Supprime l'entrée liée à la clé spécifiée.
         * @param key La clé à laquelle supprimer l'entrée.
         * @return
         */
        bool remove(const char *key);
        bool remove(uint64 key);

        /**
         * @brief Permet d'obtenir le nombre d'éléments stockés dans la `hash_map`.
         * @return Le nombre d'éléments stockés dans la `hash_map`.
         */
        usize get_number_of_elements() const;

      private:
        hash_entry<Type> **m_map;
        usize m_size;
        usize m_number_of_elements;
        memory_manager *m_memory_manager;
    };

    template <typename Type>
    inline hash_map<Type>::hash_map(ctx *context, usize size)
            : m_map(nullptr), m_size(size), m_number_of_elements(0), m_memory_manager(nullptr)
    {
        if (context != nullptr)
        {
            m_memory_manager = context->get_memory_manager();

            m_map = mem::alloc_table<hash_entry<Type>>(m_memory_manager, size);
        }
    }

    template <typename Type>
    inline hash_entry<Type> *hash_map<Type>::operator[](const char *key)
    {
        return operator[](string::hash(key));
    }

    template <typename Type>
    inline hash_entry<Type> *hash_map<Type>::operator[](uint64 key)
    {
        uint64 bucket = key % m_size;

        hash_entry<Type> *entry = m_map[bucket];

        if (entry == nullptr)
        {
            return nullptr;
        }

        // TODO: faire une recherche binaire.
        while (entry != nullptr)
        {
            if (entry->key == key)
            {
                return entry;
            }

            entry = entry->next;
        }

        return nullptr;
    }

    template <typename Type>
    inline hash_entry<Type> *hash_map<Type>::insert(const char *key, const Type &value)
    {
        return insert(string::hash(key), value);
    }

    template <typename Type>
    inline hash_entry<Type> *hash_map<Type>::insert(uint64 key, const Type &value)
    {
        uint64 bucket = key % m_size;

        // Cherche dans la table si la clé est déjà présente.
        hash_entry<Type> *entry = operator[](key);

        // Si la clé est présente, remplace simplement sa valeur.
        if (entry != nullptr)
        {
            entry->value = value;

            return entry;
        }

        // Ajoute la valeur à la clé.
        entry = m_map[bucket];

        // S'il n'y a pas encore de bucket, le crée.
        if (entry == nullptr)
        {
            entry = mem::alloc_type<hash_entry<Type>>(m_memory_manager);

            if (entry == nullptr)
            {
                return nullptr;
            }

            entry->key      = key;
            entry->value    = value;
            entry->previous = nullptr;
            entry->next     = nullptr;

            m_map[bucket] = entry;

            m_number_of_elements++;

            return entry;
        }

        while (entry->next != nullptr)
        {
            entry = entry->next;
        }

        entry->next = mem::alloc_type<hash_entry<Type>>(m_memory_manager);

        if (entry->next == nullptr)
        {
            return nullptr;
        }

        entry->next->key      = key;
        entry->next->value    = value;
        entry->next->previous = entry;
        entry->next->next     = nullptr;

        m_number_of_elements++;

        return entry->next;
    }

    template <typename Type>
    inline bool hash_map<Type>::remove(const char *key)
    {
        return remove(string::hash(key));
    }

    template <typename Type>
    inline bool hash_map<Type>::remove(uint64 key)
    {
        // Récupère l'entrée à supprimer.
        hash_entry<Type> *entry = operator[](key);

        if (entry == nullptr)
        {
            return false;
        }

        if (entry->previous != nullptr)
        {
            entry->previous->next = entry->next;

            if (entry->next != nullptr)
            {
                entry->next->previous = entry->previous;
            }
        }
        else
        {
            uint64 bucket = key % m_size;

            m_map[bucket] = entry->next;

            if (entry->next != nullptr)
            {
                entry->next->previous = nullptr;
            }
        }

        mem::dealloc_type<hash_entry<Type>>(m_memory_manager, entry);

        m_number_of_elements--;

        return true;
    }

    template <typename Type>
    inline usize hash_map<Type>::get_number_of_elements() const
    {
        return m_number_of_elements;
    }
} // namespace deep

#endif
