#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

Game::Game()
{
    quitGame = false;
    currentWeather = "Sunny";
}

void Game::setupGame()
{
    string playerName;

    cout << "Enter your farmer's name: ";
    getline(cin, playerName);

    if (playerName.empty())
    {
        playerName = "Farmer";
    }

    player = Farmer(playerName);

    // The final bundle requires one item from five categories.
    bundleItems.push_back(Item("Any Crop", "Crop", 0, true, 0));
    bundleItems.push_back(Item("Any Fish", "Fish", 0, true, 0));
    bundleItems.push_back(Item("Any Mineral", "Mineral", 0, true, 0));
    bundleItems.push_back(Item("Any Animal Product", "Animal Product", 0, true, 0));
    bundleItems.push_back(Item("Any Forage Item", "Forage", 0, true, 0));

    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        bundleDonated.push_back(false);
    }

    // Each villager affects gameplay by giving an item, money, or friendship.
    villagers.push_back(Villager(
        "Mayor Lewis", "Town Square", "Tracks bundle progress",
        "The Community Center needs one last bundle. Please finish it before Day 10 ends!",
        Item(), false, 15, 1));

    villagers.push_back(Villager(
        "Willy", "Beach", "Fishing expert",
        "A good farmer should know the water too. Take this fish for the bundle.",
        Item("Sunfish", "Fish", 25, true, 0), true, 0, 1));

    villagers.push_back(Villager(
        "Linus", "Forest", "Foraging guide",
        "The forest gives plenty if you respect it. This should help your bundle.",
        Item("Wild Horseradish", "Forage", 20, true, 0), true, 0, 1));

    villagers.push_back(Villager(
        "Clint", "Mines", "Blacksmith",
        "I found a clean piece of copper ore. You can use it for the final bundle.",
        Item("Copper Ore", "Mineral", 30, true, 0), true, 0, 1));

    villagers.push_back(Villager(
        "Marnie", "Marnie's Ranch", "Ranch owner",
        "You have been helping the whole valley. Please take this fresh egg.",
        Item("Egg", "Animal Product", 25, true, 0), true, 0, 1));

    loadMonsters("monsters.txt");
    generateWeather();
}

void Game::loadMonsters(string filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        // These defaults keep the game playable if the text file is missing.
        monsters.push_back(Monster("Green Slime", 30, 6));
        monsters.push_back(Monster("Cave Bat", 25, 7));
        return;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream lineStream(line);
        string monsterName;
        int monsterHealth;
        int monsterDamage;

        getline(lineStream, monsterName, ',');
        lineStream >> monsterHealth;
        lineStream.ignore();
        lineStream >> monsterDamage;

        if (!monsterName.empty())
        {
            monsters.push_back(Monster(monsterName, monsterHealth, monsterDamage));
        }
    }

    inputFile.close();
}

