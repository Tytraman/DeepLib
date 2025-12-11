#include "../term.hpp"
#include "../error.hpp"
#include "internal_data.hpp"

namespace deep
{
    fd core_term_get_std_handle(void *internal_context, core_term::std_handle h)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD input;

        switch (h)
        {
            default:
            {
                if (internal_data != nullptr)
                {
                    internal_data->result = error::InvalidEnumValue;
                }

                return invalid_fd;
            }
            case core_term::std_handle::Input:
            {
                input = STD_INPUT_HANDLE;
            }
            break;
            case core_term::std_handle::Output:
            {
                input = STD_OUTPUT_HANDLE;
            }
            break;
            case core_term::std_handle::Error:
            {
                input = STD_ERROR_HANDLE;
            }
            break;
        }

        fd output = GetStdHandle(input);

        if (output == INVALID_HANDLE_VALUE)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return invalid_fd;
        }

        return output;
    }

    bool core_term_set_encoding(void *internal_context, string_encoding /*encoding*/)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        // On force l'utilisation de l'UTF-8 sous Windows.
        if (SetConsoleOutputCP(CP_UTF8) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }

    bool core_term_add_mode(void *internal_context, fd std, core_term::mode m)
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DWORD console_mode;

        if (GetConsoleMode(std, &console_mode) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        switch (m)
        {
            default:
            {
                if (internal_data != nullptr)
                {
                    internal_data->result = error::InvalidEnumValue;
                }

                return false;
            }
            case core_term::mode::EnableProcessedOutput:
            {
                console_mode |= ENABLE_PROCESSED_OUTPUT;
            }
            break;
            case core_term::mode::EnableVirtualTerminalProcessing:
            {
                console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            }
            break;
        }

        if (SetConsoleMode(std, console_mode) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = core_convert_error_code(GetLastError());
            }

            return false;
        }

        return true;
    }
} // namespace deep
