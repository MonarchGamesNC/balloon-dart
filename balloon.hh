#include <raylib.h>

class Balloon {
    public:
        Vector2 center;
        Vector2 position;
        Texture2D balloonTexture;
        Sound popSound;

		// Constructors
		Balloon();
        Balloon(Texture2D balloonTexture, Vector2 position, Sound popSound, Vector2 velocity);
        
		void Draw();
        void Update();
        void Pop(bool playSound = true);
        bool IsClicked(Vector2 clickPosition);
        bool IsPopped();
    private:
        bool isPopped = false;
        float scaleFactor;
        Rectangle collider;
        Vector2 velocity;
};