#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

// Item objects are stored in the farmer's inventory.
class Item
{
private:
    string name;
    string type;
    int value;
    bool bundleItem;
    int energyRestore;

public:
    Item();
    Item(string itemName, string itemType, int itemValue,
         bool neededForBundle, int restoreAmount);

    string getName() const;
    string getType() const;
    int getValue() const;
    bool isBundleItem() const;
    int getEnergyRestore() const;

    void displayItem() const;
};

#endif
