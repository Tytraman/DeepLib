#ifndef DEEP_CORE_FILESYSTEM_HPP
#define DEEP_CORE_FILESYSTEM_HPP

#include "deep_core_export.h"
#include "types.hpp"

namespace deep
{
    class DEEP_CORE_API core_fs
    {
      public:
        /**
         * @enum file_mode
         * @brief Détermine la façon d'ouvrir un fichier.
         */
        enum class DEEP_CORE_API file_mode
        {
            None = 0,
            /**
             * @brief Donne la possibilité d'ajouter des données à la fin d'un
             * fichier sans écraser les données déjà existantes.
             * @remark Génère une erreur si le fichier n'existe pas.
             */
            Append = 1,
            /**
             * @brief Crée toujours un fichier. S'il existe déjà, l'ouvre et le
             * tronque en remettant sa taille à 0.
             */
            Create = 2,
            /**
             * @brief Crée un nouveau fichier uniquement s'il n'existe pas.
             * @remark Génère une erreur si le fichier existe déjà.
             */
            CreateNew = 3,
            /**
             * @brief Ouvre un fichier si existant.
             * @remark Génère une erreur si le fichier n'existe pas.
             */
            Open = 4,
            /**
             * @brief Ouvre un fichier s'il existe ou le crée dans le cas
             * contraire.
             */
            OpenOrCreate = 5,
            /**
             * @brief Ouvre un fichier et le tronque en remettant sa taille à
             * 0.
             * @remark Génère une erreur si le fichier n'existe pas.
             */
            Truncate = 6
        };

        /**
         * @enum file_access
         * @brief Détermine le niveau d'accès à un fichier.
         */
        enum class DEEP_CORE_API file_access
        {
            None = 0,
            /**
             * @brief Autorise la lecture seulement.
             */
            Read = 1,
            /**
             * @brief Autorise l'écriture seulement.
             */
            Write = 2,
            /**
             * @brief Autorise la lecture et l'écriture.
             */
            ReadWrite = 3
        };

        /**
         * @enum file_share
         * @brief Détermine le niveau de partage du fichier avec les autres
         * processus.
         */
        enum class DEEP_CORE_API file_share
        {
            None = 0,
            /**
             * @brief Autorise les autres processus à supprimer le fichier.
             */
            Delete = 1,
            /**
             * @brief Autorise les autres processus à lire le fichier.
             */
            Read = 2,
            /**
             * @brief Autorise les autres processus à écrire dans le fichier.
             */
            Write = 3,
            /**
             * @brief Autorise les autres processus à lire et écrire dans le
             * fichier.
             */
            ReadWrite = 4
        };

      public:
        /**
         * @brief Retourne le chemin de travail actuel.
         */
        static const char *get_current_working_directory();

        /**
         * @brief Ouvre un fichier.
         */
        static fd open_file(const char *filename, file_mode mode,
                            file_access access, file_share share);

        static bool delete_file(const char *filename);
    };

    extern const char *core_get_current_working_directory(void *internal_context);
    extern fd core_open_file(void *internal_context, const char *filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share);
    extern bool core_delete_file(void *internal_context, const char *filename);

} // namespace deep

#endif
