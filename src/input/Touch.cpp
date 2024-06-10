#include <LCursor.h>
#include <LTouchDownEvent.h>
#include <LTouchMoveEvent.h>
#include "../utils/Global.h"
#include "../utils/Settings.h"
#include "../scene/Scene.h"
#include "Touch.h"

/* Touch point positions are in the [0.0, 1.0] range for both x and y axes.
 * There is no direct way to determine which output a touch screen belongs to.
 * This implementation maps the touch point positions to the output where
 * the cursor is currently positioned using toGlobal().
 * You could use the input device information of each touch event to associate it
 * with a particular output. */

void Touch::touchDownEvent(const LTouchDownEvent &event)
{
    LOutput *activeOutput { cursor()->output() };

    if (!activeOutput)
        return;

    const LPointF globalPos { toGlobal(activeOutput, event.pos()) };
    G::scene().handleTouchDownEvent(event, globalPos, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Touch::touchMoveEvent(const LTouchMoveEvent &event)
{
    LOutput *activeOutput { cursor()->output() };

    if (!activeOutput)
        return;

    const LPointF globalPos { toGlobal(activeOutput, event.pos()) };
    G::scene().handleTouchMoveEvent(event, globalPos, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Touch::touchUpEvent(const LTouchUpEvent &event)
{
    G::scene().handleTouchUpEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Touch::touchFrameEvent(const LTouchFrameEvent &event)
{
    G::scene().handleTouchFrameEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}

void Touch::touchCancelEvent(const LTouchCancelEvent &event)
{
    G::scene().handleTouchCancelEvent(event, SETTINGS_SCENE_EVENT_OPTIONS);
}
