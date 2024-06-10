#include <LScreenshotRequest.h>
#include <LAnimation.h>
#include "Compositor.h"
#include "Output.h"
#include "utils/Global.h"

void Output::initializeGL()
{
    G::scene().handleInitializeGL(this);

    /* Fade-in animation example */

    LWeak<Output> weakRef { this };
    fadeInView.insertAfter(&G::layers()[LLayerOverlay]);
    fadeInView.setOpacity(0.f);

    LAnimation::oneShot(1000, // Ms
    [weakRef](LAnimation *anim) // On Update
    {
        // Oops the output was probably unplugged!
        if (!weakRef)
        {
            anim->stop();
            return;
        }

        weakRef->fadeInView.setPos(weakRef->pos());
        weakRef->fadeInView.setSize(weakRef->size());
        weakRef->fadeInView.setOpacity(1.f - powf(anim->value(), 5.f));
        weakRef->repaint();
    },
    [weakRef](LAnimation *) // On Finish
    {
        // Remove it from the scene
        if (weakRef)
            weakRef->fadeInView.setParent(nullptr);
    });
}

void Output::paintGL()
{
    G::scene().handlePaintGL(this);

    /* Screen capture requests for this single frame */
    for (LScreenshotRequest *req : screenshotRequests())
        req->accept(true);

    /*
     * V-SYNC:
     *
     * Clients can suggest enabling or disabling v-sync for specific surfaces using LSurface::preferVSync().
     * For instance, you may choose to enable or disable it when displaying a toplevel surface in fullscreen mode.
     * Refer to enableVSync() for more information.
     */

    /*
     * Oversampling:
     *
     * When you assign a fractional scale to an output, oversampling is enabled by default to mitigate aliasing artifacts,
     * but this may impact performance.
     * For instance, you might want to switch off oversampling when displaying a fullscreen top-level window. Refer to enableFractionalOversampling().
     *
     * Note: Oversampling is unnecessary and always disabled when using integer scales. Therefore, it's recommended to stick with integer scales
     * and select an appropriate LOutputMode that suits your requirements.
     */
}

void Output::moveGL()
{
    G::scene().handleMoveGL(this);
}

void Output::resizeGL()
{
    G::scene().handleResizeGL(this);
}

void Output::uninitializeGL()
{
    G::scene().handleUninitializeGL(this);
}

void Output::setGammaRequest(LClient *client, const LGammaTable *gamma)
{
    L_UNUSED(client)
    setGamma(gamma);
}

void Output::availableGeometryChanged()
{
    /* Refer to the default implementation in the documentation. */
    LOutput::availableGeometryChanged();
}
