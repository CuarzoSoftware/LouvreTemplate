#include <LKeyboardKeyEvent.h>
#include <LSessionLockManager.h>
#include <LLauncher.h>
#include "Keyboard.h"
#include "../Global.h"
#include "../scene/Scene.h"
#include "../Settings.h"

Keyboard::Keyboard(const void *params) noexcept : LKeyboard(params)
{
    /* Key press repeat rate */
    setRepeatInfo(32, 500);

    /* Keymap sent to clients and used by the compositor, check the LKeyboard class or XKB doc */
    setKeymap(
        nullptr,  // Rules
        nullptr,  // Model
        nullptr,  // Layout
        nullptr); // Options
}

void Keyboard::keyEvent(const LKeyboardKeyEvent &event)
{
    /* The AuxFunc flag adds the Ctrl + Shift + ESC shortcut to quit, ensure
     * to add a way to exit if you remove it */
    G::scene().handleKeyboardKeyEvent(event, SCENE_EVENT_OPTIONS);

    /* Launches a session lock client */
    if (sessionLockManager()->state() != LSessionLockManager::Locked
        && event.keyCode() == KEY_POWER
        && event.state() == LKeyboardKeyEvent::Released)
        LLauncher::launch(SETTINGS_SESSION_LOCK_CLIENT);
}
