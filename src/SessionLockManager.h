#ifndef SESSIONLOCKMANAGER_H
#define SESSIONLOCKMANAGER_H

#include <LSessionLockManager.h>

using namespace Louvre;

/* Handles client requests to lock the user session */

class SessionLockManager final : public LSessionLockManager
{
public:
    using LSessionLockManager::LSessionLockManager;

private:
    bool lockRequest(LClient *client) override;
    void stateChanged() override;
};

#endif // SESSIONLOCKMANAGER_H
