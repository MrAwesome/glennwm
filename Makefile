PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include glennwm.c glennwmlib.c maximize.c -L$(PREFIX)/lib -lX11 -o glennwm

maximize:
	$(CC) $(CFLAGS) -I$(PREFIX)/include maximize.c -L$(PREFIX)/lib -lX11 -o maximize

listwindows:
	$(CC) $(CFLAGS) -I$(PREFIX)/include listwindows.c -L$(PREFIX)/lib -lX11 -o listwindows

install:
	cp glennwm /usr/bin/glennwm

clean:
	rm -f glennwm
