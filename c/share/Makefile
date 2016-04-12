encrpty.o: encrypt.c
	gcc -c -I. encrypt.c -o encrypt.o
checksum.o: checksum.c 
	gcc -c -I. checksum.c -o checksum.o
libhfsecurity.a: encrypt.o checksum.o
	ar -rcs libhfsecurity.a encrypt.o checksum.o
main: main.c libhfsecurity.a
	gcc main.c -I. -L. -lhfsecurity -o main

