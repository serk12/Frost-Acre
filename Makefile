# exe vars
MODEL = cup
JSON = "./data/json/guitar.json"
MIDI =  "./data/midis/cuartoDeSegundo.mid"

JSONNOTE = "./data/jsonMidi/$(MODEL).json"
WAVOUT =  "./data/wav/$(MODEL).wav"
PRERENDERDOC = "./data/prerender/$(MODEL).json"
OBJ3D = "./data/obj/$(MODEL).obj"

# Libraries on which TARGET depends
LIBS = lib/eigen/
# Name of the executable
TARGET = frostAcre.exe
RESULTS_DEFAULT = results.txt
# Place to store all generated files
BUILD_DIR = build
FOLDERS = $(BUILD_DIR) ./data/jsonMidi ./data/prerender ./data/wav
# Compiler. On non-gnu systems you may want to change this
CC = g++
EXTRAFLAGS = -std=gnu++14 -Wall -Wextra -fopenmp

# All source files. Header files are detected automatically
SRCS = $(shell find ./code/ ./lib/midifile -name \*.cpp)
BASE = $(foreach f, $(SRCS), $(notdir $(basename $(f))))
OBJECTS = $(foreach f, $(BASE), $(BUILD_DIR)/$(f).o)

# PHONY converts all "file conversor" to simple commands
.PHONY: all clean simulate simulateMem run midi prerender

all: $(FOLDERS) midi prerender simulate

clean:
	rm build/*

run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)

simulateMem: $(BUILD_DIR)/$(TARGET)
	valgrind -v --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSONNOTE)
	valgrind -v --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSON) $(JSONNOTE)
	valgrind -v --leak-check=full --show-leak-kinds=all $(BUILD_DIR)/$(TARGET) $(PRERENDERDOC) $(MIDI) $(JSONNOTE) $(WAVOUT)

midi: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSONNOTE)

prerender: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(OBJ3D) $(JSON) $(PRERENDERDOC)

simulate: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) $(PRERENDERDOC) $(MIDI) $(JSONNOTE) $(WAVOUT)

$(FOLDERS):
	mkdir $@

# SECONDEXPANSION works like first strike ($) and second strike ($$) on magic
.SECONDEXPANSION:
%.o: $$(shell find ./code/ ./lib/midifile -name  $$(notdir $$(basename $$@)).cpp)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) -g -c $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) -I $(LIBS) $(EXTRAFLAGS) $^ -o $(BUILD_DIR)/$(TARGET)
