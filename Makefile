# Libraries on which TARGET depends
LIBS = lib/eigen/
# Name of the executable
TARGET = frostAcre.exe
RESULTS_DEFAULT = results.txt
# Place to store all generated files
BUILD_DIR = build
# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14

# All source files. Header files are detected automatically
SRCS = $(shell find ./code/ -name \*.cpp)
BASE = $(foreach f, $(SRCS), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)

# PHONY converts all "file conversors" to simple commands
.PHONY: all clean test

all: $(TARGET)
clean:
	rm build/*
test: $(TARGET)
	$(BUILD_DIR)/$(TARGET) > $(BUILD_DIR)/$(RESULTS_DEFAULT)
# SECONDEXPANSION works like first strike ($) and second strike ($$) on magic
.SECONDEXPANSION:
%.o: $$(shell find ./code/ -name  $$(notdir $$(basename $$@)).cpp)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)
