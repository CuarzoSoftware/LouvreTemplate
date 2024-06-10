#ifndef SESSIONLOCKROLE_H
#define SESSIONLOCKROLE_H

#include <LSessionLockRole.h>

using namespace Louvre;

/* Created by a session lock client for each initialized output.
 * The default implementation assigns it the same size and position
 * as the output it is assigned to. See exclusiveOutput() and LOutput::sessionLockRole().
 * If the client does not create one for a given output, the user
 * content should be hidden; for example, by blacking out the screen. */
class SessionLockRole final : public LSessionLockRole
{
public:
    using LSessionLockRole::LSessionLockRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // SESSIONLOCKROLE_H
