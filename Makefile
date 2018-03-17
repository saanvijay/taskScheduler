include ./makefile.rules


EXE  := $(BIN_DIR)/taskScheduler
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, objs/%.o, $(SRCS)) 

CFLAGS += $(C++11)
LIBFLAGS = -lpthread

VPATH := $(OBJ_DIR) $(BIN_DIR)

DEPS := $(OBJS:.o=.d)
 
.PHONY: all
all : $(EXE)

$(EXE) : $(OBJS)
	@echo "--------- Creating $(notdir $@) ---------"
	mkdir -p ${@D}
	$(CC) $(OFLAG) $@ $^ $(LIBFLAGS) 
	@echo "============== DONE ====================="
	@echo ''


$(OBJ_DIR)/%.o : %.cpp
	$(cpp_compile_rule_body)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(EXE)

-include $(DEPS)
