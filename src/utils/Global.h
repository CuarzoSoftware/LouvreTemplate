#ifndef GLOBAL_H
#define GLOBAL_H

#include <LNamespaces.h>

using namespace Louvre;

class Compositor;
class Output;
class Scene;
class LayerView;
class Assets;
class Systemd;
class Seat;

/* This is just a utility for quick access to the Compositor members and
 * to prevent type casting all the time */
class G
{
public:

    enum ViewHint
    {
        SSDEdge = 1
    };

    static Compositor *compositor() noexcept
    {
        return (Compositor*)Louvre::compositor();
    }

    static Seat *seat() noexcept
    {
        return (Seat*)Louvre::seat();
    }

    static Scene &scene() noexcept;
    static LayerView *layers() noexcept;
    static Assets *assets() noexcept;
    static Systemd *systemd() noexcept;
};

#endif // GLOBAL_H
