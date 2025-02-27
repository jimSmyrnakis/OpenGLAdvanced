#include "Shader.hpp"
#include <glad/gl.h>
#include <unordered_map>

#include "Compile.cpp"

namespace Game{

    

    Shader::Shader(void){
        GLCALL( m_ProgramId = glCreateProgram() );
    }

    Shader::~Shader(void){
        GLCALL( glDeleteProgram(m_ProgramId));
    }

    void Shader::SetShader(const char* source ){
        LinkProgram(source , m_ProgramId);
        m_Source = (char*)source;
    }

    void Shader::Bind(void) const{
        GLCALL( glUseProgram(m_ProgramId));
    }

    void Shader::Unbind(void) const{
        GLCALL( glUseProgram(0));
    }
    
}