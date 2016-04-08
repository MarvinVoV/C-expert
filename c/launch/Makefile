launch.o: launch.c launch.h
	gcc -c launch.c

thruster.o: thruster.c thruster.h
	gcc -c thruster.c

main.o: main.c launch.c thruster.c 
	gcc -c main.c  

main: main.o launch.o thruster.o
	gcc main.o launch.o thruster.o -o main
