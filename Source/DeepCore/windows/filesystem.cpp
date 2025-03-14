#include "../filesystem.hpp"
#include "../error.hpp"
#include "../memory.hpp"
#include <Windows.h>

namespace deep
{
    namespace core
    {

        const char *core_get_current_working_directory(uint64 *result)
        {
            constexpr DWORD cwd_len    = 8192;
            constexpr DWORD buffer_len = cwd_len / 2;

            static char cwd[cwd_len];
            WCHAR buffer[buffer_len];

            // Détermine la taille nécessaire au buffer pour récupérer le chemin.
            DWORD buf_len = GetCurrentDirectoryW(0, nullptr);

            if (buf_len > buffer_len)
            {
                *result = error::OutOfRange;

                return nullptr;
            }

            buf_len = GetCurrentDirectoryW(buffer_len, buffer);

            if (buf_len == 0)
            {
                *result = core_convert_error_code(GetLastError());

                return nullptr;
            }

            // Détermine la taille nécessaire pour stocker la conversion.
            int bytes = WideCharToMultiByte(CP_UTF8, 0, buffer, buf_len, nullptr, 0, nullptr, nullptr);

            if (bytes >= sizeof(cwd))
            {
                *result = error::OutOfRange;

                return nullptr;
            }

            bytes = WideCharToMultiByte(CP_UTF8, 0, buffer, buf_len, cwd, sizeof(cwd), nullptr, nullptr);

            if (bytes == 0)
            {
                *result = core_convert_error_code(GetLastError());

                return nullptr;
            }

            cwd[bytes] = '\0';

            *result = error::NoError;

            return cwd;
        }

        fd core_open_file(uint64 *result, const char *filename, fs::file_mode mode, fs::file_access access, fs::file_share share)
        {
            DWORD mode_flags   = 0;
            DWORD access_flags = 0;
            DWORD share_flags  = 0;

            fd file_descriptor;

            // Détermine la taille nécessaire pour stocker la conversion.
            // Retourne le nombre de caractères que cela va produire.
            int characters_number = MultiByteToWideChar(CP_UTF8, 0, filename, -1, nullptr, 0);

            WCHAR *buffer = static_cast<WCHAR *>(core_alloc(result, characters_number * sizeof(*buffer)));

            if (buffer == nullptr)
            {
                return false;
            }

            // D'après la documentation officielle la fonction ajoute un caractère null à la fin puisque le paramètre pour la taille est de '-1'.
            characters_number = MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, characters_number);

            if (characters_number == 0)
            {
                core_dealloc(result, buffer);

                *result = core_convert_error_code(GetLastError());

                return invalid_fd;
            }

            switch (mode)
            {
                default:
                    break;
                case fs::file_mode::Create:
                {
                    mode_flags |= CREATE_ALWAYS;
                }
                break;
                case fs::file_mode::CreateNew:
                {
                    mode_flags |= CREATE_NEW;
                }
                break;
                case fs::file_mode::Append:
                {
                    mode_flags |= OPEN_ALWAYS;
                    access_flags |= FILE_APPEND_DATA;
                }
                    goto ignore_access;
                case fs::file_mode::Open:
                {
                    mode_flags |= OPEN_EXISTING;
                }
                break;
                case fs::file_mode::OpenOrCreate:
                {
                    mode_flags |= OPEN_ALWAYS;
                }
                break;
                case fs::file_mode::Truncate:
                {
                    mode_flags |= TRUNCATE_EXISTING;
                }
                break;
            }

            switch (access)
            {
                default:
                    break;
                case fs::file_access::Read:
                {
                    access_flags |= FILE_GENERIC_READ;
                }
                break;
                case fs::file_access::Write:
                {
                    access_flags |= FILE_GENERIC_WRITE;
                }
                break;
                case fs::file_access::ReadWrite:
                {
                    access_flags |= FILE_GENERIC_READ | FILE_GENERIC_WRITE;
                }
                break;
            }

        ignore_access:

            switch (share)
            {
                default:
                    break;
                case fs::file_share::Read:
                {
                    share_flags |= FILE_SHARE_READ;
                }
                break;
                case fs::file_share::Write:
                {
                    share_flags |= FILE_SHARE_WRITE;
                }
                break;
                case fs::file_share::Delete:
                {
                    share_flags |= FILE_SHARE_DELETE;
                }
                break;
                case fs::file_share::ReadWrite:
                {
                    share_flags |= FILE_SHARE_READ | FILE_SHARE_WRITE;
                }
                break;
            }

            file_descriptor = CreateFileW(buffer, access_flags, share_flags, nullptr, mode_flags, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_POSIX_SEMANTICS, nullptr);

            core_dealloc(result, buffer);

            if (file_descriptor == invalid_fd)
            {
                *result = core_convert_error_code(GetLastError());

                return invalid_fd;
            }

            *result = error::NoError;

            return file_descriptor;
        }

        bool core_delete_file(uint64 *result, const char *filename)
        {
            BOOL ret;

            // Détermine la taille nécessaire pour stocker la conversion.
            // Retourne le nombre de caractères que cela va produire.
            int characters_number = MultiByteToWideChar(CP_UTF8, 0, filename, -1, nullptr, 0);

            WCHAR *buffer = static_cast<WCHAR *>(core_alloc(result, characters_number * sizeof(*buffer)));

            if (buffer == nullptr)
            {
                return false;
            }

            // D'après la documentation officielle la fonction ajoute un caractère null à la fin puisque le paramètre pour la taille est de '-1'.
            characters_number = MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, characters_number);

            if (characters_number == 0)
            {
                core_dealloc(result, buffer);

                *result = core_convert_error_code(GetLastError());

                return false;
            }

            ret = DeleteFileW(buffer);

            core_dealloc(result, buffer);

            if (ret == 0)
            {
                *result = core_convert_error_code(GetLastError());

                return false;
            }

            *result = error::NoError;

            return true;
        }
    } // namespace core
} // namespace deep
