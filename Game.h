#ifndef GAME_H
#define GAME_H

#include "Farmer.h"
#include "Item.h"
#include "Monster.h"
#include "Villager.h"
#include <string>
#include <vector>

using namespace std;

// Game controls the game loop, locations, bundle, and endings.
class Game
{
private:
    Farmer player;
    vector<Villager> villagers;
    vector<Monster> monsters;
    vector<Item> bundleItems;
    vector<bool> bundleDonated;
    bool quitGame;
    string currentWeather;

    void setupGame();
    void loadMonsters(string filename);
    int getValidChoice(int minimum, int maximum);

    void displayIntroduction() const;
    void displayDashboard() const;
    void displayMap() const;
    void displayMainMenu() const;
    void displayHelp() const;
    void displayBundlePlanner() const;

    void moveMenu();
    void performLocationAction();
    void farmActions();
    void townActions();
    void forestActions();
    void beachActions();
    void mineActions();
    void ranchActions();
    void communityCenterActions();
    void jojaActions();

    bool talkToVillager(string villagerName);
    bool sellItem();
    bool donateItems();
    bool buyMissingBundleItem();
    void battle(Monster enemy);

    void completeAction();
    void advanceDay();
    void generateWeather();
    int getBundleProgress() const;
    bool isBundleComplete() const;
    int findBundleType(string itemType) const;
    void displayBundle() const;
    void displayEnding() const;
    int calculateScore() const;
    string mapLabel(string locationName) const;

public:
    Game();
    void run();
};

#endif
