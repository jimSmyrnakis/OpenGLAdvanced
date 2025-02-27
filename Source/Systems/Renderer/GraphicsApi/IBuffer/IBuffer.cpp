#include "IBuffer.hpp"
#include <glad/gl.h>

namespace Game{
    IBuffer::IBuffer(void){
       GLCALL( glGenBuffers(1 , &m_BufferId) );
    }
    IBuffer::~IBuffer(void){
        GLCALL( glDeleteBuffers(1 , &m_BufferId) );
    }

    void IBuffer::SetData(void* data , u32 size){
        ASSERT(size , "Index Buffer Data size is zero (0) !!!");

        m_Data = data;
        m_Size = size;

        GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_BufferId) );
        GLCALL( glBufferData(GL_ELEMENT_ARRAY_BUFFER , m_Size , m_Data , GL_STATIC_DRAW) );
        GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0         ) );
    }

    void IBuffer::Bind(void)    const { GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_BufferId) ); }
    void IBuffer::Unbind(void)  const { GLCALL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0         ) ); }
}