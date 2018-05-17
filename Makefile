# Libraries on which TARGET depends
LIBS = lib/eigen/
# Name of the executable
TARGET = frostAcre.exe
RESULTS_DEFAULT = results.txt
# Place to store all generated files
BUILD_DIR = build
# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14 -Wall -Wextra

# All source files. Header files are detected automatically
SRCS = $(shell find ./code/ ./lib/midifile -name \*.cpp)
BASE = $(foreach f, $(SRCS), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)

# PHONY converts all "file conversor" to simple commands
.PHONY: all clean test run midi

all: $(BUILD_DIR)/$(TARGET)

clean:
	rm build/*

run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)

test: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) "./test/obj/simpleForm/simpleForm.obj" "./test/json/wood.json" "./test/midis/allNotes.mid" ""

midi: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) "./test/midis/allNotes.mid" "./test/jsonMidi/hmm.json"

# SECONDEXPANSION works like first strike ($) and second strike ($$) on magic
.SECONDEXPANSION:
%.o: $$(shell find ./code/ ./lib/midifile -name  $$(notdir $$(basename $$@)).cpp)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)
