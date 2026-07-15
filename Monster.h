#ifndef MONSTER_H
#define MONSTER_H

#include "Character.h"

class Monster : public Character
{
private:
    int attackDamage;

public:
    Monster();
    Monster(string monsterName, int monsterHealth, int damage);

    int getAttackDamage() const;
    void displayStats() const;
};

#endif
