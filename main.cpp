#include <iostream>
#include "raylib.h"
#include "balloonSpawner.h"
#include "resourcemanager.h"
#include "screen_logo.c"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, SETTINGS, CREDITS } GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Balloon Popper Game");
    InitAudioDevice();              // Initialize audio device
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Allow the user to resize the window
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Create balloon spawner
        // Give screen width and height
        // Allow for a max number of balloons
        // Spawn balloons at random locations
    // Screens
		// Splash screen with Raylib logo
		// Start screen
			// Tap to start
		// Game screen
			// Game loop for balloon poppings
			// Small back button / gear button
		// Setting screen for sound volume?
			// Maybe save setting somewhere?
			// If not notify it's per play session
	
	ResourceManager resourceManager = ResourceManager();
    resourceManager.LoadResources();

    BalloonSpawner ballonSpawner = BalloonSpawner(
        resourceManager.BlueBaloon,
        3.0f
    );

	// Play BG Music for entire game.. for this it will not be 
	// scene specific
	//PlayMusicStream(resourceManager.BGMusic);
    InitLogoScreen();
    //--------------------------------------------------------------------------------------
	GameScreen currentScreen = LOGO;
    // Main game loop
	while (!WindowShouldClose()) {   // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		// 
		//----------------------------------------------------------------------------------
		// NOTE: This could be in a music manager of sorts but eh...
		switch (currentScreen) {
			case LOGO:
				UpdateLogoScreen();
            default:
                break;
		}
		
		//UpdateMusicStream(resourceManager.BGMusic);	
		
		// Spawn balloons
		// ballonSpawner.Update();
       
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (currentScreen) {
			case LOGO:
				DrawLogoScreen();
            default:
                break;
		}
			// Draw spawned balloons
			// ballonSpawner.Draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    resourceManager.UnloadAllResources();
    //--------------------------------------------------------------------------------------
	CloseAudioDevice(); // Close the audio device
	CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}