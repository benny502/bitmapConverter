#include "bitmap.h"


namespace BNDecoder{


    Bitmap::Bitmap(){
        header = new BMPHeader;
        info = new BMPInfo;
    }

    Bitmap Bitmap::loadBMP(const char* path){
        char drive[255];
        char dir[255];
        char filename[255];
        char extensions[5];
        _splitpath(path, drive, dir, filename, extensions);
        upper(extensions, 1, 4);
        std::string ext(extensions);
        if(ext != ".BMP"){
            throw NotBitmapException();
        }
        std::ifstream in(path, std::ios::binary|std::ios::in);
        if(!in.is_open()){
            throw OpenFileFailedException();
        }
        Bitmap bitmap;
        BMPHeader* header = bitmap.getHeader();
        BMPInfo* info = bitmap.getInfo();

        bzero(header, sizeof(header));
		bzero(info, sizeof(info));
		in.read((char*)header, sizeof(BMPHeader));
		in.read((char*)info, sizeof(BMPInfo));
        uint32_t rowSize = ceil((float)info->biWidth * (float)info->biBitCount / 8 / 4) * 4;
        uint32_t rowOffset = rowSize - ceil(info->biWidth * info->biBitCount / 8);
        uint32_t buf;
        uint32_t planesLength = 0;
        if(info->biBitCount <= 8){
            planesLength = pow(2,info->biBitCount) * sizeof(uint32_t);
        }
        bzero(&bitmap.planes, sizeof(bitmap.planes));
        in.read((char*)&bitmap.planes, planesLength);
        if(info->biCompression > 0){
            throw NotSupportException();
        }
        for(int row=0; row < info->biHeight; row++){
            for(int pixel=0; pixel<info->biWidth; pixel++){
                in.read((char*)&buf, ceil((float)info->biBitCount / 8.0));
                bitmap.data.push_back(buf); 
            }
            in.seekg(rowOffset,  std::ios::cur);
        }
        in.close();
        return bitmap;
    }

    void Bitmap::setData(std::list<uint32_t> source, int biBitCount){
        data = source;
        info->biBitCount = biBitCount;
        uint32_t rowSize = ceil((float)info->biWidth * (float)info->biBitCount / 8 / 4) * 4;
        info->biSizeImage = info->biHeight * rowSize;
        header->bfSize = sizeof(BMPHeader) + sizeof(BMPInfo) + info->biSizeImage;
        uint32_t planesLength = 0;
        if(biBitCount <= 8){
            planesLength = pow(2,biBitCount) * sizeof(uint32_t);
        }
        header->bfOffBits = sizeof(BMPHeader) + sizeof(BMPInfo) + planesLength;
    }

    void Bitmap::out(const char* path){
        uint32_t rowSize = ceil((float)info->biWidth * (float)info->biBitCount / 8.0 / 4.0) * 4;
        uint32_t rowOffset = rowSize - ceil(info->biWidth * info->biBitCount / 8.0);
        std::ofstream out(path, std::ios::binary|std::ios::out);
        out.write((char*)header, sizeof(BMPHeader));
        out.write((char*)info, sizeof(BMPInfo));
        uint32_t planesLength = 0;
        if(info->biBitCount <= 8){
            planesLength = pow(2,info->biBitCount) * sizeof(uint32_t);
        }
        out.write((char*)planes, planesLength);
        std::list<uint32_t>::iterator buf = data.begin();
        for(int row=0; row < info->biHeight; row++){
            for(int pixel=0; pixel<info->biWidth; pixel++){
                out.write((char*)&(*buf), ceil((float)info->biBitCount / 8.0));
                buf++;
            }
            //out.seekp(rowOffset,  std::ios::cur);
            uint32_t zero = 0;
            out.write((char*)&zero, rowOffset);
        }
        out.flush();
        out.close();
    }

    BMPHeader* Bitmap::getHeader(){
        return header;
    }

    BMPInfo* Bitmap::getInfo(){
        return info;
    }

    std::list<uint32_t> Bitmap::getData(){
        return data;
    }

    uint32_t* Bitmap::getPlanes(){
        return planes;
    }

    int Bitmap::getBitCount(){
        return info->biBitCount;
    }

    Bitmap::~Bitmap(){
        delete header;
        delete info;
    }
}