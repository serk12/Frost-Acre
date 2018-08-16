# exe vars
PRERENDERDOC = "./data/prerender/pre.json"
OBJ3D = "./data/obj/cube2.obj"
JSON = "./data/json/guitar.json"
MIDI =  "./data/midis/cuartoDeSegundo.mid"
JSONNOTE = "./data/jsonMidi/14def.json"
WAVOUT =  "./data/wav/sound.wav"



# Libraries on which TARGET depends
LIBS = lib/eigen/
# Name of the executable
TARGET = frostAcre.exe
RESULTS_DEFAULT = results.txt
# Place to store all generated files
BUILD_DIR = build
# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14 -Wall -Wextra -fopenmp

# All source files. Header files are detected automatically
SRCS = $(shell find ./code/ ./lib/midifile -name \*.cpp)
BASE = $(foreach f, $(SRCS), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)

# PHONY converts all "file conversor" to simple commands
.PHONY: all clean test testMem run midi prerender

all: midi prerender test

clean:
	rm build/*

run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)

testMem: $(BUILD_DIR)/$(TARGET)
	valgrind -v --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/$(TARGET) $(OBJ3D) $(MIDI) $(JSONNOTE)
	valgrind -v --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSON) $(MIDI) $(JSONNOTE) $(WAVOUT)

midi: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(OBJ3D) $(MIDI) $(JSONNOTE)

prerender: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSON) $(PRERENDERDOC)

test: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(PRERENDERDOC) $(MIDI) $(JSONNOTE) $(WAVOUT)

# SECONDEXPANSION works like first strike ($) and second strike ($$) on magic
.SECONDEXPANSION:
%.o: $$(shell find ./code/ ./lib/midifile -name  $$(notdir $$(basename $$@)).cpp)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)
