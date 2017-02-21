#ifndef DECODERFACTORY_H
#define DECODERFACTORY_H
#include "bpp4.h"
#include "bpp8.h"
#include "rgb565.h"
#include "rgb888.h"
#include "rgb8888.h"


#define DECODER_BPP4 4
#define DECODER_BPP8 8
#define DECODER_RGB888 24
#define DECODER_RGB565 16
#define DECODER_RGB8888 32

namespace BNDecoder{
    class DecoderFactory{
        public:
            static IDecoder* createDecoder(int decoderType){
                switch(decoderType){
                    case DECODER_BPP4:
                        return new BPP4(); 
                    case DECODER_BPP8:
                        return new BPP8(); 
                    case DECODER_RGB8888:
                        return new RGB8888(); 
                    case DECODER_RGB888:
                        return new RGB888();
                    case DECODER_RGB565:
                        return new RGB565(); 
                    default:
                        throw NotSupportException();
                }
            }
    };
}

#endif