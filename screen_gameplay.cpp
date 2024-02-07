#include "screen_gameplay.h"
#include "raylib.h"

GameplayScreen::GameplayScreen() {
	Init();
}

GameplayScreen::GameplayScreen(ResourceManager resourceManager) {
    // TODO:: Handle the resource manager here instead of in the main game loop
    // that way each screen can have its own resource manager and unload resources
    // once the screen is done... or something like that
    this->resourceManager = resourceManager;

    // Run other init tasks
	Init();
}

// GameplayScreen::~GameplayScreen() {
//     Unload();
// }

void GameplayScreen::Init() {
    ballonSpawner = BalloonSpawner(
        resourceManager.BlueBaloon,
        1.0f
    );
}

void GameplayScreen::Update() {
    // UpdateMusicStream(resourceManager.BGMusic);	

    ballonSpawner.Update();
}

void GameplayScreen::Draw() {
    ballonSpawner.Draw();
}

void GameplayScreen::Unload() {}

int GameplayScreen::Finish() {
    return 0;
}

