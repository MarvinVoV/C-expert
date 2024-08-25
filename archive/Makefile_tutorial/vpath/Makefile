# Run with command: make foo.o
CC = gcc

INCDIR = headers
I_INCDIR=$(addprefix -I,$(INCDIR))
VPATH = src:headers

# With the value of VPATH, the prerequisite is equals to 'foo.o : src/foo.c headers/myheader.h'
# '$<' means the name of the first prerequisite.
# '$<' is called automatic variable
foo.o: foo.c myheader.h
	@echo $<
	$(CC) $(I_INCDIR) -c $< -o $@



.PHONY: clean
clean:
	rm foo.o
