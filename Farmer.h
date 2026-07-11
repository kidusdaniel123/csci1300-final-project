#ifndef FARMER_H
#define FARMER_H
#include "Character.h"

class Farmer : public Character {
private:
    int energy;
    int crops;

public:
    Farmer(string name);
    int getEnergy();
    int getCrops();
    bool workOnFarm();
    void rest();
};

#endif
