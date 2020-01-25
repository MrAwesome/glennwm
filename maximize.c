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
