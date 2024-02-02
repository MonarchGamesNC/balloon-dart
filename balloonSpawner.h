#include <vector>
#include "balloon.h"
#include "timer.h"

class BalloonSpawner {
    public:
        void Spawn();
        void Update();
        void Draw();
        void UnloadTextures();
        BalloonSpawner(Texture2D texture, float spawnRate);
    
    private:
        Timer timer;
        Texture2D texture;
        float lastSpawnPoint;
        std::vector<float> spawnPoints {};
        std::vector<Balloon> balloonsSpawned = {};
};
