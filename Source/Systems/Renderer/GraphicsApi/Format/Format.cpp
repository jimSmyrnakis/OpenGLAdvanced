#include "Format.hpp"

#include <glad/gl.h>



namespace Game{
    u32 GetOpenGLInternalTextureFormat(ImageFormat format){
        switch (format){
            case ImageFormat::RGB4      : return GL_RGB4    ;
            case ImageFormat::RGB8      : return GL_RGB8    ;
            case ImageFormat::RGBA2     : return GL_RGBA2   ;
            case ImageFormat::RGBA4     : return GL_RGBA4   ;
            case ImageFormat::RGBA8     : return GL_RGBA8   ;
            case ImageFormat::RGB5A1    : return GL_RGB5_A1 ;
            case ImageFormat::RGBA16    : return GL_RGBA16  ; 
            case ImageFormat::RGBA32    : return GL_RGBA32  ;
            
            default:
                ASSERT(0 , "Undefined Image Format Type !!!");
        }
        return 0;
    }

    u32 GetOpenGLDepthFormat(DepthFormat format){
        switch(format){
            case DepthFormat::DEPTH16 : return GL_DEPTH_COMPONENT16;
            case DepthFormat::DEPTH24 : return GL_DEPTH_COMPONENT24;
            case DepthFormat::DEPTH32 : return GL_DEPTH_COMPONENT32;
            default:
                ASSERT(0 , "Undefind Depth Foramt Type !!!");
                return 0;
        }
        return 0;
    }


    u32 GetOpenGLFilter(Filter filter){
        switch (filter){
            case Filter::LINEAR : return GL_LINEAR;
            case Filter::NEAREST: return GL_NEAREST;
            default:
                ASSERT(0 , "Undefined Filter Type !!!");
                return 0;
        }
        return 0;
    }
}