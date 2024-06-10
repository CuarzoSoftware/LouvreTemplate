#ifndef SUBSURFACEROLE_H
#define SUBSURFACEROLE_H

#include <LSubsurfaceRole.h>

using namespace Louvre;

/*
 * This is a special role where the surface is always positioned relative to its parent surface
 * (refer to localPos()) and should be composited as if it were part of it.
 * It's commonly used for displaying video within a web browser and similar scenarios.
 */
class SubsurfaceRole final : public LSubsurfaceRole
{
public:
    using LSubsurfaceRole::LSubsurfaceRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // SUBSURFACEROLE_H
