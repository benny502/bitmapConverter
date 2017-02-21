#ifndef BITMAP_H
#define BITMAP_H
#include "bndecoder.h"
#include <math.h>
#include <fstream>
#include <iostream>

namespace BNDecoder{

    class Bitmap{
        private:
            BMPHeader* header;
            BMPInfo* info;
            std::list<uint32_t> data;
            uint32_t planes[256];
            Bitmap();
        public:
            ~Bitmap();
            static Bitmap loadBMP(const char* path);
            BMPHeader* getHeader();
            BMPInfo* getInfo();
            uint32_t* getPlanes();
            std::list<uint32_t> getData();
            void setData(std::list<uint32_t> data, int biBitCount);
            int getBitCount();   
            void out(const char* path);
    };
}

#endif
