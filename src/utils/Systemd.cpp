#include <LLog.h>
#include "Systemd.h"
#include "Global.h"
#include "../Compositor.h"

using namespace Louvre;

Systemd::Systemd() noexcept
{
    Int32 ret { sd_bus_open_user(&bus) };

    if (ret < 0)
    {
        LLog::error("Systemd: Failed to connect to the user bus: %s.", strerror(-ret));
        goto failOpen;
    }

    /* Check xdg-desktop-portal-wlr status changes */
    ret = sd_bus_add_match(bus,
                           NULL,
                           "type='signal',"
                           "sender='org.freedesktop.systemd1',"
                           "interface='org.freedesktop.systemd1.Manager',"
                           "member='UnitNew'",
                           serviceEventHandler,
                           this);

    if (ret < 0)
    {
        LLog::error("Systemd: Failed to add match: %s.", strerror(-ret));
        goto failMatch;
    }

    busFd = sd_bus_get_fd(bus);

    if (busFd < 0)
    {
        LLog::error("Failed to get bus file descriptor: %s\n", strerror(-busFd));
        goto failMatch;
    }

    eventSource = G::compositor()->addFdListener(busFd, this, [](Int32, UInt32, void *data) -> Int32 {

        Systemd *systemd { static_cast<Systemd*>(data) };

        Int32 ret;

        while ((ret = sd_bus_process(systemd->bus, NULL) > 0)) {}

        if (ret < 0)
            LLog::error("Failed to process bus: %s", strerror(-ret));

        return 0;
    });

    restartXdgDesktopPortal();
    return;

failMatch:
    sd_bus_unref(bus);
failOpen:
    bus = nullptr;
}

Systemd::~Systemd()
{
    if (eventSource)
        G::compositor()->removeFdListener(eventSource);

    if (bus)
        sd_bus_unref(bus);
}

UInt32 Systemd::getServiceMainPID(const std::string &serviceName) noexcept
{
    if (!bus)
        return 0;

    sd_bus_error error { SD_BUS_ERROR_NULL };
    sd_bus_message *reply { NULL };
    int ret { 0 };

    ret = sd_bus_call_method(bus,
                             "org.freedesktop.systemd1",
                             "/org/freedesktop/systemd1",
                             "org.freedesktop.systemd1.Manager",
                             "GetUnit",
                             &error,
                             &reply,
                             "s",
                             serviceName.c_str()
                             );

    if (ret < 0)
    {
        LLog::error("Systemd: Failed to call GetUnit method: %s.", error.message);
        sd_bus_error_free(&error);
        return 0;
    }

    const char *unitPath;
    ret = sd_bus_message_read(reply, "o", &unitPath);

    if (ret < 0)
    {
        LLog::fatal("Failed to read unit object path: %s.", strerror(-ret));
        sd_bus_message_unref(reply);
        return 0;
    }

    UInt32 pid;
    ret = sd_bus_get_property_trivial(bus,
                                      "org.freedesktop.systemd1",
                                      unitPath,
                                      "org.freedesktop.systemd1.Service",
                                      "MainPID",
                                      &error,
                                      'u',
                                      &pid
                                      );
    if (ret < 0)
    {
        LLog::error("Systemd: Failed to get service's MainPID: %s.", error.message);
        sd_bus_error_free(&error);
        sd_bus_message_unref(reply);
        return 0;
    }

    sd_bus_message_unref(reply);

    return pid;
}

bool Systemd::restartXdgDesktopPortal() noexcept
{
    if (!bus)
        return false;

    if (system("dbus-update-activation-environment --systemd WAYLAND_DISPLAY XDG_CURRENT_DESKTOP=wlroots") != 0)
        return false;

    sd_bus_message *reply { nullptr };
    Int32 ret = sd_bus_call_method(bus,
                             "org.freedesktop.systemd1",
                             "/org/freedesktop/systemd1",
                             "org.freedesktop.systemd1.Manager",
                             "RestartUnit",
                             NULL,
                             &reply,
                             "ss",
                             "xdg-desktop-portal.service",
                             "replace"
                             );
    if (ret < 0)
    {
        LLog::error("Systemd: Failed to restart xdg-desktop-portal.service: %s.", strerror(-ret));
        return false;
    }

    sd_bus_message_unref(reply);
    return true;
}

Int32 Systemd::serviceEventHandler(sd_bus_message *m, void *data, sd_bus_error */*retError*/)
{
    const char *unitName, *unitPath;
    Int32 ret = sd_bus_message_read(m, "so", &unitName, &unitPath);

    if (ret < 0)
    {
        LLog::error("Failed to read signal parameters: %s", strerror(-ret));
        return 0;
    }

    if (strcmp(unitName, "xdg-desktop-portal-wlr.service") != 0)
        return 0;

    Systemd *systemd { static_cast<Systemd*>(data) };
    sd_bus_error error { SD_BUS_ERROR_NULL };

    ret = sd_bus_get_property_trivial(systemd->bus,
                                      "org.freedesktop.systemd1",
                                      unitPath,
                                      "org.freedesktop.systemd1.Service",
                                      "MainPID",
                                      &error,
                                      'u',
                                      &systemd->xdgDesktopPortalWlrPID
                                      );
    if (ret < 0)
    {
        LLog::error("Systemd: Failed to get xdg-desktop-portal-wlr MainPID: %s.", error.message);
        sd_bus_error_free(&error);
        return 0;
    }

    return 0;
}
