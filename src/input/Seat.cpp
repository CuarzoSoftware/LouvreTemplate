#include <LCompositor.h>
#include <LInputDevice.h>
#include <libinput.h>
#include "Seat.h"
#include "../utils/Settings.h"

void Seat::enabledChanged()
{
    if (enabled())
    {
        /* Devices configuration may have changed in another session */
        configureInputDevices();
    }
    else
    {
        /* User switched to another TTY, see LSeat::setTTY() */
    }
}

void Seat::outputPlugged(LOutput *output)
{
    /* Refer to the default implementation in the documentation. */
    LSeat::outputPlugged(output);
}

void Seat::outputUnplugged(LOutput *output)
{
    /* Refer to the default implementation in the documentation. */
    LSeat::outputUnplugged(output);
}

void Seat::inputDevicePlugged(LInputDevice *device)
{
    L_UNUSED(device)
    configureInputDevices();
}

void Seat::inputDeviceUnplugged(LInputDevice *device)
{
    L_UNUSED(device)
}

/*
 * Listen to all input backend events, e.g.
 * tablet events which aren't supported yet.
 */
void Seat::nativeInputEvent(void *event)
{
    if (compositor()->inputBackendId() == LInputBackendLibinput)
    {
        libinput_event *ev { static_cast<libinput_event*>(event) };
        L_UNUSED(ev);

        // ...
    }
}

void Seat::configureInputDevices() noexcept
{
    if (compositor()->inputBackendId() != LInputBackendLibinput)
        return;

    libinput_device *dev;

    for (LInputDevice *device : inputDevices())
    {
        if (!device->nativeHandle())
            continue;

        dev = static_cast<libinput_device*>(device->nativeHandle());

        // Disable while typing
        libinput_device_config_dwt_set_enabled(dev, LIBINPUT_CONFIG_DWT_DISABLED);

        // Disable touchpad click areas
        libinput_device_config_click_set_method(dev, LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER);

        // Enable natural scrolling
        libinput_device_config_scroll_set_natural_scroll_enabled(dev, 1);
    }
}
