#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

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

    void setName(string characterName);
    void setHealth(int characterHealth);

    void takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const;
};

#endif
