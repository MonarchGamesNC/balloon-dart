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

    // Add spawn points
    // TODO - Make list based on screen width
    spawnPoints = {
        100, 200, 300, 400, 500, 600, 700, 800, 900
    };
}

void BalloonSpawner::Spawn() {
    // Pick a random spawn point from the
    // list of spawn points, and spawn a balloon there
    // 1. Create a list of spawn points
    // 2. Pick a random spawn point
    // 3. Spawn a balloon at that spawn point

    float startingY = (float)(GetScreenHeight()+200);

    // Randomly pick a spawn point
    int randomIndex = GetRandomValue(0, spawnPoints.size()-1);

    Balloon balloon = Balloon(
        texture,
        // Spawn off screen
        Vector2{ spawnPoints[randomIndex], startingY},
        Vector2{ 0, -2.0f}
    );

    // Print out the number of balloons spawned
    std::cout << "Balloons before spawned: " << balloonsSpawned.size() << std::endl;

    balloonsSpawned.push_back(balloon);

    // Print out the number of balloons spawned
    std::cout << "Balloons after spawned: " << balloonsSpawned.size() << std::endl;
}

void BalloonSpawner::Update() {
    timer.Tick();

    if (balloonsSpawned.size() == 0) {
        Spawn();
    }

    for (int i = 0; i < balloonsSpawned.size(); i++) {
        // Store index in local loop variable
        Balloon &balloon = balloonsSpawned[i];

        balloon.Update();

        // Check if balloon is popped
        if (balloon.IsPopped()) {
            balloonsSpawned.erase(balloonsSpawned.begin() + i);
        }
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