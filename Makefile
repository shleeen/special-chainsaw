PROJECT_NAME = example

# Define the names of key files
SOURCE_FILE = $(PROJECT_NAME).cpp
OBJECT_FILE = $(PROJECT_NAME).o
EXECUTABLE = $(PROJECT_NAME).exe
# WINDOW_SOURCE = libs/sdw/DrawingWindow.cpp
# WINDOW_OBJECT = libs/sdw/DrawingWindow.o

RANDOM_SOURCE = random.cpp
RANDOM_OBJECT = random.o

CTRNN_SOURCE = CTRNN.cpp
CTRNN_OBJECT = CTRNN.o

EXAMPLE_SOURCE = example.cpp
EXAMPLE_OBJECT = example.o


# Build settings
COMPILER = g++ 
# COMPILER = g++ -Xpreprocessor -fopenmp 
COMPILER_OPTIONS = -c -pipe -Wall -std=c++11
DEBUG_OPTIONS = -ggdb -g3
FUSSY_OPTIONS = -Werror -pedantic
SANITIZER_OPTIONS = -O1 -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
SPEEDY_OPTIONS = -Ofast -funsafe-math-optimizations -march=native
LINKER_OPTIONS = 
#-mconsole

# Set up flags
# SDW_COMPILER_FLAGS := -I./libs/sdw
# GLM_COMPILER_FLAGS := -I./libs/glm
# If you have a manual install of SDL, you might not have sdl2-config. Compiler flags should be something like: -I/usr/local/include/SDL2 -D_THREAD_SAFE
# SDL_COMPILER_FLAGS := $(shell sdl2-config --cflags)
# If you have a manual install of SDL, you might not have sdl2-config. Linker flags should be something like: -L/usr/local/lib -lSDL2
# SDL_LINKER_FLAGS := $(shell sdl2-config --libs)
# SDW_LINKER_FLAGS := $(WINDOW_OBJECT) $(HELPER_OBJECT) $(CANVASPOINT_OBJECT) ${TEXTUREPOINT_OBJECT} ${COLOUR_OBJECT} ${CANVASTRIANGLE_OBJECT} ${MODELTRIANGLE_OBJECT} ${UTILS_OBJECT} ${RASTERISE_OBJECT} ${CAMERA_OBJECT} ${RAYTRACER_OBJECT} ${PPM_OBJECT} ${RENDERER_OBJECT} ${MATERIAL_OBJECT}

default: diagnostic

# Rule to help find errors (when you get a segmentation fault)
# NOTE: Needs the "Address Sanitizer" library to be installed in order to work (might not work on lab machines !)
diagnostic: random ctrnn example
	$(COMPILER) $(COMPILER_OPTIONS) $(FUSSY_OPTIONS) $(SANITIZER_OPTIONS) -o $(OBJECT_FILE) $(SOURCE_FILE) $(SDL_COMPILER_FLAGS) $(SDW_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)
	$(COMPILER) $(LINKER_OPTIONS) $(FUSSY_OPTIONS) $(SANITIZER_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) $(SDW_LINKER_FLAGS) $(SDL_LINKER_FLAGS) -lomp
	# $(COMPILER) $(LINKER_OPTIONS) $(FUSSY_OPTIONS) $(SANITIZER_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) $(SDW_LINKER_FLAGS) $(SDL_LINKER_FLAGS)
	./$(EXECUTABLE)

# Rule to compile and link for production release
production: random ctrnn example
	$(COMPILER) $(COMPILER_OPTIONS) -o $(OBJECT_FILE) $(SOURCE_FILE) $(SDL_COMPILER_FLAGS) $(SDW_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)
	$(COMPILER) $(LINKER_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) $(SDW_LINKER_FLAGS) $(SDL_LINKER_FLAGS) -lomp
	# $(COMPILER) $(LINKER_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) $(SDW_LINKER_FLAGS) $(SDL_LINKER_FLAGS) 
	./$(EXECUTABLE)

# Rule to compile and link for use with a debugger
debug: random ctrnn
	$(COMPILER) $(COMPILER_OPTIONS) $(DEBUG_OPTIONS) -o $(OBJECT_FILE) $(SOURCE_FILE)
	$(COMPILER) $(LINKER_OPTIONS) $(DEBUG_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) 
	./$(EXECUTABLE)

# Rule to build for high performance executable
speedy: random ctrnn example
	$(COMPILER) $(COMPILER_OPTIONS) $(SPEEDY_OPTIONS) -o $(OBJECT_FILE) $(SOURCE_FILE) $(SDL_COMPILER_FLAGS) $(SDW_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)
	$(COMPILER) $(LINKER_OPTIONS) $(SPEEDY_OPTIONS) -o $(EXECUTABLE) $(OBJECT_FILE) $(SDW_LINKER_FLAGS) $(SDL_LINKER_FLAGS)
	./$(EXECUTABLE)


# Rule for building the DisplayWindow
# window:
# 	$(COMPILER) $(COMPILER_OPTIONS) -o $(WINDOW_OBJECT) $(WINDOW_SOURCE) $(SDL_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)


random:
	$(COMPILER) $(COMPILER_OPTIONS) -o $(RANDOM_OBJECT) $(RANDOM_SOURCE)

ctrnn:
	$(COMPILER) $(COMPILER_OPTIONS) -o $(CTRNN_OBJECT) $(CTRNN_SOURCE) $(SDL_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)

example:
	$(COMPILER) $(COMPILER_OPTIONS) -o $(EXAMPLE_OBJECT) $(EXAMPLE_SOURCE) $(SDL_COMPILER_FLAGS) $(GLM_COMPILER_FLAGS)


# Files to remove during clean
clean:
	rm $(OBJECT_FILE)
	rm $(EXECUTABLE)