#include <vector>
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
	Texture bgGraphic;
	Music bgMusic;
	Font font;
	BalloonSpawner ballonSpawner;
	
	std::vector<Texture2D> textures;
	
	void loadTextures();
	void DrawBgGraphic();
	
};