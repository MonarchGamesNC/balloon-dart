#include <raylib.h>
#include "screen.hh"

class PlaygroundScreen : public Screen {
public:
	PlaygroundScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	GameScreen GetNextScreen();
private:
	int finishScreen = 0;
    int frame = 0;
    int horizontalFrame = 0;
    int verticalFrame = 0;
    
    Texture2D graphic;
};
