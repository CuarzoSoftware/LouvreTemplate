#ifndef LAYERROLE_H
#define LAYERROLE_H

#include <LLayerRole.h>

using namespace Louvre;

/*
 * This role is used for creating panels, wallpapers, notifications, etc.
 * Refer to the documentation of the LExclusivZone class for more details.
 */

class LayerRole final : public LLayerRole
{
public:
    using LLayerRole::LLayerRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // LAYERROLE_H
