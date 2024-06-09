#include "Global.h"
#include "Surface.h"
#include "scene/LayerView.h"
#include "roles/ToplevelRole.h"

Surface::Surface(const void *params) noexcept : LSurface(params)
{

}

LView *Surface::getView() noexcept
{
    if (tl() && tl()->ssd)
        return tl()->ssd.get();

    return &view;
}

void Surface::roleChanged()
{
    /* When a client assigns the LCursorRole to a surface, we use LCursor to render it
     * instead of the scene, so we hide the view here.
     * See Pointer::setCursorRequest() and the documentation for LClientCursor and LCursor. */
    if (cursorRole())
        view.setVisible(false);
}

/* Louvre already manages the Z-axis ordering of all surfaces for us, ensuring that the order specified
 * in each role protocol is respected. See LCompositor::surfaces() and LCompositor::layer().
 * Since we are using the scene system, we need to update the order of our views manually.
 * This can be accomplished as shown in both event listeners below.
 * Note: You're of course free to not follow this order, but you probably should. */
void Surface::layerChanged()
{
    getView()->setParent(&G::layers()[layer()]);
}

void Surface::orderChanged()
{
    /* Previous surface in LCompositor::surfaces() */
    Surface *prev { static_cast<Surface*>(prevSurface()) };

    /* Re-insert the view only if there is a previous surface within the same layer */
    getView()->insertAfter((prev && prev->layer() == layer()) ? prev->getView() : nullptr);
}
