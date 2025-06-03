#include <LDND.h>
#include <LCursor.h>
#include <LClientCursor.h>
#include <LClient.h>
#include "Pointer.h"
#include "../utils/Global.h"
#include "../utils/Settings.h"
#include "../scene/Scene.h"
#include "../utils/Assets.h"

Pointer::Pointer(const void *params) noexcept : LPointer(params) {}

void Pointer::pointerMoveEvent(const LPointerMoveEvent &event)
{
    G::scene().handlePointerMoveEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);

    if (seat()->dnd()->dragging() && seat()->dnd()->triggeringEvent().type() != LEvent::Type::Touch)
    {
        if (seat()->dnd()->action() == LDND::Copy)
            cursor()->setCursor(G::assets()->cursors.copy.get());
        else if (seat()->dnd()->action() == LDND::Move || seat()->dnd()->action() == LDND::Ask)
            cursor()->setCursor(G::assets()->cursors.drag.get());
        else if (seat()->dnd()->action() == LDND::NoAction)
            cursor()->setCursor(G::assets()->cursors.denied.get());

        /*
         * Some clients update the cursor during DND sessions, but not always
         * cursor()->setCursor(seat()->dnd()->origin()->client()->lastCursorRequest()); */

        return;
    }

    /* Normally, we should restore the cursor if no surface is focused. However, during
     * toplevel move or resize sessions, clients typically update the cursor to indicate
     * the edge or corner being resized, but the cursor position might move outside the surface,
     * causing it to lose focus.*/

    if (!seat()->toplevelMoveSessions().empty() || !seat()->toplevelResizeSessions().empty())
        return;

    if (!G::scene().pointerFocus().empty() && G::scene().pointerFocus().front()->userData() == G::SSDEdge)
        return;

    if (focus() && focus()->layer() != Louvre::LLayerBackground)
        cursor()->setCursor(focus()->client()->lastCursorRequest());
    else
    {
        cursor()->useDefault();
        cursor()->setVisible(true);
    }
}

void Pointer::pointerButtonEvent(const LPointerButtonEvent &event)
{
    G::scene().handlePointerButtonEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerScrollEvent(const LPointerScrollEvent &event)
{
    G::scene().handlePointerScrollEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerSwipeBeginEvent(const LPointerSwipeBeginEvent &event)
{
    G::scene().handlePointerSwipeBeginEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerSwipeUpdateEvent(const LPointerSwipeUpdateEvent &event)
{
    G::scene().handlePointerSwipeUpdateEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerSwipeEndEvent(const LPointerSwipeEndEvent &event)
{
    G::scene().handlePointerSwipeEndEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerPinchBeginEvent(const LPointerPinchBeginEvent &event)
{
    G::scene().handlePointerPinchBeginEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerPinchUpdateEvent(const LPointerPinchUpdateEvent &event)
{
    G::scene().handlePointerPinchUpdateEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerPinchEndEvent(const LPointerPinchEndEvent &event)
{
    G::scene().handlePointerPinchEndEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerHoldBeginEvent(const LPointerHoldBeginEvent &event)
{
    G::scene().handlePointerHoldBeginEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::pointerHoldEndEvent(const LPointerHoldEndEvent &event)
{
    G::scene().handlePointerHoldEndEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Pointer::setCursorRequest(const LClientCursor &clientCursor)
{
    if (!seat()->toplevelMoveSessions().empty() || !seat()->toplevelResizeSessions().empty())
        return;

    if (seat()->dnd()->dragging() && seat()->dnd()->triggeringEvent().type() != LEvent::Type::Touch)
        return;

    /* Allows to set the cursor only if one of its surfaces has pointer focus */
    if (focus() && focus()->client() == clientCursor.client())
        cursor()->setCursor(clientCursor);
}
