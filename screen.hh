#ifndef SCREEN_H
#define SCREEN_H

enum GameScreen {
	SPLASH = 0,
	LOGO,
	MAINMENU,
	GAMEPLAY,
	CREDITS
};

class Screen {
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;
	virtual int Finish() = 0;
	virtual bool Closed() = 0;
	virtual GameScreen GetNextScreen() = 0;
};

#endif
