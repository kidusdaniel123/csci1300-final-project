#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Character.h"
#include "Farmer.h"
#include "Monster.h"

using namespace std;

vector<Monster> loadMonsters(string filename);
void displayMainMenu();
void explore(Farmer& player, const vector<Monster>& monsters);
void battle(Farmer& player, Monster enemy);

vector<Monster> loadMonsters(string filename)
{
    vector<Monster> monsters;
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open " << filename << endl;
        return monsters;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string monsterName;
        string healthText;
        string damageText;

        getline(ss, monsterName, ',');
        getline(ss, healthText, ',');
        getline(ss, damageText);

        if (monsterName.empty() || healthText.empty() || damageText.empty())
        {
            continue;
        }

        int monsterHealth = stoi(healthText);
        int monsterDamage = stoi(damageText);

        monsters.push_back(Monster(monsterName, monsterHealth, monsterDamage));
    }

    inputFile.close();
    return monsters;
}

void displayMainMenu()
{
    cout << "\n==============================\n";
    cout << "         FARM SURVIVAL\n";
    cout << "==============================\n";
    cout << "1. View player stats\n";
    cout << "2. Work on farm\n";
    cout << "3. Rest\n";
    cout << "4. Explore\n";
    cout << "5. Quit\n";
    cout << "==============================\n";
    cout << "Enter your choice: ";
}

void battle(Farmer& player, Monster enemy)
{
    cout << "\n==============================\n";
    cout << "            BATTLE\n";
    cout << "==============================\n";
    cout << "A " << enemy.getName() << " attacks you!\n";

    bool battleOver = false;

    while (!battleOver && player.isAlive() && enemy.isAlive())
    {
        cout << "\n------------------------------\n";
        cout << player.getName() << " Health: "
             << player.getHealth() << "/" << player.getMaxHealth() << endl;
        cout << enemy.getName() << " Health: "
             << enemy.getHealth() << "/" << enemy.getMaxHealth() << endl;
        cout << "------------------------------\n";
        cout << "1. Attack\n";
        cout << "2. Run\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            int playerDamage = 10 + rand() % 11;
            cout << "\nYou attack the " << enemy.getName()
                 << " for " << playerDamage << " damage!\n";

            enemy.takeDamage(playerDamage);

            if (enemy.isAlive())
            {
                int enemyDamage = enemy.getAttackDamage();
                cout << "The " << enemy.getName()
                     << " attacks you for " << enemyDamage << " damage!\n";
                player.takeDamage(enemyDamage);
            }
        }
        else if (choice == 2)
        {
            int escapeChance = rand() % 2;

            if (escapeChance == 0)
            {
                cout << "\nYou successfully escaped!\n";
                battleOver = true;
            }
            else
            {
                cout << "\nYou failed to escape!\n";
                int enemyDamage = enemy.getAttackDamage();
                cout << "The " << enemy.getName()
                     << " attacks you for " << enemyDamage << " damage!\n";
                player.takeDamage(enemyDamage);
            }
        }
        else
        {
            cout << "\nInvalid choice. Please choose 1 or 2.\n";
        }
    }

    if (!enemy.isAlive())
    {
        int foodReward = 3 + rand() % 6;
        cout << "\n==============================\n";
        cout << "You defeated the " << enemy.getName() << "!\n";
        cout << "You found " << foodReward << " food.\n";
        cout << "==============================\n";
        player.addFood(foodReward);
    }

    if (!player.isAlive())
    {
        cout << "\n==============================\n";
        cout << "           GAME OVER\n";
        cout << "==============================\n";
        cout << "You were defeated by the " << enemy.getName() << ".\n";
    }
}

void explore(Farmer& player, const vector<Monster>& monsters)
{
    int energyCost = 10;

    if (!player.useEnergy(energyCost))
    {
        cout << "\nYou do not have enough energy to explore.\n";
        cout << "Try resting first.\n";
        return;
    }

    cout << "\nYou leave your farm and explore the wilderness...\n";
    cout << "-" << energyCost << " energy\n";

    int eventChance = rand() % 100;

    if (eventChance < 30)
    {
        int foodFound = 2 + rand() % 7;
        cout << "\nYou found an abandoned supply crate!\n";
        cout << "You gained " << foodFound << " food.\n";
        player.addFood(foodFound);
    }
    else
    {
        if (monsters.empty())
        {
            cout << "\nYou explored the wilderness, but found nothing.\n";
        }
        else
        {
            int randomIndex = rand() % monsters.size();
            Monster enemy = monsters[randomIndex];
            battle(player, enemy);
        }
    }

    player.nextDay();
}

int main()
{
    srand(time(0));

    cout << "================================\n";
    cout << "       WELCOME TO FARM SURVIVAL\n";
    cout << "================================\n";

    string playerName;
    cout << "Enter your farmer's name: ";
    getline(cin, playerName);

    if (playerName.empty())
    {
        playerName = "Farmer";
    }

    Farmer player(playerName);
    vector<Monster> monsters = loadMonsters("monsters.txt");

    cout << "\nWelcome, " << player.getName() << "!\n";
    cout << monsters.size() << " monsters were loaded from monsters.txt.\n";

    int choice = 0;

    while (choice != 5 && player.isAlive())
    {
        cout << "\nCurrent Day: " << player.getDay() << endl;
        displayMainMenu();
        cin >> choice;

        if (choice == 1)
        {
            player.displayStats();
        }
        else if (choice == 2)
        {
            player.workOnFarm();
        }
        else if (choice == 3)
        {
            player.rest();
        }
        else if (choice == 4)
        {
            explore(player, monsters);
        }
        else if (choice == 5)
        {
            cout << "\nThanks for playing Farm Survival!\n";
            cout << "You survived for " << player.getDay() << " days.\n";
        }
        else
        {
            cout << "\nInvalid choice. Please choose 1 through 5.\n";
        }
    }

    if (!player.isAlive())
    {
        cout << "\nYou survived until day " << player.getDay() << ".\n";
        cout << "Better luck next time!\n";
    }

    return 0;
}
