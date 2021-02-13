#include "WorldState.hpp"
#include <cmath>
#include "iostream"

void WorldState::loadAndRenderChunk(int x, int z)
{
    if (x < 1 || z < 1) {
        return;
    }

    std::string formatted_coord_string = std::to_string(x) + ',' + std::to_string(z);
    
    if ( !(this->chunks.count(formatted_coord_string) > 0) )
    {
        this->chunks[formatted_coord_string] = new Chunk(x,z);
    }

    Vector3 pos = { (x * 16) - 16, 0, (z * 16) - 16 };

    DrawModel(this->chunks[formatted_coord_string]->model, pos, 1, WHITE);
}

Block WorldState::getBlockAtPos(int x, int y, int z)
{
    if (x < 1 || y < 1 || z < 1 || y > 256) {
        return (Block){ BLOCK_TYPE::_NULL };
    }

    int chunkX = ceil((double)x / (double)16);
    int chunkZ = ceil((double)z / (double)16);

    std::string formatted_coord_string = std::to_string(chunkX) + ',' + std::to_string(chunkZ);

    if ( !(this->chunks.count(formatted_coord_string) > 0) )
    {
        return (Block){ BLOCK_TYPE::_NULL };
    }

    int chunkBlockX = x - (16 * (chunkX - 1));
    int chunkBlockZ = z - (16 * (chunkZ - 1));

    return this->chunks[formatted_coord_string]->blocks[chunkBlockX - 1][y - 1][chunkBlockZ - 1];
}