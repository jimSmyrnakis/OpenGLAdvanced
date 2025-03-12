#pragma once
#include <Defs.hpp>
#include <glad/gl.h>
#include "../Format/Format.hpp"

namespace Game{
    class Sampler2D{
        public:
            

        private:
            u32     m_ObjectId;
            u32     m_SampleUnit;
            Filter  m_MagnificationFilter;
            Filter  m_MinificationFilter;

    };
    
    /*Texture2D class represent a simple 2 Dimensions Immutable Texture 
      and bind that to a texture unit .*/
    class Texture2D{
        public:
            struct InternalResolution{
                u32                         Width   ;
                u32                         Height  ;
                TextureInternalFormat       Format  ;
            };

            

        public:
            Texture2D(u32 Unit = 0 ,const InternalResolution& MaxResolution = {.Width = 1080 , .Height = 720 , .Format = TextureInternalFormat::RGBA16} );
            /*
             * This Constructor takes the texture unit we want to bind our texture and the maximum size of the texture via the 
             * MaxResolution . In other words our texture has specific max size that can not change after (That's mean's Immutable texture)
             * but the data format and size can change as long as they are fit in that texture . We use this class only for 2D simple texture
             * but the data format of the image could be different . 
             * 
            */
            ~Texture2D(void);

            bool HasAllocated(void) const;
            /*Using a proxy target in the start , the construtor can say if the required space was able to allocated on the target device .
              If yes then the space is already allocated */

            void SetUnit(u32 TextureUnit); // TODO - A check if the texture unit exist's for the current implementation
            /* Change the texture unit ==> int maxTextureUnits;
glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);*/

            u32 GetUnit(void) const;
            /* Just return's the unit we specified in the beggining */

            void SetSubImage(void* data , u32 XOffset , u32 YOffset , u32 Width , u32 Height , TextureExternalFormat Format  );
            /*
             * Set Image Data (data) to a texture from the coordinates ( XOffset , YOffset) to ( XOffset + Width - 1 , YOffset + Height - 1) 
             * plus is converting the data format to the internal format of the Texture  
             * TODO - If Previusly a other texture is binded for the current texture unit then when the function return's things must remain as is 
            */

            void Bind(void) ;
            /*
             * Based on the unit , this function activates the texture unit and bind this texture to it
             * If we need more than the available texture units then other way around that must be found 
             * such as a buffer texture object or bindless texture (Ofcourse bindless texture's are not 
             * available in every version of the)
            */
            void Unbind(void) ;
            /*
             * Activates the texture unit we have set for this texture and bind's the 0 texture name witch 
             * means that our texture unit is unbinded the current texture object
            */

            void SetFilter(Filter MagnificationFilter , Filter MinificationFilter);
            /*
             * Specifies the filter will be used in texture function on glsl shader code 
             * when filters a texel from the texture . 
            */
        private:
            u32                 m_TextureUnit;      // texture unit that this texture will bound to
            u32                 m_ObjectId;         // The Texture Object Name 
            u32                 m_Sampler2DId;      // The Sampler object id 
            InternalResolution  m_MaxResolution;    // The maximum resolution of the 2D Texture 
            bool                m_HasSpace;         // TODO
            
    };



}