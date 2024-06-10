#ifndef SURFACEVIEW_H
#define SURFACEVIEW_H

#include <LSurfaceView.h>

using namespace Louvre;

class Surface;

/*
 * This is used as the primary view for a surface.
 * While the base LSurfaceView class could have been directly used, this subclass is provided
 * in case there's a need to override its behavior.
 */
class SurfaceView final : public LSurfaceView
{
public:
    SurfaceView(Surface *surface) noexcept;
};

#endif // SURFACEVIEW_H
