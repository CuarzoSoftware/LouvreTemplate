#ifndef SOLIDCOLORBUTTONVIEW_H
#define SOLIDCOLORBUTTONVIEW_H

#include <LSolidColorView.h>
#include <LEdge.h>
#include <LWeak.h>

using namespace Louvre;

class ToplevelDecorationView;

/* Used for toplevel decoration edges, titlebar and buttons */

class SolidColorButtonView final : public LSolidColorView
{
public:

    enum ButtonType
    {
        Edge,
        Close,
        Maximize
    };

    SolidColorButtonView(ToplevelDecorationView *ssd, ButtonType buttonType, LBitset<LEdge> edge, LView *parent = nullptr) noexcept;

    // If 0 == Titlebar button, Top == Titlebar, else window edges
    LBitset<LEdge> edge;
    ButtonType buttonType;
    LWeak<ToplevelDecorationView> ssd;

    void pointerButtonEvent(const LPointerButtonEvent &event) override;
    void pointerEnterEvent(const LPointerEnterEvent &event) override;
    void pointerLeaveEvent(const LPointerLeaveEvent &event) override;
    void pointerMoveEvent(const LPointerMoveEvent &event) override;

    void touchDownEvent(const LTouchDownEvent &event) override;

    bool nativeMapped() const noexcept override;
};

#endif // SOLIDCOLORBUTTONVIEW_H
