#pragma once

#include <Defs.hpp>
#include "../Format/Format.hpp"

namespace Game{
    /*The  Idea : Making a Frame Buffer Object Different from the Frame Buffer of the screen 
      we are able to use any render buffer we want and extend the functionality as we wish . 
      Of course i don't want to make this class enable for examble depth testing   or 
      stencil but i prefer this class to defined if we want to create a depth or stencil 
      buffer for usage in the future (Some Meshe's may require depth testing , where others 
      may require Bleding but not Depth testing - as a sphere that is made of glass but has 
      some dust on it defined as the texture with rgba values ) . The other most important 
      reason is resolution . We can make a fixed size frame buffer, or even better a dynamic 
      size frame buffer . To make a dynamic resolution frame buffer , by my approach ,  we 
      need to defined the maximum resolution we possible need . This Resolution will define 
      the render buffer's actual size of pixel elements and to do that i going to use textures 
      . Creating a Texture for the target frame buffer with fixed maximum size and then attach 
      this texture as a color render buffer on our frame buffer is the way to go . This makes 
      possible to render on the texture as our color buffer and then just do one last draw call
      from the target frame buffer to actualy apply the bind texture to the color buffer of the 
      target . If the Target is the system Frame Buffer then the texture is applied there and after 
      is shown on the screen (Window Contex) . Another Question is what happens with the viewport ? 
      We know where we render on the texture from our frame buffer , then we have the size of the 
      actual texture that the target frame buffer need to filter and draw on its own space . In 
      Order to do that we need a filter texture function on the shader language to actually apply
      the filtering only in a portion of the texture to the hole area . Let's say we found a way to
      do that , then what happens with the viewport ? As we know we render on triangles witch means 
      that we can make a rectangle of the size and position of what is defined in our own special 
      viewport method from a user and so we just move the rectangle as demanded . This means that 
      we need to know the maximum size of the screen and actually pass that as our max size , and 
      so the maximum size of color buffer , depth buffer etc. This is not a bad approach but has 
      big memory usage (one for the common texture used as texture and color buffer and the actual 
      color buffer size of the terget frame buffer , that probably is the same size with the screen
      that we render - info given from the contex probably ) . Last and more Important is that 
      resolution is not defined just by size of pixels elements in 2D but plus the size of the pixel
      element that defines the color palete available to us (Image Format) */
    class FBuffer{

        private: /*Identifiers*/
            u32 m_FBOid;    // Frame Buffer Object Identifier
            u32 m_RDBOid;   // Render Depth Buffer Object Identifier
            u32 m_RCBOid;   // Render Color Buffer Object Identifier
            u32 m_TFBOid;   // Target Frame Buffer Object Identifier

        private: /*Resolution , Formats and other related member's */
            u32         m_MaxWidth      ;       // The Width  of all Render buffer's for this Frame Buffer  
            u32         m_MaxHeight     ;       // The Height of all Render buffer's for this Frame Buffer
            ImageFormat m_PixelFormat   ;       // Color Render Buffer Format (RGB,RGBA - 4/8/16/32 ) 
            DepthFormat m_Depth         ;       // Depth Render Buffer Format (Depth - 12/24/32)
    };
}