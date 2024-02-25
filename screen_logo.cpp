#include <cstddef>

#include "screen_logo.h"
#include "raylib.h"

LogoScreen::LogoScreen() {
	Init();
}

void LogoScreen::Init() {
	font = LoadFontEx("./assets/fonts/EazyChat.ttf", 72, NULL, 0);
	finishScreen = 0;
	framesCounter = 0;
	lettersCount = 0;

	logoPositionX = GetScreenWidth()/2 - 250;
	logoPositionY = GetScreenHeight()/2;


	state = 0;
	alpha = 1.0f;
}

void LogoScreen::Draw() {
	if (state == 0) {    // Draw "raylib" text-write animation + "powered by"
		DrawTextEx(
			font,
			TextSubtext("Monarch Games", 0, lettersCount),
			Vector2{ (float)logoPositionX, (float)logoPositionY},
			72,
			0,
			Fade(BLACK, alpha)
		); // Draw text using font and additional parameters
	}
}

void LogoScreen::Update() {
	if (state == 0) {    // State 3: "raylib" text-write animation logic
    framesCounter++;
		if (lettersCount < 14) {
			if (framesCounter/12) { // Every 12 frames, one more letter!
				lettersCount++;
				framesCounter = 0;
			}
		} else {    // When all letters have appeared, just fade out everything
			if (framesCounter > 200) {
				alpha -= 0.02f;
				if (alpha <= 0.0f) {
					alpha = 0.0f;
					finishScreen = 1;   // Jump to next screen
				}
			}
		}
  }
}

void LogoScreen::Unload() {
	UnloadFont(font);
}

GameScreen LogoScreen::GetNextScreen() {
	return GAMEPLAY;
}

int LogoScreen::Finish() {  return finishScreen; }