#include "Farmer.h"
#include <iostream>

using namespace std;

Farmer::Farmer() : Character("Farmer", 100)
{
    energy = 100;
    maxEnergy = 100;
    money = 50;
    day = 1;
    maxDays = 10;
    actionsRemaining = 3;
    maxActions = 3;
    friendship = 0;
    jojaInfluence = 0;
    currentLocation = "Farm";
}

Farmer::Farmer(string farmerName) : Character(farmerName, 100)
{
    energy = 100;
    maxEnergy = 100;
    money = 50;
    day = 1;
    maxDays = 10;
    actionsRemaining = 3;
    maxActions = 3;
    friendship = 0;
    jojaInfluence = 0;
    currentLocation = "Farm";
}

int Farmer::getEnergy() const
{
    return energy;
}

int Farmer::getMaxEnergy() const
{
    return maxEnergy;
}

int Farmer::getMoney() const
{
    return money;
}

int Farmer::getDay() const
{
    return day;
}

int Farmer::getMaxDays() const
{
    return maxDays;
}

int Farmer::getActionsRemaining() const
{
    return actionsRemaining;
}

int Farmer::getFriendship() const
{
    return friendship;
}

int Farmer::getJojaInfluence() const
{
    return jojaInfluence;
}

string Farmer::getCurrentLocation() const
{
    return currentLocation;
}

bool Farmer::spendEnergy(int amount)
{
    if (energy < amount)
    {
        return false;
    }

    energy -= amount;
    return true;
}

void Farmer::restoreEnergy(int amount)
{
    energy += amount;

    if (energy > maxEnergy)
    {
        energy = maxEnergy;
    }
}

bool Farmer::spendMoney(int amount)
{
    if (money < amount)
    {
        return false;
    }

    money -= amount;
    return true;
}

void Farmer::addMoney(int amount)
{
    money += amount;
}

bool Farmer::useAction()
{
    if (actionsRemaining <= 0)
    {
        return false;
    }

    actionsRemaining--;
    return true;
}

void Farmer::endDay()
{
    day++;
    energy = maxEnergy;
    actionsRemaining = maxActions;

    // Sleeping restores a small amount of health.
    heal(10);
}

bool Farmer::isSeasonOver() const
{
    return day > maxDays;
}

void Farmer::moveTo(string locationName)
{
    currentLocation = locationName;
}

void Farmer::addFriendship(int amount)
{
    friendship += amount;
}

void Farmer::addJojaInfluence(int amount)
{
    jojaInfluence += amount;
}

void Farmer::addItem(Item item)
{
    inventory.push_back(item);
}

bool Farmer::hasItemType(string itemType) const
{
    for (int i = 0; i < static_cast<int>(inventory.size()); i++)
    {
        if (inventory[i].getType() == itemType)
        {
            return true;
        }
    }

    return false;
}

bool Farmer::removeItemType(string itemType)
{
    for (int i = 0; i < static_cast<int>(inventory.size()); i++)
    {
        if (inventory[i].getType() == itemType)
        {
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }

    return false;
}

int Farmer::getInventorySize() const
{
    return static_cast<int>(inventory.size());
}

Item Farmer::getItemAt(int index) const
{
    if (index >= 0 && index < static_cast<int>(inventory.size()))
    {
        return inventory[index];
    }

    return Item();
}

bool Farmer::removeItemAt(int index)
{
    if (index < 0 || index >= static_cast<int>(inventory.size()))
    {
        return false;
    }

    inventory.erase(inventory.begin() + index);
    return true;
}

void Farmer::displayInventory() const
{
    cout << "\n=============== INVENTORY ===============\n";

    if (inventory.empty())
    {
        cout << "Your inventory is empty.\n";
    }
    else
    {
        for (int i = 0; i < static_cast<int>(inventory.size()); i++)
        {
            cout << i + 1 << ". ";
            inventory[i].displayItem();
        }
    }

    cout << "=========================================\n";
}
