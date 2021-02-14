#include "WorldState.hpp"
#include <cmath>
#include "iostream"

WorldState::WorldState() {
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 100; z++) {
                this->_chunks[x][y][z] = nullptr;
            }
        }
    }
}

void WorldState::loadAndRenderChunk(int x, int y, int z)
{
    
    if (x < 0 || y < 0 || z < 0 || y > 16) {
        return;
    }

    

    //std::string formatted_coord_string = std::to_string(x) + ',' + std::to_string(z);
    
    if ( (this->_chunks[x][y][z] == nullptr) )
    {   
        this->_chunks[x][y][z] = new Chunk(x, y, z);   
    }

    Vector3 pos = { (x * 16), y * 16, (z * 16) };

    DrawModel(this->_chunks[x][y][z]->model, pos, 1, WHITE);
}

Block WorldState::getBlockAtPos(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0 || y > 256) {
        return (Block){ BLOCK_TYPE::_NULL };
    }

    
    int chunkX = floor((double)x / (double)16);
    //std::cout << "x" << x << "chunkX" << chunkX << std::endl;
    int chunkY = floor((double)y / (double)16);
    int chunkZ = floor((double)z / (double)16);

    //std::string formatted_coord_string = std::to_string(chunkX) + ',' + std::to_string(chunkZ);

    if ( (this->_chunks[chunkX][chunkY][chunkZ] == nullptr) )
    {
        return (Block){ BLOCK_TYPE::_NULL };
    }

    int chunkBlockX = x - (16 * (chunkX));
    int chunkBlockY = x - (16 * (chunkY));
    int chunkBlockZ = z - (16 * (chunkZ));

    return this->_chunks[chunkX][chunkY][chunkZ]->blocks[chunkBlockX][chunkBlockY][chunkBlockZ];
}

WorldState::~WorldState() { }