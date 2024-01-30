#include "resourcemanager.h"

void ResourceManager::LoadResources() {
    BlueBaloon = LoadTexture("./assets/blue_balloon_1.png");
}

void ResourceManager::UnloadAllResources() {
    UnloadTexture(BlueBaloon);
}