#include "Texture.hpp"

namespace Game{
    Texture2D::Texture2D(u32 Unit  ,const Resolution& MaxResolution)  {

        m_TextureUnit = GL_TEXTURE0 + Unit;
        m_MaxResolution = MaxResolution;
        m_HasSpace = true;
        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glGenTextures(1 , &m_ObjectId) );
        GLCALL( glBindTexture(GL_TEXTURE_2D , m_ObjectId) );
        /*A proxy request first */
        //query the desire space
        //glTexStorage2D(GL_PROXY_TEXTURE_2D , 1 , GetOpenGLImageFormat(m_MaxResolution.Format) ,m_MaxResolution.Width , m_MaxResolution.Height );
        //query if the dimensions are zero and if yes , no space has left on the target
        //glTextureParameteri()

        GLCALL( glTexStorage2D(
            GL_TEXTURE_2D , 1 , 
            GetOpenGLInternalTextureFormat(m_MaxResolution.Format) , 
            m_MaxResolution.Width , m_MaxResolution.Height) );

        ASSERT(m_HasSpace , "No Available space for the texture !!!");
        
    }
    Texture2D::~Texture2D(void){
        if (m_HasSpace)
            GLCALL( glDeleteTextures(1 , &m_ObjectId) );
    }

    
    u32  Texture2D::GetUnit(void) const{
        return m_TextureUnit;
    }

    void Texture2D::Bind(void) {
        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glBindTexture(GL_TEXTURE_2D , m_ObjectId) );
    }

    void Texture2D::Unbind(void) {
        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glBindTexture(GL_TEXTURE_2D , 0)); 
    }

    void Texture2D::SetSubImage(void* data , u32 XOffset , u32 YOffset , u32 Width , u32 Height , ImageFormat Format){
        ASSERT(m_HasSpace , "No Space For the Texture exist's !!!");

        GLCALL(glActiveTexture(m_TextureUnit));
        GLCALL(glBindTexture(GL_TEXTURE_2D , m_ObjectId));
        u32 ExternalFormat , DataType;
        GetOpenGLExternalImageFormat(Format , ExternalFormat , DataType);
        GLCALL(glTexSubImage2D(GL_TEXTURE_2D , 0 , XOffset , YOffset , Width , Height , ExternalFormat , DataType , data));

    }

    bool Texture2D::HasAllocated(void) const { return m_HasSpace; }
}