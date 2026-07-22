//
// Created by Jkurt on 7/19/2026.
//

#ifndef RAYLIBGAME_DATA_H
#define RAYLIBGAME_DATA_H
#include <algorithm>
#include "raylib.h"
#include <string>
#include <vector>
#include <map>

class Unit;

/*
########################################
#               UNIT
########################################
*/
struct Resource
{
    int current;
    int max;
    int base;
    int modifier;
    // Decreases Current Resource by amount.
    int DecreaseCur(int amount)
    {
        current = std::clamp(current - amount, 0, max);
        return current;
    }
    int IncreaseCur(int amount)
    {
        current = std::clamp(current + amount, 0, max);
        return current;
    }
    [[nodiscard]] int GetCurrent() const
    {
        return current;
    }
    int IncreaseMod(int amount)
    {
        modifier = std::clamp(modifier + amount, -99, max);
        return modifier;
    }
    int DecreaseMod(int amount)
    {
        modifier = std::clamp(modifier - amount, -99, max);
        return modifier;
    }
    int IncreaseBase(int amount)
    {
        base = std::clamp(base+amount, 1, 99);
        return base;
    }
    int DecreaseBase(int amount)
    {
        base = std::clamp(base-amount, 1, 99);
        return base;
    }
    int ReCalculateMax()
    {
        max = std::clamp(base + modifier, 1, 99);
        return max;
    }
};

struct Attribute
{
    int base;
    int modifier;

    [[nodiscard]] int GetCurrent() const
    {
        const int current =  base + modifier;
        return current;
    }
    int IncreaseBase(int amount)
    {
        base = std::clamp(base+amount, 0, 99);
        return base;
    }
    int DecreaseBase(int amount)
    {
        base = std::clamp(base-amount, 0, 99);
        return base;
    }
};

struct UnitDefinition
{
    std::string id;
    std::string name;
    int hp;
    int damage;
    int mov;
};

struct RuntimeData
{
    Resource health;
    Attribute damage;
    Attribute movement;
};

/*
########################################
#               GRID
########################################
*/

struct Coord
{
    int x;
    int y;

    bool operator==(const Coord& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Coord& other) const
    {
        return !(*this == other);
    }

    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }

    Coord operator-(const Coord& other) const
    {
        return { x - other.x, y - other.y };
    }
};
// Handles the Visuals of the Cell.
enum class CELL_STATE {IDLE, TARGET, MOVE, ATTACK, DEPLOY, SPAWN, OBJECT, HEAL, TRAP};
struct Cell
{
    Coord coord;
    CELL_STATE state;
    bool walkable;
    bool occupied;
};

/*
########################################
#               ACTION
########################################
*/

enum class ACTION_STATE {IDLE, RANGE, TARGET, DISPLAY, CONFIRM, EXECUTE, CLEAR};
enum class ACTION_TYPE {NONE, DAMAGE, HEAL, BUFF, DEBUFF, MOVE};

struct ActionRequest
{
    Unit* requestor = nullptr;
    ACTION_TYPE type = ACTION_TYPE::NONE;
    ACTION_STATE currentState = ACTION_STATE::IDLE;
    Coord targetCoord = {-1,-1};
    int amount = 0;
    Resource* resourceToImpact = nullptr;
    Attribute* attributeToImpact = nullptr;
};

/*
########################################
#               COMBAT
########################################
*/

enum class COMBAT_STATE {INITIALIZE, DEPLOY, SPAWN, NEW_ROUND, PLAYER, ENEMY, END_ROUND};

/*
########################################
#               GAME
########################################
*/

enum class GAME_STATE
{
    MENU, CITY, ENCOUNTER
};

/*
########################################
#               UI
########################################
*/

enum class UI_STATE {IDLE, LOAD, SAVE, ROSTER, MISSION, TURN, TARGET, CONFIRM, OPTIONS};
enum class EVENT {NEWGAME, CONTINUEGAME, EXIT, CONFIRM, };

struct UIElement
{
    Vector2 anchor; // screen anchor
    Vector2 pivot;  // local point inside the element
    Vector2 offset;
    Vector2 size;
};

inline Rectangle GetRect(const UIElement &element, const int screenWidth, const int screenHeight)
{
    Vector2 anchorPos = {
        screenWidth * element.anchor.x,
        screenHeight * element.anchor.y
    };

    Vector2 pivotOffset = {
        element.size.x * element.pivot.x,
        element.size.y * element.pivot.y
    };

    return {
        anchorPos.x + element.offset.x - pivotOffset.x,
        anchorPos.y + element.offset.y - pivotOffset.y,
        element.size.x,
        element.size.y
    };
}
struct MenuButton
{
    UIElement element;
    Color baseColor;
    Color outlineColor;
    std::string text;
    Sound hovered;
    Sound clicked;
    bool shouldChangeState;
    GAME_STATE newGameState;
    bool newUIState;
    UI_STATE uiState;

    bool Draw() const
    {
        Rectangle rect = GetRect(
            element,
            GetScreenWidth(),
            GetScreenHeight()
        );

        Vector2 mousePosition = GetMousePosition();
        bool isHovered = CheckCollisionPointRec(mousePosition, rect);
        bool isClicked = isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        Color fillColor = baseColor;
        if (isHovered)
        {
            fillColor = ColorBrightness(baseColor, 0.2f);
            PlaySound(hovered);
        }
        if (isClicked)
        {
            fillColor = ColorBrightness(baseColor, -0.2f);
            PlaySound(clicked);
        }

        DrawRectangleRec(rect, fillColor);
        DrawRectangleLinesEx(rect, 2.0f, outlineColor);

        constexpr int fontSize = 24;
        int textWidth = MeasureText(text.c_str(), fontSize);

        ::DrawText(
            text.c_str(),
            static_cast<int>(rect.x + rect.width / 2.0f - textWidth / 2.0f),
            static_cast<int>(rect.y + rect.height / 2.0f - fontSize / 2.0f),
            fontSize,
            WHITE
        );

        return isClicked;
    }
};

struct Panel
{
    UIElement element;
    Color baseColor;
    Color outlineColor;

    void Draw() const
    {
        Rectangle rect = GetRect(
            element,
            GetScreenWidth(),
            GetScreenHeight()
        );

        DrawRectangleRec(rect, baseColor);
        DrawRectangleLinesEx(rect, 2.0f, outlineColor);
    }
    Vector2 GetPosition()
    {
       auto rect = GetRect(element, GetScreenWidth(), GetScreenHeight());
        Vector2 position = {rect.x, rect.y};
        return position;
    }
};

struct Title
{
    UIElement element;
    Color textColor;
    std::string text;
    Font font;
    int fontSize;
    void Draw() const
    {
        Rectangle rect = GetRect(
            element,
            GetScreenWidth(),
            GetScreenHeight()
        );

        Vector2 textSize = MeasureTextEx(
            font,
            text.c_str(),
            static_cast<float>(fontSize),
            1.0f
        );

        Vector2 textPos = {
            rect.x + rect.width / 2.0f - textSize.x / 2.0f,
            rect.y + rect.height / 2.0f - textSize.y / 2.0f
        };

        ::DrawTextEx(
            font,
            text.c_str(),
            textPos,
            static_cast<float>(fontSize),
            1.0f,
            textColor
        );
    }
};


#endif //RAYLIBGAME_DATA_H
