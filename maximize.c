#include <X11/Xlib.h>

Window get_top_window(Display* disp, Window root) {
  Window root_return;
  Window parent_return;
  Window *children_return;
  unsigned int nchildren_return;

  if (XQueryTree(disp, root, &root_return, &parent_return, &children_return, &nchildren_return) != 0
      && nchildren_return > 0
      ) {
    return children_return[nchildren_return-1];
  } else {
    return root;
  }
}

void maximize_top_window(Display* disp) {
	int scr = DefaultScreen(disp);
	int sw = DisplayWidth(disp, scr);
	int sh = DisplayHeight(disp, scr);

    Window root = DefaultRootWindow(disp);
    Window top_window = get_top_window(disp, root);

    if (top_window == root) {
      return;
    }

    //XSelectInput(disp, root, SubstructureRedirectMask);
    XMoveResizeWindow(disp, top_window, 0, 0, sw, sh);
    //XMapWindow(disp, top_window);
    //XSetInputFocus(disp, top_window, RevertToPointerRoot, CurrentTime);
    //XFlush(disp);
}
