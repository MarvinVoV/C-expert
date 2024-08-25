CC = gcc
IDIR = ../lib
LIBDIR = ../lib
ODIR = .
CFLAGS = -g -Wall -O -I$(IDIR)

LIBS = wraplinux.o wrapsocket.o wrapstdio.o wrapsignal.o 

all: server1 client1
client1: client1.o $(LIBS)
	$(CC) $(CFLAGS) client1.o $(LIBS) -o $@
server1: server1.o $(LIBS)
	$(CC) $(CFLAGS) server1.o $(LIBS) -o $@
client1.o: $(LIBS)
	$(CC) $(CFLAGS) -c client1.c $(LIBS) -o $@
server1.o: $(LIBS)
	$(CC) $(CFLAGS) -c server1.c $(LIBS) -o $@

wraplinux.o: $(LIBDIR)/wraplinux.c 
	$(CC) $(CFLAGS) -c $(LIBDIR)/wraplinux.c -o $@
wrapsocket.o: $(LIBDIR)/wrapsocket.c 
	$(CC) $(CFLAGS) -c $(LIBDIR)/wrapsocket.c -o $@
wrapstdio.o: $(LIBDIR)/wrapstdio.c 
	$(CC) $(CFLAGS) -c $(LIBDIR)/wrapstdio.c -o $@
wrapsignal.o: $(LIBDIR)/wrapsignal.c 
	$(CC) $(CFLAGS) -c $(LIBDIR)/wrapsignal.c -o $@

.PHONY: clean
clean:
	rm -rf $(ODIR)/*.o *~ client1 server1
