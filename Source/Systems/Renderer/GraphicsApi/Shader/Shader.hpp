#pragma once 
#include <Defs.hpp>
#include <glm/glm.hpp>
#include "../UBuffer/UBuffer.hpp"
#include "VShader.hpp"
#include "FShader.hpp"
#include <stdlib.h>

namespace Game{


    class Shader{
        

        public:
            Shader(VShader& Vertex , FShader& Fragment , alloc Malloc = malloc, dalloc Free = free);
            ~Shader(void);

            void Bind(void) ;
            void Unbind(void) ;

            UBuffer* GetUniforms(void) ;


        private:
            
            void FindUniforms(void);
            void UpdateUniforms(void);
            
        private:
            u32             m_ProgramId     ;   // id of the program
            VShader*        m_Vertex        ;   // Vertex Shader
            FShader*        m_Fragment      ;   // Fragment Shader
            bool            m_HasProgram    ;   // Used to define if a program has created (usefull for CreateProgram method)    
            UBuffer*        m_Uniforms      ;   // a uniform's buffer for this program
            alloc           m_Malloc        ;   // memory allocation function
            dalloc          m_Free          ;   // memory free function

    };

}