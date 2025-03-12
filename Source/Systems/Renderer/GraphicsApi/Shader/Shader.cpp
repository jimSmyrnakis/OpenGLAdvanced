#include "Shader.hpp"
#include <glad/gl.h>

namespace Game{

    

    Shader::Shader(VShader& Vertex , FShader& Fragment , alloc Malloc, dalloc Free ){
        m_Fragment  = nullptr;
        m_Vertex    = nullptr;
        m_Uniforms  = nullptr;

        ASSERT(Malloc , "nullptr for memory allocator function !!!");
        if (Malloc == nullptr)
            Malloc = malloc;
        
        ASSERT(Free , "nullptr for memory free function !!!");
        if (Free == nullptr)
            Free = free;
        
        m_HasProgram = true;

        if (Vertex.HasCompiled() == false){
            ASSERT(0 , "Vertex Shader has not comppiled !!!");
            m_HasProgram = false;
            return;
        }

        if (Fragment.HasCompiled() == false){
            ASSERT(0, "Fragment Shader has not compiled !!!");
            m_HasProgram = false;
            return;
        }

        GLCALL( m_ProgramId = glCreateProgram() );

        if (m_ProgramId == 0){
            m_HasProgram = false;
            return ;
        }

        GLCALL( glAttachShader(m_ProgramId , Vertex.GetId()) );
        GLCALL( glAttachShader(m_ProgramId , Fragment.GetId()) );

        GLCALL( glLinkProgram(m_ProgramId) );
        GLint program_linked;
        glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &program_linked);
        if (program_linked != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(m_ProgramId, 1024, &log_length, message);
            ASSERT(0 , message);
            m_HasProgram = false;
            return;
        }

        m_Malloc    = Malloc;
        m_Free      = Free;
        m_Vertex    = &Vertex;
        m_Fragment  = &Fragment;

        FindUniforms();

    }

    Shader::~Shader(void){
        GLCALL( glDeleteProgram(m_ProgramId));
        if (m_Uniforms)
            delete m_Uniforms;

        if (m_Fragment != nullptr){
           GLCALL( glDetachShader(m_ProgramId , m_Fragment->GetId() ) );
        }

        if (m_Vertex != nullptr){
            GLCALL( glDetachShader(m_ProgramId , m_Vertex->GetId()) );
        }


        
        
    }

    


    void Shader::Bind(void) {
        GLCALL( glUseProgram(m_ProgramId));
        UpdateUniforms();
    }

    void Shader::Unbind(void) {
        GLCALL( glUseProgram(0));
    }
    
    UBuffer* Shader::GetUniforms(void) { 
        ASSERT(m_HasProgram , "No Program is Created !!!");
        return m_Uniforms; 
    }

    //TODO
    void Shader::FindUniforms(void){
        u32 UniformsCount;
        
    }

    //TODO
    void Shader::UpdateUniforms(void){

    }
}