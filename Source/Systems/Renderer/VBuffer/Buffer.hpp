#pragma once
#include "../../Core.hpp"
#include <vector>
#include <string>

namespace dot{

    

    uint32_t SizeOfShaderDataType(ShaderDataType type);

    

    class IndexBuffer{

    public:
        IndexBuffer(void);
        virtual ~IndexBuffer(void);

        virtual uint32_t GetCount(void) const = 0;
        virtual void Bind(void) const = 0;
        virtual void Unbind(void) const = 0;
        static IndexBuffer* Create(uint32_t* indexData , dotSize count);
    };



    class VertexBuffer{

    public:
        VertexBuffer(void);
        virtual ~VertexBuffer(void);

        virtual void Bind(void) const = 0;
        virtual void Unbind(void) const = 0;
        virtual VertexLayout& GetLayout(void) = 0;
        virtual const VertexLayout& GetLayout(void) const = 0;
        virtual void SetLayout(const VertexLayout layout) = 0;
        
        static VertexBuffer* Create(float* vertexData , dotSize count);
    };

    class VertexArray{

    public:
        VertexArray(void) = default;
        virtual ~VertexArray(void) = default;

        virtual void Bind(void) const = 0;
        virtual void Unbind(void) const = 0;

        virtual void AddVertexBuffer(const VertexBuffer& buffer) = 0;
        virtual void SetIndexBuffer (const IndexBuffer&  index)  = 0;   

        virtual IndexBuffer& GetIndexBuffer(void) const = 0;     
        
        static VertexArray* Create(void);
    };

};