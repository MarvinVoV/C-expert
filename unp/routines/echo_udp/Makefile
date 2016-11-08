CC = gcc
CFLAGS = -g -Wall
INCDIR := $(addprefix -I, ../../header)
VPATH := ../../header:../../libs

all: echoserver echoclient
echoserver: echoserver.o  
	$(CC) $^ -o $@
echoserver.o: echoserver.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
	
echoclient: echoclient.o
	$(CC) $^ -o $@
echoclient.o: echoclient.c
	$(CC) $(CLFAGS) $(INCDIR) -c $< -o $@




.PYONE: clean cleanobjs
clean:
	@rm -f *.o echoserver echoclient

cleanobjs:
	@rm -f *.o
