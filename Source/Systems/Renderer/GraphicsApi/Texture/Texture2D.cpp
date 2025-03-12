#include "Texture2D.hpp"

namespace Game{
    
    Texture2D::Texture2D(u32 Unit  ,const InternalResolution& MaxResolution)  {
        
        SetUnit(Unit);
        m_MaxResolution = MaxResolution;
        m_HasSpace = true;

        GLCALL( glGenSamplers(1 , &m_Sampler2DId) );
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE ) );
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE ) );
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_MIN_FILTER , GL_LINEAR));
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_MAG_FILTER , GL_LINEAR));

        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glGenTextures(1 , &m_ObjectId) );
         
        GLCALL( glBindTexture(GL_TEXTURE_2D , m_ObjectId) );
        GLCALL( glBindSampler(m_TextureUnit - GL_TEXTURE0 , m_Sampler2DId ) );
        /*A proxy request first - TODO */
        //query the desire space
        //glTexStorage2D(GL_PROXY_TEXTURE_2D , 1 , GetOpenGLImageFormat(m_MaxResolution.Format) ,m_MaxResolution.Width , m_MaxResolution.Height );
        //query if the dimensions are zero and if yes , no space has left on the target device
        //glTextureParameteri()
        //ASSERT(m_HasSpace , "No Available space for the texture !!!");
        GLCALL( glTexStorage2D(
            GL_TEXTURE_2D , 1 , 
            GetOpenGLInternalTextureFormat(m_MaxResolution.Format) , 
            m_MaxResolution.Width , m_MaxResolution.Height) );

        
        
        
    }

    Texture2D::~Texture2D(void){
        if (m_HasSpace)
            GLCALL( glDeleteTextures(1 , &m_ObjectId) );
        GLCALL( glDeleteSamplers(1 , &m_Sampler2DId) );
    }

    
    u32  Texture2D::GetUnit(void) const{
        return m_TextureUnit - GL_TEXTURE0;
    }

    void Texture2D::Bind(void) {
        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glBindTexture(GL_TEXTURE_2D , m_ObjectId) );
        GLCALL( glBindSampler(m_TextureUnit - GL_TEXTURE0 , m_Sampler2DId) );
    }

    void Texture2D::Unbind(void) {
        GLCALL( glActiveTexture(m_TextureUnit) );
        GLCALL( glBindTexture(GL_TEXTURE_2D , 0)); 
        GLCALL( glBindSampler(m_TextureUnit - GL_TEXTURE0 , 0) );
    }

    void Texture2D::SetSubImage(void* data , u32 XOffset , u32 YOffset , u32 Width , u32 Height , TextureExternalFormat Format){
        ASSERT(m_HasSpace , "No Space For the Texture exist's !!!");

        GLCALL(glActiveTexture(m_TextureUnit));
        GLCALL(glBindTexture(GL_TEXTURE_2D , m_ObjectId));
        u32 ExternalFormat , DataType;
        ExternalFormat = GetOpenGLExternalTextureFormat(Format);
        DataType = GetOpenGLExternalTextureType(Format);
        GLCALL(glTexSubImage2D(GL_TEXTURE_2D , 0 , XOffset , YOffset , Width , Height , ExternalFormat , DataType , data));

    }

    bool Texture2D::HasAllocated(void) const { return m_HasSpace; }

    void Texture2D::SetUnit(u32 TextureUnit) { m_TextureUnit = GL_TEXTURE0 + TextureUnit; }

    void Texture2D::SetFilter(Filter MagnificationFilter , Filter MinificationFilter){
        ASSERT( 
            (MagnificationFilter==Filter::LINEAR) || (MagnificationFilter==Filter::NEAREST) , 
            "Magnification Filter is not a valid 2D Texture Filter !");

        ASSERT( 
            (MinificationFilter==Filter::LINEAR) || (MinificationFilter==Filter::NEAREST) , 
            "Minification Filter is not a valid 2D Texture Filter !");

        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE ) );
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_WRAP_T , GL_CLAMP_TO_EDGE ) );
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_MIN_FILTER , GetOpenGLFilter(MagnificationFilter)));
        GLCALL( glSamplerParameteri(m_Sampler2DId , GL_TEXTURE_MAG_FILTER , GetOpenGLFilter(MinificationFilter)));

    }

}