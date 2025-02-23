#include "OpenGLBuffer.hpp"
#include <glad/glad.h>

GLenum dot::ShaderDataTypeToOpenGLType(dot::ShaderDataType type){

    switch(type){
        case ShaderDataType::Float  : return GL_FLOAT;
        case ShaderDataType::Float2 : return GL_FLOAT;
        case ShaderDataType::Float3 : return GL_FLOAT;
        case ShaderDataType::Float4 : return GL_FLOAT;
        case ShaderDataType::Mat3   : return GL_FLOAT;
        case ShaderDataType::Mat4   : return GL_FLOAT;
        case ShaderDataType::Int    : return GL_INT;
        case ShaderDataType::Int2   : return GL_INT;
        case ShaderDataType::Int3   : return GL_INT;
        case ShaderDataType::Int4   : return GL_INT;
        case ShaderDataType::Bool   : return GL_BOOL;
    };
    DOT_ENGINE_ASSERT(0 , "Unknown Shader Data Type !");
    return 0;
}
//================================================================================================
//===========================Vertex Buffer========================================================
//================================================================================================
dot::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertexData , dotSize count) : VertexBuffer() , m_Layout({{"None" , ShaderDataType::Bool}})  {
    glGenBuffers(1 , &m_ObjectId);
    glBindBuffer(GL_ARRAY_BUFFER , m_ObjectId);
    glBufferData(GL_ARRAY_BUFFER , count*sizeof(float) , vertexData , GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

dot::OpenGLVertexBuffer::~OpenGLVertexBuffer(void){
    glDeleteBuffers(1 , &m_ObjectId);
}

void dot::OpenGLVertexBuffer::Bind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER , m_ObjectId);
}

void dot::OpenGLVertexBuffer::Unbind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER , 0);
}

dot::VertexLayout& dot::OpenGLVertexBuffer::GetLayout(void) {
    return m_Layout;
}

const dot::VertexLayout& dot::OpenGLVertexBuffer::GetLayout(void) const {
    return m_Layout;
}

void dot::OpenGLVertexBuffer::SetLayout(const dot::VertexLayout layout) {
    m_Layout = layout;
}
//================================================================================================
//===========================Index  Buffer========================================================
//================================================================================================
dot::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indexData , dotSize count) : IndexBuffer() , m_Count(count) {
    glGenBuffers(1 , &m_ObjectId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_ObjectId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , count*sizeof(uint32_t) , indexData , GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}

dot::OpenGLIndexBuffer::~OpenGLIndexBuffer(void){
    glDeleteBuffers(1 , &m_ObjectId);
}

void dot::OpenGLIndexBuffer::Bind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_ObjectId);
}

void dot::OpenGLIndexBuffer::Unbind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}

uint32_t dot::OpenGLIndexBuffer::GetCount(void) const {
    return m_Count;
}


//================================================================================================
//===========================Vertex Array ========================================================
//================================================================================================

dot::OpenGLVertexArray::OpenGLVertexArray(void) : m_IElement(nullptr){
    glGenVertexArrays(1 , &m_ObjectId);
    
}

dot::OpenGLVertexArray::~OpenGLVertexArray(void){
    glDeleteVertexArrays(1, &m_ObjectId);
}

void dot::OpenGLVertexArray::Bind(void) const {
    glBindVertexArray(m_ObjectId);
    for (auto el : m_VElements)
        el->Bind();
    

    if (m_IElement != nullptr)
        m_IElement->Bind();

    
}

void dot::OpenGLVertexArray::Unbind(void) const {
    
    for (auto el : m_VElements)
        el->Unbind();
    

    if (m_IElement != nullptr)
        m_IElement->Unbind();
        
    glBindVertexArray(0);
}


void dot::OpenGLVertexArray::AddVertexBuffer(const dot::VertexBuffer& vo) {
    DOT_ENGINE_ASSERT(vo.GetLayout().GetElements().size() , "Vertex Buffer has no layout !");
    glBindVertexArray(m_ObjectId);
    vo.Bind();

    uint32_t layout_index = 0;

    VertexElement element = vo.GetLayout().GetElements().at(layout_index);

    for (layout_index = 0 ; layout_index < vo.GetLayout().GetElements().size(); layout_index++){

        glEnableVertexAttribArray(layout_index);
        element = vo.GetLayout().GetElements().at(layout_index);
        glVertexAttribPointer(
            layout_index ,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLType(element.Type) ,
            element.Normallized ? GL_FALSE : GL_TRUE ,
            vo.GetLayout().GetStride() ,
            (const void*)element.Offs 
        );
    }

    m_VElements.push_back((dot::VertexBuffer*)&vo);
}

void dot::OpenGLVertexArray::SetIndexBuffer(const dot::IndexBuffer& io) {
    glBindVertexArray(m_ObjectId);
    io.Bind();
    m_IElement = (IndexBuffer*)&io;
}

dot::IndexBuffer& dot::OpenGLVertexArray::GetIndexBuffer(void) const {
    DOT_ENGINE_ASSERT(m_IElement , "No Index buffer is set to the Vertex Array !");
    return *m_IElement;
}
