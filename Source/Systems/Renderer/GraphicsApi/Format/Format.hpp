#pragma once

#include <Defs.hpp>

namespace Game{
    enum class ImageFormat{
        RGBA8   , 
        RGBA4   , 
        RGBA2   , 
        RGB8    , 
        RGB4    , 
        RGB2    ,
        RGB5A1  ,
        RGBA16  ,
        RGBA32  ,
        
    };

    u32 GetOpenGLInternalTextureFormat(ImageFormat format);
    void GetOpenGLExternalImageFormat(ImageFormat format , u32& externalFormat , u32& dataType);
    u32 GetOpenGLDataTypeFromImageFormat(ImageFormat format);

    enum class DepthFormat{
        DEPTH16 , DEPTH24 , DEPTH32
    };

    u32 GetOpenGLDepthFormat(DepthFormat format);

    enum class Filter{
        LINEAR , NEAREST
    };

    u32 GetOpenGLFilter(Filter filter);

    
}