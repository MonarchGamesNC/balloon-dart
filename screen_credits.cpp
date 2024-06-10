#include <iostream>
#include <raylib.h>
#include "screen_credits.hh"


CreditsScreen::CreditsScreen() {
	if (!screenReady) {
		Init();
		finishScreen = 0;
		exitButtonTimer = 0.75; // needs to hold for 1 seconds
	}
}

void CreditsScreen::Init() {
	this->loadTextures();

	this->font = LoadFontEx("./assets/fonts/EazyChat.ttf", 72, NULL, 0);
	this->bgGraphic = LoadTexture("./assets/bgs/cardboard.png");

	this->bgMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(bgMusic, 0.2);

	screenReady = true;
}

void CreditsScreen::Update() {
	if (!IsMusicStreamPlaying(bgMusic)) {
		PlayMusicStream(bgMusic);
	}

	UpdateMusicStream(bgMusic);	
}

void CreditsScreen::Draw() {
	DrawBgGraphic();

    DrawTextEx(font, "Credits", Vector2{(float)(GetScreenWidth()/2),(float)(GetScreenHeight()/2)}, 72, 0, BLUE);

    DrawTextEx(font, "Art -- Link", Vector2{ 0,0}, 32, 0, BLUE);
    DrawTextEx(font, "Music -- Link", Vector2{0, 35}, 32, 0, BLUE);
    DrawTextEx(font, "Font -- Link", Vector2{0, 70}, 32, 0, BLUE);
    DrawTextEx(font, "Engine -- Link", Vector2{0, 105}, 32, 0, BLUE);
    DrawTextEx(font, "Dedicated", Vector2{0, 140}, 32, 0, BLUE);
    DrawTextEx(font, "Written by", Vector2{0, 175}, 32, 0, BLUE);
}

void CreditsScreen::DrawBgGraphic() {
	// Draw bg to entire screen
	DrawTexturePro(
        bgGraphic,
		Rectangle { 0, 0, (float)bgGraphic.width,  (float)bgGraphic.height },
		Rectangle { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
		Vector2 { 0, 0 },
        0,
        WHITE
    );
}

void CreditsScreen::Unload() {
	UnloadMusicStream(bgMusic);
	UnloadTexture(bgGraphic);
}

int CreditsScreen::Finish() {
    return finishScreen;
}

bool CreditsScreen::Closed() { return false; }

GameScreen CreditsScreen::GetNextScreen() {
	return MAINMENU;
}


void CreditsScreen::loadTextures() {
	// Load all the textures we need for now
}