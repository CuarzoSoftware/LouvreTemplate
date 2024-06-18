#include "SSD.h"
#include "../roles/ToplevelRole.h"
#include "../Surface.h"
#include "../utils/Settings.h"

SSD::SSD(ToplevelRole *toplevel) noexcept :
    LLayerView(),
    toplevel(toplevel)
{
    toplevel->setExtraGeometry(SETTINGS_SSD_EXTRA_GEOMETRY);

    insertAfter(&toplevel->surf()->view);
    toplevel->surf()->view.setParent(this);
    toplevel->surf()->view.enableCustomPos(true);
    toplevel->surf()->view.setCustomPos(0, 0);

    const LSize buttonsSize { 8, 8 };

    close.setSize(buttonsSize);
    maximize.setSize(buttonsSize);
    minimize.setSize(buttonsSize);

    updateGeometry();
}

SSD::~SSD()
{
    toplevel->setExtraGeometry({
        .left = 0,
        .top = 0,
        .right = 0,
        .bottom = 0
    });

    toplevel->surf()->view.setParent(this->parent());
    toplevel->surf()->view.enableCustomPos(false);
}

void SSD::updateGeometry() noexcept
{
    const LMargins extraGeo { toplevel->extraGeometry() };
    setSize(toplevel->windowGeometry().size());

    titlebar.setPos(-extraGeo.left, -extraGeo.top);
    titlebar.setSize(size().width() + extraGeo.left + extraGeo.right, extraGeo.top);

    close.setPos(extraGeo.left, (extraGeo.top - close.size().h()) / 2);
    maximize.setPos(close.nativePos().x() + close.size().w() + extraGeo.left, close.nativePos().y());
    minimize.setPos(maximize.nativePos().x() + maximize.size().w() + extraGeo.left, maximize.nativePos().y());

    L.setSize(extraGeo.left, size().h());
    L.setPos(-extraGeo.left, 0);

    R.setSize(extraGeo.right, size().h());
    R.setPos(size().w(), 0);

    B.setSize(size().w(), extraGeo.bottom);
    B.setPos(0, size().h());

    BL.setSize(extraGeo.left, extraGeo.bottom);
    BL.setPos(-extraGeo.left, size().h());

    BR.setSize(extraGeo.right, extraGeo.bottom);
    BR.setPos(size().w(), size().h());

    LBitset<LToplevelRole::State> stateChanges { toplevel->state() ^ prevState };

    if (stateChanges.check(LToplevelRole::Activated))
    {
        LRGBAF color;

        if (toplevel->activated())
            color = SETTINGS_SSD_COLOR_ACTIVE;
        else
            color = SETTINGS_SSD_COLOR_INACTIVE;

        for (LView *child : children())
        {
            if (child->type() == LView::Type::SolidColorType)
            {
                static_cast<SSDTouchable*>(child)->setColor((const LRGBF&) color);
                static_cast<SSDTouchable*>(child)->setOpacity(color.a);
            }
        }
    }

    prevState = toplevel->state();
}

const LPoint &SSD::nativePos() const noexcept
{
    return toplevel->rolePos();
}

bool SSD::nativeMapped() const noexcept
{
    return toplevel->surface()->mapped();
}
