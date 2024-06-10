#ifndef SCENE_H
#define SCENE_H

#include <LScene.h>
#include "LayerView.h"

using namespace Louvre;

/* This single scene, hosted within the Compositor class, is used to render
 * all views on every initialized output and handle input events.
 *
 * It contains a mainView() and five child layer views, following the same structure
 * as the Louvre surface layers concept.
 *
 * For more details, see LSurfaceLayer and the "Order" section of the LSurface class documentation.
 */
class Scene final : public LScene
{
public:
    Scene() noexcept;

    /* Background, Bottom, Middle, Top and Overlay layers. */
    LayerView layers[5];
};

#endif // SCENE_H
