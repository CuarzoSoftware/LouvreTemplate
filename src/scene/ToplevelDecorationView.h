#ifndef TOPLEVELDECORATIONVIEW_H
#define TOPLEVELDECORATIONVIEW_H

#include <LToplevelRole.h>
#include <LLayerView.h>
#include <LSolidColorView.h>
#include <LWeak.h>
#include "SolidColorButtonView.h"
#include "../Settings.h"

using namespace Louvre;

class ToplevelRole;

/* Container for toplevel SSD */

class ToplevelDecorationView final : public LLayerView
{
public:
    ToplevelDecorationView(ToplevelRole *toplevel) noexcept;
    ~ToplevelDecorationView();

    void updateGeometry() noexcept;

    const LPoint &nativePos() const noexcept override;
    bool nativeMapped() const noexcept override;

    LWeak<ToplevelRole> toplevel;
    LBitset<LToplevelRole::State> prevState;

    SolidColorButtonView titlebar   { this, SolidColorButtonView::Edge, LEdgeTop, this };
    SolidColorButtonView close      { this, SolidColorButtonView::Close, 0, &titlebar };
    SolidColorButtonView maximize   { this, SolidColorButtonView::Maximize, 0, &titlebar };

    // Edges / corners
    SolidColorButtonView L  { this, SolidColorButtonView::Edge, LEdgeLeft, this };
    SolidColorButtonView BL { this, SolidColorButtonView::Edge, LEdgeLeft | LEdgeBottom, this };
    SolidColorButtonView B  { this, SolidColorButtonView::Edge, LEdgeBottom, this };
    SolidColorButtonView BR { this, SolidColorButtonView::Edge, LEdgeRight | LEdgeBottom, this };
    SolidColorButtonView R  { this, SolidColorButtonView::Edge, LEdgeRight, this };
};

#endif // TOPLEVELDECORATIONVIEW_H
