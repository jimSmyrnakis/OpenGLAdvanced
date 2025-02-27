#include "VLayout.hpp"

namespace Game{
    u32 SizeOfShaderDataType(ShaderDataType type){

        switch(type){
            case ShaderDataType::Float  : return 1*sizeof(float);
            case ShaderDataType::Float2 : return 2*sizeof(float);
            case ShaderDataType::Float3 : return 3*sizeof(float);
            case ShaderDataType::Float4 : return 4*sizeof(float);
            case ShaderDataType::Mat3   : return 3*3*sizeof(float);
            case ShaderDataType::Mat4   : return 4*4*sizeof(float);
            case ShaderDataType::Int    : return 1*sizeof(int);
            case ShaderDataType::Int2   : return 2*sizeof(int);
            case ShaderDataType::Int3   : return 3*sizeof(int);
            case ShaderDataType::Int4   : return 4*sizeof(int);
            case ShaderDataType::Bool   : return 1*sizeof(bool);
        };
        ASSERT(0 , "Unknown Shader Data Type !");
        return 0;
    }

    GLenum ShaderDataTypeToOpenGLType(ShaderDataType type){
        switch(type){
            case ShaderDataType::Float  : return GL_FLOAT;
            case ShaderDataType::Float2 : return GL_FLOAT;
            case ShaderDataType::Float3 : return GL_FLOAT;
            case ShaderDataType::Float4 : return GL_FLOAT;
            case ShaderDataType::Mat3   : return GL_FLOAT;
            case ShaderDataType::Mat4   : return GL_FLOAT;
            case ShaderDataType::Int    : return GL_INT  ;
            case ShaderDataType::Int2   : return GL_INT  ;
            case ShaderDataType::Int3   : return GL_INT  ;
            case ShaderDataType::Int4   : return GL_INT  ;
            case ShaderDataType::Bool   : return GL_BOOL ;
        };
        ASSERT(0 , "Unknown Shader Data Type !");
        return 0;
    }

    /*
        ==================================================================================================================================
        ==============================================================Vertex Attribute====================================================
        ==================================================================================================================================
    */

    VertexAttribute::VertexAttribute( ShaderDataType type , bool Norm)
        :   Type(type) , Size(0) , Offs(0) , Normallized(Norm) {
        Size = SizeOfShaderDataType(Type);

    }

    u32 VertexAttribute::GetComponentCount(void) const{

        switch(Type){
            case ShaderDataType::Float  : return 1  ;
            case ShaderDataType::Float2 : return 2  ;
            case ShaderDataType::Float3 : return 3  ;
            case ShaderDataType::Float4 : return 4  ;
            case ShaderDataType::Mat3   : return 3*3;
            case ShaderDataType::Mat4   : return 4*4;
            case ShaderDataType::Int    : return 1  ;
            case ShaderDataType::Int2   : return 2  ;
            case ShaderDataType::Int3   : return 3  ;
            case ShaderDataType::Int4   : return 4  ;
            case ShaderDataType::Bool   : return 1  ;
        };
        ASSERT(0 , "Unknown Shader Data Type !");
        return 0;
    }

    /*
        ==================================================================================================================================
        ==============================================================Vertex Layout=======================================================
        ==================================================================================================================================
    */
    
    VertexLayout::VertexLayout(void){
        m_Stride = 0;
    }
    
    const std::vector<VertexAttribute>& VertexLayout::GetAttributes(void) const { return m_Attributes; }
    
    u32 VertexLayout::GetStride(void) const { return m_Stride; }

    void VertexLayout::AddAttribute(const VertexAttribute& attribute){
        m_Attributes.push_back(attribute);
        CalculateOffsetsAndStride();
    }

    void VertexLayout::CalculateOffsetsAndStride(void){
        ASSERT(m_Attributes.size() , "Vertex Buffer Layout has not Vertex Attributes specified!");
        uint32_t Offset = 0;
        for (VertexAttribute& attribute : m_Attributes){
            attribute.Offs = Offset;
            Offset += attribute.Size;
        }
        m_Stride = Offset;
    
    }
    
}