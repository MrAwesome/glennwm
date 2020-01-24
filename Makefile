PREFIX?=/usr/X11R6
CFLAGS?=-Os -pedantic -Wall

all:
	$(CC) $(CFLAGS) -I$(PREFIX)/include glennwm.c glennwmlib.c -L$(PREFIX)/lib -lX11 -o glennwm

install:
	cp glennwm /usr/bin/glennwm

clean:
	rm -f glennwm
