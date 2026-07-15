#include "Farmer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Farmer::Farmer() : Character("Farmer", 100)
{
    energy = 100;
    maxEnergy = 100;
    food = 10;
    crops = 0;
    day = 1;
}

Farmer::Farmer(string farmerName) : Character(farmerName, 100)
{
    energy = 100;
    maxEnergy = 100;
    food = 10;
    crops = 0;
    day = 1;
}

int Farmer::getEnergy() const
{
    return energy;
}

int Farmer::getMaxEnergy() const
{
    return maxEnergy;
}

int Farmer::getFood() const
{
    return food;
}

int Farmer::getCrops() const
{
    return crops;
}

int Farmer::getDay() const
{
    return day;
}

bool Farmer::workOnFarm()
{
    int energyCost = 15;

    if (energy < energyCost)
    {
        cout << "\nYou do not have enough energy to work on the farm.\n";
        cout << "Try resting first.\n";
        return false;
    }

    int cropsGained = 2 + rand() % 4;
    int foodGained = 3 + rand() % 5;

    energy -= energyCost;
    crops += cropsGained;
    food += foodGained;

    cout << "\nYou worked hard on the farm!\n";
    cout << "+" << cropsGained << " crops\n";
    cout << "+" << foodGained << " food\n";
    cout << "-" << energyCost << " energy\n";

    nextDay();
    return true;
}

void Farmer::rest()
{
    int energyRestored = 30;
    int healthRestored = 10;

    energy += energyRestored;
    if (energy > maxEnergy)
    {
        energy = maxEnergy;
    }

    heal(healthRestored);

    cout << "\nYou rested for the day.\n";
    cout << "Your energy and health have been restored.\n";

    nextDay();
}

bool Farmer::useEnergy(int amount)
{
    if (energy < amount)
    {
        return false;
    }

    energy -= amount;
    return true;
}

void Farmer::addFood(int amount)
{
    food += amount;
}

void Farmer::addCrops(int amount)
{
    crops += amount;
}

void Farmer::nextDay()
{
    day++;
}

void Farmer::displayStats() const
{
    cout << "\n==============================\n";
    cout << "       PLAYER STATISTICS\n";
    cout << "==============================\n";
    cout << "Name:   " << name << endl;
    cout << "Day:    " << day << endl;
    cout << "Health: " << health << "/" << maxHealth << endl;
    cout << "Energy: " << energy << "/" << maxEnergy << endl;
    cout << "Food:   " << food << endl;
    cout << "Crops:  " << crops << endl;
    cout << "==============================\n";
}
