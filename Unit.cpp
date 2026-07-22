//
// Created by Jkurt on 7/19/2026.
//

#include "Unit.h"

void Unit::Heal(int amount)
{
    data.health.IncreaseCur(amount);
}

void Unit::TakeDamage(int amount)
{
    data.health.DecreaseCur(amount);
}

