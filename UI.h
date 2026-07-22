//
// Created by Jkurt on 7/19/2026.
//

#ifndef RAYLIBGAME_UI_H
#define RAYLIBGAME_UI_H
#include "Colors.h"
#include "Game.h"
#include "Data.h"
#include "Options.h"
using namespace Colors;

class UI
{
public:
    explicit UI(Game& inGame);
    void Draw();
    static void LoadData();
private:
    // REFS
    Game& game;

    // Functions
    void Update();

    // UI STATE
    UI_STATE state = UI_STATE::IDLE;

    // Universal Buttons
    UIElement optionsButton{{1.0f, 1.0f}, {1.0f, 1.0f}, 0.0f, 0.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
    MenuButton options{ optionsButton, DarkPlum, White, "Options",
                    nullptr, nullptr, 0, 0, 0, 0,
                    nullptr, nullptr, 0,0,0,0,
                    false, GAME_STATE::MENU,  false, UI_STATE::OPTIONS};

    UIElement closeButton{{1.0f, 1.0f}, {1.0f, 1.0f}, 0.0f, 0.0f, 32*RENDER_SCALE, 32*RENDER_SCALE};
    MenuButton close{ closeButton, Red, White, "X",
                    nullptr, nullptr, 0, 0, 0, 0,
                    nullptr, nullptr, 0,0,0,0,
                    false, game.GetGameState(),  false, UI_STATE::IDLE};
    UIElement optionsPanel{{0.5f, 0.5f}, {0.5f, 0.5f}, 0.0f, -100.0f, VIRTUAL_RESOLUTION.x/4, VIRTUAL_RESOLUTION.y/2};
    Panel optionsMenu{optionsPanel, DarkGray, White};

    // Fonts
    static Font alagard;


};


#endif //RAYLIBGAME_UI_H