#include <Defs.hpp>
#include "ReadSource.cpp"

namespace Game{
    u32 CompileShader(const char* src , GLenum ShaderType){
        switch(ShaderType){
            case GL_VERTEX_SHADER:
            case GL_FRAGMENT_SHADER:
            case GL_GEOMETRY_SHADER:
                break;
            default:
                ASSERT(0 , "Unsupported Shader type !!!");
                return 0;
        }
        
        i32 shad;
        GLCALL( shad = glCreateShader(ShaderType) );
        /*Create The Shader Object*/
        GLCALL( glShaderSource(shad, 1, &src, 0) );
        /*Set the source to the Shader Object */
        GLCALL( glCompileShader(shad) );
        /*Compile the Shader */
        i32 ShaderCompiled;
        glGetShaderiv(shad, GL_COMPILE_STATUS, &ShaderCompiled);
        /*Get Compilation Status*/
        if (ShaderCompiled == GL_FALSE){
            // if compilation failed
            char message[1024];
            i32  len = 1024;
            glGetShaderInfoLog(shad, 1024, &len, message);
            ASSERT(0 , (const char*)message);

        }

        return shad;

    }

    void LinkProgram(const char* src , u32 programId ){
        std::unordered_map<GLenum, std::string> Shads = SplitShader(std::string(src));
        u32 ShadersIds[3];
        

        ShadersIds[0] = CompileShader(Shads[GL_VERTEX_SHADER].c_str()   , GL_VERTEX_SHADER);
        auto it = Shads.find(GL_GEOMETRY_SHADER);
        if (it != Shads.end())
            ShadersIds[1] = CompileShader(it->second.c_str(), GL_GEOMETRY_SHADER);
        else
            ShadersIds[1] = 0;
        ShadersIds[2] = CompileShader(Shads[GL_FRAGMENT_SHADER].c_str() , GL_FRAGMENT_SHADER);

        
        /*Attach all shaders*/
        for (int i = 0; i < 3; i++){
            if (ShadersIds[i] == 0)
                continue;
            GLCALL( glAttachShader(programId , ShadersIds[i] ) );
        }

        GLCALL( glLinkProgram(programId) );
        GLint program_linked;
        glGetProgramiv(programId, GL_LINK_STATUS, &program_linked);
        if (program_linked != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetProgramInfoLog(programId, 1024, &log_length, message);
            ASSERT(0 , message);
        }

        /*Delete and Detach Shader's*/
        for (int i = 0; i < Shads.size(); i++){
            if (ShadersIds[i] == 0)
                break;

            GLCALL( glDetachShader(programId , ShadersIds[i] ) );    
            GLCALL( glDeleteShader(ShadersIds[i]) );
        }


    }
}