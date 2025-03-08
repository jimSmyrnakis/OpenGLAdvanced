#pragma once
#include <Defs.hpp>
#include <glad/gl.h>
#include "../Format/Format.hpp"

namespace Game{

    
    
    /*Texture2D class represent a simple 2 Dimensions Immutable Texture 
      and bind that to a texture unit .*/
    class Texture2D{
        public:
            struct Resolution{
                u32         Width;
                u32         Height;
                ImageFormat Format;
            };
        public:
            Texture2D(u32 Unit = 0 ,const Resolution& MaxResolution = {.Width = 1080 , .Height = 720 , .Format = ImageFormat::RGBA32} );
            /*
             * This Constructor takes the texture unit we want to bind our texture and the maximum size of the texture via the 
             * MaxResolution . In other words our texture has specific max size that can not change after (That's mean's Immutable texture)
             * but the data format and size can change as long as they are fit in that texture . We use this class only for 2D simple texture
             * but the data format of the image could be different . 
            */
            ~Texture2D(void);

            bool HasAllocated(void) const;
            /*Using a proxy target in the start , the construtor can say if the required space was able to allocated on the target device .
              If yes then the space is already allocated */

            void SetUnit(u32 TextureUnit);
            /* */
            u32 GetUnit(void) const;
            /* Just return's the unit we specified in the beggining */

            void SetSubImage(void* data , u32 XOffset , u32 YOffset , u32 Width , u32 Height , ImageFormat Format  );
            /*
             * Set Image Data (data) to a texture from the coordinates ( XOffset , YOffset) to ( XOffset + Width - 1 , YOffset + Height - 1) 
             * plus is converting the data format to the internal format of the Texture  
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
        private:
            u32         m_TextureUnit;      // texture unit that this texture will bound to
            u32         m_ObjectId;         // The Texture Object Name 
            Resolution  m_MaxResolution;    // The maximum resolution of the 2D Texture 
            bool        m_HasSpace;
    };

}