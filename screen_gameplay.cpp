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
	balloonTexture = LoadTexture("./assets/blue_balloon_1.png");
	bgMusic = LoadMusicStream("./assets/bg_music_1.ogg");
	
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
  ballonSpawner.Draw();
}

void GameplayScreen::Unload() {
	UnloadMusicStream(bgMusic);
	UnloadTexture(balloonTexture);
}

int GameplayScreen::Finish() {
    return 0;
}

GameScreen GameplayScreen::GetNextScreen() {
	return CREDITS;
}