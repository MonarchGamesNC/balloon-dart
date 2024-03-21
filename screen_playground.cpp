#include "screen_playground.hh"

PlaygroundScreen::PlaygroundScreen() {
    Init();
}

void PlaygroundScreen::Init() {
    this->graphic = LoadTexture("./assets/gfx/blue_balloon.png");
}

void PlaygroundScreen::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        if (horizontalFrame == 2){
            horizontalFrame = 0;

            if (verticalFrame == 0) {
                verticalFrame = 1;
            } else {
                verticalFrame = 0;
            }
        } else {
            horizontalFrame++;
        }
    }
}

void PlaygroundScreen::Draw() {
    if (horizontalFrame == 2 && verticalFrame == 1) {
       return;
    }

    float scaleFactor = 0.5f;
    Vector2 position = { 450, 300 };
    Texture2D texture = this->graphic;

    float width = (float)(texture.width/3);
    float height = (float)(texture.height/2);
    
    // Set center
    Vector2 center = Vector2{
        (float)(width*scaleFactor) / 2,
        (float)(height * scaleFactor) / 2
    };

    Rectangle finalPosition = Rectangle{
        position.x,
        position.y,
        (float)(width*scaleFactor),
        float(height*scaleFactor)
    };

    Rectangle framePosition = Rectangle{
        width*horizontalFrame,
        height*verticalFrame,
        width,
        height
    };

    DrawTexturePro(
        texture,
        framePosition,
        finalPosition,
        center,
        0,
        WHITE
    );

    float x = finalPosition.x - center.x;
    float y = finalPosition.y - center.y;
    Vector2 topLeft = (Vector2){ x, y };
    Vector2 topRight = (Vector2){ x + finalPosition.width, y };
    Vector2 bottomLeft = (Vector2){ x, y + finalPosition.height };
    Vector2 bottomRight = (Vector2){ x + finalPosition.width, y + finalPosition.height };

    DrawLineEx(topLeft, topRight, 2, RED);
    DrawLineEx(topRight, bottomRight, 2, RED);
    DrawLineEx(bottomRight, bottomLeft, 2, RED);
    DrawLineEx(bottomLeft, topLeft, 2, RED);

}

void PlaygroundScreen::Unload() {
}

int PlaygroundScreen::Finish() {
    return finishScreen;
}

GameScreen PlaygroundScreen::GetNextScreen() {
    return SPLASH;
}
