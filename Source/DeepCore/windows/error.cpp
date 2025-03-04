#include "../error.hpp"

namespace deep
{
    uint64 core_convert_error_code(native_error error_code)
    {
        switch (error_code)
        {
            default:
                return error::UnknownError;
            case ERROR_SUCCESS:
                return error::NoError;
            case ERROR_INVALID_FUNCTION:
                return error::InvalidFunction;
            case ERROR_FILE_NOT_FOUND:
                return error::NoSuchFile;
            case ERROR_PATH_NOT_FOUND:
                return error::NoSuchDirectory;
            case ERROR_TOO_MANY_OPEN_FILES:
                return error::TooManyOpenFiles;
            case ERROR_ACCESS_DENIED:
                return error::AccessDenied;
            case ERROR_INVALID_HANDLE:
                return error::BadFileDescriptor;
            case ERROR_NOT_ENOUGH_MEMORY:
            case ERROR_OUTOFMEMORY:
                return error::NotEnoughMemory;
            case ERROR_INVALID_BLOCK:
                return error::BadAddress;
            case ERROR_INVALID_ACCESS:
                return error::BadAccess;
            case ERROR_INVALID_DATA:
                return error::BadData;
            case ERROR_INSUFFICIENT_BUFFER:
                return error::OutOfRange;
            case ERROR_INVALID_FLAGS:
                return error::InvalidArgument;
        }
    }
} // namespace deep
