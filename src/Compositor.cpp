#include <protocols/ScreenCopy/GScreenCopyManager.h>
#include <LLauncher.h>
#include <LTimer.h>
#include <LGlobal.h>
#include <LClient.h>
#include "Compositor.h"
#include "Output.h"
#include "Surface.h"
#include "Settings.h"
#include "Global.h"
#include "Seat.h"

#include "roles/ToplevelRole.h"

#include "input/Pointer.h"
#include "input/Keyboard.h"
#include "input/Touch.h"

void Compositor::initialized()
{
    setenv("WAYLAND_DISPLAY", getenv("LOUVRE_WAYLAND_DISPLAY"), 1);

    assets = std::make_unique<Assets>();
    systemd = std::make_unique<Systemd>();

    /* Configure already plugged input devices, check the Seat class */
    G::seat()->configureInputDevices();

    Int32 totalWidth { 0 };

    // Initializes and arranges outputs from left to right
    for (LOutput *output : seat()->outputs())
    {
        // Sets a scale factor of 2 when DPI >= 200
        output->setScale(output->dpi() >= 200 ? 2.f : 1.f);

        // Change it if any of your displays is rotated/flipped
        output->setTransform(LTransform::Normal);

        output->setPos(LPoint(totalWidth, 0));
        totalWidth += output->size().w();
        addOutput(output);
        output->repaint();
    }

    /* Sets a background wallpaper using swaybg */;
    LLauncher::launch(std::string("swaybg -m fill -i ") + (compositor()->defaultAssetsPath() / "wallpaper.png").string());

    /* Launches Waybar */;
    LLauncher::launch("waybar");
}

void Compositor::uninitialized()
{
    /* All factory objects, client resources and backends are still available at this point.
     * Textures should be released here before the graphic backend is uninitialized */

    assets.reset();
    systemd.reset();
}

LFactoryObject *Compositor::createObjectRequest(LFactoryObject::Type objectType, const void *params)
{
    if (objectType == LFactoryObject::Type::LOutput)
        return new Output(params);

    if (objectType == LFactoryObject::Type::LSurface)
        return new Surface(params);

    if (objectType == LFactoryObject::Type::LToplevelRole)
        return new ToplevelRole(params);

    if (objectType == LFactoryObject::Type::LSeat)
        return new Seat(params);

    if (objectType == LFactoryObject::Type::LPointer)
        return new Pointer(params);

    if (objectType == LFactoryObject::Type::LKeyboard)
        return new Keyboard(params);

    if (objectType == LFactoryObject::Type::LTouch)
        return new Touch(params);

    /* Tells Louvre to use the default class for the given LFactoryObject type */
    return nullptr;
}

void Compositor::onAnticipatedObjectDestruction(LFactoryObject *object)
{
    L_UNUSED(object)

    /* Do not delete the object! */
}

bool Compositor::createGlobalsRequest()
{
    /* The default imp creates all globals supported by Louvre */
    return LCompositor::createGlobalsRequest();
}

bool Compositor::globalsFilter(LClient *client, LGlobal *global)
{

#ifdef SETTINGS_XDG_DESKTOP_PORTAL_SCREENCAST_ONLY
    if (global->isType<Protocols::ScreenCopy::GScreenCopyManager>() && systemd && systemd->xdgDesktopPortalWlrPID != 0)
    {
        pid_t clientPID;
        client->credentials(&clientPID);

        if ((UInt32)clientPID != systemd->xdgDesktopPortalWlrPID)
            return false;
    }
#endif

    return true;
}
