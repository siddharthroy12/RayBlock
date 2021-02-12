#include "Chunk.hpp"
#include <cstdlib>
#include "rlgl.h"
#include "Block.hpp"
#include <cstring>
#include "WorldContext.hpp"

Chunk::Chunk(int x, int z) {
    this->posX = x;
    this->posZ = z;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                this->blocks[x][y][z] = (Block){BLOCK_TYPE::SOLID};
            }
        }
    }
    
    this->calculateMesh();
    this->firstGen = false;
}

void Chunk::calculateMesh()
{
    if (!this->firstGen)
    {
        UnloadModel(this->model);
    }
    
    Mesh mesh = {0};
    mesh.vboId = (unsigned int *)RL_CALLOC(7, sizeof(unsigned int));

    float *vertices = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 256 * sizeof(float));
    float *normals = (float *)RL_MALLOC(36 * 3 * 16 * 16 * 256 * sizeof(float));
    float *texcoords = (float *)RL_MALLOC(36 * 2 * 16 * 16 * 256 * sizeof(float));

    int verticesCount = 0;
    int texcoordsCount = 0;
    int normalsCount = 0;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                if (this->blocks[x][y][z].TYPE == BLOCK_TYPE::SOLID) {
                    SOLID_BLOCK_VERTICES blockVertices = GenCubeVertices(x, y, z);
                    // Vertices
                    // West
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.WEST_VERTICES[v];
                    }
                    verticesCount += 6 * 3;
                    // East
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.EAST_VERTICES[v];
                    }
                    verticesCount += 6 * 3;
                    // Top
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.TOP_VERTICES[v];
                    }
                    verticesCount += 6 *3;
                    // Bottom
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.BOTTOM_VERTICES[v];
                    }
                    verticesCount += 6 * 3;
                    // North
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.NORTH_VERTICES[v];
                    }
                    verticesCount += 6 * 3;
                    // South
                    for (int v = 0; v < 6 * 3; v++)
                    {
                        vertices[verticesCount + v] = blockVertices.SOUTH_VERTICES[v];
                    }
                    verticesCount += 6 *3;

                    // Textures coords
                    // West
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.WEST_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;
                    // East
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.EAST_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;
                    // Top
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.TOP_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;
                    // Bottom
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.BOTTOM_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;
                    // North
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.NORTH_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;
                    // South
                    for (int t = 0; t < 6 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = SOLID_BLOCK_MESH.TEX_COORDS.SOUTH_COORDS[t];
                    }
                    texcoordsCount += 6 * 2;

                    // Normals
                    // West
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.WEST_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                    // East
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.EAST_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                    // Top
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.TOP_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                    // Bottom
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.BOTTOM_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                    // North
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.NORTH_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                    // South
                    for (int n = 0; n < 6 * 3; n++)
                    {
                        normals[normalsCount + n] = SOLID_BLOCK_MESH.NOMALS.SOUTH_NORMALS[n];
                    }
                    normalsCount += 6 * 3;
                }
            }
        }
    }

    mesh.vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
    memcpy(mesh.vertices, vertices, verticesCount * sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
    memcpy(mesh.texcoords, texcoords, texcoordsCount * sizeof(float));

    mesh.normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
    memcpy(mesh.normals, normals, normalsCount * sizeof(float));

    mesh.vertexCount = verticesCount / 3;         // fixme: Why divide by 3 ???
    mesh.triangleCount = (verticesCount / 3) / 2; // fixme: Why divide by 3 and 2 ???

    RL_FREE(vertices);
    RL_FREE(texcoords);
    RL_FREE(normals);

    rlLoadMesh(&mesh, false);

    this->model = LoadModelFromMesh(mesh);

    this->model.materials[0].maps[MAP_DIFFUSE].texture = LoadTexture(ASSETS_PATH "grass.png");
}

Vector3 Chunk::getBlockWorldCoord(int x, int y, int z)
{
    Vector3 blockWorldCoord = {
        ((this->posX - 1) * 16) + x + 1,
        y + 1,
        ((this->posZ - 1) * 16) + z + 1
    };

    return blockWorldCoord;
}

Chunk::~Chunk() {
    if (!this->firstGen)
    {
        UnloadModel(this->model);
    }
}