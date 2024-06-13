#include <iostream>
#include <raylib.h>
#include "screen_credits.hh"


// TODO:: Make drawClickableText a class? It would handle drawing and knowing if text is being targeted and/or clicked
// void DrawClickableText(const char* text, Vector2 loc, Font font, Color color, Color hoverColor) {
// 	DrawTextEx(font, text, loc, 32, 0, color);
// 	// Now underline the text
// 	DrawLineEx(Vector2{loc.x, loc.y+32}, Vector2{loc.x + MeasureText(text, 32), loc.y+32}, 2, color);
// }

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

	screenCenterX = GetScreenWidth()/2;
    screenCenterY = GetScreenHeight()/2;

	titlePositionX = screenCenterX - 250;
	titlePositionY = screenCenterY - 250;

	screenReady = true;
}

void CreditsScreen::Update() {
	if (!IsMusicStreamPlaying(bgMusic)) {
		PlayMusicStream(bgMusic);
	}

	UpdateMusicStream(bgMusic);


	// Check if the cursor is over the first credits
	if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float)titlePositionX - 50, 300, 410, 32})) {
		// Make cursor a pointer
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		ba1Color = ba1HoverColor;
		// If we click it
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			OpenURL("https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?item=134l668d3b3n083827");
			ba1Color = WHITE;
		}
	} else {
		SetMouseCursor(MOUSE_CURSOR_ARROW);
		ba1Color = ba1NormalColor;
	}
}

void CreditsScreen::Draw() {
	DrawBgGraphic();

	// TITLE
    Vector2 titleLoc = Vector2{ (float)titlePositionX, (float)titlePositionY};
    DrawTextEx(font, "Credits", titleLoc, 72, 0, BLUE);

	// Draw the credits
	creditListStartingX = titlePositionX - 50;
    
	DrawTextEx(font, "* Balloon Art by Robert Brooks", Vector2{creditListStartingX,creditListStartingY}, 32, 0, ba1Color); // https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?item=134l668d3b3n083827
	DrawLineEx(Vector2{creditListStartingX+MeasureText("*", 32), creditListStartingY+30}, Vector2{creditListStartingX+410, creditListStartingY+30}, 1, ba1Color);

    DrawTextEx(font, "* Background Art by Robert Brooks", Vector2{creditListStartingX,creditListStartingY+35}, 32, 0, BLACK); // https://www.gamedeveloperstudio.com/graphics/viewgraphic.php?item=1y6j2z002s2a8n0y2t
    DrawTextEx(font, "* Music by Cleyton Kauffman", Vector2{creditListStartingX, creditListStartingY+70}, 32, 0, BLACK); // https://opengameart.org/content/childrens-march-theme
	DrawTextEx(font, "* Sound Effects by qubodup", Vector2{creditListStartingX, creditListStartingY+105}, 32, 0, BLACK); // https://freesound.org/people/qubodup/sounds/182856/
    DrawTextEx(font, "* Font by Syaf Rizal (Khurasan)", Vector2{creditListStartingX, creditListStartingY+140}, 32, 0, BLACK); // https://www.dafont.com/eazy-chat.font
    DrawTextEx(font, "* Powered by Raylib", Vector2{creditListStartingX, creditListStartingY+175}, 32, 0, BLACK); // https://raylib.com
    DrawTextEx(font, "* Written by Celio", Vector2{creditListStartingX, creditListStartingY+210}, 32, 0, BLACK); // https://celioreyes.com
    DrawTextEx(font, "Dedicated to my little one! She loves balloons", Vector2{creditListStartingX, creditListStartingY+280}, 32, 0, BLACK);
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
