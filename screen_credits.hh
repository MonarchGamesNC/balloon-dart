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

  	int screenCenterX = 0;
    int screenCenterY = 0;
	int titlePositionX = 0;
	int titlePositionY = 0;
	float creditListStartingY = 300;
	float creditListStartingX = 50;
	int creditListSpacing = 32;

	Color ba1Color = BLACK;
	Color ba1NormalColor = BLACK;
	Color ba1HoverColor = BLUE;


	Texture bgGraphic;
	Music bgMusic;
	Font font;
	
	void loadTextures();
	void DrawBgGraphic();
	
};