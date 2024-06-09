#include <LScreenshotRequest.h>
#include "Compositor.h"
#include "Output.h"
#include "Global.h"

void Output::initializeGL()
{
    G::scene().handleInitializeGL(this);
}

void Output::paintGL()
{
    G::scene().handlePaintGL(this);

    /* Screen capture requests for this single frame */
    for (LScreenshotRequest *req : screenshotRequests())
        req->accept(true);
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
