#ifndef DEEP_CORE_FILESYSTEM_HPP
#define DEEP_CORE_FILESYSTEM_HPP

#include "DeepCore/deep_core_export.h"
#include "DeepCore/types.hpp"

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

        enum class DEEP_CORE_API seek_origin
        {
            Begin,
            Current,
            End
        };

      public:
        /**
         * @brief Retourne le chemin de travail actuel.
         */
        static const char *get_current_working_directory(void *internal_context);

        /**
         * @brief Ouvre un fichier.
         */
        static fd open_file(void *internal_context, const native_char *filename, file_mode mode,
                            file_access access, file_share share);

        static bool close_file(void *internal_context, fd file_descriptor);

        static bool flush_file(void *internal_context, fd file_descriptor);

        static bool seek_file(void *internal_context, fd file_descriptor, isize offset, seek_origin origin, usize *new_size);

        static bool delete_file(void *internal_context, const native_char *filename);

        static bool read_file(void *internal_context, fd file_descriptor, usize count, void *dest, usize *bytes_read);
        static bool write_file(void *internal_context, fd file_descriptor, usize count, void *from, usize *bytes_written);

        static bool get_file_size(void *internal_context, fd file_descriptor, usize *dest);

        static bool set_file_size(void *internal_context, fd file_descriptor, usize size);

        static bool get_file_position(void *internal_context, fd file_descriptor, usize *dest);
    };

    extern const char *core_get_current_working_directory(void *internal_context);
    extern fd core_open_file(void *internal_context, const native_char *filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share);
    extern bool core_close_file(void *internal_context, fd file_descriptor);
    extern bool core_flush_file(void *internal_context, fd file_descriptor);
    extern bool core_seek_file(void *internal_context, fd file_descriptor, isize offset, core_fs::seek_origin origin, usize *new_size);
    extern bool core_delete_file(void *internal_context, const native_char *filename);
    extern bool core_read_file(void *internal_context, fd file_descriptor, usize count, void *dest, usize *bytes_read);
    extern bool core_write_file(void *internal_context, fd file_descriptor, usize count, void *from, usize *bytes_written);
    extern bool core_get_file_size(void *internal_context, fd file_descriptor, usize *dest);
    extern bool core_set_file_size(void *internal_context, fd file_descriptor, usize size);
    extern bool core_get_file_position(void *internal_context, fd file_descriptor, usize *dest);

} // namespace deep

#endif
