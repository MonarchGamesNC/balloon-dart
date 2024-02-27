#include <iostream>
#include "raylib.h"
#include "screen_gameplay.h"

#define BALLOON_SPAWN_RATE 3.0f

// TODO:: Make singleton to use in gameplay to keep track of score
GameplayScreen::GameplayScreen() {
	if (!screenReady) Init();
}


void GameplayScreen::Init() {
	this->loadTextures();

	bgGraphic = LoadTexture("./assets/bgs/cardboard.png");
	

	bgMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(bgMusic, 0.1);

	ballonSpawner = BalloonSpawner(
		this->textures,
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
	UnloadTexture(bgGraphic);

	for (unsigned i = 0; i < this->textures.size(); i++) {
		UnloadTexture(this->textures[i]);
	}

	// Reset vector
	this->textures.clear();
}

int GameplayScreen::Finish() {
    return 0;
}

GameScreen GameplayScreen::GetNextScreen() {
	return CREDITS;
}

void GameplayScreen::loadTextures() {
	// Load all the textures we need for now
	this->textures.emplace_back(LoadTexture("./assets/gfx/blue_balloon_1.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/green_balloon_1.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/orange_balloon_1.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/pink_balloon_1.png"));
}