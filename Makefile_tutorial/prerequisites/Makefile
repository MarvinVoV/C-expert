OBJDIR := objdir
OBJS := $(addprefix $(OBJDIR)/, foo.o bar.o)

all: $(OBJS)
	@echo $^

# targets: normal-prerequisites | order-only-prerequisites
$(OBJS): | pre1 pre2

pre1:
	@echo mkdir objdir

pre2: 
	@echo mkdir target
