#pragma once 

#include <Defs.hpp>
#include <glad/gl.h>
#include <vector>


namespace Game{

    enum class ShaderDataType{
        Float ,
        Float2,
        Float3,
        Float4,
        Mat3  ,
        Mat4  ,
        Int   ,
        Int2  ,
        Int3  ,
        Int4  ,
        Bool 
    };

    GLenum ShaderDataTypeToOpenGLType(ShaderDataType type);

    struct VertexAttribute{
        ShaderDataType  Type;
        u32             Size;
        u32             Offs;
        bool            Normallized;

        VertexAttribute( ShaderDataType type , bool Norm = true);

        u32 GetComponentCount(void) const;
    };

    class VertexLayout{
        public:
            
            VertexLayout(void);

            void AddAttribute(const VertexAttribute& attribute);

            const std::vector<VertexAttribute>& GetAttributes(void) const ;

            u32 GetStride(void) const ;
        private:
            std::vector<VertexAttribute> m_Attributes;
            u32                          m_Stride  ;
        private:
            void CalculateOffsetsAndStride(void);
    };
}