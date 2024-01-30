#include "raylib.h"
#include "balloonSpawner.h"
#include <iostream>


BalloonSpawner::BalloonSpawner(Texture2D texture, float spawnRate) {
    this->texture = texture;
    
    timer = Timer(spawnRate, true, [&](){
        Spawn();
    });

    // Start ticking
    timer.Start();
}

void BalloonSpawner::Spawn() {
    // Pick a random spawn point from the
    // list of spawn points, and spawn a balloon there
    // 1. Create a list of spawn points
    // 2. Pick a random spawn point
    // 3. Spawn a balloon at that spawn point

    float startingY = (float)(GetScreenHeight()+200);

    Balloon balloon = Balloon(
        texture,
        // Spawn off screen
        Vector2{ 500, startingY},
        Vector2{ 0, -2.0f}
    );

    balloonsSpawned.push_back(balloon);
}

void BalloonSpawner::Update() {
    timer.Tick();


    if (balloonsSpawned.size() == 0) {
        Spawn();
    }

    for (int i = 0; i < balloonsSpawned.size(); i++) {
        balloonsSpawned[i].Update();
    }
}

void BalloonSpawner::Draw() {
    for (int i = 0; i < balloonsSpawned.size(); i++) {
        balloonsSpawned[i].Draw();
    }
}

void BalloonSpawner::UnloadTextures() {
    for (int i = 0; i < balloonsSpawned.size(); i++) {
        UnloadTexture(balloonsSpawned[i].balloonTexture);
    }
}