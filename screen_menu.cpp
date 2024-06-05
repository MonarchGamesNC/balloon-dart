#include <cstddef>
#include <cstring>
#include "screen_menu.hh"

bool isSameColor(Color, Color);

MainMenuScreen::MainMenuScreen() {
	Init();
}

void MainMenuScreen::Init() {
    bgGraphic = LoadTexture("./assets/bgs/cardboard.png");
	titleFont = LoadFontEx("./assets/fonts/EazyChat.ttf", 72, NULL, 0);
	menuItemFont = LoadFontEx("./assets/fonts/EazyChat.ttf", 48, NULL, 0);
    finishScreen = 0;
	framesCounter = 0;
	lettersCount = 0;

    screenCenterX = GetScreenWidth()/2;
    screenCenterY = GetScreenHeight()/2;

	titlePositionX = screenCenterX - 250;
	titlePositionY = screenCenterY - 250;

	state = 0;
	alpha = 1.0f;

    startMenuItemLoc = Vector2{(float)screenCenterX - 65, (float)screenCenterY};
    startMenuItemRect = Rectangle {startMenuItemLoc.x, startMenuItemLoc.y, menuItemWidth, menuItemHeight};

    creditsMenuItemLoc = Vector2{(float)screenCenterX - 83, (float)screenCenterY + 50};
    creditsMenuItemRect = Rectangle {creditsMenuItemLoc.x, creditsMenuItemLoc.y, menuItemWidth, menuItemHeight};

    exitMenuItemLoc = Vector2{(float)screenCenterX - 50, (float)screenCenterY + 100};
    exitMenuItemRect = Rectangle {exitMenuItemLoc.x, exitMenuItemLoc.y, menuItemWidth, menuItemHeight};
}

void MainMenuScreen::Draw() {
    // Draw bg to entire screen
    Rectangle bgSource = Rectangle { 0, 0, (float)bgGraphic.width,  (float)bgGraphic.height };
    Rectangle bgDest = Rectangle { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

	DrawTexturePro(bgGraphic, bgSource, bgDest, Vector2{}, 0, WHITE);
    
    // TITLE
    Vector2 titleLoc = Vector2{ (float)titlePositionX, (float)titlePositionY};
    DrawTextEx(titleFont, "Balloon Popper", titleLoc, 72, 0, BLUE);

    // Menu
    DrawTextEx(menuItemFont, "Start", startMenuItemLoc, 48, 0, startMenuItemColor);
    DrawTextEx(menuItemFont, "Credits", creditsMenuItemLoc, 48, 0, creditsMenuItemColor);

    #if !PLATFORM_WEB
    DrawTextEx(menuItemFont, "Exit", exitMenuItemLoc, 48, 0, exitMenuItemColor);
    #endif
}

void MainMenuScreen::Update() {
    // Check if mouse is over start button
    if (CheckCollisionPointRec(GetMousePosition(), startMenuItemRect)) {
        startMenuItemColor = menuItemHoverColor;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            nextScreen = GAMEPLAY;
            finishScreen = 1;
        }
    } else if (isSameColor(startMenuItemColor, menuItemHoverColor)) {
        startMenuItemColor = menuItemNormalColor;
    }

    if (CheckCollisionPointRec(GetMousePosition(), creditsMenuItemRect)) {
        creditsMenuItemColor = menuItemHoverColor;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            nextScreen = CREDITS;
            finishScreen = 1;
        }
    } else if (isSameColor(creditsMenuItemColor, menuItemHoverColor)) {
        creditsMenuItemColor = menuItemNormalColor;
    } 

    #if !PLATFORM_WEB
    if (CheckCollisionPointRec(GetMousePosition(), exitMenuItemRect)) {
        exitMenuItemColor = menuItemHoverColor;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            state = 50; // 50 is closed for now
        }
    } else if (isSameColor(exitMenuItemColor, menuItemHoverColor)) {
        exitMenuItemColor = menuItemNormalColor;
    } 
    #endif
}

void MainMenuScreen::Unload() {
    UnloadFont(titleFont);
    UnloadFont(menuItemFont);
    UnloadTexture(bgGraphic);
}

GameScreen MainMenuScreen::GetNextScreen() {
	return nextScreen;
}

int MainMenuScreen::Finish() {  return finishScreen; }

bool MainMenuScreen::Closed() { return state == 50; }

bool isSameColor(Color a, Color b) {
    if (a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a) {
        return true;
    }

    return false;
}