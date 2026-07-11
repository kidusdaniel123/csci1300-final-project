#include "Monster.h"

Monster::Monster(string name, int health, int attackPower)
    : Character(name, health) {
    if (attackPower < 0) this->attackPower = 0;
    else this->attackPower = attackPower;
}

int Monster::getAttackPower() { return attackPower; }

void Monster::attack(Character& target) {
    target.takeDamage(attackPower);
}
