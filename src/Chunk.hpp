#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Block.hpp"
#include "raylib.h"

class Chunk
{
private:
    bool firstGen = true;
    Vector3 getBlockWorldCoord(int x, int y, int z);
public:
    int posX;
    int posZ;
    Block blocks[16][256][16];
    Model model;
    void calculateMesh();
    Chunk(int x, int z);
    ~Chunk();
};


#endif