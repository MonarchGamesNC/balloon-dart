#ifndef SCREEN_H
#define SCREEN_H

enum GameScreen {
	SPLASH = 0,
	LOGO,
	TITLE,
	GAMEPLAY,
	SETTINGS,
	CREDITS
};

class Screen {
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;
	virtual int Finish() = 0;
	virtual GameScreen GetNextScreen();
};

#endif
