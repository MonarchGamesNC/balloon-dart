#include "raylib.h"
#include "screen_gameplay.h"
#include <iostream>
#define BALLOON_SPAWN_RATE 3.0f

GameplayScreen::GameplayScreen() {
	if (!screenReady) Init();
}

// GameplayScreen::~GameplayScreen() {
//     Unload();
// }

void GameplayScreen::Init() {
	balloonTexture = LoadTexture("./assets/gfx/blue_balloon_1.png");
	bgGraphic = LoadTexture("./assets/bgs/cardboard.png");
	

	bgMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(bgMusic, 0.1);

	ballonSpawner = BalloonSpawner(
		balloonTexture,
		BALLOON_SPAWN_RATE
	);

	screenReady = true;
}

void GameplayScreen::Update() {
	if (!IsMusicStreamPlaying(bgMusic)) {
		PlayMusicStream(bgMusic);
	}

	UpdateMusicStream(bgMusic);	
	ballonSpawner.Update();
}

void GameplayScreen::Draw() {
	DrawBgGraphic();
	ballonSpawner.Draw();
}

void GameplayScreen::DrawBgGraphic() {
	// Draw bg to entire screen
	DrawTexturePro(
        bgGraphic,
		Rectangle { 0, 0, (float)bgGraphic.width,  (float)bgGraphic.height },
		// TODO:: Make a static rectangle to use across
		Rectangle { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
		Vector2 { 0, 0 },
        0,
        WHITE
    );
}

void GameplayScreen::Unload() {
	UnloadMusicStream(bgMusic);
	UnloadTexture(balloonTexture);
	UnloadTexture(bgGraphic);
}

int GameplayScreen::Finish() {
    return 0;
}

GameScreen GameplayScreen::GetNextScreen() {
	return CREDITS;
}