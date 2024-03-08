#include "screen.h"
#include "raylib.h"
class LogoScreen : public Screen {
public:
	LogoScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	GameScreen GetNextScreen();
private:
	Font font;
	int framesCounter = 0;
	int finishScreen = 0;

	int logoPositionX = 0;
	int logoPositionY = 0;

	int lettersCount = 0;

	// int topSideRecWidth = 0;
	// int leftSideRecHeight = 0;

	// int bottomSideRecWidth = 0;
	// int rightSideRecHeight = 0;

	int state = 0;              // Logo animation states
	float alpha = 1.0f;
};
