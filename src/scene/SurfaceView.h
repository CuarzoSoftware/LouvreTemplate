#ifndef SURFACEVIEW_H
#define SURFACEVIEW_H

#include <LSurfaceView.h>

using namespace Louvre;

class Surface;

/* We create a SurfaceView for each Surface.*/
class SurfaceView final : public LSurfaceView
{
public:
    SurfaceView(Surface *surface) noexcept;
};

#endif // SURFACEVIEW_H
