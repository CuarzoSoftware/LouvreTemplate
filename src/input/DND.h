#ifndef DND_H
#define DND_H

#include <LDND.h>

using namespace Louvre;

/* Drag & drop session manager */

class DND final : public LDND
{
public:
    using LDND::LDND;

private:
    void startDragRequest() override;
    void cancelled() override;
    void dropped() override;
};

#endif // DND_H
