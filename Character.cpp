#include "Character.h"

Character::Character()
{
    name = "Unknown";
    health = 100;
    maxHealth = 100;
}

Character::Character(string characterName, int characterHealth)
{
    name = characterName;
    health = characterHealth;
    maxHealth = characterHealth;
}

string Character::getName() const
{
    return name;
}

int Character::getHealth() const
{
    return health;
}

int Character::getMaxHealth() const
{
    return maxHealth;
}

void Character::setName(string characterName)
{
    name = characterName;
}

void Character::setHealth(int characterHealth)
{
    health = characterHealth;

    if (health > maxHealth)
    {
        health = maxHealth;
    }

    if (health < 0)
    {
        health = 0;
    }
}

void Character::takeDamage(int damage)
{
    health -= damage;

    if (health < 0)
    {
        health = 0;
    }
}

void Character::heal(int amount)
{
    health += amount;

    if (health > maxHealth)
    {
        health = maxHealth;
    }
}

bool Character::isAlive() const
{
    return health > 0;
}
