#ifndef SURFACE_H
#define SURFACE_H

#include <LSurface.h>
#include "scene/SurfaceView.h"

using namespace Louvre;

class ToplevelRole;

class Surface final : public LSurface
{
public:
    using LSurface::LSurface;

    SurfaceView view { this };

    ToplevelRole *tl() noexcept
    {
        return (ToplevelRole*)toplevel();
    }

    LView *getView() noexcept;

    void roleChanged() override;
    void layerChanged() override;
    void orderChanged() override;
    void mappingChanged() override;
    void minimizedChanged() override;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // SURFACE_H
