#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

namespace Game{

        typedef  int32_t i32;
        typedef uint32_t u32;

        typedef  int16_t i16;
        typedef uint16_t u16;

        typedef  int8_t i8;
        typedef uint8_t u8;

        typedef  int64_t i64;
        typedef uint64_t u64;
}

#define __break_point_ asm("int3")

#define ASSERT(x , ...) if (!(x)) { fprintf(stderr , __VA_ARGS__ ); __break_point_;}

void    GLClearErrors  (void);
bool    GLLogCall(const char* FunctionName , const char* SourceFile , unsigned int line);
#define GLCALL(function) \
        GLClearErrors();\
        (function);\
        ASSERT(GLLogCall(#function , __FILE__ , __LINE__ ) , ":(");
