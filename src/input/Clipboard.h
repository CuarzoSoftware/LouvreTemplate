#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <LClipboard.h>

using namespace Louvre;

class Clipboard final : public LClipboard
{
public:
    using LClipboard::LClipboard;

private:
    bool setClipboardRequest(LClient *client, const LEvent &triggeringEvent) override;
    bool persistentMimeTypeFilter(const std::string &mimeType) const override;
};

#endif // CLIPBOARD_H
