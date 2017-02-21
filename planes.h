#ifndef PLANES_H
#define PLANES_H
#include "bndecoder.h"

namespace BNDecoder{

    class Planes{
        public:
            Planes(std::list<Pixel> data, uint16_t maxColors);
            ~Planes();
            void setData(std::list<Pixel> data);
            void run();
            void setMaxColor(uint32_t num);
            std::list<Pixel> getPlanes();
        private:
            std::list<Pixel> data;
            uint32_t leafNum;
            uint32_t maxColors;
            OctreeNode* tree;
            OctreeNode* reducible[8];
            OctreeNode* createNode(uint16_t i, uint16_t level);
            void addColor(OctreeNode* node, Pixel color, uint16_t level);
            void _getPlanes(OctreeNode* node, std::list<Pixel>& data);
            void reduceTree();

    };
}

#endif