#include <unordered_map>
#include <string>
#include <string.h>
#include <glad/gl.h>

GLenum ShaderTypeFromString(const std::string& type){
    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment")
        return GL_FRAGMENT_SHADER;
    if (type == "geometry")
        return GL_GEOMETRY_SHADER;
    
    ASSERT(0 , "Undefined Shader Type " );

    return 0;
}

std::unordered_map<GLenum , std::string> SplitShader(const std::string& ShaderSource){
    std::unordered_map<GLenum , std::string> spliter;
    const char* typeToken = "#type";
    size_t typeTokenSize = strlen(typeToken);
    size_t pos = ShaderSource.find(typeToken , 0);

    while(pos != std::string::npos){

        size_t eol = ShaderSource.find_first_of("\r\n", pos);
        ASSERT(eol != std::string::npos , "Syntax error");
        size_t begin = pos + typeTokenSize + 1;
        std::string type = ShaderSource.substr(begin , eol - begin );
        ASSERT(ShaderTypeFromString(type),"Invalid Shader Type !");

        size_t nextLinePos = ShaderSource.find_first_not_of("\r\n" , eol);
        pos = ShaderSource.find(typeToken , nextLinePos);
        
        spliter[ShaderTypeFromString(type)] = ShaderSource.substr(nextLinePos , 
        pos - 
        ((nextLinePos == std::string::npos) ? (ShaderSource.size() -1) : (nextLinePos))
        );

        if (nextLinePos == std::string::npos)
            break;
        
        
    }

    printf("========Vertex Shader=========\n%s\n" , spliter[GL_VERTEX_SHADER].c_str());
    //printf("========Geometry Shader=======\n%s\n" , spliter[GL_GEOMETRY_SHADER].c_str());
    printf("========Fragment Shader=======\n%s\n" , spliter[GL_FRAGMENT_SHADER].c_str());


    return spliter;
}

