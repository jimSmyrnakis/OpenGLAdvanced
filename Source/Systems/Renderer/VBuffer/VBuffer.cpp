#include "VBuffer.hpp"

namespace Game{
    VBuffer::VBuffer(void){
        GLCALL( glGenBuffers(1 , &m_BufferId) );
    }

    VBuffer::~VBuffer(void){
        GLCALL( glDeleteBuffers(1 , &m_BufferId) );
    }

    void VBuffer::SetData(float* data , u32 size){
        ASSERT(size , "Vertex data have 0 size !!!");
        m_Data = data;
        m_Size = size;

        GLCALL( glBufferData(GL_ARRAY_BUFFER , m_Size , m_Data , GL_STATIC_DRAW) );
    }

    void VBuffer::Bind(void) const {  GLCALL( glBindBuffer(GL_ARRAY_BUFFER , m_BufferId) ); }
    void VBuffer::Unbind(void) const { GLCALL( glBindBuffer(GL_ARRAY_BUFFER , 0) ); }

    VertexLayout& VBuffer::GetLayout(void) const  { return (const VertexLayout)m_Layout; }
    void VBuffer::SetLayout(const VertexLayout& layout) ;
}