#include "Global.h"
#include "../Compositor.h"

Scene &G::scene() noexcept
{
    return compositor()->scene;
}

LayerView *G::layers() noexcept
{
    return scene().layers;
}

Assets *G::assets() noexcept
{
    return compositor()->assets.get();
}

Systemd *G::systemd() noexcept
{
    return compositor()->systemd.get();
}
