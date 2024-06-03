#include "screen_playground.hh"

PlaygroundScreen::PlaygroundScreen() {
    Init();
}

void PlaygroundScreen::Init() {
    this->graphic = LoadTexture("./assets/gfx/blue_balloon.png");
    this->graphic2 = LoadTexture("./assets/gfx/blue_balloon.png");
    this->sprite = AnimatedSprite(this->graphic, Vector2{ 400, 300 }, 2, 3, 6);

    this->sprite.AddAnimation(
        "idle",
        {
            Vector2{ 0, 0 }
        }
    );

    this->sprite.AddAnimation(
        "pop",
        {
            Vector2{ 0, 0 },
            Vector2{ 1, 0 },
            Vector2{ 2, 0 },
            Vector2{ 0, 1 },
            Vector2{ 1, 1 },
            Vector2{ 2, 1 },
        }
    );

    this->sprite.PlayAnimation("pop");

    this->balloon = Balloon(
        this->graphic2,
        Vector2{ 200, 300 },
        Sound(),
        Vector2{ 0, -2.0f}
    );
}

void PlaygroundScreen::Update() { 
    if (!this->sprite.IsAnimationFinished()) {
        this->sprite.Update();
    }

    this->balloon.Update();
}

void PlaygroundScreen::Draw() {
    if (!this->sprite.IsAnimationFinished()) {
        this->sprite.Draw();
    }

    this->balloon.Draw();
}

void PlaygroundScreen::Unload() {
    UnloadTexture(this->graphic);
    UnloadTexture(this->graphic2);
}

int PlaygroundScreen::Finish() {
    return finishScreen;
}

GameScreen PlaygroundScreen::GetNextScreen() {
    return SPLASH;
}
