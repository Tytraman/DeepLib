#include "../filesystem.hpp"
#include "../error.hpp"
#include <Windows.h>

namespace deep
{
    const char *core_get_current_working_directory(ctx &context)
    {
        static char cwd[8192];
        WCHAR buffer[4096];

        // Détermine la taille nécessaire au buffer pour récupérer le chemin.
        DWORD buf_len = GetCurrentDirectoryW(0, nullptr);

        if (buf_len > 4096)
        {
            context.result = error::OutOfRange;

            return nullptr;
        }

        buf_len = GetCurrentDirectoryW(4096, buffer);

        if (buf_len == 0)
        {
            context.result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        // Détermine la taille nécessaire pour stocker la conversion.
        int bytes = WideCharToMultiByte(CP_UTF8, 0, buffer, buf_len, nullptr, 0, nullptr, nullptr);

        if (bytes >= sizeof(cwd))
        {
            context.result = error::OutOfRange;

            return nullptr;
        }

        bytes = WideCharToMultiByte(CP_UTF8, 0, buffer, buf_len, cwd, sizeof(cwd), nullptr, nullptr);

        if (bytes == 0)
        {
            context.result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        cwd[bytes] = '\0';

        context.result = error::NoError;

        return cwd;
    }

    fd core_open_file(ctx &context, const char *filename, fs::file_mode mode, fs::file_access access, fs::file_share share)
    {
        DWORD mode_flags = 0;
        DWORD access_flags = 0;
        DWORD share_flags = 0;

        fd file_descriptor;

        WCHAR buffer[4096];

        // Détermine la taille nécessaire pour stocker la conversion.
        int bytes = MultiByteToWideChar(CP_UTF8, 0, filename, -1, nullptr, 0);

        if (bytes > sizeof(buffer) / sizeof(WCHAR))
        {
            context.result = error::OutOfRange;

            return invalid_fd;
        }

        // D'après la documentation officielle la fonction ajoute un caractère null à la fin puisque le paramètre pour la taille est de '-1'.
        bytes = MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, sizeof(buffer) / sizeof(WCHAR));

        if (bytes == 0)
        {
            context.result = core_convert_error_code(GetLastError());

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

        if (file_descriptor == invalid_fd)
        {
            context.result = core_convert_error_code(GetLastError());

            return invalid_fd;
        }

        context.result = error::NoError;

        return file_descriptor;
    }

    bool core_delete_file(ctx &context, const char *filename)
    {
        WCHAR buffer[4096];

        // Détermine la taille nécessaire pour stocker la conversion.
        int bytes = MultiByteToWideChar(CP_UTF8, 0, filename, -1, nullptr, 0);

        if (bytes > sizeof(buffer) / sizeof(WCHAR))
        {
            context.result = error::OutOfRange;

            return false;
        }

        // D'après la documentation officielle la fonction ajoute un caractère null à la fin puisque le paramètre pour la taille est de '-1'.
        bytes = MultiByteToWideChar(CP_UTF8, 0, filename, -1, buffer, sizeof(buffer) / sizeof(WCHAR));

        if (bytes == 0)
        {
            context.result = core_convert_error_code(GetLastError());

            return false;
        }

        if (DeleteFileW(buffer) == 0)
        {
            context.result = core_convert_error_code(GetLastError());

            return false;
        }

        context.result = error::NoError;

        return true;
    }
} // namespace deep
