#include "../filesystem.hpp"
#include "../error.hpp"
#include "../memory.hpp"
#include "internal_data.hpp"

#include <Windows.h>

namespace deep
{

    const native_char *core_get_current_working_directory(void *internal_context)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        constexpr DWORD cwd_len    = 8192;
        constexpr DWORD buffer_len = cwd_len / 2;

        static WCHAR buffer[buffer_len];

        // Détermine la taille nécessaire au buffer pour récupérer le chemin.
        DWORD buf_len = GetCurrentDirectoryW(0, nullptr);

        if (buf_len > buffer_len)
        {
            internal_data->result = error::OutOfRange;

            return nullptr;
        }

        buf_len = GetCurrentDirectoryW(buffer_len, buffer);

        if (buf_len == 0)
        {
            internal_data->result = core_convert_error_code(GetLastError());

            return nullptr;
        }

        internal_data->result = error::NoError;

        return buffer;
    }

    fd core_open_file(void *internal_context, const native_char *filename, core_fs::file_mode mode, core_fs::file_access access, core_fs::file_share share)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD mode_flags   = 0;
        DWORD access_flags = 0;
        DWORD share_flags  = 0;

        fd file_descriptor;

        switch (mode)
        {
            default:
                return invalid_fd;
            case core_fs::file_mode::Create:
            {
                mode_flags |= CREATE_ALWAYS;
            }
            break;
            case core_fs::file_mode::CreateNew:
            {
                mode_flags |= CREATE_NEW;
            }
            break;
            case core_fs::file_mode::Append:
            {
                mode_flags |= OPEN_ALWAYS;
                access_flags |= FILE_APPEND_DATA;
            }
                goto ignore_access;
            case core_fs::file_mode::Open:
            {
                mode_flags |= OPEN_EXISTING;
            }
            break;
            case core_fs::file_mode::OpenOrCreate:
            {
                mode_flags |= OPEN_ALWAYS;
            }
            break;
            case core_fs::file_mode::Truncate:
            {
                mode_flags |= TRUNCATE_EXISTING;
            }
            break;
        }

        switch (access)
        {
            default:
                break;
            case core_fs::file_access::Read:
            {
                access_flags |= FILE_GENERIC_READ;
            }
            break;
            case core_fs::file_access::Write:
            {
                access_flags |= FILE_GENERIC_WRITE;
            }
            break;
            case core_fs::file_access::ReadWrite:
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
            case core_fs::file_share::Read:
            {
                share_flags |= FILE_SHARE_READ;
            }
            break;
            case core_fs::file_share::Write:
            {
                share_flags |= FILE_SHARE_WRITE;
            }
            break;
            case core_fs::file_share::Delete:
            {
                share_flags |= FILE_SHARE_DELETE;
            }
            break;
            case core_fs::file_share::ReadWrite:
            {
                share_flags |= FILE_SHARE_READ | FILE_SHARE_WRITE;
            }
            break;
        }

        file_descriptor = CreateFileW(filename, access_flags, share_flags, nullptr, mode_flags, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_POSIX_SEMANTICS, nullptr);

        if (file_descriptor == invalid_fd)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return invalid_fd;
        }

        internal_data->result = error::NoError;

        return file_descriptor;
    }

    bool core_close_file(void *internal_context, fd file_descriptor)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        if (CloseHandle(file_descriptor) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }

    bool core_flush_file(void *internal_context, fd file_descriptor)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        if (FlushFileBuffers(file_descriptor) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }

    bool core_seek_file(void *internal_context, fd file_descriptor, isize offset, core_fs::seek_origin origin, usize *new_size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LARGE_INTEGER linteger;
        linteger.QuadPart = offset;

        DWORD method;
        switch (origin)
        {
            default:
            {
                if (internal_data != nullptr)
                {
                    internal_data->result = error::InvalidArgument;
                }

                return false;
            }
            case core_fs::seek_origin::Begin:
            {
                method = FILE_BEGIN;
            }
            break;
            case core_fs::seek_origin::Current:
            {
                method = FILE_CURRENT;
            }
            break;
            case core_fs::seek_origin::End:
            {
                method = FILE_END;
            }
            break;
        }

        if (SetFilePointerEx(file_descriptor, linteger, &linteger, method) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (new_size != nullptr)
        {
            *new_size = make_unsigned<LONGLONG>(linteger.QuadPart);
        }

        return true;
    }

    bool core_delete_file(void *internal_context, const native_char *filename)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        if (DeleteFileW(filename) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        internal_data->result = error::NoError;

        return true;
    }

    bool core_read_file(void *internal_context, fd file_descriptor, usize count, void *dest, usize *bytes_read)
    {
        static constexpr DWORD max_bytes = 4096;

        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        usize total = 0;
        usize diff  = count;

        DWORD bytes = 0;

        while (total < count)
        {
            if (ReadFile(file_descriptor, static_cast<uint8 *>(dest) + total, diff > max_bytes ? max_bytes : static_cast<DWORD>(diff), &bytes, nullptr) == 0)
            {
                if (internal_data != nullptr)
                {
                    internal_data->result = core_convert_error_code(GetLastError());
                }

                return false;
            }

            if (bytes == 0)
            {
                break;
            }

            total += bytes;

            diff = count - total;
        }

        if (bytes_read != nullptr)
        {
            *bytes_read = total;
        }

        return true;
    }

    bool core_write_file(void *internal_context, fd file_descriptor, usize count, const void *from, usize *bytes_written)
    {
        static constexpr DWORD max_bytes = 4096;

        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        usize total = 0;
        usize diff  = count;

        DWORD bytes = 0;

        while (total < count)
        {
            if (WriteFile(file_descriptor, static_cast<const uint8 *>(from) + total, diff > max_bytes ? max_bytes : static_cast<DWORD>(diff), &bytes, nullptr) == 0)
            {
                if (internal_data != nullptr)
                {
                    internal_data->result = core_convert_error_code(GetLastError());
                }

                return false;
            }

            if (bytes == 0)
            {
                break;
            }

            total += bytes;

            diff = count - total;
        }

        if (bytes_written != nullptr)
        {
            *bytes_written = total;
        }

        return true;
    }

    bool core_get_file_size(void *internal_context, fd file_descriptor, usize *dest)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LARGE_INTEGER linteger;

        if (GetFileSizeEx(file_descriptor, &linteger) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (dest != nullptr)
        {
            *dest = make_unsigned<LONGLONG>(linteger.QuadPart);
        }

        return true;
    }

    bool core_set_file_size(void *internal_context, fd file_descriptor, usize size)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        usize current_position = 0;

        // Pour augmenter la taille d'un fichier il faut déplacer la position à la taille souhaitée et la définir comme fin de fichier.

        if (!core_get_file_position(internal_context, file_descriptor, &current_position))
        {
            return false;
        }

        // Met la position à la taille souhaitée.
        if (!core_seek_file(internal_context, file_descriptor, make_signed<usize>(size), core_fs::seek_origin::Begin, nullptr))
        {
            return false;
        }

        // Défini la position comme emplacement de fin de fichier.
        if (SetEndOfFile(file_descriptor) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        // Remet la position à là où elle était à l'origine.
        if (!core_seek_file(internal_context, file_descriptor, make_signed<usize>(current_position), core_fs::seek_origin::Begin, nullptr))
        {
            return false;
        }

        return true;
    }

    bool core_get_file_position(void *internal_context, fd file_descriptor, usize *dest)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        LARGE_INTEGER linteger;
        linteger.QuadPart = 0;

        if (SetFilePointerEx(file_descriptor, linteger, &linteger, FILE_CURRENT) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        if (dest != nullptr)
        {
            *dest = make_unsigned<LONGLONG>(linteger.QuadPart);
        }

        return true;
    }

    native_char *core_get_executable_path(void *internal_context, usize *path_bytes_size, usize *path_length)
    {
        DWORD nsize       = MAX_PATH;
        usize total_size  = (static_cast<usize>(nsize) + 1) * sizeof(native_char);
        native_char *path = static_cast<native_char *>(core_mem::alloc(internal_context, total_size));
        native_char *temp_path;

        if (path == nullptr)
        {
            return nullptr;
        }

        while (true)
        {
            nsize = GetModuleFileNameW(nullptr, path, nsize);

            if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            {
                break;
            }

            nsize += MAX_PATH;
            total_size = (static_cast<usize>(nsize) + 1) * sizeof(native_char);

            temp_path = static_cast<native_char *>(core_mem::realloc(internal_context, path, total_size));

            if (temp_path == nullptr)
            {
                core_mem::dealloc(internal_context, path);

                return nullptr;
            }

            path = temp_path;
        }

        if (path_bytes_size != nullptr)
        {
            *path_bytes_size = total_size;
        }

        if (path_length != nullptr)
        {
            *path_length = nsize;
        }

        return path;
    }
} // namespace deep
