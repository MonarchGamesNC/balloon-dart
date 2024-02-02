#include <string>
#include "raylib.h"

class ResourceManager {
    public:
        // ~ResourceManager();
        void LoadResources();
        void UnloadAllResources();
        Texture2D BlueBaloon;
		Music BGMusic;
};