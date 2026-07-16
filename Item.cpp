#include "Item.h"
#include <iostream>

using namespace std;

Item::Item()
{
    name = "Unknown Item";
    type = "Other";
    value = 0;
    bundleItem = false;
    energyRestore = 0;
}

Item::Item(string itemName, string itemType, int itemValue,
           bool neededForBundle, int restoreAmount)
{
    name = itemName;
    type = itemType;
    value = itemValue;
    bundleItem = neededForBundle;
    energyRestore = restoreAmount;
}

string Item::getName() const
{
    return name;
}

string Item::getType() const
{
    return type;
}

int Item::getValue() const
{
    return value;
}

bool Item::isBundleItem() const
{
    return bundleItem;
}

int Item::getEnergyRestore() const
{
    return energyRestore;
}

void Item::displayItem() const
{
    cout << name << " - " << type << " - Value: " << value << "g";

    if (bundleItem)
    {
        cout << " - Bundle item";
    }

    if (energyRestore > 0)
    {
        cout << " - Restores " << energyRestore << " energy";
    }

    cout << endl;
}
