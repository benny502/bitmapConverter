#ifndef RGB888_H
#define RGB888_H

#include "decoder.h"

namespace BNDecoder{

    class RGB888 : public IDecoder{
        public:
            virtual std::list<Pixel> decode(std::list<uint32_t> data, uint32_t* planes);
            virtual std::list<uint32_t> encode(std::list<Pixel> data, uint32_t* planes);
    };

}

#endif 