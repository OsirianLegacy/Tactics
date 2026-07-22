//
// Created by Jkurt on 7/19/2026.
//

#ifndef RAYLIBGAME_GAME_H
#define RAYLIBGAME_GAME_H
#include <vector>
#include <map>
#include "Data.h"
#include <string>
class Game
{
public:
    Game();
    void SetGameState(GAME_STATE newState);
    [[nodiscard]] GAME_STATE GetGameState() const;
    void Initialize();
    RuntimeData GetUnitFromRoster(const std::string& unitID);
    void AddUnitToRoster(std::string unitID, RuntimeData unitData);
    bool RemoveUnitFromRoster(const std::string& unitID);

private:
    GAME_STATE state = GAME_STATE::MENU;
    std::map<std::string, RuntimeData> roster ={};
};


#endif //RAYLIBGAME_GAME_H