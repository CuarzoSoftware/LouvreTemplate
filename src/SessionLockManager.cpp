#include <LTouchCancelEvent.h>
#include <LSessionLockRole.h>
#include <LLauncher.h>
#include <LOutput.h>
#include <LCursor.h>
#include <LSeat.h>
#include <LClipboard.h>
#include <LKeyboard.h>
#include <LPointer.h>
#include <LTouch.h>
#include <LDND.h>

#include "SessionLockManager.h"
#include "utils/Settings.h"

bool SessionLockManager::lockRequest(LClient *client)
{
    L_UNUSED(client);

    /* Allow all requests by default. */

    return true;
}

void SessionLockManager::stateChanged()
{
    switch (state())
    {
    case Unlocked:
        break;
    case Locked:
        seat()->dnd()->cancel();
        seat()->touch()->sendCancelEvent(LTouchCancelEvent());
        seat()->keyboard()->setGrab(nullptr);
        seat()->pointer()->setDraggingSurface(nullptr);

        if (cursor()->output() && cursor()->output()->sessionLockRole())
        {
            seat()->pointer()->setFocus(cursor()->output()->sessionLockRole()->surface());
            seat()->keyboard()->setFocus(cursor()->output()->sessionLockRole()->surface());
        }
        else
        {
            seat()->pointer()->setFocus(nullptr);
            seat()->keyboard()->setFocus(nullptr);
        }
        break;

    /* The locking-client died, let's launch it again */
    case DeadLocked:
        LLauncher::launch(SETTINGS_SESSION_LOCK_CLIENT);
        break;
    }
}
