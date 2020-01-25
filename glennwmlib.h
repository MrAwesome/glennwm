#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _ModAndKeyAndCmd {
  unsigned int mask;
  KeySym key;
  void (*func)(Display *disp);
} ModAndKeyAndCmd;

void spawn(Display *disp, const char **com);

void handle_keypress(Display *disp, XKeyEvent *xkey,
                     ModAndKeyAndCmd keybinding);

void grabkey(Display *disp, ModAndKeyAndCmd keybinding);

void maximize_top_window(Display* disp);
Window get_top_window(Display* disp, Window root);
