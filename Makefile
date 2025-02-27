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
BinnFiles= \
$(BinDir)/Program.o $(BinDir)/Defs.o 	 \
$(BinDir)/Shader.o $(BinDir)/Model.o 	 \
$(BinDir)/VBuffer.o $(BinDir)/IBuffer.o  \
$(BinDir)/VLayout.o $(BinDir)/VABuffer.o \
$(BinDir)/FBuffer.o

all: Final
	echo "Finish..."


Final: Program.o Defs.o Shader.o IBuffer.o VBuffer.o Model.o VLayout.o VABuffer.o FBuffer.o
	g++ $(BinnFiles) -o $(ExeDir)/Game $(FlagsGpp)

	
Program.o: $(SrcDir)/Program.cpp 
	g++ -c $(SrcDir)/Program.cpp -o $(BinDir)/Program.o  $(CommonFlags) 

Defs.o: $(SrcDir)/Defs.cpp
	g++ -c $(SrcDir)/Defs.cpp -o $(BinDir)/Defs.o $(CommonFlags) 

Shader.o: $(SrcDir)/Systems/Renderer/GraphicsApi/Shader/Shader.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/GraphicsApi/Shader/Shader.cpp -o $(BinDir)/Shader.o $(CommonFlags) 

VLayout.o: $(SrcDir)/Systems/Renderer/GraphicsApi/VBuffer/VLayout.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/GraphicsApi/VBuffer/VLayout.cpp -o $(BinDir)/VLayout.o $(CommonFlags) 

VBuffer.o: $(SrcDir)/Systems/Renderer/GraphicsApi/VBuffer/VBuffer.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/GraphicsApi/VBuffer/VBuffer.cpp -o $(BinDir)/VBuffer.o $(CommonFlags) 

IBuffer.o: $(SrcDir)/Systems/Renderer/GraphicsApi/IBuffer/IBuffer.cpp 
	g++ -c $(SrcDir)/Systems/Renderer/GraphicsApi/IBuffer/IBuffer.cpp -o $(BinDir)/IBuffer.o $(CommonFlags) 

VABuffer.o: $(SrcDir)/Systems/Renderer/GraphicsApi/VABuffer/VABuffer.cpp 
	g++ -c  $(SrcDir)/Systems/Renderer/GraphicsApi/VABuffer/VABuffer.cpp -o $(BinDir)/VABuffer.o $(CommonFlags) -Wno-int-to-pointer-cast

FBuffer.o: $(SrcDir)/Systems/Renderer/GraphicsApi/FBuffer/FBuffer.cpp 
	g++ -c  $(SrcDir)/Systems/Renderer/GraphicsApi/FBuffer/FBuffer.cpp -o $(BinDir)/FBuffer.o $(CommonFlags) 

Model.o: $(SrcDir)/Model/Model.cpp 
	g++ -c $(SrcDir)/Model/Model.cpp -o $(BinDir)/Model.o $(CommonFlags) 


executable: $(ExecFiles)
	gdb $(ExeDir)/Game  

clear:
	rm -rf $(ExecFiles) $(BinnFiles)
