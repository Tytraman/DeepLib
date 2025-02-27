#include "../error.hpp"
#include <cerrno>

namespace deep
{
    uint64 core_convert_error_code(native_error error_code)
    {
        switch (error_code)
        {
            default:
                return error::UnknownError;
            case 0:
                return error::NoError;
            case ERANGE:
                return error::OutOfRange;
            case EACCES:
                return error::PermissionDenied;
            case EBADF:
                return error::BadFileDescriptor;
            case EBUSY:
                return error::Busy;
            case EDQUOT:
                return error::DiskQuotaExceeded;
            case EEXIST:
                return error::FileExists;
            case EFAULT:
                return error::BadAddress;
            case EFBIG:
                return error::FileTooLarge;
            case EINVAL:
                return error::InvalidArgument;
            case EISDIR:
                return error::IsADirectory;
            case ELOOP:
                return error::TooManyLevelsOfSymbolicLinks;
            case EMFILE:
                return error::TooManyOpenFiles;
            case ENAMETOOLONG:
                return error::FilenameTooLong;
            case ENFILE:
                return error::TooManyOpenFiles;
            case ENODEV:
                return error::NoSuchDevice;
            case ENOENT:
                return error::NoSuchFileOrDirectory;
            case ENOMEM:
                return error::NotEnoughMemory;
            case ENOSPC:
                return error::NoSpaceLeftOnDevice;
            case ENOTDIR:
                return error::NotADirectory;
            case ENXIO:
                return error::NoSuchDeviceOrAddress;
            case EOPNOTSUPP:
                return error::OperationNotSupported;
            case EOVERFLOW:
                return error::Overflow;
            case EPERM:
                return error::OperationNotPermitted;
            case EROFS:
                return error::ReadOnlyFilesystem;
            case ETXTBSY:
                return error::TextFileBusy;
            case EWOULDBLOCK:
                return error::OperationWouldBlock;
        }
    }
} // namespace deep
