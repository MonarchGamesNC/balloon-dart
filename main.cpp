#include <iostream>
#include "raylib.h"
#include "balloonSpawner.h"
#include "resourcemanager.h"
#include "screen_logo.h"

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
    //--------------------------------------------------------------------------------------
	GameScreen currentScreen = LOGO;
	LogoScreen logoScreen = LogoScreen();
    
	// Main game loop
	while (!WindowShouldClose()) {   // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		// 
		//----------------------------------------------------------------------------------
		// NOTE: This could be in a music manager of sorts but eh...
		currentScreen.Update();
		
		//UpdateMusicStream(resourceManager.BGMusic);	
		
		// Spawn balloons
		// ballonSpawner.Update();
       
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
			currentScreen.Draw();
			// Draw spawned balloons
			// ballonSpawner.Draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    resourceManager.UnloadAllResources();
	
	// Unload current screen data before closing
    switch (currentScreen) {
        case LOGO: logoScreen.Unload(); break;
        // case TITLE: UnloadTitleScreen(); break;
        // case GAMEPLAY: UnloadGameplayScreen(); break;
        // case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    //--------------------------------------------------------------------------------------
	CloseAudioDevice(); // Close the audio device
	CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Change to screen, no transition
static void ChangeToScreen(int screen) {
    // Unload current screen
    switch (currentScreen) {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case GAMEPLAY: UnloadGameplayScreen(); break;
        case ENDING: UnloadEndingScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen) {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case GAMEPLAY: InitGameplayScreen(); break;
        case ENDING: InitEndingScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(int screen) {
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect
static void UpdateTransition(void) {
    if (!transFadeOut)
    {
        transAlpha += 0.02f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                // case TITLE: UnloadTitleScreen(); break;
                // case GAMEPLAY: UnloadGameplayScreen(); break;
                // case ENDING: UnloadEndingScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                // case LOGO: InitLogoScreen(); break;
                // case TITLE: InitTitleScreen(); break;
                // case GAMEPLAY: InitGameplayScreen(); break;
                // case ENDING: InitEndingScreen(); break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = -1;
        }
    }
}