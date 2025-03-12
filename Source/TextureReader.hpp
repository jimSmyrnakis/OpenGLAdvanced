#pragma once
#include "Systems/Renderer/GraphicsApi/Texture/Texture2D.hpp"
#include <string>

namespace Game{
    bool ReadTiff(
        const std::string Path      , 
        void* Data                  , 
        Game::u32  MaxWidth         ,
        Game::u32  MaxHeight        , 
        Game::u32* Width            , 
        Game::u32* Height           );
    
}