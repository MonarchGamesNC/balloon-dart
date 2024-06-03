#include <iostream>
#include <raylib.h>
#include "balloon.hh"
#include "animated_sprite.hh"

extern int score;

Balloon::Balloon() {
    // Default constructor
    // Not sure if this is needed
}

Balloon::Balloon(Texture2D _balloonTexture, Vector2 _position, Sound _popSound, Vector2 _velocity) {
    // Load texture internally?
    position = _position;
    velocity = _velocity;
    popSound = _popSound;
    scaleFactor = 0.5f;

    this->sprite = AnimatedSprite(_balloonTexture, position, 2, 3, 12);
    this->sprite.AddAnimation("idle",{ { 0, 0 } });
    this->sprite.AddAnimation( "pop",{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }});
    this->sprite.PlayAnimation("idle");
    
    // These values are hardcoded for the balloon textures I am using
    // The base image is 512x512 but scaling down by 0.5f
    // The balloon is in the center of the image with the rest being transparent
    // The Vector2 295, 365 is the size of the balloon without the tied 
    // These are just rough numbers that worked for my use case and could be improved
    // But since I want to just finish game loop, this will suffice for now
    Vector2 colliderSize = Vector2{ (float)(295*scaleFactor), (float)(365*scaleFactor) };
    Vector2 trueCenter = Vector2{ position.x - (colliderSize.x/2), position.y - (105) }; // 105 is the offset from the top of the balloon to the center of the balloon
    
    // TODO:: make triangle collider which will allow for a more accurate collision detection
    // maybe have the triangles be negative space and then check if the mouse is in the negative space
    collider = Rectangle{ trueCenter.x, trueCenter.y, colliderSize.x, colliderSize.y };
}

// Draw
void Balloon::Draw() {
    if (isPopped) {
        return;
    }

    this->sprite.Draw();
}

// Update each frame
void Balloon::Update() {
    if (this->sprite.GetCurrentAnimationName() == "pop" && this->sprite.IsAnimationFinished()) {
        isPopped = true;
    }
    
    if (isPopped) return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Check if mouse is in ballon center circle
        if (!this->isPopping && IsClicked(GetMousePosition())) {
            score += 1;
            Pop();
        }
    }

    this->sprite.Update(); // Position is updated in the sprite

    this->sprite.position.x += (velocity.x * GetFrameTime()) * 75;
    this->sprite.position.y += (velocity.y * GetFrameTime()) * 75;
	
	// Update collider
    collider.x = this->sprite.position.x - (collider.width / 2);
    collider.y =  this->sprite.position.y - (collider.height / 2);
    
	// Check if balloon is off screen
    if (this->sprite.position.y < -250) Pop(false);
}

bool Balloon::IsClicked(Vector2 clickPosition) {
    // Check if mouse is in ballon center circle
    if (CheckCollisionPointRec(clickPosition, collider)) {
        return true;
    }

    return false;
}

bool Balloon::IsPopped() {
    return isPopped;
}

// Pop balloon (hide balloon)
// move off screen then delete
void Balloon::Pop(bool playSound) {
    if (!this->isPopping) {
        this->isPopping = true;
        this->sprite.PlayAnimation("pop");
    }
    
    if (playSound) PlaySound(popSound);
    
    collider.x = (float)(GetScreenWidth() * 2);
    collider.y = (float)(GetScreenHeight() * 2);
    position = Vector2{ (float)(GetScreenWidth() *2), (float)GetScreenHeight() * 2 };
    velocity = Vector2{ 0, 0 };
}
