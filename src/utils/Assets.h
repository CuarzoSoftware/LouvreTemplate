#ifndef ASSETS_H
#define ASSETS_H

#include <LXCursor.h>
#include <memory>

using namespace Louvre;

class Assets
{
public:

    Assets() noexcept;

    void loadCursors() noexcept;

    struct {
        std::unique_ptr<LXCursor> arrow;
        std::unique_ptr<LXCursor> copy;
        std::unique_ptr<LXCursor> drag;
        std::unique_ptr<LXCursor> denied;

        std::unique_ptr<LXCursor> resizeL;
        std::unique_ptr<LXCursor> resizeT;
        std::unique_ptr<LXCursor> resizeR;
        std::unique_ptr<LXCursor> resizeB;
        std::unique_ptr<LXCursor> resizeTL;
        std::unique_ptr<LXCursor> resizeTR;
        std::unique_ptr<LXCursor> resizeBR;
        std::unique_ptr<LXCursor> resizeBL;
    } cursors;
};

#endif // ASSETS_H
