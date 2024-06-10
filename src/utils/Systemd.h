#ifndef SYSTEMD_H
#define SYSTEMD_H

#include <string>
#include <systemd/sd-bus.h>

#include <LNamespaces.h>

using namespace Louvre;

class Systemd
{
public:
    Systemd() noexcept;
    ~Systemd();

    sd_bus *bus { nullptr };
    Int32 busFd { -1 };
    wl_event_source *eventSource { nullptr };

    UInt32 xdgDesktopPortalWlrPID { 0 };

    UInt32 getServiceMainPID(const std::string &serviceName) noexcept;
    bool restartUserService(const std::string &serviceName) noexcept;
    bool restartXdgDesktopPortal() noexcept;
    static Int32 serviceEventHandler(sd_bus_message *m, void *userdata, sd_bus_error *retError);
};

#endif // SYSTEMD_H
