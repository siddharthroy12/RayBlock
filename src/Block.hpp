#ifndef BLOCK_HPP
#define BLOCK_HPP

enum class BLOCK_TYPE
{
    SOLID,
    AIR,
    _NULL,
};

struct SOLID_BLOCK_NORMALS
{
    float WEST_NORMALS[18] = {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    float EAST_NORMALS[18] = {
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
    };

    float TOP_NORMALS[18] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    float BOTTOM_NORMALS[18] = {
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    float NORTH_NORMALS[18] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    float SOUTH_NORMALS[18] = {
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f
    };
};

struct SOLID_BLOCK_TEXTURE_COORDS {
    float WEST_COORDS[12] = {
        0.5f, 1.0f,
        0.25f, 1.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.5f, 0.0f,
        0.5f, 1.0f,
    };

    float EAST_COORDS[12] = {
        0.25f, 1.0f,
        0.25f, 0.0f,
        0.5f, 0.0f,

        0.5f, 0.0f,
        0.5f, 1.0f,
        0.25f, 1.0f,
    };

    float TOP_COORDS[12] = {
        0.0f, 0.0f,
        0.25f, 0.0f,
        0.25f, 1.0f,

        0.25f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };

    float BOTTOM_COORDS[12] = {
        0.0f, 0.0f,
        0.25f, 0.0f,
        0.25f, 1.0f,

        0.25f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };

    float NORTH_COORDS[12] = {
        0.25f, 1.0f,
        0.25f, 0.0f,
        0.5f, 0.0f,

        0.5f, 0.0f,
        0.5f, 1.0f,
        0.25f, 1.0f,
    };

    float SOUTH_COORDS[12] = {
        0.5f, 1.0f,
        0.25f, 1.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.5f, 0.0f,
        0.5f, 1.0f,
    };
};

struct SOLID_BLOCK_VERTICES
{
    float WEST_VERTICES[18] = {0};
    float EAST_VERTICES[18] = {0};
    float TOP_VERTICES[18] = {0};
    float BOTTOM_VERTICES[18] = {0};
    float NORTH_VERTICES[18] = {0};
    float SOUTH_VERTICES[18] = {0};
};

SOLID_BLOCK_VERTICES GenCubeVertices(int x, int y, int z);

struct _SOLID_BLOCK_MESH
{
    SOLID_BLOCK_NORMALS NOMALS;
    SOLID_BLOCK_TEXTURE_COORDS TEX_COORDS;
};

extern _SOLID_BLOCK_MESH SOLID_BLOCK_MESH;

struct Block
{
    BLOCK_TYPE TYPE;
};

#endif