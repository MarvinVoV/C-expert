CC = gcc
CFLAGS = -g -Wall
INCDIR := $(addprefix -I, ../../header)
VPATH := ../../header:../../libs

all: echoserver echotcpclient
echoserver: echoserver.o writen.o signal.o 
	$(CC) $^ -o $@
echoserver.o: echoserver.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
writen.o: writen.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
signal.o: signal.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
	


echotcpclient: echotcpclient.o writen.o readline.o
	$(CC) $^ -o $@
echotcpclient.o: echotcpclient.c
	$(CC) $(CLFAGS) $(INCDIR) -c $< -o $@
readline.o: readline.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.PYONE: clean cleanobjs
clean:
	@rm -f *.o echoserver echotcpclient

cleanobjs:
	@rm -f *.o
