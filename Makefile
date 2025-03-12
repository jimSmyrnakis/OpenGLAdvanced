#Base directories
ExeDir= ./Executables
BinDir= ./Binaries
SrcDir= ./Source

#Libraries Include files
GladInc= ./Glad/Include
GLFWInc= ./GLFW/include
GLMInc = ./glm
AssimpInc= ./assimp/include
TiffInc= ./TIFF/libtiff/libtiff

#Libraries Dir 
GladLib= ./Glad/Library/Linux/x86_64/Debug
GLFWLib= ./GLFW/build/src
TiffLib= ./TIFF/libtiff/build/libtiff

#TIFF Dir


#includes
Incs= -I$(GLFWInc) -I$(GLMInc) -I$(GladInc) -I$(SrcDir) -I$(TiffInc)

#libraries
libs= -L$(GladLib) -L$(GLFWLib) -L$(TiffLib) -lglad -lglfw #-ltiff
#g++ common Flags
CommonFlags= -g $(Incs)
#g++ Final Flags 
FlagsGpp=  $(libs) $(CommonFlags) -lglad -lglfw -lassimp

ExecFiles= $(ExeDir)/Game
BinnFiles= \
$(BinDir)/Program.o $(BinDir)/Defs.o 	 		\
$(BinDir)/Shader.o $(BinDir)/Model.o 	 		\
$(BinDir)/VBuffer.o $(BinDir)/IBuffer.o  		\
$(BinDir)/VLayout.o $(BinDir)/VABuffer.o 		\
$(BinDir)/FBuffer.o $(BinDir)/Texture2D.o		\
$(BinDir)/Format.o	$(BinDir)/UBuffer.o 		    #$(BinDir)/TextureReader.o

all: Final
	echo "Finish..."


Final: Program.o Defs.o Shader.o IBuffer.o VBuffer.o Model.o VLayout.o VABuffer.o FBuffer.o Texture2D.o Format.o UBuffer.o #TextureReader.o
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

UBuffer.o: $(SrcDir)/Systems/Renderer/GraphicsApi/UBuffer/UBuffer.cpp 
	g++ -c  $(SrcDir)/Systems/Renderer/GraphicsApi/UBuffer/UBuffer.cpp -o $(BinDir)/UBuffer.o $(CommonFlags) 

Texture2D.o: $(SrcDir)/Systems/Renderer/GraphicsApi/Texture/Texture2D.cpp
	g++ -c  $(SrcDir)/Systems/Renderer/GraphicsApi/Texture/Texture2D.cpp -o $(BinDir)/Texture2D.o $(CommonFlags) 

Format.o: $(SrcDir)/Systems/Renderer/GraphicsApi/Format/Format.cpp
	g++ -c  $(SrcDir)/Systems/Renderer/GraphicsApi/Format/Format.cpp -o $(BinDir)/Format.o $(CommonFlags) 

Model.o: $(SrcDir)/Model/Model.cpp 
	g++ -c $(SrcDir)/Model/Model.cpp -o $(BinDir)/Model.o $(CommonFlags) 

TextureReader.o: $(SrcDir)/TextureReader.cpp 
	g++ -c $(SrcDir)/TextureReader.cpp  -o $(BinDir)/TextureReader.o $(CommonFlags) 


executable: $(ExecFiles)
	cd $(ExeDir)
	gdb ./Game
	cd ../  

clear:
	rm -rf $(ExecFiles) $(BinnFiles)
