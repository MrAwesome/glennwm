#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "glennwmlib.h"

void spawn(Display *disp, const char **com) {
  if (fork())
    return;
  if (disp)
    close(ConnectionNumber(disp));
  setsid();
  execvp((char *)com[0], (char **)com);
}

void handle_keypress(Display *disp, XKeyEvent *xkey,
                     ModAndKeyAndCmd keybinding) {
  if (XLookupKeysym(xkey, 0) == keybinding.key) {
    keybinding.func(disp);
  }
}

void grabkey(Display *disp, ModAndKeyAndCmd keybinding) {
  XGrabKey(disp, XKeysymToKeycode(disp, keybinding.key), keybinding.mask,
           DefaultRootWindow(disp), True, GrabModeAsync, GrabModeAsync);
}
