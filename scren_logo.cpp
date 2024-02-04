#include "screen.h"

class LogoScreen : public Screen {
public:
	void Init();
	void Draw();
	void Update();
	void Unload();
	int Finish();
};

void LogoScreen::Init() {}

void LogoScreen::Draw() {}

void LogoScreen::Update() {}

void LogoScreen::Unload() {}

int LogoScreen::Finish() { return 0; }