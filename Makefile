CC = g++
INCLUDE = /usr/include/SDL2/
FLAGS = -g -Wfatal-errors -std=c++11 -I$(INCLUDE)
LDFLAGS = -lSDL2 -lSDL2_image -lGL -lGLEW
TARGET = out

SRC = *.cpp

all:
	$(CC) $(FLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)