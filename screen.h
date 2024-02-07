#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>

class Screen {
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Unload() = 0;
	virtual int Finish() = 0;
};

#endif