int Game::getValidChoice(int minimum, int maximum)
{
    int choice;

    while (true)
    {
        cin >> choice;

        if (!cin.fail() && choice >= minimum && choice <= maximum)
        {
            return choice;
        }

        cout << "Invalid input. Enter a number from "
             << minimum << " to " << maximum << ": ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Game::displayIntroduction() const
{
    cout << "\n====================================================\n";
    cout << "         FARM SURVIVAL: THE FINAL BUNDLE\n";
    cout << "====================================================\n";
    cout << "The Community Center is almost restored.\n";
    cout << "Collect and donate one Crop, Fish, Mineral,\n";
    cout << "Animal Product, and Forage Item before Day 10 ends.\n";
    cout << "You have only three actions each day, so plan wisely.\n";
    cout << "JojaMart can help, but every shortcut has a cost.\n";
    cout << "====================================================\n";
}

string Game::mapLabel(string locationName) const
{
    if (player.getCurrentLocation() == locationName)
    {
        return "*" + locationName;
    }

    return locationName;
}

void Game::displayMap() const
{
    cout << "\nMap (* = current location):\n";
    cout << "                         [" << mapLabel("Mines") << "]\n";
    cout << "                              |\n";
    cout << "[" << mapLabel("Farm") << "] -- [" << mapLabel("Town Square")
         << "] -- [" << mapLabel("Community Center") << "] -- ["
         << mapLabel("Beach") << "]\n";
    cout << "    |              |                    |\n";
    cout << "[" << mapLabel("Forest") << "]   [" << mapLabel("Marnie's Ranch")
         << "]        [" << mapLabel("JojaMart") << "]\n";
}

void Game::displayDashboard() const
{
    cout << "\n====================================================\n";
    cout << "              THE FINAL BUNDLE\n";
    cout << "====================================================\n";
    cout << "Farmer: " << player.getName() << endl;
    cout << "Day: " << player.getDay() << " / " << player.getMaxDays()
         << "    Actions: " << player.getActionsRemaining() << " / 3\n";
    cout << "Health: " << player.getHealth() << " / " << player.getMaxHealth()
         << "    Energy: " << player.getEnergy() << " / " << player.getMaxEnergy()
         << "    Money: " << player.getMoney() << "g\n";
    cout << "Location: " << player.getCurrentLocation()
         << "    Weather: " << currentWeather << endl;
    cout << "Friendship: " << player.getFriendship()
         << "    Joja Influence: " << player.getJojaInfluence() << endl;
    cout << "Bundle Progress: " << getBundleProgress() << " / "
         << bundleItems.size() << " items donated\n";
    cout << "Inventory Items: " << player.getInventorySize() << endl;

    displayMap();
    cout << "====================================================\n";
}

void Game::displayMainMenu() const
{
    cout << "\nWhat would you like to do?\n";
    cout << "1. Move to another location\n";
    cout << "2. Take an action at this location\n";
    cout << "3. View inventory\n";
    cout << "4. View final bundle\n";
    cout << "5. End the current day\n";
    cout << "6. Help\n";
    cout << "7. Smart Bundle Planner (extra credit)\n";
    cout << "8. Quit game\n";
    cout << "Enter choice: ";
}

void Game::displayHelp() const
{
    cout << "\n==================== HELP ====================\n";
    cout << "Goal: Donate one item from each bundle category.\n";
    cout << "Moving and most gameplay actions use one action.\n";
    cout << "You receive three actions each day and 100 energy.\n";
    cout << "Talk to villagers, gather items, or use JojaMart.\n";
    cout << "Visit the Community Center to donate your items.\n";
    cout << "The season ends after Day 10.\n";
    cout << "Weather changes each day and affects farming, fishing,\n";
    cout << "foraging, and whether the mines are open.\n";
    cout << "The Smart Bundle Planner recommends useful next steps.\n";
    cout << "==============================================\n";
}

void Game::generateWeather()
{
    // Weather changes at the start of each day.
    int weatherRoll = rand() % 100;

    if (weatherRoll < 45)
    {
        currentWeather = "Sunny";
    }
    else if (weatherRoll < 80)
    {
        currentWeather = "Rainy";
    }
    else
    {
        currentWeather = "Stormy";
    }
}

void Game::advanceDay()
{
    player.endDay();

    if (!player.isSeasonOver())
    {
        generateWeather();
        cout << "Tomorrow's weather is " << currentWeather << ".\n";
    }
}

void Game::displayBundlePlanner() const
{
    cout << "\n=============== SMART BUNDLE PLANNER ===============\n";

    if (isBundleComplete())
    {
        cout << "The final bundle is complete. Great work!\n";
        cout << "====================================================\n";
        return;
    }

    bool recommendationShown = false;

    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        if (bundleDonated[i])
        {
            continue;
        }

        string itemType = bundleItems[i].getType();
        cout << "Still needed: " << itemType << "\n";

        if (player.hasItemType(itemType))
        {
            cout << "  You already have this category. Visit the Community Center to donate it.\n";
        }
        else if (itemType == "Crop")
        {
            cout << "  Recommended: Return to the Farm and harvest a Parsnip.\n";
            if (currentWeather == "Sunny")
            {
                cout << "  Sunny weather lowers the farming energy cost today.\n";
            }
        }
        else if (itemType == "Fish")
        {
            cout << "  Recommended: Visit Willy at the Beach or go fishing.\n";
            if (currentWeather == "Rainy")
            {
                cout << "  Rainy weather gives you a better fishing chance today.\n";
            }
        }
        else if (itemType == "Mineral")
        {
            if (currentWeather == "Stormy")
            {
                cout << "  The Mines are closed by the storm. Talk to Clint on another day or use JojaMart.\n";
            }
            else
            {
                cout << "  Recommended: Visit Clint or mine for Copper Ore in the Mines.\n";
            }
        }
        else if (itemType == "Animal Product")
        {
            cout << "  Recommended: Visit Marnie at Marnie's Ranch for an Egg.\n";
        }
        else if (itemType == "Forage")
        {
            cout << "  Recommended: Visit Linus or forage in the Forest.\n";
            if (currentWeather == "Rainy")
            {
                cout << "  Rainy weather may uncover an extra forest item today.\n";
            }
        }

        recommendationShown = true;
    }

    if (recommendationShown)
    {
        cout << "\nGeneral advice: Save JojaMart for emergencies because each shortcut\n";
        cout << "increases Joja Influence and can change your ending.\n";
    }

    cout << "====================================================\n";
}

void Game::completeAction()
{
    player.useAction();

    if (player.getActionsRemaining() == 0 && !isBundleComplete())
    {
        cout << "\nYou have used all three actions for today.\n";
        cout << "You return home and sleep. Energy and some health are restored.\n";
        advanceDay();
    }
}

void Game::moveMenu()
{
    const string locations[] = {
        "Farm", "Town Square", "Forest", "Beach", "Mines",
        "Marnie's Ranch", "Community Center", "JojaMart"};

    cout << "\nWhere would you like to go?\n";

    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << ". " << locations[i] << endl;
    }

    cout << "9. Cancel\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 9);

    if (choice == 9)
    {
        return;
    }

    string destination = locations[choice - 1];

    if (destination == player.getCurrentLocation())
    {
        cout << "You are already at " << destination << ".\n";
        return;
    }

    player.moveTo(destination);
    cout << "You travel to " << destination << ".\n";
    completeAction();
}

