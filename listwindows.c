#include <X11/Xlib.h>
#include <stdio.h>

int main(void) {
  int i;
  char* win_name;

  Display *disp;
  if (!(disp = XOpenDisplay(0x0)))
    return 1;
  XEvent ev;
  Window root = DefaultRootWindow(disp);

  Window root_return;
  Window parent_return;
  Window *children_return;
  unsigned int nchildren_return;

  if (XQueryTree(disp, root, &root_return, &parent_return, &children_return, &nchildren_return) != 0) {
    for (i=0; i<nchildren_return; i++) {
      XFetchName(disp, children_return[i], &win_name);
      printf("WIN: %s\n", win_name);
    }
    printf("%d\n", nchildren_return);
  } else {
    // handle error
  }
  return 0;
}
