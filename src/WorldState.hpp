#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

#include <map>
#include <string>
#include "Chunk.hpp"
#include "Block.hpp"

class WorldState {
    public:
    std::map<std::string, Chunk*> chunks;
    void loadAndRenderChunk(int x, int z);
    Block getBlockAtPos(int x, int y, int z);
};


#endif