bool Game::talkToVillager(string villagerName)
{
    for (int i = 0; i < static_cast<int>(villagers.size()); i++)
    {
        if (villagers[i].getName() == villagerName)
        {
            villagers[i].interact(player);
            return true;
        }
    }

    cout << "That villager could not be found.\n";
    return false;
}

bool Game::sellItem()
{
    if (player.getInventorySize() == 0)
    {
        cout << "You do not have anything to sell.\n";
        return false;
    }

    player.displayInventory();
    cout << player.getInventorySize() + 1 << ". Cancel\n";
    cout << "Choose an item to sell: ";

    int choice = getValidChoice(1, player.getInventorySize() + 1);

    if (choice == player.getInventorySize() + 1)
    {
        return false;
    }

    Item soldItem = player.getItemAt(choice - 1);
    player.addMoney(soldItem.getValue());
    player.removeItemAt(choice - 1);

    cout << "You sold " << soldItem.getName() << " for "
         << soldItem.getValue() << "g.\n";
    return true;
}

void Game::farmActions()
{
    cout << "\nFarm Actions:\n";
    int farmEnergyCost = 15;

    if (currentWeather == "Sunny")
    {
        farmEnergyCost = 10;
    }

    cout << "1. Harvest a Parsnip (" << farmEnergyCost << " energy)\n";
    cout << "2. Rest by the farmhouse (+35 energy, +10 health)\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (!player.spendEnergy(farmEnergyCost))
        {
            cout << "You do not have enough energy.\n";
            return;
        }

        player.addItem(Item("Parsnip", "Crop", 20, true, 0));
        cout << "You harvested a Parsnip!\n";

        if (currentWeather == "Sunny" && rand() % 100 < 40)
        {
            player.addItem(Item("Golden Parsnip", "Crop", 35, true, 0));
            cout << "The sunshine helped you harvest a bonus Golden Parsnip!\n";
        }
        completeAction();
    }
    else if (choice == 2)
    {
        player.restoreEnergy(35);
        player.heal(10);
        cout << "You take a short rest.\n";
        completeAction();
    }
}

void Game::townActions()
{
    cout << "\nTown Square Actions:\n";
    cout << "1. Talk to Mayor Lewis\n";
    cout << "2. Sell an inventory item\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (talkToVillager("Mayor Lewis"))
        {
            completeAction();
        }
    }
    else if (choice == 2)
    {
        if (sellItem())
        {
            completeAction();
        }
    }
}

