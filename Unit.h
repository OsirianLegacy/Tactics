//
// Created by Jkurt on 7/19/2026.
//

#ifndef RAYLIBGAME_UNIT_H
#define RAYLIBGAME_UNIT_H
#include <raylib.h>
#include "Data.h"

class Unit
{
public:
    void TakeDamage(int amount);
    void Heal(int amount);

private:
    RuntimeData data = {};

};


#endif //RAYLIBGAME_UNIT_H