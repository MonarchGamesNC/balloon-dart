#include <cstddef>
#include <raylib.h>
#include <cstring>
#include "screen_menu.hh"

MainMenuScreen::MainMenuScreen() {
	Init();
}

void MainMenuScreen::Init() {
    bgGraphic = LoadTexture("./assets/bgs/cardboard.png");
	titleFont = LoadFontEx("./assets/fonts/EazyChat.ttf", 72, NULL, 0);
	menuItemFont = LoadFontEx("./assets/fonts/EazyChat.ttf", 48, NULL, 0);
    finishScreen = 0;
	framesCounter = 0;
	lettersCount = 0;

    screenCenterX = GetScreenWidth()/2;
    screenCenterY = GetScreenHeight()/2;

	titlePositionX = screenCenterX - 250;
	titlePositionY = screenCenterY - 250;

	state = 0;
	alpha = 1.0f;
}

void MainMenuScreen::Draw() {
    // Draw bg to entire screen
	DrawTexturePro(
        bgGraphic,
		Rectangle { 0, 0, (float)bgGraphic.width,  (float)bgGraphic.height },
		Rectangle { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
		Vector2 { 0, 0 },
        0,
        WHITE
    );
	// if (state == 0) {    // Draw "raylib" text-write animation + "powered by"
	// 	DrawTextEx(
	// 		font,
	// 		TextSubtext("Monarch Games", 0, lettersCount),
	// 		Vector2{ (float)logoPositionX, (float)logoPositionY},
	// 		72,
	// 		0,
	// 		Fade(BLACK, alpha)
	// 	); // Draw text using font and additional parameters
	// }
    
    DrawTextEx(
        titleFont,
        "Balloon Popper",
        Vector2{ (float)titlePositionX, (float)titlePositionY},
        72,
        0,
        BLUE
    );


    DrawTextEx(
        menuItemFont,
        "Start",
        Vector2{ (float)screenCenterX - 65, (float)screenCenterY},
        48,
        0,
        menuColor
    );


    DrawTextEx(
        menuItemFont,
        "Credits",
        Vector2{ (float)screenCenterX - 83, (float)screenCenterY + 50},
        48,
        0,
        WHITE
    );
}

void MainMenuScreen::Update() {
    // Check if mouse is over start button
    if (CheckCollisionPointRec(GetMousePosition(), Rectangle { (float)screenCenterX - 65, (float)screenCenterY, 130, 48 })) {
        menuColor = BLACK;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            nextScreen = GAMEPLAY;
            finishScreen = 1;
        }
    }
    //  else if (std::strcmp(menuColor, "BLACK") == 0) {
    //     menuColor = WHITE;
    // }
// 	if (state == 0) {    // State 3: "raylib" text-write animation logic
//     framesCounter++;
// 		if (lettersCount < 14) {
// 			if (framesCounter/12) { // Every 12 frames, one more letter!
// 				lettersCount++;
// 				framesCounter = 0;
// 			}
// 		} else {    // When all letters have appeared, just fade out everything
// 			if (framesCounter > 200) {
// 				alpha -= 0.02f;
// 				if (alpha <= 0.0f) {
// 					alpha = 0.0f;
// 					finishScreen = 1;   // Jump to next screen
// 				}
// 			}
// 		}
//   }
}

void MainMenuScreen::Unload() {
    UnloadFont(titleFont);
    UnloadFont(menuItemFont);
    UnloadTexture(bgGraphic);
}

GameScreen MainMenuScreen::GetNextScreen() {
	return nextScreen;
}

int MainMenuScreen::Finish() {  return finishScreen; }