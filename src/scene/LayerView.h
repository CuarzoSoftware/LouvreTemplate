#ifndef LAYER_H
#define LAYER_H

#include <LLayerView.h>

using namespace Louvre;

class LayerView final : public LLayerView
{
public:
    LayerView(LView *parent = nullptr) noexcept;
};

#endif // LAYER_H
