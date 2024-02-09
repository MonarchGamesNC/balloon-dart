#include "screen.h"
#include "resourcemanager.h"
#include "balloonSpawner.h"

class GameplayScreen : public Screen {
public:
	GameplayScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	GameScreen GetNextScreen();
private:
	bool screenReady = false;
	// TODO:: Make this a list of textures
	Texture balloonTexture;
	Music bgMusic;
	BalloonSpawner ballonSpawner;
	
};