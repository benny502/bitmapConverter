#include "rgb565.h"
namespace BNDecoder{

    std::list<Pixel> RGB565::decode(std::list<uint32_t> data, uint32_t* planes){
        std::list<Pixel> res;
        for(std::list<uint32_t>::iterator i=data.begin(); i!=data.end(); i++){
            Pixel rgb;
            bzero(&rgb, sizeof(Pixel));
            rgb.r = (*i & 0xF800) >> 8;
            rgb.g = (*i & 0x7E0) >> 3;
            rgb.b = (*i & 0x1F) << 3;
            res.push_back(rgb); 
        }
        return res;
    }

    std::list<uint32_t> RGB565::encode(std::list<Pixel> data, uint32_t* planes){
        std::list<uint32_t> res;
        for(std::list<Pixel>::iterator rgb = data.begin();rgb != data.end(); ++rgb){
            uint32_t pixel = (((*rgb).r & 0xF8 ) << 8) | (((*rgb).g & 0xFC ) << 3) | (((*rgb).b & 0xF8) >>3);
            res.push_back(pixel);
        }
        return res;
    }

}