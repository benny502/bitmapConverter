#include "bpp8.h"
namespace BNDecoder{

    std::list<Pixel> BPP8::decode(std::list<uint32_t> data, uint32_t* planes){
        std::list<Pixel> res;
        for(std::list<uint32_t>::iterator i=data.begin(); i!=data.end(); i++){
            Pixel rgb;
            bzero(&rgb, sizeof(Pixel));
            rgb.r = (planes[*i] & 0xFF0000) >> 16;
            rgb.g = (planes[*i] & 0xFF00) >> 8;
            rgb.b = planes[*i] & 0xFF;
            res.push_back(rgb); 
        }
        return res;
    }

    std::list<uint32_t> BPP8::encode(std::list<Pixel> data, uint32_t* planes){
        std::list<uint32_t> res;
        std::list<Pixel> plist;
        Planes creator(data, 256);
        creator.run();
        plist = creator.getPlanes();
        std::list<Pixel>::iterator rgb;
        for(rgb = plist.begin(); rgb != plist.end(); rgb++){
            *planes = ((*rgb).r << 16) | ((*rgb).g << 8) | (*rgb).b;
            planes ++;
        }

        for(std::list<Pixel>::iterator color = data.begin(); color != data.end(); color++){
            std::list<Pixel>::iterator best = plist.begin();
            uint16_t bestNum = abs((*best).r - (*color).r) + abs((*best).g - (*color).g) + abs((*best).b - (*color).b);
            rgb = plist.begin();
            while(rgb != plist.end()){
                uint16_t current = abs((*color).r - (*rgb).r) + abs((*color).g - (*rgb).g) + abs((*color).b - (*rgb).b);
                if(current < bestNum){
                    best = rgb;
                    bestNum = current;
                }
                rgb ++;
            }
            uint32_t pixel = std::distance(plist.begin(), best);
            res.push_back(pixel);
        }
        return res;
    }

}