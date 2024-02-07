#include "screen.h"
#include "resourcemanager.h"
#include "balloonSpawner.h"

class GameplayScreen : public Screen {
public:
	GameplayScreen();
    GameplayScreen(ResourceManager resourceManager);
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
private:
    ResourceManager resourceManager;
    BalloonSpawner ballonSpawner;
	
};