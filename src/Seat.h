#ifndef SEAT_H
#define SEAT_H

#include <LSeat.h>

using namespace Louvre;

class Seat final : public LSeat
{
public:
    using LSeat::LSeat;

    void enabledChanged() override;

    void outputPlugged(LOutput *output) override;
    void outputUnplugged(LOutput *output) override;

    void inputDevicePlugged(LInputDevice *device) override;
    void inputDeviceUnplugged(LInputDevice *device) override;

    void nativeInputEvent(void *event) override;

    /* Libinput device configuration example */
    void configureInputDevices() noexcept;
};

#endif // SEAT_H
