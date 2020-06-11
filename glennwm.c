#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "glennwmlib.h"

#define LOGMSG(x)                                                              \
  FILE *f = fopen("/tmp/glennwm.log", "a+");                                   \
  x;                                                                           \
  fclose(f);

#define BIND(mod, key, cmd)                                                    \
  (ModAndKeyAndCmd) { mod, key, cmd }

#define CMD_RUNNER(name, ...)                                           \
  static const char *cmd_##name[] = {__VA_ARGS__};                            \
  void name(Display *disp) { spawn(disp, cmd_##name); }

CMD_RUNNER(screenshot, "maim", "-s", "/tmp/lol.png", NULL)
CMD_RUNNER(clipmenu, "clipmenu", NULL)
CMD_RUNNER(terminal, "urxvt", NULL)
CMD_RUNNER(xkill, "xkill", "-frame", NULL)
CMD_RUNNER(browser, "qutebrowser", NULL)
CMD_RUNNER(vol_up, "pulsemixer", "--change-volume", "+3", NULL)
CMD_RUNNER(vol_down, "pulsemixer", "--change-volume", "-3", NULL)
CMD_RUNNER(vol_mute, "pulsemixer", "--toggle-mute", NULL)
CMD_RUNNER(player_toggle, "playerctl", "play-pause", NULL)
void exit_wm(Display *disp) { exit(EXIT_SUCCESS); }

int main(void) {
  int i;

  ModAndKeyAndCmd cmds[] = {
      BIND(Mod1Mask, XK_F2, screenshot),
      BIND(Mod1Mask, XK_F3, maximize_all_windows),
      BIND(Mod1Mask, XK_F8, clipmenu),
      BIND(Mod1Mask, XK_F9, terminal),
      BIND(Mod1Mask, XK_F10, browser),
      BIND(Mod1Mask, XK_F11, xkill),
      BIND(Mod1Mask, XK_F12, exit_wm),
      BIND(Mod4Mask, XK_y, vol_down),
      BIND(Mod4Mask, XK_u, vol_up),
      BIND(0, XF86XK_AudioLowerVolume, vol_down),
      BIND(0, XF86XK_AudioRaiseVolume, vol_up),
      BIND(0, XF86XK_AudioPlay, player_toggle),
      BIND(Mod4Mask, XK_q, player_toggle),
      BIND(0, XF86XK_AudioMute, vol_mute),
  };
  unsigned int num_cmds = (sizeof(cmds) / sizeof(ModAndKeyAndCmd));

  Display *disp;
  XEvent ev;

  if (!(disp = XOpenDisplay(0x0)))
    return 1;

  // Start the WM with an appropriately-sized terminal in "fullscreen".
  terminal(disp);
  maximize_all_windows(disp);

  for (i = 0; i < num_cmds; i++) {
    grabkey(disp, cmds[i]);
  }

  for (;;) {
    XNextEvent(disp, &ev);
    maximize_all_windows(disp);

    if (ev.type == KeyPress) {
      for (i = 0; i < num_cmds; i++) {
        handle_keypress(disp, &ev.xkey, cmds[i]);
      }
    }
  }
}
