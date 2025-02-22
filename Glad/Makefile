#object folder's
objd32= ./Object/Linux/x86_32/Debug
objr32= ./Object/Linux/x86_32/Release
objd64= ./Object/Linux/x86_64/Debug
objr64= ./Object/Linux/x86_64/Release
objdarm64= ./Object/Linux/Arm64/Debug
objrarm64= ./Object/Linux/Arm64/Release

#Library folder's
libd32= ./Library/Linux/x86_32/Debug
libr32= ./Library/Linux/x86_32/Release
libd64= ./Library/Linux/x86_64/Debug
libr64= ./Library/Linux/x86_64/Release
libdarm64= ./Library/Linux/Arm64/Debug
librarm64= ./Library/Linux/Arm64/Release

#Include folder's
inc= ./Include

#source Folder's
src= ./Source

#common flags
flagsX86_32= -I$(inc) -DDESKTOP_PC
flagsX86_64= -I$(inc) -DDESKTOP_PC
flagsArm64 = -I$(inc) -DRASBERY_PY

#Cross compilers 
I64CC   = x86_64-linux-gnu-gcc
I386CC  = i686-linux-gnu-gcc
ARM64CC = aarch64-linux-gnu-gcc

ARCH := $(shell uname -m)

ifeq ($(ARCH),x86_64)
	I64CC = gcc
else ifeq ($(ARCH),i686)
	I386CC = gcc 
else ifeq ($(ARCH),aarch64)
	ARM64CC = gcc 
endif

library: Compile test
	ar rcs $(libd32)/libglad.a $(objd32)/glad.o
	ar rcs $(libr32)/libglad.a $(objr32)/glad.o
	ar rcs $(libd64)/libglad.a $(objd64)/glad.o
	ar rcs $(libr64)/libglad.a $(objr64)/glad.o
	ar rcs $(libdarm64)/libglad.a $(objdarm64)/glad.o
	ar rcs $(librarm64)/libglad.a $(objrarm64)/glad.o

Compile: $(src)/gl.c $(src)/gles2.c
	$(I386CC)  $(flagsX86_32) -g -c $(src)/gl.c 	-o $(objd32)/glad.o 
	$(I386CC)  $(flagsX86_32)    -c $(src)/gl.c 	-o $(objr32)/glad.o 
	$(I64CC)   $(flagsX86_64) -g -c $(src)/gl.c 	-o $(objd64)/glad.o 
	$(I64CC)   $(flagsX86_64)    -c $(src)/gl.c 	-o $(objr64)/glad.o 
	$(ARM64CC) $(flagsArm64)  -g -c $(src)/gles2.c -o $(objdarm64)/glad.o 
	$(ARM64CC) $(flagsArm64)     -c $(src)/gles2.c -o $(objrarm64)/glad.o 

allLibs= $(libd32)/libglad.a $(libr32)/libglad.a $(libd64)/libglad.a $(libr64)/libglad.a $(libdarm64)/libglad.a $(librarm64)/libglad.a
allObjs= $(objd32)/glad.o    $(objr32)/glad.o    $(objd64)/glad.o    $(objr64)/glad.o    $(objdarm64)/glad.o    $(objrarm64)/glad.o 
allFiles= $(allObjs) $(allLibs)

test:
	file $(objd32)/glad.o 
	file $(objd64)/glad.o 
	file $(objr32)/glad.o 
	file $(objr64)/glad.o
	file $(objrarm64)/glad.o 
	file $(objdarm64)/glad.o 

clear_objects:
	rm -rf $(allObjs)
clear_libraries:
	rm -rf $(allLibs)

clear: clear_objects clear_libraries
	echo "Object's are cleared !"