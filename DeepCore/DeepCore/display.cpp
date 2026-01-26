#include "DeepCore/display.hpp"
#include "DeepCore/error.hpp"
#include "DeepCore/windows/internal_data.hpp"

namespace deep
{
    int32 core_display_get_monitor_count() noexcept
    {
        return GetSystemMetrics(SM_CMONITORS);
    }

    bool core_display_get_monitor_infos(void *internal_context, uint32 monitor_index, uint32 *width, uint32 *height, uint32 *frequency) noexcept
    {
        internal_data_win32 *internal_data = static_cast<internal_data_win32 *>(internal_context);

        DISPLAY_DEVICEW dd;
        dd.cb = sizeof(dd);

        if (EnumDisplayDevicesW(nullptr, monitor_index, &dd, 0) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = error::OutOfRange;
            }

            return false;
        }

        DEVMODEW dm;
        dm.dmSize = sizeof(dm);

        if (EnumDisplaySettingsW(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm) == 0)
        {
            if (internal_data != nullptr)
            {
                internal_data->result = error::UnknownError;
            }

            return false;
        }

        if (width != nullptr)
        {
            *width = dm.dmPelsWidth;
        }

        if (height != nullptr)
        {
            *height = dm.dmPelsHeight;
        }

        if (frequency != nullptr)
        {
            *frequency = dm.dmDisplayFrequency;
        }

        return true;
    }

    bool core_display_get_primary_monitor_index(uint32 *monitor_index) noexcept
    {
        if (monitor_index == nullptr)
        {
            return false;
        }

        DISPLAY_DEVICEW dd;
        dd.cb = sizeof(dd);

        uint32 index = 0;

        while (EnumDisplayDevicesW(nullptr, index, &dd, 0) != 0)
        {
            if ((dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) &&
                (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE))
            {
                *monitor_index = index;

                return true;
            }

            index++;
        }

        return false;
    }
} // namespace deep
