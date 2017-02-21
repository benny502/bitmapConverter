#ifndef BPP4_H
#define BPP4_H

#include "decoder.h"

namespace BNDecoder{

    struct byte{
        uint8_t first;
        uint8_t second;
    };

    class BPP4 : public IDecoder{
        public:
            BPP4();
            virtual std::list<Pixel> decode(std::list<uint32_t> data, uint32_t* planes);
            virtual std::list<uint32_t> encode(std::list<Pixel> data, uint32_t* planes);
        private:
            std::list<byte> bytes;
            std::list<byte>::iterator cur;
            bool first;
            void push(uint8_t item);
            std::list<uint32_t> getBytes();
    };

}

#endif 