#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
using namespace std;

class Character {
private:
    string name;
    int health;

public:
    Character(string name, int health);
    string getName();
    int getHealth();
    void takeDamage(int amount);
    void heal(int amount);
    bool isAlive();
};

#endif
