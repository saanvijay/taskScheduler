#######################################################################
#######################################################################
include ./makefile.rules


SRCS := timer.cpp \
	taskScheduler.cpp

OBJS := $(patsubst %.cpp, objs/%.o, $(SRCS)) 
EXE  := $(BIN_DIR)/taskScheduler

CFLAGS += $(C++11)

VPATH := $(OBJ_DIR) \
	 $(BIN_DIR) \
	 src

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
	@echo "--------- Cleaning $(EXE) ---------"
	rm -rf $(OBJ_DIR) 
	rm -rf $(BIN_DIR) 
	rm -rf $(EXE)
	@echo "============== DONE ====================="
	@echo ''

-include $(DEPS)
