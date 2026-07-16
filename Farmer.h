#ifndef FARMER_H
#define FARMER_H

#include "Character.h"
#include "Item.h"
#include <string>
#include <vector>

using namespace std;

// The Farmer is the player. The class stores Item objects in an inventory.
class Farmer : public Character
{
private:
    int energy;
    int maxEnergy;
    int money;
    int day;
    int maxDays;
    int actionsRemaining;
    int maxActions;
    int friendship;
    int jojaInfluence;
    string currentLocation;
    vector<Item> inventory;

public:
    Farmer();
    Farmer(string farmerName);

    int getEnergy() const;
    int getMaxEnergy() const;
    int getMoney() const;
    int getDay() const;
    int getMaxDays() const;
    int getActionsRemaining() const;
    int getFriendship() const;
    int getJojaInfluence() const;
    string getCurrentLocation() const;

    bool spendEnergy(int amount);
    void restoreEnergy(int amount);
    bool spendMoney(int amount);
    void addMoney(int amount);
    bool useAction();
    void endDay();
    bool isSeasonOver() const;

    void moveTo(string locationName);
    void addFriendship(int amount);
    void addJojaInfluence(int amount);

    void addItem(Item item);
    bool hasItemType(string itemType) const;
    bool removeItemType(string itemType);
    int getInventorySize() const;
    Item getItemAt(int index) const;
    bool removeItemAt(int index);
    void displayInventory() const;
};

#endif
