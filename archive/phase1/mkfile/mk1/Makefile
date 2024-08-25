OBJS = main.o hello1.o hello2.o
CC = gcc
CFLAGS = -Wall -O -g

hello: $(OBJS)
	$(CC) $(OBJS) -o $@
main.o:hello1.o hello2.o
	$(CC) $(CFLAGS) -c main.c hello1.o hello2.o -o $@
hello1.o:hello1.c hello.h
	$(CC) $(CFLAGS) -c hello1.c -o $@
hello2.o:hello2.c hello.h
	$(CC) $(CFLAGS) -c hello2.c -o $@

.PHONY:clean help
clean:
	rm -rf *.o hello
help:
	@echo You must be root to make
