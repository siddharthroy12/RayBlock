#include "Chunk.hpp"
#include <cstdlib>
#include "rlgl.h"
#include "Block.hpp"
#include <cstring>
#include "WorldContext.hpp"
#include <iostream>

Chunk::Chunk(int x, int y, int z) {
    
    this->posX = x;
    this->posY = y;
    this->posZ = z;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                this->blocks[x][y][z] = (Block){BLOCK_TYPE::SOLID};
            }
        }
    }

    vertices = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 16 * sizeof(float));
    normals = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 16 * sizeof(float));
    texcoords = (float *)RL_MALLOC(36 * 2 * 16 * 16 * 16 * sizeof(float));

    mesh.vboId = (unsigned int *)RL_CALLOC(7, sizeof(unsigned int));
    this->mesh.vertices = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 16 * sizeof(float));
    this->mesh.texcoords = (float *)RL_MALLOC(36 * 2 * 16 * 16 * 16 * sizeof(float));
    this->mesh.normals = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 16 * sizeof(float));
    this->mesh.vertexCount = 0;
    this->mesh.triangleCount = 0;
    rlLoadMesh(&mesh, false);

    this->texture = LoadTexture(ASSETS_PATH "grass.png");
    model.transform = MatrixIdentity();

    model.meshCount = 1;
    model.meshes = (Mesh *)RL_CALLOC(model.meshCount, sizeof(Mesh));
    model.meshes[0] = mesh;
    model.materialCount = 1;
    model.materials = (Material *)RL_CALLOC(model.materialCount, sizeof(Material));
    model.materials[0] = LoadMaterialDefault();

    model.meshMaterial = (int *)RL_CALLOC(model.meshCount, sizeof(int));
    model.meshMaterial[0] = 0;  // First material index

    this->model.materials[0].maps[MAP_DIFFUSE].texture = this->texture;
    this->calculateMesh();

}

void Chunk::calculateMesh()
{
    int verticesCount = 0;
    int texcoordsCount = 0;
    int normalsCount = 0;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                if (this->blocks[x][y][z].TYPE == BLOCK_TYPE::SOLID) {
                    SOLID_BLOCK_VERTICES blockVertices = GenCubeVertices(x, y, z);
                    //std::cout << "CunkX" << posX << std::endl;
                    Vector3 blockWorldCoord = getBlockWorldCoord(x, y, z);
                    //std::cout << "BlockX" << x << std::endl;
                    //std::cout << "BlockWorldX" << blockWorldCoord.x << std::endl;
                    Vector3 tmp;
                    Block blockToCheck;
                    // West
                    tmp = blockWorldCoord;
                    tmp.z += 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.WEST_VERTICES[v];
                        }
                        verticesCount += 6 * 3;
                        // Texture coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.WEST_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.WEST_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                    // East
                    tmp = blockWorldCoord;
                    tmp.z -= 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.EAST_VERTICES[v];
                        }
                        verticesCount += 6 * 3;
                        // Texture coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.EAST_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.EAST_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                    // Top
                    tmp = blockWorldCoord;
                    tmp.y += 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.TOP_VERTICES[v];
                        }
                        verticesCount += 6 *3;
                        // Texture Coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.TOP_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.TOP_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                    // Bottom
                    tmp = blockWorldCoord;
                    tmp.y -= 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.BOTTOM_VERTICES[v];
                        }
                        verticesCount += 6 * 3;
                        // Texture Coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.BOTTOM_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.BOTTOM_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                    // North
                    tmp = blockWorldCoord;
                    tmp.x += 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.NORTH_VERTICES[v];
                        }
                        verticesCount += 6 * 3;
                        // Texture Coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.NORTH_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.NORTH_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                    // South
                    tmp = blockWorldCoord;
                    tmp.x -= 1;
                    blockToCheck = worldState->getBlockAtPos(tmp.x, tmp.y, tmp.z);
                    if (!(blockToCheck.TYPE == BLOCK_TYPE::SOLID))
                    {
                        // Vertices
                        for (int v = 0; v < 6 * 3; v++)
                        {
                            vertices[verticesCount + v] = blockVertices.SOUTH_VERTICES[v];
                        }
                        verticesCount += 6 *3;
                        // Texture Coords
                        for (int t = 0; t < 6 * 2; t++)
                        {
                            texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.SOUTH_COORDS[t];
                        }
                        texcoordsCount += 6 * 2;
                        // Normals
                        for (int n = 0; n < 6 * 3; n++)
                        {
                            normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.SOUTH_NORMALS[n];
                        }
                        normalsCount += 6 * 3;
                    }
                }
            }
        }
    }

    // RL_FREE(model.meshes[0].vertices);
    // RL_FREE(model.meshes[0].texcoords);
    // RL_FREE(model.meshes[0].normals);

    //model.meshes[0].vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
    memcpy(model.meshes[0].vertices, vertices, verticesCount * sizeof(float));

    //model.meshes[0].texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
    memcpy(model.meshes[0].texcoords, texcoords, texcoordsCount * sizeof(float));

    //model.meshes[0].normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
    memcpy(model.meshes[0].normals, normals, normalsCount * sizeof(float));



    this->model.meshes[0].vertexCount = verticesCount / 3;         // fixme: Why divide by 3 ???
    this->model.meshes[0].triangleCount = (verticesCount / 3) / 2; // fixme: Why divide by 3 and 2 ???

    rlUpdateMesh(this->model.meshes[0], 0, verticesCount);
    rlUpdateMesh(this->model.meshes[0], 1, verticesCount);
    rlUpdateMesh(this->model.meshes[0], 2, verticesCount);
    //this->model.meshes[0] = mesh;
}

Vector3 Chunk::getBlockWorldCoord(int x, int y, int z)
{
    Vector3 blockWorldCoord = {
        x + (this->posX * 16),
        y + (this->posY * 16),
        z + (this->posZ * 16)
    };

    return blockWorldCoord;
}

Chunk::~Chunk() {

    RL_FREE(vertices);
    RL_FREE(texcoords);
    RL_FREE(normals);

    UnloadTexture(this->texture);
    if (!this->firstGen)
    {
        UnloadModel(this->model);
    }
}