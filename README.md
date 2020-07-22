# glennwm
A very, very simple WM. For Glenn, By Glenn. 

This is crafted very specifically for my own use case, feel free to tinker with it to match your own.

I recommend pairing with urxvt, kdeconnect, clipmenud, and unclutter - but feel free to customize as you see fit.

## Installation
Add at least the last line of this to `.xinitrc`:
```
(sleep 5 && unclutter -b --timeout 3) &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape' &
clipmenud &
exec /usr/lib/kdeconnectd &
exec /home/glenn/glennwm/glennwm
```

Then run this to test changes:
```cd ~/glennwm && make && cd && startx```

Alt-F12 quits. You can see the rest of the bindings in `glennwm.c`.

## Credits
Heavily inspired by [nullwm](https://github.com/DebianJoe/nullWM).
