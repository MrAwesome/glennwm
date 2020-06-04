#include <X11/Xlib.h>
#include "glennwmlib.h"

void maximize_top_window(Display* disp) {
	int scr = DefaultScreen(disp);
	int sw = DisplayWidth(disp, scr);
	int sh = DisplayHeight(disp, scr);

  Window top_window = get_top_window(disp);

  if (top_window == (unsigned long)NULL) {
    return;
  }

  //XSelectInput(disp, root, SubstructureRedirectMask);
  XMoveResizeWindow(disp, top_window, 0, 0, sw, sh);
  //XMapWindow(disp, top_window);
  //XSetInputFocus(disp, top_window, RevertToPointerRoot, CurrentTime);
  //XFlush(disp);
}

void maximize_all_windows(Display* disp) {
  int i;
	int scr = DefaultScreen(disp);
	int sw = DisplayWidth(disp, scr);
	int sh = DisplayHeight(disp, scr);
  Window root = DefaultRootWindow(disp);
  Window root_return;
  Window parent_return;
  Window *children_return;
  unsigned int nchildren_return;

  if (XQueryTree(disp, root, &root_return, &parent_return, &children_return, &nchildren_return) != 0) {
    for (i=0; i<nchildren_return; i++) {
      Window child_window = children_return[i];
      if (child_window != (unsigned long)NULL) {
        XMoveResizeWindow(disp, child_window, 0, 0, sw, sh);
      }
    }
  } else {
    // handle error
  }
}