void Game::forestActions()
{
    cout << "\nForest Actions:\n";
    cout << "1. Forage for an item (15 energy)\n";
    cout << "2. Talk to Linus\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (!player.spendEnergy(15))
        {
            cout << "You do not have enough energy.\n";
            return;
        }

        player.addItem(Item("Wild Horseradish", "Forage", 20, true, 0));
        cout << "You found a Wild Horseradish!\n";

        if (currentWeather == "Rainy" && rand() % 100 < 50)
        {
            player.addItem(Item("Rain Mushroom", "Forage", 30, true, 0));
            cout << "The rain revealed a bonus Rain Mushroom!\n";
        }
        completeAction();
    }
    else if (choice == 2)
    {
        if (talkToVillager("Linus"))
        {
            completeAction();
        }
    }
}

void Game::beachActions()
{
    cout << "\nBeach Actions:\n";
    int fishingEnergyCost = 20;
    int fishingChance = 70;

    if (currentWeather == "Rainy")
    {
        fishingEnergyCost = 15;
        fishingChance = 90;
    }
    else if (currentWeather == "Stormy")
    {
        fishingChance = 45;
    }

    cout << "1. Go fishing (" << fishingEnergyCost << " energy)\n";
    cout << "2. Talk to Willy\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (!player.spendEnergy(fishingEnergyCost))
        {
            cout << "You do not have enough energy.\n";
            return;
        }

        int catchChance = rand() % 100;

        if (catchChance < fishingChance)
        {
            player.addItem(Item("Sunfish", "Fish", 25, true, 0));
            cout << "You caught a Sunfish!\n";
        }
        else
        {
            cout << "The fish got away this time.\n";
        }

        completeAction();
    }
    else if (choice == 2)
    {
        if (talkToVillager("Willy"))
        {
            completeAction();
        }
    }
}

void Game::battle(Monster enemy)
{
    cout << "\nA " << enemy.getName() << " blocks your path!\n";

    while (player.isAlive() && enemy.isAlive())
    {
        cout << "\nYour Health: " << player.getHealth()
             << "    " << enemy.getName() << " Health: "
             << enemy.getHealth() << endl;
        cout << "1. Attack\n";
        cout << "2. Try to run\n";
        cout << "Enter choice: ";

        int choice = getValidChoice(1, 2);

        if (choice == 1)
        {
            int damage = 10 + rand() % 11;
            enemy.takeDamage(damage);
            cout << "You deal " << damage << " damage.\n";

            if (enemy.isAlive())
            {
                player.takeDamage(enemy.getAttackDamage());
                cout << "The " << enemy.getName() << " deals "
                     << enemy.getAttackDamage() << " damage to you.\n";
            }
        }
        else
        {
            if (rand() % 2 == 0)
            {
                cout << "You escaped safely.\n";
                return;
            }

            cout << "You could not escape!\n";
            player.takeDamage(enemy.getAttackDamage());
        }
    }

    if (!enemy.isAlive())
    {
        cout << "You defeated the " << enemy.getName() << "!\n";
    }
}

void Game::mineActions()
{
    cout << "\nMines Actions:\n";
    cout << "1. Mine for Copper Ore (25 energy)\n";
    cout << "2. Talk to Clint\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (currentWeather == "Stormy")
        {
            cout << "The mine entrance is closed because of the storm.\n";
            return;
        }

        if (!player.spendEnergy(25))
        {
            cout << "You do not have enough energy.\n";
            return;
        }

        if (!monsters.empty() && rand() % 100 < 35)
        {
            Monster enemy = monsters[rand() % monsters.size()];
            battle(enemy);
        }

        if (player.isAlive())
        {
            player.addItem(Item("Copper Ore", "Mineral", 30, true, 0));
            cout << "You mined a piece of Copper Ore!\n";
        }

        completeAction();
    }
    else if (choice == 2)
    {
        if (talkToVillager("Clint"))
        {
            completeAction();
        }
    }
}

void Game::ranchActions()
{
    cout << "\nMarnie's Ranch Actions:\n";
    cout << "1. Talk to Marnie\n";
    cout << "2. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 2);

    if (choice == 1)
    {
        if (talkToVillager("Marnie"))
        {
            completeAction();
        }
    }
}

int Game::findBundleType(string itemType) const
{
    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        if (bundleItems[i].getType() == itemType)
        {
            return i;
        }
    }

    return -1;
}

