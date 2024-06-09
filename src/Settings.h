#ifndef SETTINGS_H
#define SETTINGS_H

/*
 * SCREEN SHARING
 */

/* If defined, only xdg-desktop-portal-wlr will be allowed to capture screens.
 * Ensure that both xdg-desktop-portal and xdg-desktop-portal-wlr are installed.
 * For more details, refer to the Systemd class, Compositor::globalsFilter(),
 * Output::paintGL() and the LScreenshotRequest class documentation.
 *
 * To configure the output chooser and other settings, visit:
 * https://man.archlinux.org/man/xdg-desktop-portal-wlr.5
 */
#define SETTINGS_XDG_DESKTOP_PORTAL_SCREENCAST_ONLY

/*
 * SESSION LOCK
 *
 * Session Lock client launched when the POWER key is pressed,
 * see the Keyboard class.
 */

#define SETTINGS_SESSION_LOCK_CLIENT "gtklock"

/*
 * SERVER-SIDE DECORATIONS
 */

/* Ennable SSD for clients that support it */
#define SETTINGS_SSD

/* SSD titlebar/edges size */
#define SETTINGS_SSD_EXTRA_GEOMETRY { .left = 8, .top = 20, .right = 8, .bottom = 8 }

/* SSD titlebar/edges color */
#define SETTINGS_SSD_COLOR_ACTIVE {0.1f, 0.1f, 0.3f, 1.f}
#define SETTINGS_SSD_COLOR_INACTIVE {0.1f, 0.1f, 0.1f, 0.7f}

/*
 * INPUT DEVICES
 *
 * Check the Seat class.
 */

#define SETTINGS_DISABLE_WHILE_TYPING false

#endif // SETTINGS_H
