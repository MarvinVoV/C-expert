SUB_OBJ_FOLDER := demo
SUB_OBJ_DIR := $(OBJ_DIR)/$(SUB_OBJ_FOLDER)
SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
CUR_DIR := $(PROJECT_DIR)/$(SELF_DIR)
SUB_SRC := $(wildcard $(CUR_DIR)*.c)
SUB_SRC_FILES := $(foreach f,$(SUB_SRC),$(shell basename $(f)))
SUB_OBJS := $(addprefix $(SUB_OBJ_DIR)/,$(patsubst %.c,%.o,$(SUB_SRC_FILES)))





demo: $(SUB_OBJS) $(LIB_OBJ) 
	$(CC) $^ -o $(BIN_DIR)/$@
$(SUB_OBJS): $(SUB_SRC) | SUBPRE
	$(CC) $(CFLAGS) $(I_INC) -c $^ -o $@


SUBPRE:
	@mkdir -p $(SUB_OBJ_DIR)
