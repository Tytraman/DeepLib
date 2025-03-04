#include "../filesystem.hpp"
#include "../error.hpp"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

namespace deep
{
    const char *core_get_current_working_directory(ctx &context)
    {
        static char *cwd[4096];

        if (getcwd(cwd, sizeof(cwd)) == nullptr)
        {
            context.result = core_convert_error_code(errno);

            return nullptr;
        }

        context.result = error::NoError;

        return cwd;
    }

    fd core_open_file(ctx &context, const char *filename, fs::file_mode mode,
                      fs::file_access access, fs::file_share share)
    {
        (void) share;

        int flags = 0;

        switch (access)
        {
            default:
                break;
            case fs::file_access::Read:
            {
                flags |= O_RDONLY;
            }
            break;
            case fs::file_access::Write:
            {
                flags |= O_WRONLY;
            }
            break;
            case fs::file_access::ReadWrite:
            {
                flags |= O_RDWR;
            }
            break;
        }

        switch (mode)
        {
            default:
                break;
            case fs::file_mode::Append:
            {
                flags |= O_APPEND;
            }
            break;
            case fs::file_mode::Create:
            {
                flags |= O_CREAT | O_TRUNC;
            }
            break;
            case fs::file_mode::CreateNew:
            {
                flags |= O_CREAT | O_EXCL;
            }
            break;
            case fs::file_mode::Open:
            {
                // Aucun flag n'a besoin d'être utilisé pour l'ouverture simple.
            }
            break;
            case fs::file_mode::OpenOrCreate:
            {
                flags |= O_CREAT;
            }
            break;
            case fs::file_mode::Truncate:
            {
                flags |= O_TRUNC;
            }
            break;
        }

        fd file_descriptor = open(filename, flags, 0);

        if (file_descriptor < 0)
        {
            context.result = core_convert_error_code(errno);

            return invalid_fd;
        }

        context.result = error::NoError;

        return file_descriptor;
    }

    bool core_delete_file(ctx &context, const char *filename)
    {
        if (unlink(filename) != 0)
        {
            context.result = core_convert_error_code(errno);

            return false;
        }

        return true;
    }

} // namespace deep
