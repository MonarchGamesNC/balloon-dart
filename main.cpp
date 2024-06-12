#include <iostream>
#include <raylib.h>

#include "screen_logo.hh"
#include "screen_splash.hh"
#include "screen_gameplay.hh"
#include "screen_menu.hh"
#include "screen_playground.hh"
#include "screen_credits.hh"

#define GAME_TITLE "Balloon Pop"

Screen* ChangeToScreen(Screen*, GameScreen);

// TODO:: Enable web version of Raylib
// TODO:: Add GUI for MainMenu (Play, Credits, Exit)
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
	#ifdef RELEASE
		SetTraceLogLevel(LOG_NONE);
	#else
		SetTraceLogLevel(LOG_DEBUG);
	#endif

	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1200;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, GAME_TITLE);
	// SetWindowState(FLAG_WINDOW_RESIZABLE); // Allow the user to resize the window
	SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	InitAudioDevice();              // Initialize audio device

	//--------------------------------------------------------------------------------------
	Screen* currentScreen = new MainMenuScreen(); // default screen to start at
	
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

		// If any screen wants to gracefully close the window...
		// do it here
		if (currentScreen->Closed()) break;
		
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


//Change to screen, no transition
Screen* ChangeToScreen(Screen* currentScreen, GameScreen screen) {
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
		case MAINMENU:
			nextScreen = new MainMenuScreen();
			break;
		case CREDITS:
			nextScreen = new CreditsScreen();
			break;
		default: 
			nextScreen = new GameplayScreen();
			break;
	}

	return nextScreen;
};