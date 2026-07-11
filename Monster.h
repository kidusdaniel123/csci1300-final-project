#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"

class Monster : public Character {
private:
    int attackPower;

public:
    Monster(string name, int health, int attackPower);
    int getAttackPower();
    void attack(Character& target);
};

#endif
