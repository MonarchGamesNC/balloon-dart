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
	bool Closed();
	GameScreen GetNextScreen();
private:
    Texture bgGraphic;
	Font titleFont;
    Font menuItemFont;
    Color menuItemNormalColor = WHITE;
	Color menuItemHoverColor = BLACK;
	GameScreen nextScreen = GAMEPLAY;

	int framesCounter = 0;
	int finishScreen = 0;

    int screenCenterX = 0;
    int screenCenterY = 0;
	int titlePositionX = 0;
	int titlePositionY = 0;

	Vector2 startMenuItemLoc;
	Rectangle startMenuItemRect;
	Color startMenuItemColor = menuItemNormalColor;
	Vector2 creditsMenuItemLoc;
	Rectangle creditsMenuItemRect;
	Color creditsMenuItemColor = menuItemNormalColor;
	Vector2 exitMenuItemLoc;
	Rectangle exitMenuItemRect;
	Color exitMenuItemColor = menuItemNormalColor;

	float menuItemWidth = 130;
	float menuItemHeight = 48;

	int lettersCount = 0;

	int state = 0;              // Logo animation states
	float alpha = 1.0f;
};
