#include "planes.h"

namespace BNDecoder{
    Planes::Planes(std::list<Pixel> data, uint16_t maxColors){
        leafNum = 0;
        this->data = data;
        tree = new OctreeNode;
        this->maxColors = maxColors;
        for(int i=0; i < 8; ++i) reducible[i] = 0;
    }

    void Planes::setData(std::list<Pixel> data){
        this->data = data;
    }

    OctreeNode* Planes::createNode(uint16_t i, uint16_t level){
        OctreeNode* node = new OctreeNode;
        for(uint16_t i=0; i<8; i++){
            node->children[i] = 0;
        }
        if(level==7){
            node->isLeaf = true;
            leafNum ++;
        }else{
            node->isLeaf = false;
            node->next = reducible[level];
            reducible[level] = node;
        }
        return node;
    }

    void Planes::addColor(OctreeNode* node, Pixel color, uint16_t level){
        if(node->isLeaf == true){
            node->r += color.r;
            node->g += color.g;
            node->b += color.b;
            node->pixelCount++;
        }else{
            uint8_t mask[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
            uint16_t i = ((color.r & mask[level]) >> (5 - level)) | ((color.g & mask[level]) >> (6 - level)) | ((color.b & mask[level]) >> (7 - level));
            if(node->children[i] == NULL){
                node->children[i] = createNode(i, level);
            }
            addColor(node->children[i], color, level + 1);
        }
    }

    void Planes::reduceTree(){
        uint16_t level = 6;
        while(reducible[level] == NULL) {
            level--;
        }
        OctreeNode* node = reducible[level];
        reducible[level] = node->next;
        uint32_t r = 0,g = 0,b = 0;
        uint32_t pixelCount = 0;
        for(uint8_t i=0;i<8;++i){
            if(NULL == node->children[i]) continue;
            r += node->children[i]->r;
            g += node->children[i]->g;
            b += node->children[i]->b;
            pixelCount += node->children[i]->pixelCount;
            leafNum --;
            delete node->children[i];
            node->children[i] = 0;
        }
        node->r = r;
        node->g = g;
        node->b = b;
        node->isLeaf = true;
        node->pixelCount = pixelCount;
        if(node->pixelCount == 0){
            1==1;
        }
        leafNum ++;
    }

    void Planes::run(){
        if(data.empty()){
            throw UnknowException();
        }
        for(std::list<Pixel>::iterator i = data.begin(); i != data.end(); ++i){
            addColor(tree, *i, 0);
            while(leafNum > maxColors) reduceTree();
        }
    }

    std::list<Pixel> Planes::getPlanes(){
        std::list<Pixel> data;
        _getPlanes(tree, data);
        return data;
    }

    void Planes::_getPlanes(OctreeNode* node, std::list<Pixel>& data){
        if(node->isLeaf == true){
            Pixel color;
            color.r = node->r / node->pixelCount;
            color.g = node->g / node->pixelCount;
            color.b = node->b / node->pixelCount;
            data.push_back(color);
        }
        for(uint16_t i=0; i < 8; ++i){
            if(node->children[i] == NULL) continue;
            _getPlanes(node->children[i], data);
        }
    }

    void Planes::setMaxColor(uint32_t num){
        maxColors = num;
    }

    Planes::~Planes(){
        delete tree;
    }


}