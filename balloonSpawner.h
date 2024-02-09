#ifndef BALLOONSPAWNER_H
#define BALLOONSPAWNER_H
#include <vector>
#include "balloon.h"
#include "timer.h"

class BalloonSpawner {
    public:
        void Spawn();
        void Update();
        void Draw();
        void UnloadTextures();
        BalloonSpawner();
        BalloonSpawner(Texture2D texture, float spawnRate);
    
    private:
        Timer timer;
        Texture2D texture;
        int lastSpawnPointIndex;
        float spawnRate;
        float lifetimeTime; // TODO: rename this to something more accurate
        std::vector<float> spawnPoints {};
        std::vector<Balloon> balloonsSpawned = {};

        void spawnTick();
		int getRandomSpawnPoint();
};

#endif