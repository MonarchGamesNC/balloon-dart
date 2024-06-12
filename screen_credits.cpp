#include <iostream>
#include <raylib.h>
#include "screen_credits.hh"


CreditsScreen::CreditsScreen() {
	if (!screenReady) {
		Init();
		finishScreen = 0;
		exitButtonTimer = 0.75; // needs to hold for 1 seconds
	}
}

void CreditsScreen::Init() {
	this->loadTextures();

	this->font = LoadFontEx("./assets/fonts/EazyChat.ttf", 72, NULL, 0);
	this->bgGraphic = LoadTexture("./assets/bgs/cardboard.png");

	this->bgMusic = LoadMusicStream("./assets/sfx/bg_music_1.ogg");
	SetMusicVolume(bgMusic, 0.2);

	screenReady = true;
}

void CreditsScreen::Update() {
	if (!IsMusicStreamPlaying(bgMusic)) {
		PlayMusicStream(bgMusic);
	}

	UpdateMusicStream(bgMusic);	
}

void CreditsScreen::Draw() {
	DrawBgGraphic();

    DrawTextEx(font, "Credits", Vector2{(float)(GetScreenWidth()/2),(float)(GetScreenHeight()/2)}, 72, 0, BLUE);

    DrawTextEx(font, "Balloon Art by Robert Brooks", Vector2{ 0,0}, 32, 0, MAGENTA); // https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?item=134l668d3b3n083827
    DrawTextEx(font, "Background Art by Robert Brooks", Vector2{ 0,35}, 32, 0, MAGENTA); // https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?item=1y6j2z002s2a8n0y2t
    DrawTextEx(font, "Music by Cleyton Kauffman", Vector2{0, 70}, 32, 0, MAGENTA); // https://opengameart.org/content/childrens-march-theme
	DrawTextEx(font, "Sound Effects by qubodup", Vector2{0, 105}, 32, 0, MAGENTA); // https://freesound.org/people/qubodup/sounds/182856/
    DrawTextEx(font, "Font by Syaf Rizal (Khurasan)", Vector2{0, 140}, 32, 0, MAGENTA); // https://www.dafont.com/eazy-chat.font
    DrawTextEx(font, "Powered by Raylib", Vector2{0, 175}, 32, 0, MAGENTA); // https://raylib.com
    DrawTextEx(font, "Game by Celio", Vector2{0, 210}, 32, 0, MAGENTA); // https://celioreyes.com
    DrawTextEx(font, "Dedicated to my little one! She loves to balloons", Vector2{0, 245}, 32, 0, MAGENTA);
}

void CreditsScreen::DrawBgGraphic() {
	// Draw bg to entire screen
	DrawTexturePro(
        bgGraphic,
		Rectangle { 0, 0, (float)bgGraphic.width,  (float)bgGraphic.height },
		Rectangle { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
		Vector2 { 0, 0 },
        0,
        WHITE
    );
}

void CreditsScreen::Unload() {
	UnloadMusicStream(bgMusic);
	UnloadTexture(bgGraphic);
}

int CreditsScreen::Finish() {
    return finishScreen;
}

bool CreditsScreen::Closed() { return false; }

GameScreen CreditsScreen::GetNextScreen() {
	return MAINMENU;
}


void CreditsScreen::loadTextures() {
	// Load all the textures we need for now
}