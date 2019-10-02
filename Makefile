CC = g++
AR = ar
LIB = libEternal.a
ARFLAGS = -crv
INCLUDE = -I include
FLAGS = -Wfatal-errors -std=c++11 $(INCLUDE)
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lGLEW
TARGET = a.out

SRC = $(wildcard src/*.cpp)

all:
	$(CC) $(FLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

lib:
	$(CC) $(INCLUDE) -c $(filter-out main.cpp, $(SRC))
	$(AR) $(ARFLAGS) $(LIB) $(wildcard *.o)

clean:
	rm *.o
