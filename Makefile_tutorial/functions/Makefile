
objs = $(patsubst %.c,%.o,$(wildcard *.c))

all:
	@echo $(objs)


files = foo.elc bar.o lose.o
filter:
	@echo $(filter %.o,$(files))


# '@' or .SILENT phony suppress echo content
LIST=one two three

.SILENT: forfun
forfun: 
	for i in $(LIST); do \
		echo $$i; \
	done


# '$(var:a=b)' meaning is to take the value of the variable var, replace every a at the end of a word with b in that value
# this case is equivalent to '$(patsubst a,b,$(var))'
foo := a.o b.o c.o
bar := $(foo:.o=.c)
coo := $(foo:%.o=%.c)
show:
	@echo $(bar)
	@echo $(coo)



x := variable1
y := $(subst 1,2,$(x));
showy:
	@echo $(y)


showfun:
	@echo $(basename src/foo.c src-1.0/bar hacks)   # src/foo src-1.0/bar hacks
	@echo $(addsuffix .c, foo bar) # foo.c bar.c
	@echo $(addprefix src/, foo bar) # src/foo src/bar
	@echo $(shell pwd)


dirs := a b c d
files := $(foreach dir, $(dirs), $(wildcard $(dir)/*))
allfiles:
	@echo $(files)
	
