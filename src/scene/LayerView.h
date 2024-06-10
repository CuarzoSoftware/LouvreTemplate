#ifndef LAYER_H
#define LAYER_H

#include <LLayerView.h>

using namespace Louvre;

/*
 * This is used for the background, bottom, middle, top, and overlay layers.
 * While the base LLayerView class could have been directly used, this subclass is provided
 * in case there's a need to override its behavior.
 */
class LayerView final : public LLayerView
{
public:
    using LLayerView::LLayerView;
};

#endif // LAYER_H
