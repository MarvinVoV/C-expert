SHELL = /bin/bash
CC = gcc
CFLAGS = -g -Wall

SRC_DIR := src
INC_DIR := header
OBJ_DIR := $(addsuffix /objs,$(shell pwd))
BIN_DIR := target

LIB_DIR := src/libs

# Find source file in custom library
LIB_SRC := $(shell find $(LIB_DIR) -type f -name '*.c') 

# Compile library source files
LIB_OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o,$(foreach f,$(LIB_SRC),$(shell basename $(f))))

SUBMKS := $(shell find $(SRC_DIR) -type f -iname '*.mk')

# Add include header files
I_INC := $(addprefix -I,$(INC_DIR))

# Project Path
PROJECT_DIR := $(shell pwd)

# Search header files in header and source file in src recursively.
SRC_PATH := $(shell find $(SRC_DIR) -type d)
VPATH := $(foreach dir,$(SRC_PATH),$(dir:%=%:))
VPATH += $(INC_DIR)

# Export all variables to submakes.
export


# Compile library source files
$(LIB_OBJ): $(LIB_SRC) | PRE 
	$(CC) $(CFLAGS) $(I_INC) -c $^ -o $@

# Creat objects output folder
PRE:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@mkdir $(OBJ_DIR) $(BIN_DIR)


.PHONY: cleanlib clean
cleanlib:
	@rm -rf $(OBJ_DIR)
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	

.PHONY: all  $(SUBMKS)
all: $(SUBMKS)
$(SUBMKS): | $(LIB_OBJ)
	$(MAKE) -f $@



