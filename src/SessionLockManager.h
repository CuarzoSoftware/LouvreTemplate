#ifndef SESSIONLOCKMANAGER_H
#define SESSIONLOCKMANAGER_H

#include <LSessionLockManager.h>

using namespace Louvre;

/* 
 * This class allows you to accept or deny client requests to lock the session
 * based on what you return inside the lockRequest() method.
 *
 * It also notifies you when the session is locked, unlocked, or deadlocked (when the locking-client terminates).
 * 
 * When a client locks the user session, all outputs should be blacked out, preventing
 * any open apps or user content from being displayed. The locking client creates a SessionLockRole surface for
 * each initialized output (see LOutput::sessionLockRole()) which covers the entire output area. 
 * These surfaces typically display a password input to allow the user to unlock the session.
 * While the session is locked, only surfaces from the locking client should be displayed, which is why we
 * override the SurfaceView::nativeMapped() method.
 * 
 * If the locking client dies, the session remains locked and the state() changes to DeadLocked.
 * In such cases, the compositor should launch another locking client or provide its own user
 * authentication mechanisms and call forceUnlock().
 */
class SessionLockManager final : public LSessionLockManager
{
public:
    using LSessionLockManager::LSessionLockManager;

private:
    bool lockRequest(LClient *client) override;
    void stateChanged() override;
};

#endif // SESSIONLOCKMANAGER_H
