#ifndef CURSORROLE_H
#define CURSORROLE_H

#include <LCursorRole.h>

using namespace Louvre;

/*
 * Used by clients to set the cursor icon and hotspot.
 *
 * See Pointer::setCursorRequest(), LClientCursor and LCursor.
 */
class CursorRole final : public LCursorRole
{
public:
    using LCursorRole::LCursorRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // CURSORROLE_H
