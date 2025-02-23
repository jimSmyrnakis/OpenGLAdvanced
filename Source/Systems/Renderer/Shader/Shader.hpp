#pragma once 
#include <Defs.hpp>
#include <stdint.h>
#include <stddef.h>

namespace Game{


    class Shader{
        public:
            Shader(void);
            ~Shader(void);

            void SetShader(const char* source );

            void Bind(void) const;
            void Unbind(void) const;

        private:
            void GenerateShaders(void);
            
        private:
            u32             m_ProgramId;
            char*           m_Source;

    };

}