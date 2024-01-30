#include <vector>
#include "balloon.h"
#include "timer.h"

class BalloonSpawner {
    public:
        BalloonSpawner(Texture2D texture, float spawnRate);
        void Spawn();
        void Update();
        void Draw();
        void UnloadTextures();
    
    private:
        Texture2D texture;
        Timer timer;
        std::vector<Balloon> balloonsSpawned = {};
};
