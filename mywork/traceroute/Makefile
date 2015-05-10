CC = gcc
IDIR = ../lib
LIBDIR = ../lib
ODIR = .
CFLAGS = -g -Wall -O -I$(IDIR)

LIBS = wraplinux.o wrapsocket.o wrapstdio.o wrapsignal.o 
OBJS = main.o $(LIBS)


troute: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
main.o: $(LIBS) 
	$(CC) $(CFLAGS) -c main.c $(LIBS) -o $@
	
recvicmp: recvicmp.o $(LIBS)
	$(CC) $(CFLAGS) recvicmp.o $(LIBS) -o $@
recvicmp.o: $(LIBS)
	$(CC) $(CFLAGS) -c recvicmp.c $(LIBS) -o $@

sendicmp: sendicmp.o $(LIBS)
	$(CC) $(CFLAGS) sendicmp.o $(LIBS) -o $@
sendicmp.o: $(LIBS)
	$(CC) $(CFLAGS) -c sendicmp.c $(LIBS) -o $@
	
sendarp: sendarp.o $(LIBS)
	$(CC) $(CFLAGS) sendarp.o $(LIBS) -o $@
sendarp.o: $(LIBS)
	$(CC) $(CFLAGS) -c sendarp.c $(LIBS) -o $@

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
	rm -rf $(ODIR)/*.o *~ troute recvicmp sendarp
