#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "glennwmlib.h"

#define LOGMSG(x)                                                              \
  FILE *f = fopen("/tmp/glennwm.log", "a+");                                   \
  x;                                                                           \
  fclose(f);

#define BIND(x, y, z)                                                          \
  (ModAndKeyAndCmd) { x, y, z }

// TODO: require less boilerplate
static const char *cmd_clipmenu[] = {"clipmenu", NULL};
static const char *cmd_term[] = {"urxvt", NULL};
static const char *cmd_xkill[] = {"xkill", "-frame", NULL};
static const char *cmd_xterm[] = {"xterm", NULL};
static const char *cmd_browser[] = {"qutebrowser", NULL};
static const char *cmd_screenshot[] = {"maim", "-s", "/tmp/lol.png", NULL};

void run_screenshot(Display *disp) { spawn(disp, cmd_screenshot); }
void run_clipmenu(Display *disp) { spawn(disp, cmd_clipmenu); }
void run_xkill(Display *disp) { spawn(disp, cmd_xkill); }
void run_term(Display *disp) { spawn(disp, cmd_term); }
void run_xterm(Display *disp) { spawn(disp, cmd_xterm); }
void run_browser(Display *disp) { spawn(disp, cmd_browser); }
void run_quit(Display *disp) { exit(EXIT_SUCCESS); }

int main(void) {
  int i;

  ModAndKeyAndCmd cmds[] = {
      BIND(Mod1Mask, XK_F2, run_screenshot),
      BIND(Mod1Mask, XK_F3, maximize_all_windows),
      BIND(Mod1Mask, XK_F5, run_xterm),
      BIND(Mod1Mask, XK_F8, run_clipmenu),
      BIND(Mod1Mask, XK_F9, run_term),
      BIND(Mod1Mask, XK_F10, run_browser),
      BIND(Mod1Mask, XK_F11, run_xkill),
      BIND(Mod1Mask, XK_F12, run_quit),
  };
  unsigned int num_cmds = (sizeof(cmds) / sizeof(ModAndKeyAndCmd));

  Display *disp;
  XEvent ev;

  if (!(disp = XOpenDisplay(0x0)))
    return 1;

  // Start the WM with an appropriately-sized terminal in "fullscreen".
  run_term(disp);

  for (i = 0; i < num_cmds; i++) {
    grabkey(disp, cmds[i]);
  }

  for (;;) {
    XNextEvent(disp, &ev);
    maximize_top_window(disp);

    if (ev.type == KeyPress) {
      for (i = 0; i < num_cmds; i++) {
        handle_keypress(disp, &ev.xkey, cmds[i]);
      }
    }
  }
}
