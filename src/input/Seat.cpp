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

        libinput_device_config_dwt_set_enabled(dev, (libinput_config_dwt_state)SETTINGS_DISABLE_WHILE_TYPING);
    }
}
