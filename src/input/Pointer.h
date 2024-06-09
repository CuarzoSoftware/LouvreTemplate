#ifndef POINTER_H
#define POINTER_H

#include <LPointer.h>

using namespace Louvre;

class Pointer final : public LPointer
{
public:
    Pointer(const void *params) noexcept;

    void pointerMoveEvent(const LPointerMoveEvent &event) override;
    void pointerButtonEvent(const LPointerButtonEvent &event) override;
    void pointerScrollEvent(const LPointerScrollEvent &event) override;

    void pointerSwipeBeginEvent(const LPointerSwipeBeginEvent &event) override;
    void pointerSwipeUpdateEvent(const LPointerSwipeUpdateEvent &event) override;
    void pointerSwipeEndEvent(const LPointerSwipeEndEvent &event) override;

    void pointerPinchBeginEvent(const LPointerPinchBeginEvent &event) override;
    void pointerPinchUpdateEvent(const LPointerPinchUpdateEvent &event) override;
    void pointerPinchEndEvent(const LPointerPinchEndEvent &event) override;

    void pointerHoldBeginEvent(const LPointerHoldBeginEvent &event) override;
    void pointerHoldEndEvent(const LPointerHoldEndEvent &event) override;

    void setCursorRequest(const LClientCursor &clientCursor) override;
};

#endif // POINTER_H
