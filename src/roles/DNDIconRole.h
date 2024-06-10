#ifndef DNDICONROLE_H
#define DNDICONROLE_H

#include <LDNDIconRole.h>

using namespace Louvre;

/*
 * This role serves as an icon used by clients during drag & drop sessions.
 * See LDND::icon() for details.
 */
class DNDIconRole final : public LDNDIconRole
{
public:
    using LDNDIconRole::LDNDIconRole;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // DNDICONROLE_H
