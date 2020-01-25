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

Window get_xth_window(Display *disp, int x) {
  Window root = DefaultRootWindow(disp);
  Window root_return;
  Window parent_return;
  Window *children_return;
  unsigned int nchildren_return;

  if (XQueryTree(disp, root, &root_return, &parent_return, &children_return,
                 &nchildren_return) != 0 &&
      nchildren_return > 0) {
    return children_return[nchildren_return - x];
  } else {
    return (Window)NULL;
  }
}

Window get_top_window(Display *disp) { return get_xth_window(disp, 1); }

// void switchwin(Display *disp) {
//  char* win_name;
//  Window w = get_second_window(disp);
//  XRaiseWindow(disp, w);
//  XFetchName(disp, w, &win_name);
//  LOGMSG(fprintf(f, "LAWL: %s\n", win_name));
//}
