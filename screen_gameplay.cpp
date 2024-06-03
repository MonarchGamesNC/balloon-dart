#include <iostream>
#include <raylib.h>
#include "screen_gameplay.hh"
#include "score.hh"
#include "balloon_spawner.hh"

#define BALLOON_SPAWN_RATE 3.0f

int score = 0;

GameplayScreen::GameplayScreen() {
	if (!screenReady) {
		Init();
		score = 0;
		finishScreen = 0;
		exitButtonTimer = 0.75; // needs to hold for 1 seconds
	}
}

void GameplayScreen::Init() {
	this->loadTextures();

	this->font = LoadFontEx("./assets/fonts/EazyChat.ttf", 32, NULL, 0);
	this->bgGraphic = LoadTexture("./assets/bgs/cardboard.png");
	this->popSound = LoadSound("./assets/sfx/soft-balloon-pop.ogg");
	SetSoundVolume(popSound, 0.7);

	this->bgMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(bgMusic, 0.2);

	ballonSpawner = BalloonSpawner(
		this->textures,
		this->popSound,
		BALLOON_SPAWN_RATE
	);

	screenReady = true;
}

void GameplayScreen::Update() {
	if (!IsMusicStreamPlaying(bgMusic)) {
		PlayMusicStream(bgMusic);
	}

	if (score > 10 && ballonSpawner.SpawnRate() == BALLOON_SPAWN_RATE) {
		ballonSpawner.UpdateSpawnRate(BALLOON_SPAWN_RATE / 2);
		ballonSpawner.SetSpawnVelocity(Vector2{ 0, -3.0f });
	} else if (score > 25 && ballonSpawner.SpawnRate() == (BALLOON_SPAWN_RATE / 2)) {
		// Random denominator to make it super fast
		ballonSpawner.UpdateSpawnRate(BALLOON_SPAWN_RATE / 3.5);
		ballonSpawner.SetSpawnVelocity(Vector2{ 0, -4.0f });
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 mousePos = GetMousePosition();
		// Check if mouse is over exit button
		// For more than 5 seconds
		if (CheckCollisionPointRec(mousePos, Rectangle { (float)GetScreenWidth()-60, 10, 55, 26 })) {
			exitButtonTimer -= GetFrameTime();
			if (exitButtonTimer <= 0) {
				finishScreen = 1;
			}

			// If the button is released, reset the timer
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				exitButtonTimer = 1;
			} 
		}
		
	}

	UpdateMusicStream(bgMusic);	
	ballonSpawner.Update();
}

void GameplayScreen::Draw() {
	DrawBgGraphic();

	// Draw score
	DrawTextEx(font, TextFormat("Score %i", score), Vector2 { 10, 10 }, 32, 0, WHITE);
	DrawTextEx(font, "Exit", Vector2 { (float)GetScreenWidth()-60, 10 }, 32, 0, WHITE);
	DrawRectangle((float)GetScreenWidth()-60, 10, 55, 26 , Fade(BLACK, 0.5));
	ballonSpawner.Draw();
}

void GameplayScreen::DrawBgGraphic() {
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

void GameplayScreen::Unload() {
	UnloadMusicStream(bgMusic);
	UnloadSound(popSound);
	UnloadTexture(bgGraphic);

	for (unsigned i = 0; i < this->textures.size(); i++) {
		UnloadTexture(this->textures[i]);
	}

	// Reset vector
	this->textures.clear();
}

int GameplayScreen::Finish() {
    return finishScreen;
}

GameScreen GameplayScreen::GetNextScreen() {
	return SPLASH;
}

void GameplayScreen::loadTextures() {
	// Load all the textures we need for now
	this->textures.emplace_back(LoadTexture("./assets/gfx/blue_balloon.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/green_balloon.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/orange_balloon.png"));
	this->textures.emplace_back(LoadTexture("./assets/gfx/pink_balloon.png"));
}