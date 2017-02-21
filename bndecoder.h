#ifndef BNDECODER_H
#define BNDECODER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <list>
#include "exception.h"

namespace BNDecoder{
    #ifndef WIN32
    static void _split_whole_name(const char *whole_name, char *fname, char *ext)
    {
        char *p_ext;

        p_ext = rindex((char*)whole_name, '.');
        if (NULL != p_ext)
        {
            strcpy(ext, p_ext);
            snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
        }
        else
        {
            ext[0] = '\0';
            strcpy(fname, whole_name);
        }
    }

    static void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
    {
        char *p_whole_name;

        drive[0] = '\0';
        if (NULL == path)
        {
            dir[0] = '\0';
            fname[0] = '\0';
            ext[0] = '\0';
            return;
        }

        if ('/' == path[strlen(path)])
        {
            strcpy(dir, path);
            fname[0] = '\0';
            ext[0] = '\0';
            return;
        }

        p_whole_name = rindex((char*)path, '/');
        if (NULL != p_whole_name)
        {
            p_whole_name++;
            _split_whole_name(p_whole_name, fname, ext);

            snprintf(dir, p_whole_name - path, "%s", path);
        }
        else
        {
            _split_whole_name(path, fname, ext);
            dir[0] = '\0';
        }
    }


    #endif

    static void upper(char* str,int start, int size){
        str += start;
        for(int i=0; i < size; i++){
            *str = *str & 0xDF;
            str++;
        }
    }

    #pragma pack(1)

    struct BMPHeader{
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReverse1;
        uint16_t bfReverse2;
        uint32_t bfOffBits;
    };

    struct BMPInfo{
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;

    };


    #pragma pack()

    struct Pixel{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    struct OctreeNode{
        bool isLeaf;
        uint32_t pixelCount;
        uint32_t r;
        uint32_t g;
        uint32_t b;
        OctreeNode* children[8];
        OctreeNode* next;
    };

}

#endif