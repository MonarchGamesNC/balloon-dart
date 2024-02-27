#include <iostream>
#include <vector>
#include "raylib.h"
#include "balloonSpawner.h"


BalloonSpawner::BalloonSpawner() {
    // Default constructor
}


BalloonSpawner::BalloonSpawner(std::vector<Texture2D> _textures, float spawnRate) {
	this->spawnRate = spawnRate;
    this->lifetimeTime = spawnRate;
	this->textures = _textures;
	
	this->texture = this->textures[1];

    // Add spawn points
	float spawnPointOffset = GetScreenWidth() / 5;
	this->spawnPoints.reserve(5);
    this->spawnPoints = {
        100,
		100+spawnPointOffset,
		100+(spawnPointOffset*2),
		100+(spawnPointOffset*3),
		100+(spawnPointOffset*4)
    };

	//std::cout << "Spawn point: " << 100 << std::endl;
	//std::cout << "Spawn point: " << 100+spawnPointOffset << std::endl;
	//std::cout << "Spawn point: " << 100+(spawnPointOffset*2) << std::endl;
	//std::cout << "Spawn point: " << 100+(spawnPointOffset*3) << std::endl;
	//std::cout << "Spawn point: " << 100+(spawnPointOffset*4) << std::endl;

}

void BalloonSpawner::Spawn() {
    if (balloonsSpawned.size() >= 5) {
        std::cout << "size reached: " << balloonsSpawned.size() << std::endl;
        std::cout << "capacity reached: " << balloonsSpawned.capacity() << std::endl;
        return;
    }

    // Pick a random spawn point from the
    // list of spawn points, and spawn a balloon there
    // 1. Create a list of spawn points (DONE)
    // 2. Pick a random spawn point (DONE)
    // 3. Spawn a balloon at that spawn point (DONE)
    // 4. Make sure next random spawn isn't the same as the last (DONE)
	// 5. Pick random balloon color (DONE)
	// 6. TODO:: Play sound depending on color of balloon

    float startingY = (float)(GetScreenHeight()+200);

    // Randomly pick a spawn point
	int randomIndex = this->getRandomSpawnPoint();

    // Print out the number of balloons spawned
    std::cout << "Balloons before spawned: " << balloonsSpawned.size() << std::endl;
    std::cout << "Balloons capacity: " << balloonsSpawned.capacity() << std::endl;

    balloonsSpawned.emplace_back(Balloon(
		// Get a random texture to spawn
		textures[GetRandomValue(0, textures.size() - 1)],
        Vector2{ spawnPoints[randomIndex], startingY},
        Vector2{ 0, -2.0f}
    ));

    // Print out the number of balloons spawned
    std::cout << "Balloons after spawned: " << balloonsSpawned.size() << std::endl;
}

void BalloonSpawner::Update() {
    this->spawnTick(); // Check if we need to spawn a balloon

    // Always start with a balloon
    if (balloonsSpawned.size() == 0) {
        Spawn();
    }

    for (int i = 0; i < (int)balloonsSpawned.size(); i++) {
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
    for (int i = 0; i < (int)balloonsSpawned.size(); i++) {
        balloonsSpawned[i].Draw();
    }
}

void BalloonSpawner::UnloadTextures() {
    for (int i = 0; i < (int)balloonsSpawned.size(); i++) {
        UnloadTexture(balloonsSpawned[i].balloonTexture);
    }

}

void BalloonSpawner::spawnTick() {
     if (lifetimeTime <= 0) {
        Spawn();

        lifetimeTime = spawnRate;
    } else {
        lifetimeTime -= GetFrameTime();
    }
}

int BalloonSpawner::getRandomSpawnPoint() {
	// Randomly pick a spawn point
    int randomIndex = GetRandomValue(0, spawnPoints.size() - 1);
	// TODO:: allow debug logs but mute on release
    std::cout << "Random index: " << randomIndex << std::endl;

	if (this->lastSpawnPointIndex == randomIndex) {
		std::cout << "Random index matches previous: " << randomIndex << " prev: " << this->lastSpawnPointIndex << std::endl;
		return getRandomSpawnPoint();
	}

	this->lastSpawnPointIndex = randomIndex;

	return randomIndex;
}

int BalloonSpawner::getRandomTextureIndex() {
	// Randomly pick a spawn point
    int randomIndex = GetRandomValue(0, textures.size() - 1);
	// TODO:: allow debug logs but mute on release
    std::cout << "Random texture: " << randomIndex << std::endl;


	return randomIndex;
}