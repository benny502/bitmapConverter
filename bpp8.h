#ifndef BPP8_H
#define BPP8_H

#include "decoder.h"

namespace BNDecoder{

    class BPP8 : public IDecoder{
        public:
            virtual std::list<Pixel> decode(std::list<uint32_t> data, uint32_t* planes);
            virtual std::list<uint32_t> encode(std::list<Pixel> data, uint32_t* planes);
    };

}

#endif 