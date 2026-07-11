#include "Farmer.h"

Farmer::Farmer(string name) : Character(name, 100) {
    energy = 100;
    crops = 0;
}

int Farmer::getEnergy() { return energy; }
int Farmer::getCrops() { return crops; }

bool Farmer::workOnFarm() {
    if (energy < 20) return false;
    energy -= 20;
    crops += 5;
    return true;
}

void Farmer::rest() {
    energy += 30;
    if (energy > 100) energy = 100;
    heal(10);
}
