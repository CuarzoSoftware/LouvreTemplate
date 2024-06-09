#include <LSceneView.h>
#include "Scene.h"

Scene::Scene() noexcept : LScene()
{
    mainView()->setClearColor({
        .r = 0.01f,
        .g = 0.02f,
        .b = 0.02f,
        .a = 1.f
    });

    for (int i = 0; i <= LLayerOverlay; i++)
        layers[i].setParent(mainView());
}
