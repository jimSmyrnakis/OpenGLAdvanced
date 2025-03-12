#include "Format.hpp"

#include <glad/gl.h>



namespace Game{
    u32 GetOpenGLInternalTextureFormat(TextureInternalFormat  format){
        
        switch (format){
            case TextureInternalFormat::RGB4    :   return GL_RGB4      ;
            case TextureInternalFormat::RGB8    :   return GL_RGB8      ;
            case TextureInternalFormat::RGB16   :   return GL_RGB16     ;
            case TextureInternalFormat::RGB32UI :   return GL_RGB32UI   ;
            case TextureInternalFormat::RGB16F  :   return GL_RGB16F    ;
            case TextureInternalFormat::RGB32F  :   return GL_RGB32F    ;
            case TextureInternalFormat::RGBA4   :   return GL_RGBA4     ;
            case TextureInternalFormat::RGBA8   :   return GL_RGBA8     ;
            case TextureInternalFormat::RGBA16  :   return GL_RGBA16    ;
            case TextureInternalFormat::RGBA32UI:   return GL_RGBA32UI  ;
            case TextureInternalFormat::RGBA16F :   return GL_RGBA16F   ;
            case TextureInternalFormat::RGBA32F :   return GL_RGBA32F   ;

            default:
                ASSERT(0 , "Undefined Internal Texture Format Type !!!");
        }
        return 0;
    }

    u32 GetOpenGLExternalTextureFormat(TextureExternalFormat  format){
        switch (format){
            case TextureExternalFormat::RGB8        :   return GL_RGB           ;
            case TextureExternalFormat::RGB16       :   return GL_RGB           ;
            case TextureExternalFormat::RGB32       :   return GL_RGB           ;

            case TextureExternalFormat::RGBA8       :   return GL_RGBA          ;
            case TextureExternalFormat::RGBA16      :   return GL_RGBA          ;
            case TextureExternalFormat::RGBA32      :   return GL_RGBA          ;

            case TextureExternalFormat::RGB16F_RAW  :   return GL_RGB           ;
            case TextureExternalFormat::RGB32F_RAW  :   return GL_RGB           ;

            case TextureExternalFormat::RGBA16F_RAW :   return GL_RGBA          ;
            case TextureExternalFormat::RGBA32F_RAW :   return GL_RGBA          ;

            case TextureExternalFormat::RGB8U_RAW   :   return GL_RGB_INTEGER   ;
            case TextureExternalFormat::RGB16U_RAW  :   return GL_RGB_INTEGER   ;
            case TextureExternalFormat::RGB32U_RAW  :   return GL_RGB_INTEGER   ;

            case TextureExternalFormat::RGBA8U_RAW  :   return GL_RGBA_INTEGER  ;
            case TextureExternalFormat::RGBA16U_RAW :   return GL_RGBA_INTEGER  ;
            case TextureExternalFormat::RGBA32U_RAW :   return GL_RGBA_INTEGER  ;

            default:
                ASSERT(0 , "Undefined Internal Texture Format Type !!!");
        }
        return 0;
    }

    u32 GetOpenGLExternalTextureType(TextureExternalFormat format ){
        switch (format){
            case TextureExternalFormat::RGB8        :   return GL_UNSIGNED_BYTE     ;
            case TextureExternalFormat::RGB16       :   return GL_UNSIGNED_SHORT    ;
            case TextureExternalFormat::RGB32       :   return GL_UNSIGNED_INT      ;

            case TextureExternalFormat::RGBA8       :   return GL_UNSIGNED_BYTE     ;
            case TextureExternalFormat::RGBA16      :   return GL_UNSIGNED_SHORT    ;
            case TextureExternalFormat::RGBA32      :   return GL_UNSIGNED_INT      ;

            case TextureExternalFormat::RGB16F_RAW  :   return GL_HALF_FLOAT        ;
            case TextureExternalFormat::RGB32F_RAW  :   return GL_FLOAT             ;

            case TextureExternalFormat::RGBA16F_RAW :   return GL_HALF_FLOAT        ;
            case TextureExternalFormat::RGBA32F_RAW :   return GL_FLOAT             ;

            case TextureExternalFormat::RGB8U_RAW   :   return GL_UNSIGNED_BYTE     ;
            case TextureExternalFormat::RGB16U_RAW  :   return GL_UNSIGNED_SHORT    ;
            case TextureExternalFormat::RGB32U_RAW  :   return GL_UNSIGNED_INT      ;

            case TextureExternalFormat::RGBA8U_RAW  :   return GL_UNSIGNED_BYTE     ;
            case TextureExternalFormat::RGBA16U_RAW :   return GL_UNSIGNED_SHORT    ;
            case TextureExternalFormat::RGBA32U_RAW :   return GL_UNSIGNED_INT      ;

            default:
                ASSERT(0 , "Undefined Internal Texture Format Type !!!");
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