#include "raylib.h"
#include "balloon.h"
#include <iostream>

Balloon::Balloon(Texture2D _balloonTexture, Vector2 _position, Vector2 _velocity) {
    // Load texture internally?
    balloonTexture = _balloonTexture;
    position = _position;
    velocity = _velocity;
    scaleFactor = 0.5f;

    // Set center
    center = Vector2{ (float)(balloonTexture.width*scaleFactor) / 2, (float)(balloonTexture.height * scaleFactor) / 2 };

    // These values are hardcoded for the balloon textures I am using
    // The base image is 512x512 but scaling down by 0.5f
    // The balloon is in the center of the image with the rest being transparent
    // The Vector2 295, 365 is the size of the balloon without the tied 
    // These are just rough numbers that worked for my use case and could be improved
    // But since I want to just finish game loop, this will suffice for now
    Vector2 colliderSize = Vector2{ (float)(295*scaleFactor), (float)(365*scaleFactor) };
    Vector2 trueCenter = Vector2{ position.x - (colliderSize.x/2), position.y - (105) }; // 105 is the offset from the top of the balloon to the center of the balloon
    
    // TODO: make triangle collider which will allow for a more accurate collision detection
    // maybe have the triangles be negative space and then check if the mouse is in the negative space
    collider = Rectangle{ trueCenter.x, trueCenter.y, colliderSize.x, colliderSize.y };
}

// Draw
void Balloon::Draw() {
    if (isPopped) {
        return;
    }

    Texture2D texture = this->balloonTexture;
    float width = (float)texture.width;
    float height = (float)texture.height;

    DrawTexturePro(
        texture,
        Rectangle{ 0, 0, width, height },
        Rectangle{ position.x, position.y, (float)(width*scaleFactor), float(height*scaleFactor)},
        this->center,
        0,
        WHITE
    );

}

// Update each frame
void Balloon::Update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Check if mouse is in ballon center circle
        if (IsClicked(GetMousePosition())) {
            std::cout << "Mouse is inside balloon" << std::endl;
            Pop();
        }
    }


    if (isPopped) {
        return;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    // Check if balloon is off screen
    if (position.y < -250) {
        // Pop balloon
        Pop();
    }

    // Update collider
    collider.x = position.x - (collider.width / 2);
    collider.y = position.y - (collider.height / 2);
}

bool Balloon::IsClicked(Vector2 clickPosition) {
    // Check if mouse is in ballon center circle
    if (CheckCollisionPointRec(clickPosition, collider)) {
        return true;
    }

    return false;
}



// Pop balloon (hide balloon)
// move off screen then delete
void Balloon::Pop() {
    std::cout << "Popping balloon" << std::endl;
    // Hide the balloon... later animate pop
    isPopped = true;
    collider.x = (float)(GetScreenWidth() * 2);
    collider.y = (float)(GetScreenHeight() * 2);
    position = Vector2{ (float)(GetScreenWidth() *2), (float)GetScreenHeight() * 2 };
    velocity = Vector2{ 0, 0 };
}