bool Game::donateItems()
{
    bool donatedSomething = false;

    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        string requiredType = bundleItems[i].getType();

        if (!bundleDonated[i] && player.hasItemType(requiredType))
        {
            player.removeItemType(requiredType);
            bundleDonated[i] = true;
            donatedSomething = true;
            cout << "You donated one " << requiredType << " item.\n";
        }
    }

    if (!donatedSomething)
    {
        cout << "You do not have any new bundle items to donate.\n";
    }

    return donatedSomething;
}

void Game::communityCenterActions()
{
    cout << "\nCommunity Center Actions:\n";
    cout << "1. Donate all eligible inventory items\n";
    cout << "2. View bundle progress\n";
    cout << "3. Go back\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (donateItems())
        {
            completeAction();
        }
    }
    else if (choice == 2)
    {
        displayBundle();
    }
}

bool Game::buyMissingBundleItem()
{
    vector<int> missingIndexes;

    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        if (!bundleDonated[i] && !player.hasItemType(bundleItems[i].getType()))
        {
            missingIndexes.push_back(i);
        }
    }

    if (missingIndexes.empty())
    {
        cout << "You already own or donated every required item type.\n";
        return false;
    }

    cout << "\nMorris can sell you one missing bundle item for 35g.\n";

    for (int i = 0; i < static_cast<int>(missingIndexes.size()); i++)
    {
        int bundleIndex = missingIndexes[i];
        cout << i + 1 << ". " << bundleItems[bundleIndex].getType() << endl;
    }

    cout << missingIndexes.size() + 1 << ". Cancel\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, static_cast<int>(missingIndexes.size()) + 1);

    if (choice == static_cast<int>(missingIndexes.size()) + 1)
    {
        return false;
    }

    if (!player.spendMoney(35))
    {
        cout << "You do not have enough money.\n";
        return false;
    }

    int selectedBundleIndex = missingIndexes[choice - 1];
    string selectedType = bundleItems[selectedBundleIndex].getType();
    string itemName;

    if (selectedType == "Crop")
    {
        itemName = "Joja Parsnip";
    }
    else if (selectedType == "Fish")
    {
        itemName = "Frozen Sunfish";
    }
    else if (selectedType == "Mineral")
    {
        itemName = "Processed Copper Ore";
    }
    else if (selectedType == "Animal Product")
    {
        itemName = "Joja Egg";
    }
    else
    {
        itemName = "Packaged Wild Horseradish";
    }

    player.addItem(Item(itemName, selectedType, 10, true, 0));
    player.addJojaInfluence(1);

    cout << "You bought " << itemName << ".\n";
    cout << "Joja Influence increased by 1.\n";
    return true;
}

void Game::jojaActions()
{
    cout << "\nMorris says:\n";
    cout << "\"Why work so hard? Joja can solve your problems... for a price.\"\n";
    cout << "1. Buy one missing bundle item (35g)\n";
    cout << "2. Buy a Joja Cola (15g, +35 energy)\n";
    cout << "3. Leave JojaMart\n";
    cout << "Enter choice: ";

    int choice = getValidChoice(1, 3);

    if (choice == 1)
    {
        if (buyMissingBundleItem())
        {
            completeAction();
        }
    }
    else if (choice == 2)
    {
        if (!player.spendMoney(15))
        {
            cout << "You do not have enough money.\n";
            return;
        }

        player.restoreEnergy(35);
        player.addJojaInfluence(1);
        cout << "You drink a Joja Cola and restore 35 energy.\n";
        cout << "Joja Influence increased by 1.\n";
        completeAction();
    }
}

void Game::performLocationAction()
{
    string location = player.getCurrentLocation();

    if (location == "Farm")
    {
        farmActions();
    }
    else if (location == "Town Square")
    {
        townActions();
    }
    else if (location == "Forest")
    {
        forestActions();
    }
    else if (location == "Beach")
    {
        beachActions();
    }
    else if (location == "Mines")
    {
        mineActions();
    }
    else if (location == "Marnie's Ranch")
    {
        ranchActions();
    }
    else if (location == "Community Center")
    {
        communityCenterActions();
    }
    else if (location == "JojaMart")
    {
        jojaActions();
    }
}

