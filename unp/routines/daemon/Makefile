CC = gcc
CFLAGS = -g -Wall
INCDIR := $(addprefix -I, ../../header)
VPATH := ../../header:../../libs

all: daemonlog
daemonlog: daemonlog.o daemonize.o 
	$(CC) $^ -o $@
daemonize.o: daemonize.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
daemonlog.o: daemonlog.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@






.PYONE: clean cleanobjs
clean:
	@rm -f *.o daemonlog

cleanobjs:
	@rm -f *.o
