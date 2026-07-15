#include "Monster.h"
#include <iostream>

using namespace std;

Monster::Monster() : Character("Unknown Monster", 50)
{
    attackDamage = 10;
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

void Monster::displayStats() const
{
    cout << "Monster: " << name << endl;
    cout << "Health: " << health << "/" << maxHealth << endl;
    cout << "Attack Damage: " << attackDamage << endl;
}
