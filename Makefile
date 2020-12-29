# Makefile
#
# truefinder, Seunghyun Seo
# frog@hackerslab.com

CC= gcc
CFLAGS= -D_LINUX_
XFLAGS= -O2
OBJS= wtserver.o wterm.o wtcgi.o kbhit.o ptypair.o
EXECS= wtcgi.cgi wtserver wterm
#DEBUG= -DDEBUGZ


.c.o:
	$(CC) -c $(CFLAGS) $<

all: $(OBJS) $(EXECS)

wtserver:
	$(CC) -o wtserver $(CFLAGS) $(XFLAGS) wtserver.o ptypair.o

wtcgi.cgi:
	$(CC) -o wtcgi.cgi $(CFLAGS) $(XFLAGS) wtcgi.o

wterm:
	$(CC) -o wterm $(CFLAGS) $(XFLGAS) wterm.o kbhit.o

clean:
	rm -rf *.o $(EXECS)
