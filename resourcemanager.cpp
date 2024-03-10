#include "resourcemanager.hh"

void ResourceManager::LoadResources() {
  BlueBaloon = LoadTexture("./assets/gfx/blue_balloon_1.png");
	BGMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(BGMusic, 0.3);
}

void ResourceManager::UnloadAllResources() {
    UnloadTexture(BlueBaloon);
	UnloadMusicStream(BGMusic);
}
