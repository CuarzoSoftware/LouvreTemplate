#include <LCursor.h>
#include "Assets.h"

Assets::Assets() noexcept
{
    loadCursors();
}

void Assets::loadCursors() noexcept
{
    /* Sets the LCursor size in surface units.
     * Cursor textures and hotspots are automatically scaled to this size */
    cursor()->setSize(LSize(24, 24));

    const char *theme { nullptr };
    const Int32 sizeHint { 64 };

    /* Louvre has its own default arrow cursor, but we better load one from your system */
    cursors.arrow.reset(LXCursor::load("arrow", theme, sizeHint));

    /* Check the LCursor doc to see what replaceDefaultB() does */
    if (cursors.arrow)
        cursor()->replaceDefaultB(cursors.arrow->texture(), cursors.arrow->hotspotB());

    cursors.drag.reset(LXCursor::load("hand1", theme, sizeHint));
    cursors.copy.reset(LXCursor::load("copy", theme, sizeHint));
    cursors.denied.reset(LXCursor::load("no-drop", theme, sizeHint));


    /* For SSD toplevel resize sessions */
    cursors.resizeL.reset(LXCursor::load("left_side", theme, sizeHint));
    cursors.resizeT.reset(LXCursor::load("top_side", theme, sizeHint));
    cursors.resizeR.reset(LXCursor::load("right_side", theme, sizeHint));
    cursors.resizeB.reset(LXCursor::load("bottom_side", theme, sizeHint));

    cursors.resizeTL.reset(LXCursor::load("top_left_corner", theme, sizeHint));
    cursors.resizeTR.reset(LXCursor::load("top_right_corner", theme, sizeHint));
    cursors.resizeBR.reset(LXCursor::load("bottom_right_corner", theme, sizeHint));
    cursors.resizeBL.reset(LXCursor::load("bottom_left_corner", theme, sizeHint));
}
