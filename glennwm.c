#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "glennwmlib.h"

#define BIND(x, y, z) (ModAndKeyAndCmd){x, y, z}

// TODO: find a way to support fullscreen/wmctrl
// TODO: require less boilerplate

static const char *cmd_clipmenu[] = {"clipmenu", NULL};
static const char *cmd_termsmall[] = {"urxvt", "-geometry", "151x41", NULL};
static const char *cmd_term[] = {"urxvt", "-geometry", "135x36", NULL};
static const char *cmd_brave[] = {"brave", NULL};

void run_clipmenu(Display *disp) { spawn(disp, cmd_clipmenu); }
void run_termsmall(Display *disp) { spawn(disp, cmd_termsmall); }
void run_term(Display *disp) { spawn(disp, cmd_term); }
void run_brave(Display *disp) { spawn(disp, cmd_brave); }
void run_quit(Display *disp) { exit(EXIT_SUCCESS); }

int main(void) {
  ModAndKeyAndCmd cmds[] = {
      BIND(Mod1Mask, XK_F8, run_clipmenu),
      BIND(Mod1Mask, XK_F9, run_termsmall),
      BIND(Mod1Mask, XK_F10, run_term),
      BIND(Mod1Mask, XK_F11, run_brave),
      BIND(Mod1Mask, XK_F12, run_quit),
  };
  unsigned int num_cmds = (sizeof(cmds) / sizeof(ModAndKeyAndCmd));

  Display *disp;
  XEvent ev;

  if (!(disp = XOpenDisplay(0x0)))
    return 1;

  // Start the WM with an appropriately-sized terminal in "fullscreen".
  run_term(disp);

  for (int i = 0; i < num_cmds; i++) {
    grabkey(disp, cmds[i]);
  }

  for (;;) {
    XNextEvent(disp, &ev);
    if (ev.type == KeyPress) {
      for (int i = 0; i < num_cmds; i++) {
        handle_keypress(disp, &ev.xkey, cmds[i]);
      }
    }
  }
}
