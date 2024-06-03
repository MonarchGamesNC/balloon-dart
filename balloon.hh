#ifndef BALLOON_H
#define BALLOON_H
#include <raylib.h>
#include "animated_sprite.hh"

class Balloon {
    public:
        Vector2 position;
        AnimatedSprite sprite;
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
        bool isPopping = false;
        float scaleFactor;
        Rectangle collider;
        Vector2 velocity;
};
#endif