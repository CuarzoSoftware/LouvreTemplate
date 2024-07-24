#ifndef SURFACE_H
#define SURFACE_H

#include <LSurface.h>
#include "scene/SurfaceView.h"

using namespace Louvre;

class ToplevelRole;

/* 
 * Surfaces in Wayland are the core components of windows. Essentially, they provide 
 * a texture that can be rendered, along with additional properties such as the 
 * size, scale factor of the texture, input and damage regions, and more.
 *
 * A surface alone is useless as the compositor doesn't know how to position, render, 
 * or interact with it. This is where surface roles come into play. Roles define the 
 * type of window a surface represents, such as a popup, toplevel window, drag & drop 
 * icon, etc. Check the roles directory.
 *
 * Note: Each role provides unique semantics, so please refer to the LSurface class 
 * documentation for details.
 *
 * You can render a surface using OpenGL or LPainter. However, in this case, we use a 
 * SurfaceView which inherits all surface properties to render it efficiently within our scene. 
 * The scene repaints only damaged regions, prevents rendering stuff behind opaque areas, and so forth. 
 * You can modify properties like position, scale, clipping, opacity, and nearly any other property. 
 * Refer to the LView or LSurfaceView documentation for details.
 *
 * Surfaces with the toplevel role and using server-side decorations provide a custom container 
 * for the "view", thats why we added the getView() method. See the ToplevelRole class.
 */
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
    bool hasMappedChildSurface() const noexcept;

    void roleChanged() override;
    void layerChanged() override;
    void orderChanged() override;
    void mappingChanged() override;
    void minimizedChanged() override;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // SURFACE_H
