#include "bpp4.h"
namespace BNDecoder{

    BPP4::BPP4(){
        first = true;
        cur = bytes.begin();
    }

    std::list<Pixel> BPP4::decode(std::list<uint32_t> data, uint32_t* planes){
        std::list<Pixel> res;
        for(std::list<uint32_t>::iterator i=data.begin(); i!=data.end(); i++){
            uint32_t idx1,idx2;
            idx1 = (*i & 0xF0) >> 4;
            idx2 = *i & 0xF;
            Pixel rgb1,rgb2;
            bzero(&rgb1, sizeof(Pixel));
            bzero(&rgb2, sizeof(Pixel));
            rgb1.r = (planes[idx1] & 0xFF0000) >> 16;
            rgb1.g = (planes[idx1] & 0xFF00) >> 8;
            rgb1.b = planes[idx1] & 0xFF;
            res.push_back(rgb1);
            rgb2.r = (planes[idx2] & 0xFF0000) >> 16;
            rgb2.g = (planes[idx2] & 0xFF00) >> 8;
            rgb2.b = planes[idx2] & 0xFF;
            res.push_back(rgb2); 
        }
        return res;
    }

    std::list<uint32_t> BPP4::encode(std::list<Pixel> data, uint32_t* planes){
        std::list<uint32_t> res;
        std::list<Pixel> plist;
        Planes creator(data, 16);
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
            uint8_t pixel = std::distance(plist.begin(), best);
            push(pixel);
        }
        return getBytes();
    }

    void BPP4::push(uint8_t item){
        if(!first){
            (*cur).second = item;
            first = true;
        }else{
            byte newItem;
            newItem.first = item;
            bytes.push_back(newItem);
            cur++;
            first = false;
        }
    }

    std::list<uint32_t> BPP4::getBytes(){
        std::list<uint32_t> res;
        for(std::list<byte>::iterator i=bytes.begin();i!=bytes.end();++i){
            uint32_t buf = (*i).first  << 4 | (*i).second; 
            res.push_back(buf);
        }
        return res;
    }
}