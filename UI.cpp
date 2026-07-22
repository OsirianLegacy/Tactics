//
// Created by Jkurt on 7/19/2026.
//

#include "UI.h"

#include <cmath>

#include "Colors.h"
#include "Options.h"
#include <iostream>
using namespace Colors;

Font UI::alagard = {};

UI::UI(Game &inGame)
    : game(inGame)
{
}
void UI::LoadData()
{
    alagard = LoadFont("Assets/alagard.ttf");
}

void UI::Draw()
{
    switch (game.GetGameState())
    {
        case GAME_STATE::MENU:
        {
            // If the UI_STATE is set to OPTIONS it shows the Options Menu, Resolution Buttons, and renders the Options button on the bottom right. If it is clicked again it returns to UI_STATE::IDLE.
            if (state == UI_STATE::OPTIONS)
            {
                DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);
                UIElement optionsResolution1080{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+35}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution1080{optionsResolution1080, DarkPlum, White, "1920x1080",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
                UIElement optionsResolution720{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+105}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution720{optionsResolution720, DarkPlum, White, "1280x720",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};

                // If the player clicks the Options button again close the options menu.
                if (options.Draw())
                {
                    std::cout << "Options Button Clicked! Closing Options Menu";
                    state = UI_STATE::IDLE;
                }
                optionsMenu.Draw();

                // If the 1080p Button is Pressed set the Render Scale to 3, update the Virtual Resolution, and reset the Window Size.
                if (Resolution1080.Draw())
                {
                    std::cout << "1080p Button Clicked\n";
                    RENDER_SCALE = 3;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }

                // If the 720p Button is Pressed set the Render Scale to 2, update the Virtual Resolution, and reset the Window Size.
                if (Resolution720.Draw())
                {
                    std::cout << "720p Button Clicked\n";
                    RENDER_SCALE = 2;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }
                break;
            }
            // Draws the base Scene for the Main Menu.

            // Draws the Background
            DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);

            // Create the Runeguard title Text.
            UIElement titlePanelElement{{0.5f, 0.5f}, {0.5f, 0.5f}, 0.0f, -150, VIRTUAL_RESOLUTION.x/2, VIRTUAL_RESOLUTION.y/4 };
            Panel titlePanel{titlePanelElement, DarkPlum, White};
            // Draw the Panel that sits underneath the Text First
            titlePanel.Draw();
            Title title{titlePanelElement, White, "Runeguard Tactics", alagard, 64};
            // Then draw the Text
            title.Draw();

            // Create the New Game Button
            UIElement newGameButton{{0.5f, 0.5f}, {0.5f, 0.5f}, -160.0f, 100.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
            MenuButton newGame{ newGameButton, DarkPlum, White, "New Game",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            true, GAME_STATE::CITY,  false, UI_STATE::IDLE};

            // Create the Load Game Button
            UIElement loadGameButton{{0.5f, 0.5f}, {0.5f, 0.5f}, 160.0f, 100.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
            MenuButton loadGame{ loadGameButton, DarkPlum, White, "Load Game",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::MENU,  false, UI_STATE::IDLE};

            // Draw and also check if New Game is Clicked.
            if (newGame.Draw())
            {
                std::cout << "New Game Clicked!\n";
                // set the gameState to City to take the player to the City. Eventually we'll need to run a New Game Initialization function in Game.
                game.SetGameState(newGame.newGameState);
            }
            // Draw and also check if Load Game is Clicked
            if (loadGame.Draw())
            {
                std::cout << "Load Game Clicked!\n";
                // Obviously, eventually will need to actually load a save file, or give a menu for selecting a save file.
            }
            // draw and also check if Options button is clicked.
            if (options.Draw())
            {
                std::cout << "Options Button Clicked! Showing Options.\n";
                // Set the UI_STATE to OPTIONS to run the earlier Options Menu in the Loop and Skip the Main Menu Drawing.
                state = UI_STATE::OPTIONS;
            }

            break;
        }
            // Switches on CITY
        case GAME_STATE::CITY:
        {
            if (state == UI_STATE::OPTIONS)
            {
                // Draw the Options Menu same as above.
                DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);

                UIElement optionsResolution1080{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+35}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution1080{optionsResolution1080, DarkPlum, White, "1920x1080",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
                UIElement optionsResolution720{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+105}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution720{optionsResolution720, DarkPlum, White, "1280x720",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
                optionsMenu.Draw();
                if (options.Draw())
                {
                    std::cout << "Options Button Clicked! Closing Options Menu";
                    state = UI_STATE::IDLE;
                }
                if (Resolution1080.Draw())
                {
                    std::cout << "1080p Button Clicked\n";
                    RENDER_SCALE = 3;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }
                if (Resolution720.Draw())
                {
                    std::cout << "720p Button Clicked\n";
                    RENDER_SCALE = 2;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }
                break;
            }

            DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);
            UIElement titleText{{0.5f, 0.0f}, {0.5f, 0.5f}, 0.0f, 100, VIRTUAL_RESOLUTION.x/2, VIRTUAL_RESOLUTION.y/6 };
            Panel titlePanel{titleText, DarkPlum, White};
            titlePanel.Draw();
            Title title{titleText, White, "Welcome to Crossten", alagard, 48};
            title.Draw();
            UIElement tavernButton{{0.0f, 1.0f}, {0.0f, 1.0f}, 0.0f, 0.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
            MenuButton tavern{ tavernButton, DarkPlum, White, "Tavern",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
            UIElement clinicButton{{0.0f, 1.0f}, {0.0f, 1.0f}, 230.0f, 0.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
            MenuButton clinic{ clinicButton, DarkPlum, White, "Clinic",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::MENU,  false, UI_STATE::IDLE};
            UIElement departButton{{0.0f, 1.0f}, {0.0f, 1.0f}, 460.0f, 0.0f, VIRTUAL_RESOLUTION.x/6, VIRTUAL_RESOLUTION.y/8 };
            MenuButton depart{ departButton, DarkPlum, White, "Depart",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::MENU,  false, UI_STATE::IDLE};
            if (tavern.Draw())
            {
                std::cout << "Tavern Button Clicked!\n";
            }
            if (clinic.Draw())
            {
                std::cout << "Clinic Button Clicked!\n";
            }
            if (depart.Draw())
            {
                std::cout << "Depart Button Clicked!\n";
                game.SetGameState(GAME_STATE::ENCOUNTER);
            }
            if (options.Draw())
            {
                std::cout << "Options Button Clicked! Showing Options.\n";
                state = UI_STATE::OPTIONS;
            }
        }
            break;
            // Switches on ENCOUNTER
        case GAME_STATE::ENCOUNTER:
        {
            if (state == UI_STATE::OPTIONS)
            {
                DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);
                UIElement optionsResolution1080{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+35}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution1080{optionsResolution1080, DarkPlum, White, "1920x1080",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
                UIElement optionsResolution720{{0.5f,0.0f}, {0.5f, 0.5f}, {0.0f, optionsMenu.GetPosition().y+105}, optionsMenu.element.size.x-10, optionsMenu.element.size.y/6};
                MenuButton Resolution720{optionsResolution720, DarkPlum, White, "1280x720",
                            nullptr, nullptr, 0, 0, 0, 0,
                            nullptr, nullptr, 0,0,0,0,
                            false, GAME_STATE::CITY,  false, UI_STATE::IDLE};
                optionsMenu.Draw();
                if (options.Draw())
                {
                    std::cout << "Options Button Clicked! Closing Options Menu";
                    state = UI_STATE::IDLE;
                }

                if (Resolution1080.Draw())
                {
                    std::cout << "1080p Button Clicked\n";
                    RENDER_SCALE = 3;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }

                if (Resolution720.Draw())
                {
                    std::cout << "720p Button Clicked\n";
                    RENDER_SCALE = 2;
                    VIRTUAL_RESOLUTION = {BASE_RESOLUTION.x * RENDER_SCALE, BASE_RESOLUTION.y * RENDER_SCALE};
                    SetWindowSize(VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y);
                }

                break;
            }
            // Begin Drawing the Encounter UI
            DrawRectangle(0,0,VIRTUAL_RESOLUTION.x, VIRTUAL_RESOLUTION.y, DeepNavy);
            DrawText("Encounter", VIRTUAL_RESOLUTION.x/2,VIRTUAL_RESOLUTION.y/2, 36,White);
            if (options.Draw())
            {
                std::cout << "Options Button Clicked! Showing Options.\n";
                state = UI_STATE::OPTIONS;
            }
            break;
        }
        default: ;
    }
}



void UI::Update()
{
}





