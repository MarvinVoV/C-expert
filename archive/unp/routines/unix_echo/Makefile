CC = gcc
CFLAGS = -g -Wall
INCDIR := $(addprefix -I, ../../header)
VPATH := ../../header:../../libs

all: echoserver echostreamcli
echoserver: echoserver.o writen.o signal.o 
	$(CC) $^ -o $@
echoserver.o: echoserver.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
writen.o: writen.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
signal.o: signal.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
	

echostreamcli: echostreamcli.o writen.o readline.o
	$(CC) $^ -o $@
echostreamcli.o: echostreamcli.c
	$(CC) $(CLFAGS) $(INCDIR) -c $< -o $@
readline.o: readline.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@



.PYONE: clean cleanobjs
clean:
	@rm -f *.o echoserver echostreamcli

cleanobjs:
	@rm -f *.o
