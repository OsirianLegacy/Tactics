//
// Created by Jkurt on 7/19/2026.
//

#include "Game.h"
#include <iostream>
Game::Game() = default;

GAME_STATE Game::GetGameState() const
{
    return state;
}

void Game::SetGameState(const GAME_STATE newState)
{
    state = newState;
}

void Game::Initialize()
{
    state = GAME_STATE::MENU;
}

void Game::AddUnitToRoster(std::string unitID, RuntimeData unitData)
{
    roster.emplace(unitID, unitData);
}

RuntimeData Game::GetUnitFromRoster(const std::string& unitID)
{
    if (roster.find(unitID) != roster.end())
    {
        auto foundUnit = roster.find(unitID)->second;
        return foundUnit;
    }
        return {};
}

bool Game::RemoveUnitFromRoster(const std::string& unitID)
{
    if (roster.find(unitID) != roster.end())
    {
        roster.erase(unitID);
        return true;
    }
    std::cout << unitID << " Not found in roster. Failed to Remove Unit from Roster\n";
    return false;
}




