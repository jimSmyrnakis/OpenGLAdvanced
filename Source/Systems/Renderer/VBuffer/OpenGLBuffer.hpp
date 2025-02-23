#pragma once
#include "../Buffer.hpp"
#include <string>
#include <glad/glad.h>

namespace Game{

    

    class OpenGLIndexBuffer : public IndexBuffer{
        public:
            OpenGLIndexBuffer(uint32_t* indexData , dotSize size);
            virtual ~OpenGLIndexBuffer(void);

            virtual uint32_t GetCount(void) const override;
            virtual void     Bind(void)     const override;
            virtual void     Unbind(void)   const override;
        private:
            uint32_t m_ObjectId;
            uint32_t m_Count;
    };

    class OpenGLVertexArray : public VertexArray{
        public:
            OpenGLVertexArray(void);
            ~OpenGLVertexArray(void);

            virtual void Bind(void) const override;
            virtual void Unbind(void) const override;
            virtual void AddVertexBuffer(const VertexBuffer& vo) override;
            virtual void SetIndexBuffer(const IndexBuffer& io) override;
            virtual IndexBuffer& GetIndexBuffer(void) const override;
            
        private:
            uint32_t                    m_ObjectId;
            std::vector<VertexBuffer*>  m_VElements;
            IndexBuffer*                m_IElement;
    };

}