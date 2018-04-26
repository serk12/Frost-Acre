# Libraries on which TARGET depends
LIBS = lib/eigen/
# Name of the executable
TARGET = frostAcre.exe
# Place to store all generated files
BUILD_DIR = build
# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14

# All source files. Header files are detected automatically
SRCS = $(shell find ./code/ -name \*.cpp)
BASE = $(foreach f, $(SRCS), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)
<<<<<<< HEAD

# PHONY converts all "file conversors" to simple commands
.PHONY: all clean

all: $(TARGET)
=======

# PHONY converts all "file conversors" to simple commands
.PHONY: all clean
>>>>>>> 8bd153b5f0e8e52b1fceeda80de3a8c6ede11306

all: $(TARGET)
clean:
	rm build/*
<<<<<<< HEAD
# SECONDEXPANSION works like first strike ($) and second strike ($$) on magic
.SECONDEXPANSION:
%.o: $$(shell find ./code/ -name  $$(notdir $$(basename $$@)).cpp)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $< -o $@
=======
	
%.o:
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $(shell find ./code/ -name $(notdir $(basename $@)).cpp) -o $@
>>>>>>> 8bd153b5f0e8e52b1fceeda80de3a8c6ede11306

$(TARGET): $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)
