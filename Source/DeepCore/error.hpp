#ifndef DEEP_CORE_ERROR_HPP
#define DEEP_CORE_ERROR_HPP

#include "types.hpp"

namespace deep
{
    extern uint64 core_convert_error_code(native_error error_code);

    namespace error
    {
        static constexpr uint64 NoError                      = 0;
        static constexpr uint64 UnknownError                 = 1;
        static constexpr uint64 EmptyStr                     = 2;
        static constexpr uint64 OutOfRange                   = 3;
        static constexpr uint64 InvalidEnumValue             = 4;
        static constexpr uint64 PermissionDenied             = 5;
        static constexpr uint64 BadFileDescriptor            = 6;
        static constexpr uint64 Busy                         = 7;
        static constexpr uint64 DiskQuotaExceeded            = 8;
        static constexpr uint64 FileExists                   = 9;
        static constexpr uint64 BadAddress                   = 10;
        static constexpr uint64 FileTooLarge                 = 11;
        static constexpr uint64 InterruptedFunctionCall      = 12;
        static constexpr uint64 InvalidArgument              = 13;
        static constexpr uint64 IsADirectory                 = 14;
        static constexpr uint64 TooManyLevelsOfSymbolicLinks = 15;
        static constexpr uint64 TooManyOpenFiles             = 16;
        static constexpr uint64 FilenameTooLong              = 17;
        static constexpr uint64 NoSuchDevice                 = 18;
        static constexpr uint64 NoSuchFileOrDirectory        = 19;
        static constexpr uint64 NotEnoughMemory              = 20;
        static constexpr uint64 NoSpaceLeftOnDevice          = 21;
        static constexpr uint64 NotADirectory                = 22;
        static constexpr uint64 NoSuchDeviceOrAddress        = 23;
        static constexpr uint64 OperationNotSupported        = 24;
        static constexpr uint64 Overflow                     = 25;
        static constexpr uint64 OperationNotPermitted        = 26;
        static constexpr uint64 ReadOnlyFilesystem           = 27;
        static constexpr uint64 TextFileBusy                 = 28;
        static constexpr uint64 OperationWouldBlock          = 29;
    } // namespace error
} // namespace deep

#endif
