#Base directories
ExeDir= ./Executables
BinDir= ./Binaries
SrcDir= ./Source

#Libraries Include files
GladInc= ./Glad/Include
GLFWInc= ./GLFW/include
GLMInc = ./glm
AssimpInc= ./assimp/include

#Libraries Dir 
GladLib= ./Glad/Library/Linux/x86_64/Debug
GLFWLib= ./GLFW/build/src

#g++ Flags 
FlagsGpp= -L$(GladLib) -L$(GLFWLib) -I$(GLFWInc) -I$(GLMInc) -I$(AssimpInc) -I$(GladInc) -g -lglad -lglfw

all: test 
	echo "Finish..."

test: $(SrcDir)/test.cpp 
	g++ -o $(ExeDir)/test $(SrcDir)/test.cpp $(FlagsGpp) 

ExecFiles= $(ExeDir)/test
BinnFiles= 

execute: $(ExecFiles)
	$(ExeDir)/test 

clear:
	rm -rf $(ExecFiles) $(BinnFiles)
