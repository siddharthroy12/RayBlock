#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "Block.hpp"
#include "raylib.h"

class Chunk
{
private:
    bool firstGen = true;
    Vector3 getBlockWorldCoord(int x, int y, int z);
    Texture texture;
    Mesh mesh = {0};
    float *vertices;
    float *normals;
    float *texcoords;
public:
    int posX;
    int posY;
    int posZ;
    Block blocks[16][16][16];
    Model model = {0};
    void calculateMesh();
    Chunk(int x, int y, int z);
    ~Chunk();
};


#endif