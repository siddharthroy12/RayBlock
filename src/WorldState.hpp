#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

#include <map>
#include <string>
#include "Chunk.hpp"
#include "Block.hpp"

class WorldState {
    public:
    WorldState();
    std::map<std::string, Chunk*> chunks;
    Chunk* _chunks[100][16][100];
    void loadAndRenderChunk(int x, int y, int z);
    Block getBlockAtPos(int x, int y, int z);
    ~WorldState();
    
};


#endif