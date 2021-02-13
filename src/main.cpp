#include "raylib.h"
#include <cstdlib>
#include <cstring>
#include "rlgl.h"
#include "Chunk.hpp"
#include <iostream>
#include "WorldContext.hpp"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};      // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                              // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;                 // Camera mode type
    worldState.loadAndRenderChunk(1,1);
    std::string formatted_coord_string = std::to_string(1) + ',' + std::to_string(1);
    if ( (worldState.chunks.count(formatted_coord_string) > 0) )
    {
        worldState.chunks[formatted_coord_string]->calculateMesh();
    }
    worldState.loadAndRenderChunk(1,2);
    formatted_coord_string = std::to_string(1) + ',' + std::to_string(2);
    if ( (worldState.chunks.count(formatted_coord_string) > 0) )
    {
        worldState.chunks[formatted_coord_string]->calculateMesh();
    }
    formatted_coord_string = std::to_string(1) + ',' + std::to_string(1);
    if ( (worldState.chunks.count(formatted_coord_string) > 0) )
    {
        worldState.chunks[formatted_coord_string]->calculateMesh();
    }
    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera); // Update camera

        if (IsKeyDown('Z'))
            camera.target = (Vector3){0.0f, 0.0f, 0.0f};
        if (IsKeyDown('R')) {
            formatted_coord_string = std::to_string(1) + ',' + std::to_string(1);
            if ( (worldState.chunks.count(formatted_coord_string) > 0) )
            {
                worldState.chunks[formatted_coord_string]->calculateMesh();
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        worldState.loadAndRenderChunk(1,1);
        worldState.loadAndRenderChunk(1,2);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawRectangle(10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 320, 133, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
        DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
