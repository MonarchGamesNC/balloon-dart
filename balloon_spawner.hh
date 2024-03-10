#ifndef BALLOONSPAWNER_H
#define BALLOONSPAWNER_H
#include <vector>
#include "balloon.hh"

class BalloonSpawner {
    public:
        void Spawn();
        void Update();
        void Draw();
        void UnloadTextures();
        BalloonSpawner();
		BalloonSpawner(std::vector<Texture2D> _textures, float spawnRate);
        BalloonSpawner(std::vector<Texture2D> _textures, Sound popSound,  float spawnRate);

        void SetSpawnVelocity(Vector2 velocity);
		void UpdateSpawnRate(float rate);
		float SpawnRate();

    private:
        int lastSpawnPointIndex;
        float spawnRate;
        Vector2 spawnVelocity;
		float currentTime;
        Sound popSound;
        
		std::vector<Texture2D> textures {};
		std::vector<float> spawnPoints {};
        std::vector<Balloon> balloonsSpawned = {};

        void spawnTick();
		int getRandomSpawnPoint();
		int getRandomTextureIndex();
};

#endif