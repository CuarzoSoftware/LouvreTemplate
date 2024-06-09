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

/* These flags determine how the scene handles input events.
 * If no flags are set, the scene will simply dispatch events to the appropriate views.
 *
 * For example, if the WaylandEvents flag is set, the scene will also send input events
 * to clients using the default LPointer, LKeyboard or LTouch implementation.
 *
 * If you want to handle client events yourself while still dispatching events to views,
 * remove all flags.
 *
 * Note: The AuxFunc flag adds the Ctrl + Shift + Esc shortcut to quit. See Keyboard.
 */
#define SCENE_EVENT_OPTIONS LScene::WaylandEvents | LScene::AuxFunc | LScene::PointerConstraints

#endif // SCENE_H
