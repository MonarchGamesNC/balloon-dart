#include <iostream>
#include "raylib.h"
#include "balloonSpawner.h"
#include "resourcemanager.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Allow the user to resize the window
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    // Create balloon spawner
        // Give screen width and height
        // Allow for a max number of balloons
        // Spawn balloons at random locations
    // Create balloon
    // Balloon ballons[10] = {};
    ResourceManager resourceManager = ResourceManager();
    resourceManager.LoadResources();

    BalloonSpawner ballonSpawner = BalloonSpawner(
        resourceManager.BlueBaloon,
        3.0f
    );

    ballonSpawner.Spawn();
    // New timer
    // Timer timer = Timer(2.0f, [&ballonSpawner]() {
    //     ballonSpawner.Spawn();
    // });

    //--------------------------------------------------------------------------------------
    
    // Load textures


    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        ballonSpawner.Update();
       
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            ballonSpawner.Draw();

            // DrawTexture(balloon.balloonTexture, balloon.position.x, balloon.position.y, WHITE);     
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    // UnloadTexture(balloon.balloonTexture);
    resourceManager.UnloadAllResources();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}