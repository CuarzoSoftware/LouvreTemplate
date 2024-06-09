#include <LLayout.h>
#include "SurfaceView.h"
#include "LayerView.h"
#include "../Global.h"

SurfaceView::SurfaceView(Surface *surface) noexcept :
    LSurfaceView((LSurface*)surface, &G::layers()[LLayerMiddle])
{

}
