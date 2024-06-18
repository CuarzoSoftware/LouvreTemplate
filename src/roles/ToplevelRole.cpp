#include <LCursor.h>
#include <LOutput.h>
#include "ToplevelRole.h"
#include "../Surface.h"
#include "../utils/Settings.h"

ToplevelRole::ToplevelRole(const void *params) noexcept : LToplevelRole(params)
{
    moveSession().setOnBeforeUpdateCallback([](LToplevelMoveSession *session)
    {
        LMargins constraints { session->toplevel()->calculateConstraintsFromOutput(cursor()->output()) };

        if (constraints.bottom != LEdgeDisabled)
        {
            constraints.bottom += session->toplevel()->windowGeometry().size().h()
                + session->toplevel()->extraGeometry().top
                + session->toplevel()->extraGeometry().bottom
                - 50; // Prevents it from end up unreachable behind a bottom panel
        }
        session->setConstraints(constraints);
    });

    resizeSession().setOnBeforeUpdateCallback([](LToplevelResizeSession *session)
    {
        LMargins constraints { session->toplevel()->calculateConstraintsFromOutput(cursor()->output()) };
        session->setConstraints(constraints);
    });
}

const LPoint &ToplevelRole::rolePos() const
{
    m_rolePos = surface()->pos() - windowGeometry().topLeft() + LPoint(extraGeometry().left, extraGeometry().top);
    return m_rolePos;
}

void ToplevelRole::configureRequest()
{
    LOutput *output { cursor()->output() };

#ifdef SETTINGS_SSD
    if (supportServerSideDecorations())
    {
        setExtraGeometry(SETTINGS_SSD_EXTRA_GEOMETRY);
        configureDecorationMode(ServerSide);
    }
#endif

    if (output)
    {
        surface()->sendOutputEnterEvent(output);
        configureBounds(
            output->availableGeometry().size()
            - LSize(extraGeometry().left + extraGeometry().right, extraGeometry().top + extraGeometry().bottom));
    }
    else
        configureBounds(0, 0);

    configureSize(0,0);
    configureState(pendingConfiguration().state | Activated);
    configureCapabilities(WindowMenuCap | FullscreenCap | MaximizeCap | MinimizeCap);
}

void ToplevelRole::startMoveRequest(const LEvent &triggeringEvent)
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::startMoveRequest(triggeringEvent);
}

void ToplevelRole::startResizeRequest(const LEvent &triggeringEvent, LBitset<LEdge> edges)
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::startResizeRequest(triggeringEvent, edges);
}

void ToplevelRole::setMaximizedRequest()
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::setMaximizedRequest();
}

void ToplevelRole::unsetMaximizedRequest()
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::unsetMaximizedRequest();
}

void ToplevelRole::setFullscreenRequest(LOutput *output)
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::setFullscreenRequest(output);
}

void ToplevelRole::unsetFullscreenRequest()
{
    /* Refer to the default implementation in the documentation. */
    LToplevelRole::unsetFullscreenRequest();
}

void ToplevelRole::setMinimizedRequest()
{
    surface()->setMinimized(true);
}

void ToplevelRole::showWindowMenuRequest(const LEvent &triggeringEvent, Int32 x, Int32 y)
{
    L_UNUSED(triggeringEvent)
    L_UNUSED(x)
    L_UNUSED(y)
}

void ToplevelRole::atomsChanged(LBitset<AtomChanges> changes, const Atoms &prev)
{
    surface()->repaintOutputs();

    LBitset<State> stateChanges;
    bool updateSSD { false };

    if (changes.check(DecorationModeChanged))
    {
        if (decorationMode() == ServerSide)
            ssd = std::make_unique<SSD>(this);
        else
            ssd.reset();
    }

    if (changes.check(WindowGeometryChanged) && ssd)
        updateSSD = true;

    if (!changes.check(StateChanged))
        goto skip;

    stateChanges = state() ^ prev.state;

    if (stateChanges.check(Activated))
        updateSSD = true;

    if (stateChanges.check(Maximized))
    {
        if (maximized())
        {
            if (exclusiveOutput())
            {
                surface()->raise();
                surface()->setPos(exclusiveOutput()->pos() + exclusiveOutput()->availableGeometry().pos());
                surface()->setMinimized(false);
            }
            else
            {
                configureSize(0, 0);
                configureState(pendingConfiguration().state & ~Maximized);
            }
        }
        else if (!resizing())
        {
            surface()->setPos(prevRect.pos());
        }
    }

    if (stateChanges.check(Fullscreen))
    {
        if (fullscreen())
        {
            if (exclusiveOutput())
            {
                surface()->setPos(exclusiveOutput()->pos());
                surface()->raise();
#ifdef SETTINGS_SSD
                if (ssd)
                {
                    setExtraGeometry({0,0,0,0});
                    updateSSD = true;
                }
#endif
            }
            else
            {
                configureSize(0, 0);
                configureState(pendingConfiguration().state & ~Fullscreen);
            }
        }
        else
        {
#ifdef SETTINGS_SSD
            if (ssd)
            {
                setExtraGeometry(SETTINGS_SSD_EXTRA_GEOMETRY);
                updateSSD = true;
            }
#endif
            surface()->setPos(prevRect.pos());
        }
    }

    if (stateChanges.check(Fullscreen | Maximized) && !pendingConfiguration().state.check(Fullscreen | Maximized))
        setExclusiveOutput(nullptr);

skip:
    if (ssd && updateSSD)
        ssd->updateGeometry();
}

void ToplevelRole::titleChanged()
{
    /* See title() */
}

void ToplevelRole::appIdChanged()
{
    /* See appId() */
}

void ToplevelRole::preferredDecorationModeChanged()
{
    /* configureDecorationMode(preferredDecorationMode()); */
}
