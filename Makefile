CC := g++
AR := ar
LIB := libEternal.a
ARFLAGS := -crv
INCLUDE := -I include
FLAGS := -g -Wfatal-errors -fmax-errors=1 -std=c++11 $(INCLUDE)
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLEW
TARGET := a.out

SRC = $(wildcard src/*.cpp)

all:
	$(CC) $(FLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

lib:
	$(CC) $(INCLUDE) -c $(filter-out src/main.cpp, $(SRC))
	$(AR) $(ARFLAGS) $(LIB) $(wildcard *.o)

.PHONY:	clean
clean:
	rm *.o
