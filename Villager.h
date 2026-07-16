#ifndef VILLAGER_H
#define VILLAGER_H

#include "Farmer.h"
#include "Item.h"
#include <string>

using namespace std;

// Villagers provide dialogue and gameplay rewards.
class Villager
{
private:
    string name;
    string location;
    string role;
    string dialogue;
    Item reward;
    bool givesItem;
    int moneyReward;
    int friendshipReward;
    bool interacted;

public:
    Villager();
    Villager(string villagerName, string villagerLocation,
             string villagerRole, string villagerDialogue,
             Item itemReward, bool hasItemReward,
             int goldReward, int friendshipPoints);

    string getName() const;
    string getLocation() const;
    string getRole() const;
    bool hasInteracted() const;

    void interact(Farmer& player);
};

#endif
