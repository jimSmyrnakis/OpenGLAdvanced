#include "TextureReader.hpp"
#include "tiffio.h"
namespace Game{
    bool ReadTiff(
        const std::string Path      , 
        void* Data                  , 
        Game::u32  MaxWidth         ,
        Game::u32  MaxHeight        , 
        Game::u32* Width            , 
        Game::u32* Height           ){
    
        TIFF* tif = TIFFOpen(Path.c_str(), "r");
        if (tif) {
            uint32_t w, h;
            size_t npixels;
            uint32_t* raster;
    
            TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, Width);
            TIFFGetField(tif, TIFFTAG_IMAGELENGTH, Height);
            if ( ( (*Width) > MaxWidth ) || ( (*Height) > MaxHeight) ){
                ASSERT(0 , "TIFF file texture bigger than the maximum one !");
                return false;
            }
                
            w = *Width; h = *Height;
            npixels = w * h;
            
            
            if (TIFFReadRGBAImage(tif, w, h, (uint32_t*)Data, 0) == 0) {
                ASSERT(0 , "Failed To read Texture Data !!!");
                return false;
            }
            
            TIFFClose(tif);
        }
    
        return true;
    }
}