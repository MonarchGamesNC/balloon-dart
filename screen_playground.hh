#include <raylib.h>
#include "screen.hh"
#include "animated_sprite.hh"
#include "balloon.hh"

class PlaygroundScreen : public Screen {
public:
	PlaygroundScreen();
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
	bool Closed();
	GameScreen GetNextScreen();
private:
	int finishScreen = 0;
    
	AnimatedSprite sprite;
    Texture2D graphic;
	Texture2D graphic2;
	Balloon balloon;
};
