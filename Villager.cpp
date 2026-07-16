#include "Villager.h"
#include <iostream>

using namespace std;

Villager::Villager()
{
    name = "Unknown Villager";
    location = "Town Square";
    role = "Villager";
    dialogue = "Hello.";
    reward = Item();
    givesItem = false;
    moneyReward = 0;
    friendshipReward = 0;
    interacted = false;
}

Villager::Villager(string villagerName, string villagerLocation,
                   string villagerRole, string villagerDialogue,
                   Item itemReward, bool hasItemReward,
                   int goldReward, int friendshipPoints)
{
    name = villagerName;
    location = villagerLocation;
    role = villagerRole;
    dialogue = villagerDialogue;
    reward = itemReward;
    givesItem = hasItemReward;
    moneyReward = goldReward;
    friendshipReward = friendshipPoints;
    interacted = false;
}

string Villager::getName() const
{
    return name;
}

string Villager::getLocation() const
{
    return location;
}

string Villager::getRole() const
{
    return role;
}

bool Villager::hasInteracted() const
{
    return interacted;
}

void Villager::interact(Farmer& player)
{
    cout << "\n" << name << " says:\n\"" << dialogue << "\"\n";

    if (!interacted)
    {
        if (givesItem)
        {
            player.addItem(reward);
            cout << name << " gave you " << reward.getName() << "!\n";
        }

        if (moneyReward > 0)
        {
            player.addMoney(moneyReward);
            cout << name << " gave you " << moneyReward << "g to help the town.\n";
        }

        if (friendshipReward > 0)
        {
            player.addFriendship(friendshipReward);
            cout << "Friendship increased by " << friendshipReward << ".\n";
        }

        interacted = true;
    }
    else
    {
        cout << name << " has already helped you, but wishes you good luck.\n";
    }
}
