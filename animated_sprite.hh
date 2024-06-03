#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include <raylib.h>
#include <vector>
#include <map>

#include "animation.hh"

class AnimatedSprite {
    public:
        Vector2 center;
        Vector2 position;
        Texture2D texture;
        std::map<std::string, Animation> animations;

		// Constructors
		AnimatedSprite();
        AnimatedSprite(Texture2D texture, Vector2 position, int rows, int columns, int framesPerSecond);
        
		void Draw();
        void Update();
        void AddAnimation(std::string name, std::vector<Vector2> frames);
        void PlayAnimation(std::string name);
        std::string GetCurrentAnimationName();
        bool IsAnimationFinished();
    private:
        Animation currentAnimation;
        float scaleFactor;
        int rows;
        int columns;
        float frameWidth;
        float frameHeight;
        int framesPerSecond;
};

#endif