# Makefile to build taskScheduler

CFLAGS = -c -m64 -std=c++11 -fPIC -g
OFLAG  = -o
LD_FLAG = -lpthread
CC = g++

SRC = taskScheduler.cpp \
	timer.cpp

OBJ = taskScheduler.o \
	timer.o

HEADERS = timer.h \
	timerTask.h

EXE = taskScheduler


.PHONY: all
all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(OFLAG) $@ $^ $(LD_FLAG) 

%.o : %.cpp
	$(CC) $(CFLAGS) $(OFLAG) $@ $< $(LD_FLAG)

$(SRC) : $(HEADERS)
	

.PHONY : clean
clean :
	rm -rf $(OBJ) $(EXE)
