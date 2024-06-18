#include <LPointerButtonEvent.h>
#include <LPointerMoveEvent.h>
#include <LTouchDownEvent.h>
#include <LPointer.h>
#include <LKeyboard.h>
#include <LSeat.h>
#include <LCursor.h>
#include <LTouch.h>
#include <LTouchPoint.h>

#include "SSDTouchable.h"
#include "SSD.h"
#include "../roles/ToplevelRole.h"
#include "../utils/Global.h"
#include "../utils/Assets.h"

SSDTouchable::SSDTouchable(SSD *ssd, ButtonType buttonType, LBitset<LEdge> edge, LView *parent) noexcept :
    LSolidColorView(parent),
    edge(edge),
    buttonType(buttonType),
    ssd(ssd)
{
    enablePointerEvents(true);
    enableTouchEvents(true);

    // Buttons
    if (edge == 0)
    {
        if (buttonType == Close)
            setColor({1.f, 0.f, 0.f});
        else if (buttonType == Maximize)
            setColor({0.f, 1.f, 0.f});
        else // Minimize
            setColor({1.f, 1.f, 0.f});

        enableParentOpacity(false);
    }
    else
        setUserData(G::SSDEdge);
}

void SSDTouchable::pointerButtonEvent(const LPointerButtonEvent &event)
{
    seat()->pointer()->setFocus(ssd->toplevel->surface());
    seat()->keyboard()->setFocus(ssd->toplevel->surface());
    ssd->toplevel->surface()->raise();

    // Button
    if (edge == 0)
    {
        if (event.state() == LPointerButtonEvent::Released)
        {
            if (buttonType == Close)
                ssd->toplevel->close();
            else if (buttonType == Maximize)
            {
                if (ssd->toplevel->maximized())
                    ssd->toplevel->unsetMaximizedRequest();
                else
                    ssd->toplevel->setMaximizedRequest();
            }
            else // Minimize
                ssd->toplevel->setMinimizedRequest();

            setColorFactor({1.f, 1.f, 1.f, 1.f});
        }
    }

    if (ssd->toplevel->fullscreen())
        return;

    // Topbar
    if (edge == LEdgeTop)
    {
        if (cursor()->pos().x() - pos().x() <= ssd->toplevel->extraGeometry().left)
            ssd->toplevel->startResizeRequest(event, LEdgeLeft | LEdgeTop);
        else if (cursor()->pos().x() >= pos().x() + size().w() - ssd->toplevel->extraGeometry().right)
            ssd->toplevel->startResizeRequest(event, LEdgeRight | LEdgeTop);
        else if (cursor()->pos().y() <= pos().y() + ssd->toplevel->extraGeometry().top/4)
            ssd->toplevel->startResizeRequest(event, LEdgeTop);
        else
            ssd->toplevel->startMoveRequest(event);
    }
    // Edges / corners
    else
    {
        ssd->toplevel->startResizeRequest(event, edge);
    }
}

void SSDTouchable::pointerEnterEvent(const LPointerEnterEvent &/*event*/)
{
    // Button
    if (edge == 0)
        setColorFactor({0.5f, 0.5f, 0.5f, 1.f});
}

void SSDTouchable::pointerLeaveEvent(const LPointerLeaveEvent &/*event*/)
{
    // Button
    if (edge == 0)
        setColorFactor({1.f, 1.f, 1.f, 1.f});
}

void SSDTouchable::pointerMoveEvent(const LPointerMoveEvent &/*event*/)
{
    if (!seat()->toplevelMoveSessions().empty() || !seat()->toplevelResizeSessions().empty() || ssd->toplevel->fullscreen())
        return;

    /* Update cursor icon */
    if (edge == LEdgeTop)
    {
        if (cursor()->pos().x() - pos().x() <= ssd->toplevel->extraGeometry().left)
            cursor()->setCursor(G::assets()->cursors.resizeTL.get());
        else if (cursor()->pos().x() >= pos().x() + size().w() - ssd->toplevel->extraGeometry().right)
            cursor()->setCursor(G::assets()->cursors.resizeTR.get());
        else if (cursor()->pos().y() <= pos().y() + ssd->toplevel->extraGeometry().top/4)
            cursor()->setCursor(G::assets()->cursors.resizeT.get());
        else
            cursor()->useDefault();
    }
    else if (edge == LEdgeLeft)
        cursor()->setCursor(G::assets()->cursors.resizeL.get());
    else if (edge == LEdgeRight)
        cursor()->setCursor(G::assets()->cursors.resizeR.get());
    else if (edge == LEdgeBottom)
        cursor()->setCursor(G::assets()->cursors.resizeB.get());
    else if (edge == (LEdgeBottom | LEdgeLeft))
        cursor()->setCursor(G::assets()->cursors.resizeBL.get());
    else if (edge == (LEdgeBottom | LEdgeRight))
        cursor()->setCursor(G::assets()->cursors.resizeBR.get());
}

void SSDTouchable::touchDownEvent(const LTouchDownEvent &event)
{
    auto tp = seat()->touch()->createOrGetTouchPoint(event);
    tp->sendDownEvent(event, ssd->toplevel->surface());
    ssd->toplevel->surface()->raise();

    if (edge == LEdgeTop)
        ssd->toplevel->startMoveRequest(event);
    else if (edge == LEdgeLeft || edge == LEdgeBottom || edge == LEdgeRight)
        ssd->toplevel->startResizeRequest(event, edge);

    tp->sendDownEvent(event, nullptr);
}

bool SSDTouchable::nativeMapped() const noexcept
{
    return !ssd->toplevel->fullscreen();
}
