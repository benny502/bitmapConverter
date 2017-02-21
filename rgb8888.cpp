#include "rgb8888.h"
namespace BNDecoder{

    std::list<Pixel> RGB8888::decode(std::list<uint32_t> data, uint32_t* planes){
        std::list<Pixel> res;
        for(std::list<uint32_t>::iterator i=data.begin(); i!=data.end(); i++){
            Pixel rgb;
            bzero(&rgb, sizeof(Pixel));
            rgb.a = (*i & 0xFF000000) >> 24;
            rgb.r = (*i & 0xFF0000) >> 16;
            rgb.g = (*i & 0xFF00) >> 8;
            rgb.b = *i & 0xFF;
            res.push_back(rgb); 
        }
        return res;
    }

    std::list<uint32_t> RGB8888::encode(std::list<Pixel> data, uint32_t* planes){
        std::list<uint32_t> res;
        for(std::list<Pixel>::iterator rgb = data.begin();rgb != data.end(); ++rgb){
            uint32_t pixel = ((*rgb).a << 24) | ((*rgb).r << 16) | ((*rgb).g << 8) | (*rgb).b;
            res.push_back(pixel);
        }
        return res;
    }

}