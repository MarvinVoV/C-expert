OBJServer = selectserver.o gen.o
OBJClient = simpleclient.o gen.o
OBJudpServ = udpserv.o
OBJudpCli = udpclient.o

CC = gcc
CFLAGS = -Wall -O -g 
INCLUDE = -I../include


server: $(OBJServer)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJServer) -o $@
selectserver.o: gen.o
	$(CC) $(CFLAGS) $(INCLUDE) -c selectserver.c gen.o -o $@

client: $(OBJClient)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJClient) -o $@
simpleclient.o: gen.o
	$(CC) $(CFLAGS) $(INCLUDE) -c simpleclient.c gen.o -o $@

udpserv: $(OBJudpServ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJudpServ) -o $@
udpserv.o: gen.o
	$(CC) $(CFLAGS) $(INCLUDE) -c udpserv.c gen.o -o $@
	
udpcli: $(OBJudpCli)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJudpCli) -o $@
udpclient.o: gen.o
	$(CC) $(CFLAGS) $(INCLUDE) -c udpclient.c gen.o -o $@

gen.o: gen.c 
	$(CC) $(CFLAGS) $(INCLUDE) -c gen.c -o $@
	

.PHONY:clean help
clean:
	rm -rf *.o client server
help:
	@echo You must be root to make
	