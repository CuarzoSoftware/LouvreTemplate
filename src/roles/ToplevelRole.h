#ifndef TOPLEVELROLE_H
#define TOPLEVELROLE_H

#include <LToplevelRole.h>
#include "../scene/ToplevelDecorationView.h"

using namespace Louvre;

class Surface;

class ToplevelRole final : public LToplevelRole
{
public:
    using LToplevelRole::LToplevelRole;

    Surface *surf() noexcept
    {
        return (Surface*)surface();
    }

    std::unique_ptr<ToplevelDecorationView> ssd;

    void configureRequest() override;
    void startMoveRequest(const LEvent &triggeringEvent) override;
    void startResizeRequest(const LEvent &triggeringEvent, LBitset<LEdge> edges) override;

    void setMaximizedRequest() override;
    void unsetMaximizedRequest() override;

    void setFullscreenRequest(LOutput *output) override;
    void unsetFullscreenRequest() override;

    void setMinimizedRequest() override;

    void showWindowMenuRequest(const LEvent &triggeringEvent, Int32 x, Int32 y) override;

    void atomsChanged(LBitset<AtomChanges> changes, const Atoms &prev) override;
    void titleChanged() override;
    void appIdChanged() override;
    void preferredDecorationModeChanged() override;
};

#endif // TOPLEVELROLE_H
