#ifndef SOLIDCOLORBUTTONVIEW_H
#define SOLIDCOLORBUTTONVIEW_H

#include <LSolidColorView.h>
#include <LEdge.h>
#include <LWeak.h>

using namespace Louvre;

class SSD;

/* Used for toplevel decoration edges, titlebar and buttons */

class SSDTouchable final : public LSolidColorView
{
public:

    enum ButtonType
    {
        Edge,
        Close,
        Maximize,
        Minimize
    };

    SSDTouchable(SSD *ssd, ButtonType buttonType, LBitset<LEdge> edge, LView *parent = nullptr) noexcept;

    // If 0 == Titlebar button, Top == Titlebar, else window edges
    LBitset<LEdge> edge;
    ButtonType buttonType;
    LWeak<SSD> ssd;

    void pointerButtonEvent(const LPointerButtonEvent &event) override;
    void pointerEnterEvent(const LPointerEnterEvent &event) override;
    void pointerLeaveEvent(const LPointerLeaveEvent &event) override;
    void pointerMoveEvent(const LPointerMoveEvent &event) override;

    void touchDownEvent(const LTouchDownEvent &event) override;

    bool nativeMapped() const noexcept override;
};

#endif // SOLIDCOLORBUTTONVIEW_H
