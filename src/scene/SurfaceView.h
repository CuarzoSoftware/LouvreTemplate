#ifndef SURFACEVIEW_H
#define SURFACEVIEW_H

#include <LSurfaceView.h>

using namespace Louvre;

class Surface;

/*
 * This subclass serves as the primary view for a surface. While the base 
 * LSurfaceView class could have been used directly, this subclass is provided 
 * for cases where there's a need to override its behavior. For example, here 
 * we override the nativeMapped() method to display only surfaces from the 
 * locking-client when the session is locked.
 */
class SurfaceView final : public LSurfaceView
{
public:
    SurfaceView(Surface *surface) noexcept;

    bool nativeMapped() const noexcept override;
};

#endif // SURFACEVIEW_H
