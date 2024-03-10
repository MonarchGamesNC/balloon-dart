#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <raylib.h>

class ResourceManager {
public:
	// ~ResourceManager();
	void LoadResources();
	void UnloadAllResources();
	Texture2D BlueBaloon;
	Music BGMusic;
private:
	bool hasLoadedResources = false;

};

#endif
