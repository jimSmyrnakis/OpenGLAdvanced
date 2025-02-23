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

#includes
Incs= -I$(GLFWInc) -I$(GLMInc) -I$(GladInc) -I$(SrcDir)

#libraries
libs= -L$(GladLib) -L$(GLFWLib) -lglad -lglfw
#g++ common Flags
CommonFlags= -g $(Incs)
#g++ Final Flags 
FlagsGpp=  $(libs) $(CommonFlags) -lglad -lglfw -lassimp

ExecFiles= $(ExeDir)/Game
BinnFiles= $(BinDir)/Program.o $(BinDir)/Defs.o $(BinDir)/Shader.o $(BinDir)/Model.o

all: Final
	echo "Finish..."


Final: Program.o Defs.o Shader.o Model.o
	g++ $(BinnFiles) -o $(ExeDir)/Game $(FlagsGpp)

	
Program.o: $(SrcDir)/Program.cpp 
	g++ -c $(SrcDir)/Program.cpp -o $(BinDir)/Program.o  $(CommonFlags) 

Defs.o: $(SrcDir)/Defs.cpp
	g++ -c $(SrcDir)/Defs.cpp -o $(BinDir)/Defs.o $(CommonFlags) 

Shader.o: $(SrcDir)/Systems/Renderer/Shader/Shader.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/Shader/Shader.cpp -o $(BinDir)/Shader.o $(CommonFlags) 

Model.o: $(SrcDir)/Systems/Renderer/Model/Model.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/Model/Model.cpp -o $(BinDir)/Model.o $(CommonFlags) 


executable: $(ExecFiles)
	$(ExeDir)/Game  

clear:
	rm -rf $(ExecFiles) $(BinnFiles)
