#pragma once

#include <Defs.hpp>

namespace Game{
    enum class TextureInternalFormat{
        RGB4        ,
        RGB8        ,
        RGB16       ,
        RGB32UI     ,
        RGB16F      ,
        RGB32F      ,

        RGBA4       ,
        RGBA8       ,
        RGBA16      ,
        RGBA32UI    ,
        RGBA16F     ,
        RGBA32F     
        
    };
    
    u32 GetOpenGLInternalTextureFormat(TextureInternalFormat  format);

    
    enum class TextureExternalFormat{
        RGB8            ,
        RGB16           ,
        RGB32           ,

        RGBA8           ,
        RGBA16          ,
        RGBA32          ,

        RGB16F_RAW      ,
        RGB32F_RAW      ,

        RGBA16F_RAW     ,
        RGBA32F_RAW     ,

        RGB8U_RAW       ,
        RGB16U_RAW      ,
        RGB32U_RAW      ,

        RGBA8U_RAW      ,
        RGBA16U_RAW     ,
        RGBA32U_RAW     
    };

    u32 GetOpenGLExternalTextureFormat(TextureExternalFormat  format);
    u32 GetOpenGLExternalTextureType(TextureExternalFormat format );

    enum class DepthFormat{
        DEPTH16 , DEPTH24 , DEPTH32
    };

    u32 GetOpenGLDepthFormat(DepthFormat format);

    enum class Filter{
        LINEAR , NEAREST
    };

    u32 GetOpenGLFilter(Filter filter);

    
}