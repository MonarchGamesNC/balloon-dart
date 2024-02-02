#include "resourcemanager.h"

void ResourceManager::LoadResources() {
    BlueBaloon = LoadTexture("./assets/blue_balloon_1.png");
	BGMusic = LoadMusicStream("./assets/bg_music_1.ogg");
	SetMusicVolume(BGMusic, 0.3);
}

void ResourceManager::UnloadAllResources() {
    UnloadTexture(BlueBaloon);
	UnloadMusicStream(BGMusic);
}