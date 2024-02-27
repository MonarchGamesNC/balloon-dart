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
		BalloonSpawner(std::vector<Texture2D> _textures, float spawnRate);
    
    private:
        Timer timer;
        Texture2D texture;
        int lastSpawnPointIndex;
        float spawnRate;
		float lifetimeTime; // TODO:: rename this to something more accurate
        
		std::vector<Texture2D> textures {};
		std::vector<float> spawnPoints {};
        std::vector<Balloon> balloonsSpawned = {};

        void spawnTick();
		int getRandomSpawnPoint();
		int getRandomTextureIndex();
};

#endif