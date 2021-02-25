PROJECT_NAME = $(FILE)

# Define the names of key files
SOURCE_FILE = $(PROJECT_NAME).cpp
OBJECT_FILE = $(PROJECT_NAME).o
EXECUTABLE = $(PROJECT_NAME)

RANDOM_SOURCE = random.cpp
RANDOM_OBJECT = random.o

CTRNN_SOURCE = CTRNN.cpp
CTRNN_OBJECT = CTRNN.o

AGENT_SOURCE = Agent.cpp
AGENT_OBJECT = Agent.o


# Build settings
COMPILER = g++ 
# COMPILER = g++ -Xpreprocessor -fopenmp 
COMPILER_OPTIONS = -pipe -Wall -std=c++11
# -c  --> add this for compile and link separately 
DEBUG_OPTIONS = -ggdb -g3
FUSSY_OPTIONS = -Werror -pedantic
SANITIZER_OPTIONS = -O1 -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
SPEEDY_OPTIONS = -Ofast -funsafe-math-optimizations -march=native
LINKER_OPTIONS =


default: diagnostic

# Rule to help find errors (when you get a segmentation fault)
# NOTE: Needs the "Address Sanitizer" library to be installed in order to work (might not work on lab machines !)
diagnostic:
	$(COMPILER) $(COMPILER_OPTIONS) $(FUSSY_OPTIONS) $(SANITIZER_OPTIONS) $(RANDOM_SOURCE) $(CTRNN_SOURCE) $(AGENT_SOURCE) $(SOURCE_FILE) -o $(EXECUTABLE)
	./$(EXECUTABLE)

# Rule to compile and link for use with a debugger
debug: 
	$(COMPILER) $(COMPILER_OPTIONS) $(DEBUG_OPTIONS) $(RANDOM_SOURCE) $(CTRNN_SOURCE) $(AGENT_SOURCE) $(SOURCE_FILE) -o $(EXECUTABLE)
	./$(EXECUTABLE)

# Rule to build for high performance executable
speedy: 
	$(COMPILER) $(COMPILER_OPTIONS) $(SPEEDY_OPTIONS) $(RANDOM_SOURCE) $(CTRNN_SOURCE) $(AGENT_SOURCE) $(SOURCE_FILE) -o $(EXECUTABLE)
	./$(EXECUTABLE)


# Rule for building files
# random:
# 	$(COMPILER) $(COMPILER_OPTIONS) -o $(RANDOM_OBJECT) $(RANDOM_SOURCE)

# ctrnn:
# 	$(COMPILER) $(COMPILER_OPTIONS) -o $(CTRNN_OBJECT) $(CTRNN_SOURCE) 

# agent:
# 	$(COMPILER) $(COMPILER_OPTIONS) -o $(AGENT_OBJECT) $(AGENT_SOURCE) 


# Files to remove during clean
clean:
	rm $(OBJECT_FILE)
	rm $(EXECUTABLE)