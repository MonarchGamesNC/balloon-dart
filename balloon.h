#include "raylib.h"

class Balloon {
    public:
        Texture2D balloonTexture;
        Vector2 center;
        Vector2 position;
        Balloon(Texture2D balloonTexture, Vector2 position, Vector2 velocity);
        void Draw();
        void Update();
        void Pop();
        bool IsClicked(Vector2 clickPosition);
    private:
        bool isPopped = false;
        float scaleFactor;
        // Vector2 colliderSize;
        Rectangle collider;
        // Vector2 trueCenter;
        Vector2 velocity;
};