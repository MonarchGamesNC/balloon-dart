#include <vector>
#include <raylib.h>
#include "screen.hh"

class CreditsScreen : public Screen {
public:
	CreditsScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	bool Closed();
	GameScreen GetNextScreen();
private:
	bool screenReady = false;
	bool finishScreen = false;
	float exitButtonTimer = 0;

	Texture bgGraphic;
	Music bgMusic;
	Font font;
	
	void loadTextures();
	void DrawBgGraphic();
	
};