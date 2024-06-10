#ifndef CLIENT_H
#define CLIENT_H

#include <LClient.h>

using namespace Louvre;

class Client final : public LClient
{
public:
    using LClient::LClient;

    /* Please refer to the documentation to explore all available
     * virtual methods that can be overridden. */
};

#endif // CLIENT_H
