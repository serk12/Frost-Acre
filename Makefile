# Libraries on which TARGET depends
LIBS = lib/eigen/

# Name of the executable
TARGET = frostAcre.exe

# Place to store all generated files
BUILD_DIR = build
OBJECTS = $(shell echo $(BUILD_DIR)/*.o)
# All source files. Header files are detected automatically

SRCS = $(shell echo code/*.cpp code/*/src/*.cpp)

# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14

all:compile link

compile: $(SRCS)
	$(foreach f, $^, $(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $(basename $(f)).cpp -o $(BUILD_DIR)/$(notdir $(basename $(f))).o;)

link: $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)

clean:
	rm build/*
