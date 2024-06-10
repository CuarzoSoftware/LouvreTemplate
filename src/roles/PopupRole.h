#ifndef POPUPROLE_H
#define POPUPROLE_H

#include <LPopupRole.h>

using namespace Louvre;

/*
 * Represents a short-lived surface used for displaying tooltips, context menus, etc.
 */
class PopupRole final : public LPopupRole
{
public:
    using LPopupRole::LPopupRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // POPUPROLE_H
