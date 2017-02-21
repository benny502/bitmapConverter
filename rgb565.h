#ifndef RGB565_H
#define RGB565_H

#include "decoder.h"

namespace BNDecoder{

    class RGB565 : public IDecoder{
        public:
            virtual std::list<Pixel> decode(std::list<uint32_t> data, uint32_t* planes);
            virtual std::list<uint32_t> encode(std::list<Pixel>data, uint32_t* planes);
    };

}

#endif 