int Game::getBundleProgress() const
{
    int progress = 0;

    for (int i = 0; i < static_cast<int>(bundleDonated.size()); i++)
    {
        if (bundleDonated[i])
        {
            progress++;
        }
    }

    return progress;
}

bool Game::isBundleComplete() const
{
    return getBundleProgress() == static_cast<int>(bundleItems.size());
}

void Game::displayBundle() const
{
    cout << "\n=============== FINAL BUNDLE ===============\n";

    for (int i = 0; i < static_cast<int>(bundleItems.size()); i++)
    {
        if (bundleDonated[i])
        {
            cout << "[X] ";
        }
        else
        {
            cout << "[ ] ";
        }

        cout << bundleItems[i].getType() << endl;
    }

    cout << "Progress: " << getBundleProgress() << " / "
         << bundleItems.size() << endl;
    cout << "============================================\n";
}

int Game::calculateScore() const
{
    int daysLeft = player.getMaxDays() - player.getDay() + 1;

    if (daysLeft < 0)
    {
        daysLeft = 0;
    }

    int score = getBundleProgress() * 100;
    score += daysLeft * 25;
    score += player.getMoney();
    score += player.getFriendship() * 10;
    score -= player.getJojaInfluence() * 30;

    if (score < 0)
    {
        score = 0;
    }

    return score;
}

void Game::displayEnding() const
{
    cout << "\n====================================================\n";
    cout << "                    FINAL ENDING\n";
    cout << "====================================================\n";

    if (isBundleComplete())
    {
        if (player.getJojaInfluence() == 0 && player.getFriendship() >= 4)
        {
            cout << "COMMUNITY HERO ENDING\n";
            cout << "You restored the Community Center through hard work\n";
            cout << "and friendship. The entire valley celebrates you!\n";
        }
        else if (player.getJojaInfluence() <= 2)
        {
            cout << "RESTORED CENTER ENDING\n";
            cout << "The final bundle is complete. Joja helped a little,\n";
            cout << "but the Community Center belongs to the town again.\n";
        }
        else
        {
            cout << "JOJA SHADOW ENDING\n";
            cout << "The bundle is complete, but Joja gained major influence\n";
            cout << "over the valley because of your shortcuts.\n";
        }
    }
    else if (!player.isAlive())
    {
        cout << "DEFEAT ENDING\n";
        cout << "You were defeated in the mines before finishing the bundle.\n";
    }
    else if (player.isSeasonOver())
    {
        if (getBundleProgress() > 0)
        {
            cout << "ALMOST THERE ENDING\n";
            cout << "The season ended with " << getBundleProgress()
                 << " of " << bundleItems.size() << " items donated.\n";
        }
        else
        {
            cout << "SEASON OVER ENDING\n";
            cout << "The season ended before you donated any bundle items.\n";
        }
    }
    else
    {
        cout << "EARLY DEPARTURE ENDING\n";
        cout << "You left the valley before the final bundle was complete.\n";
    }

    cout << "\nFinal Score: " << calculateScore() << endl;
    cout << "Days Reached: " << player.getDay() << endl;
    cout << "Bundle Progress: " << getBundleProgress() << " / "
         << bundleItems.size() << endl;
    cout << "Friendship: " << player.getFriendship() << endl;
    cout << "Joja Influence: " << player.getJojaInfluence() << endl;
    cout << "====================================================\n";
}

void Game::run()
{
    srand(static_cast<unsigned int>(time(0)));

    displayIntroduction();
    setupGame();

    while (!quitGame && player.isAlive() &&
           !player.isSeasonOver() && !isBundleComplete())
    {
        displayDashboard();
        displayMainMenu();

        int choice = getValidChoice(1, 8);

        if (choice == 1)
        {
            moveMenu();
        }
        else if (choice == 2)
        {
            performLocationAction();
        }
        else if (choice == 3)
        {
            player.displayInventory();
        }
        else if (choice == 4)
        {
            displayBundle();
        }
        else if (choice == 5)
        {
            cout << "You end the day early and return home.\n";
            advanceDay();
        }
        else if (choice == 6)
        {
            displayHelp();
        }
        else if (choice == 7)
        {
            displayBundlePlanner();
        }
        else
        {
            quitGame = true;
        }
    }

    displayEnding();
}
