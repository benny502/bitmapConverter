#ifndef IDECODER_H
#define IDECODER_H

#include "bndecoder.h"
#include "planes.h"
#include <fstream>

namespace BNDecoder{

    class IDecoder{
        public:
            virtual std::list<Pixel> decode(std::list<uint32_t> data, uint32_t* planes)=0;
            virtual std::list<uint32_t> encode(std::list<Pixel> data, uint32_t* planes)=0;
            virtual std::list<Pixel> grey(std::list<Pixel> data){
                std::list<Pixel> res;
                for(std::list<Pixel>::iterator rgb = data.begin();rgb != data.end(); ++rgb){
                    uint8_t pixel = (uint8_t)((*rgb).r * 0.3 + (*rgb).g * 0.59 + (*rgb).b * 0.11);
                    Pixel item = { pixel, pixel, pixel};
                    res.push_back(item);
                }
                return res;
            }
    };


}

#endif
