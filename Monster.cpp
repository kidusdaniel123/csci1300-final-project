#include "Monster.h"

Monster::Monster() : Character("Slime", 30)
{
    attackDamage = 6;
}

Monster::Monster(string monsterName, int monsterHealth, int damage)
    : Character(monsterName, monsterHealth)
{
    attackDamage = damage;
}

int Monster::getAttackDamage() const
{
    return attackDamage;
}
