#include "Character.h"

Character::Character(string name, int health) {
    this->name = name;
    if (health < 0) this->health = 0;
    else this->health = health;
}

string Character::getName() { return name; }
int Character::getHealth() { return health; }

void Character::takeDamage(int amount) {
    if (amount < 0) return;
    health -= amount;
    if (health < 0) health = 0;
}

void Character::heal(int amount) {
    if (amount < 0) return;
    health += amount;
    if (health > 100) health = 100;
}

bool Character::isAlive() { return health > 0; }
