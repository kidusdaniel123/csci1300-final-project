#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

// Base class for living characters that have a name and health.
class Character
{
protected:
    string name;
    int health;
    int maxHealth;

public:
    Character();
    Character(string characterName, int characterHealth);

    string getName() const;
    int getHealth() const;
    int getMaxHealth() const;

    void takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const;
};

#endif
