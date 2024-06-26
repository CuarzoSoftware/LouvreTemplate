#include <LSessionLockManager.h>
#include <LLayout.h>
#include <LSurface.h>
#include "SurfaceView.h"
#include "LayerView.h"
#include "../utils/Global.h"

SurfaceView::SurfaceView(Surface *surface) noexcept :
    LSurfaceView((LSurface*)surface, &G::layers()[LLayerMiddle])
{}

bool SurfaceView::nativeMapped() const noexcept
{
    /* Keep the default implementation (it checks if surface() is nullptr, if the surface is mapped and so on) */
    return LSurfaceView::nativeMapped() && 

    /* If the session is locked, we only display surfaces from the locking-client */
    (sessionLockManager()->state() == LSessionLockManager::Unlocked
        || (sessionLockManager()->state() == LSessionLockManager::Locked 
            && sessionLockManager()->client() == surface()->client()));
}