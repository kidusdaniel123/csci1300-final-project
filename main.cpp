#include <iostream>
#include <string>
#include "Farmer.h"
#include "Monster.h"
using namespace std;

void displayMenu() {
    cout << "\n=== Farm Survival ===" << endl;
    cout << "1. View player stats" << endl;
    cout << "2. Work on farm" << endl;
    cout << "3. Rest" << endl;
    cout << "4. Explore" << endl;
    cout << "5. Quit" << endl;
    cout << "Enter choice: ";
}

int main() {
    string playerName;
    cout << "Welcome to Farm Survival!" << endl;
    cout << "Enter your farmer's name: ";
    getline(cin, playerName);

    if (playerName.empty()) playerName = "Farmer";

    Farmer player(playerName);
    bool running = true;

    while (running && player.isAlive()) {
        displayMenu();

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\nPlayer: " << player.getName() << endl;
            cout << "Health: " << player.getHealth() << endl;
            cout << "Energy: " << player.getEnergy() << endl;
            cout << "Crops: " << player.getCrops() << endl;
        }
        else if (choice == 2) {
            if (player.workOnFarm())
                cout << "You worked on the farm and harvested 5 crops." << endl;
            else
                cout << "You do not have enough energy. Try resting first." << endl;
        }
        else if (choice == 3) {
            player.rest();
            cout << "You rested and recovered energy and health." << endl;
        }
        else if (choice == 4) {
            Monster slime("Slime", 30, 10);
            cout << "You explored the fields and encountered a "
                 << slime.getName() << "!" << endl;

            slime.attack(player);

            cout << "The " << slime.getName()
                 << " attacked you for "
                 << slime.getAttackPower()
                 << " damage." << endl;

            cout << "Your health is now "
                 << player.getHealth() << "." << endl;
        }
        else if (choice == 5) {
            running = false;
            cout << "Thanks for playing!" << endl;
        }
        else {
            cout << "Invalid choice. Please choose 1 through 5." << endl;
        }
    }

    if (!player.isAlive()) {
        cout << "Your farmer ran out of health. Game over." << endl;
    }

    return 0;
}
