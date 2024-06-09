#ifndef SURFACE_H
#define SURFACE_H

#include <LSurface.h>
#include "scene/SurfaceView.h"

using namespace Louvre;

class ToplevelRole;

class Surface final : public LSurface
{
public:
    Surface(const void *params) noexcept;
    SurfaceView view { this };

    ToplevelRole *tl() noexcept
    {
        return (ToplevelRole*)toplevel();
    }

    LView *getView() noexcept;

    void roleChanged() override;
    void layerChanged() override;
    void orderChanged() override;
};

#endif // SURFACE_H
