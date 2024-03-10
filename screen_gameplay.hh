#include <vector>
#include "screen.hh"
#include "resourcemanager.hh"
#include "balloon_spawner.hh"

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
	bool finishScreen = false;
	float exitButtonTimer = 0;

	Texture bgGraphic;
	Music bgMusic;
	Sound popSound;
	Font font;
	BalloonSpawner ballonSpawner;
	
	std::vector<Texture2D> textures;
	
	void loadTextures();
	void DrawBgGraphic();
	
};