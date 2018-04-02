# Libraries on which TARGET depends
LIBS = lib/eigen/

# Name of the executable
TARGET = frostAcre.exe

# Place to store all generated files
BUILD_DIR = build

# All source files. Header files are detected automatically
SRCS = code/main.cpp code/src/*.cpp

# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14

all: make

make:
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $(SRCS) -o $(BUILD_DIR)/$(TARGET)

clean:
	rm build/*
