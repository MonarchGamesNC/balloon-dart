#include <iostream>
#include <raylib.h>

#include "screen_logo.hh"
#include "screen_splash.hh"
#include "screen_gameplay.hh"
#include "screen_menu.hh"
#include "screen_playground.hh"

#define GAME_TITLE "Balloon Pop"

// TODO:: Enable web version of Raylib
//Change to screen, no transition
Screen* ChangeToScreen(Screen* currentScreen, int screen) {
	// Unload current screen
	currentScreen->Unload();    

	Screen* nextScreen;
	// Init next screen
	switch (screen) {
		case SPLASH:
			nextScreen = new SplashScreen();
			break;
		case LOGO:
			nextScreen = new LogoScreen();
			break;
		case GAMEPLAY:
			nextScreen = new GameplayScreen();
			break;
		default: 
			nextScreen = new GameplayScreen();
			break;
	}

	return nextScreen;
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
	#ifdef RELEASE
		SetTraceLogLevel(LOG_NONE);
	#else
		SetTraceLogLevel(LOG_DEBUG);
	#endif

		//emscripten_set_main_loop(mainLoop, 0, 1);

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1200;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, GAME_TITLE);
	SetWindowState(FLAG_WINDOW_RESIZABLE); // Allow the user to resize the window
	// SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	InitAudioDevice();              // Initialize audio device

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

	//--------------------------------------------------------------------------------------
	
	Screen* currentScreen = new SplashScreen();
  	// Screen* currentScreen = new PlaygroundScreen();
	
	// Main game loop
	while (!WindowShouldClose()) {   // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		// 
		//----------------------------------------------------------------------------------
		
		currentScreen->Update();
		if (currentScreen->Finish() == 1) {
    	currentScreen = ChangeToScreen(
			currentScreen,
			currentScreen->GetNextScreen()
		);
    }
  
		// Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    	ClearBackground(RAYWHITE);
		currentScreen->Draw();
	EndDrawing();
    //----------------------------------------------------------------------------------
  }

	// De-Initialization
	currentScreen->Unload(); // Unload current screen data before closing

  //--------------------------------------------------------------------------------------
	CloseAudioDevice(); // Close the audio device
	CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}


// // Request transition to next screen
// static void TransitionToScreen(int screen) {
//     onTransition = true;
//     transFadeOut = false;
//     transFromScreen = currentScreen;
//     transToScreen = screen;
//     transAlpha = 0.0f;
// }

// // Update transition effect
// static void UpdateTransition(void) {
//     if (!transFadeOut)
//     {
//         transAlpha += 0.02f;

//         // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
//         // For that reason we compare against 1.01f, to avoid last frame loading stop
//         if (transAlpha > 1.01f)
//         {
//             transAlpha = 1.0f;

//             // Unload current screen
//             switch (transFromScreen)
//             {
//                 case LOGO: UnloadLogoScreen(); break;
//                 // case TITLE: UnloadTitleScreen(); break;
//                 // case GAMEPLAY: UnloadGameplayScreen(); break;
//                 // case ENDING: UnloadEndingScreen(); break;
//                 default: break;
//             }

//             // Load next screen
//             switch (transToScreen)
//             {
//                 // case LOGO: InitLogoScreen(); break;
//                 // case TITLE: InitTitleScreen(); break;
//                 // case GAMEPLAY: InitGameplayScreen(); break;
//                 // case ENDING: InitEndingScreen(); break;
//                 default: break;
//             }

//             currentScreen = transToScreen;

//             // Activate fade out effect to next loaded screen
//             transFadeOut = true;
//         }
//     }
//     else  // Transition fade out logic
//     {
//         transAlpha -= 0.02f;

//         if (transAlpha < -0.01f)
//         {
//             transAlpha = 0.0f;
//             transFadeOut = false;
//             onTransition = false;
//             transFromScreen = -1;
//             transToScreen = -1;
//         }
//     }
// }
