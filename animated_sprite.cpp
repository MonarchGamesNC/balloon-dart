#include <iostream>
#include <raylib.h>

#include "animated_sprite.hh"

void DebugLines(Rectangle pos, Vector2 center) {
    float x = pos.x - center.x;
    float y = pos.y - center.y;
    
    Vector2 topLeft = (Vector2){ x, y };
    Vector2 topRight = (Vector2){ x + pos.width, y };
    Vector2 bottomLeft = (Vector2){ x, y + pos.height };
    Vector2 bottomRight = (Vector2){ x + pos.width, y + pos.height };

    DrawLineEx(topLeft, topRight, 2, RED);
    DrawLineEx(topRight, bottomRight, 2, RED);
    DrawLineEx(bottomRight, bottomLeft, 2, RED);
    DrawLineEx(bottomLeft, topLeft, 2, RED);
}

AnimatedSprite::AnimatedSprite() {};

AnimatedSprite::AnimatedSprite(Texture2D texture, Vector2 _position, int rows, int columns, int framesPerSecond) {
    this->texture = texture;
    this->position = _position;
    this->rows = rows;
    this->columns = columns;
    this->framesPerSecond = framesPerSecond;
    this->animations = std::map<std::string, Animation>();
   
    // NOTE:: should we make this a parameter
    this->scaleFactor = 0.5f;

    this->frameWidth = (float)this->texture.width/this->columns;
    this->frameHeight = (float)this->texture.height/this->rows;

    // Set center
    this->center = Vector2{ 
        (float)(this->texture.width*scaleFactor) / 2,
        (float)(this->texture.height * scaleFactor) / 2
    };
}

// Draw
void AnimatedSprite::Draw() {
    Vector2 center = Vector2{
        (float)(frameWidth*scaleFactor) / 2,
        (float)(frameHeight*scaleFactor) / 2
    };
    
    Rectangle finalPosition = Rectangle{
        position.x,
        position.y,
        (float)(frameWidth*scaleFactor),
        (float)(frameHeight*scaleFactor)
    };


    float ax = frameWidth * this->currentAnimation.CurrentFrame.x;
    float ay = frameHeight * this->currentAnimation.CurrentFrame.y;

    Rectangle framePosition = Rectangle{ax, ay, frameWidth, frameHeight};
    
    DrawTexturePro(this->texture, framePosition, finalPosition, center, 0, WHITE);

    #ifdef DEBUG
    DebugLines(finalPosition, center);
    #endif

}

// Update each frame
void AnimatedSprite::Update() {
    // Loop through the animation frames
    // If we are at the end of the animation, reset to the beginning
    int index;
    if (this->currentAnimation.Finished) {
        // Once we're finished always go to the last frame
        index = this->currentAnimation.Frames.size()-1;
    } else {
        index = (int)((GetTime() - this->currentAnimation.StartTime) * this->currentAnimation.FramesPerSecond) % this->currentAnimation.Frames.size();
        if (index == (int)this->currentAnimation.Frames.size()-1) {
            this->currentAnimation.Finished = true;
            return;
        }
    }

    this->currentAnimation.CurrentFrame = this->currentAnimation.Frames[index];
}

void AnimatedSprite::AddAnimation(std::string name, std::vector<Vector2> frames) {
    this->animations[name] = Animation{
        name,
        frames,
        frames[0],
        this->framesPerSecond,
        0,
        false,
        false
    };
}

void AnimatedSprite::PlayAnimation(std::string name) {
    this->currentAnimation = this->animations[name];
    this->currentAnimation.Play();
}

bool AnimatedSprite::IsAnimationFinished() {
    return this->currentAnimation.Finished;
}

std::string AnimatedSprite::GetCurrentAnimationName() {
    return this->currentAnimation.Name;
}
