#include <raylib.h>
#include "screen.hh"

class MainMenuScreen : public Screen {
public:
	MainMenuScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	GameScreen GetNextScreen();
private:
    Texture bgGraphic;
	Font titleFont;
    Font menuItemFont;
    Color menuColor = WHITE;
	GameScreen nextScreen = GAMEPLAY;

	int framesCounter = 0;
	int finishScreen = 0;


    int screenCenterX = 0;
    int screenCenterY = 0;
	int titlePositionX = 0;
	int titlePositionY = 0;

	int lettersCount = 0;

	int state = 0;              // Logo animation states
	float alpha = 1.0f;
};
