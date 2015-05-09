CC = gcc
IDIR = ../lib
LIBDIR = ../lib
ODIR = .
CFLAGS = -g -Wall -O -I$(IDIR)

LIBS = wraplinux.o wrapsocket.o wrapstdio.o wrapsignal.o 

all: server client
client: client.o $(LIBS)
	$(CC) $(CFLAGS) client.o $(LIBS) -o $@
server: server.o $(LIBS)
	$(CC) $(CFLAGS) server.o $(LIBS) -o $@
client.o: $(LIBS)
	$(CC) $(CFLAGS) -c client.c $(LIBS) -o $@
server.o: $(LIBS)
	$(CC) $(CFLAGS) -c server.c $(LIBS) -o $@

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
	rm -rf $(ODIR)/*.o *~ client server
