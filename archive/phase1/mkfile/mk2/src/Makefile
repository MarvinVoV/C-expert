OBJS = main.o hello1.o hello2.o
CC = gcc
CFLAGS = -Wall -O -g 
INCLUDE = -I../include


hello: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $@
main.o:hello1.o hello2.o
	$(CC) $(CFLAGS) $(INCLUDE) -c main.c hello1.o hello2.o -o $@
hello1.o:hello1.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c hello1.c -o $@
hello2.o:hello2.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c hello2.c -o $@

.PHONY:clean help
clean:
	rm -rf *.o hello
help:
	@echo You must be root to make
