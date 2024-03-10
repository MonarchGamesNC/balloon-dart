#include <vector>
#include <raylib.h>
#include "balloon_spawner.hh"

BalloonSpawner::BalloonSpawner() {/* Default constructor */}

BalloonSpawner::BalloonSpawner(std::vector<Texture2D> _textures, Sound popSound,  float spawnRate) {
	this->spawnRate = spawnRate;
    this->currentTime = spawnRate;
	this->textures = _textures;
    this->popSound = popSound;
    this->spawnVelocity = Vector2{ 0, -2.0f};
    
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

    // TraceLog(LOG_DEBUG, "Spawn point: %i", 100);
    // TraceLog(LOG_DEBUG, "Spawn point: %i", 100+spawnPointOffset);
    // TraceLog(LOG_DEBUG, "Spawn point: %i", 100+(spawnPointOffset*2));
    // TraceLog(LOG_DEBUG, "Spawn point: %i", 100+(spawnPointOffset*3));
    // TraceLog(LOG_DEBUG, "Spawn point: %i", 100+(spawnPointOffset*4));
}

void BalloonSpawner::Spawn() {
    if (balloonsSpawned.size() >= 10) {
        TraceLog(LOG_DEBUG, "size reached: %i", balloonsSpawned.size());
        TraceLog(LOG_DEBUG, "capacity reached: %i", balloonsSpawned.capacity());
        return;
    }

    // Pick a random spawn point from the
    // list of spawn points, and spawn a balloon there
    // 1. Create a list of spawn points (DONE)
    // 2. Pick a random spawn point (DONE)
    // 3. Spawn a balloon at that spawn point (DONE)
    // 4. Make sure next random spawn isn't the same as the last (DONE)
	// 5. Pick random balloon color (DONE)
	// 6. Play sound depending on color of balloon (DONE)
	// 		https://freesound.org/people/wubitog/sounds/188381/
	//		https://freesound.org/people/qubodup/sounds/182856/
    // 7. TODO:: Animate

    float startingY = (float)(GetScreenHeight()+200);

    // Randomly pick a spawn point
	int randomIndex = this->getRandomSpawnPoint();


    balloonsSpawned.emplace_back(Balloon(
		textures[GetRandomValue(0, textures.size() - 1)],
        Vector2{ spawnPoints[randomIndex], startingY},
        popSound,
        spawnVelocity
    ));
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
	if (currentTime <= 0) {
        Spawn();
        currentTime = spawnRate;
    } else {
        currentTime -= GetFrameTime();
    }
}

int BalloonSpawner::getRandomSpawnPoint() {
	// Randomly pick a spawn point
    int randomIndex = GetRandomValue(0, spawnPoints.size() - 1);
	if (this->lastSpawnPointIndex == randomIndex) {
        TraceLog(LOG_DEBUG, "Random index matches previous: %i prev: %i", randomIndex, this->lastSpawnPointIndex);
		return getRandomSpawnPoint();
	}

	this->lastSpawnPointIndex = randomIndex;

	return randomIndex;
}


void BalloonSpawner::UpdateSpawnRate(float rate) {
	this->spawnRate = rate;
}

float BalloonSpawner::SpawnRate() {
	return this->spawnRate;
}

void BalloonSpawner::SetSpawnVelocity(Vector2 velocity) {
    this->spawnVelocity = velocity;
}