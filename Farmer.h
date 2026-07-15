#ifndef FARMER_H
#define FARMER_H

#include "Character.h"

class Farmer : public Character
{
private:
    int energy;
    int maxEnergy;
    int food;
    int crops;
    int day;

public:
    Farmer();
    Farmer(string farmerName);

    int getEnergy() const;
    int getMaxEnergy() const;
    int getFood() const;
    int getCrops() const;
    int getDay() const;

    bool workOnFarm();
    void rest();
    bool useEnergy(int amount);
    void addFood(int amount);
    void addCrops(int amount);
    void nextDay();

    void displayStats() const;
};

#endif
