# CSCI 1300 Final Project — Farm Survival: The Final Bundle

## Theme

This is a single-player, text-based farming adventure inspired by *Stardew Valley*. The player is a new farmer helping restore the Community Center before the season ends.

## Goal

Complete the final Community Center bundle before Day 10 ends by donating:

- One Crop
- One Fish
- One Mineral
- One Animal Product
- One Forage Item

The player has three actions per day and must manage energy, health, money, friendship, inventory, and Joja Influence.

## How to Compile

Place all `.cpp`, `.h`, and `.txt` files in the same folder. Then run:

```bash
g++ -std=c++17 main.cpp Game.cpp Character.cpp Farmer.cpp Item.cpp Villager.cpp Monster.cpp -o game
```

## How to Run

Mac or Linux:

```bash
./game
```

Windows:

```text
game.exe
```

Run the game from the project folder so it can find `monsters.txt`.

## How to Play

The dashboard repeatedly displays:

- Current day and actions remaining
- Health, energy, and money
- Current location
- Friendship and Joja Influence
- Inventory size
- Bundle progress
- A text-based map

Use the main menu to move, take location actions, view inventory, view the bundle, end the day, or quit.

### Locations

- **Farm:** Harvest crops or rest
- **Town Square:** Talk to Mayor Lewis or sell items
- **Forest:** Forage or talk to Linus
- **Beach:** Fish or talk to Willy
- **Mines:** Mine, fight monsters, or talk to Clint
- **Marnie's Ranch:** Talk to Marnie
- **Community Center:** Donate bundle items
- **JojaMart:** Buy shortcuts that increase Joja Influence

### Weather System — Extra Credit Option 4 (+5)

Weather changes each day between Sunny, Rainy, and Stormy. It has real gameplay effects:

- Sunny days lower farming energy cost and may produce a bonus crop.
- Rainy days lower fishing energy cost, improve fishing odds, and may reveal bonus forage.
- Stormy days make fishing harder and close the mine entrance for mining.

### Smart Bundle Planner — Extra Credit Option 6 (+6)

The main menu includes a Smart Bundle Planner. It checks the player's inventory, donated categories, location options, and current weather. It recommends where to go and what action to take for every missing bundle category.

### Meaningful Characters

- **Mayor Lewis:** Explains the objective and gives starter money
- **Willy:** Gives the player a Fish
- **Linus:** Gives the player a Forage Item
- **Clint:** Gives the player a Mineral
- **Marnie:** Gives the player an Animal Product
- **Morris:** Offers Joja shortcuts with a long-term cost

## Classes

### Character

Base class containing a name, health, and functions for damage, healing, and checking whether the character is alive.

### Farmer

Inherits from `Character`. Stores player resources, location, time, and a `vector<Item>` inventory. This satisfies the requirement that one class stores objects of another class.

### Item

Stores an item's name, type, value, bundle status, and energy restoration value.

### Villager

Stores each villager's location, role, dialogue, reward, and interaction state. Villagers give meaningful gameplay rewards.

### Monster

Inherits from `Character`. Stores attack damage and is used for mine encounters.

### Game

Controls the game loop, menu system, locations, map, villagers, monsters, final bundle, Joja system, and endings.

## File Input

`Game::loadMonsters()` reads monster names, health, and damage values from `monsters.txt`. The loaded data is used during mine encounters.

## Win and Loss Conditions

- **Win:** Donate all five bundle categories before the season ends.
- **Loss:** Reach Day 11 without completing the bundle or lose all health.
- **Other ending:** Quit before completing the objective.

The final ending changes based on bundle progress, friendship, and Joja Influence.

## Extra Credit Features Attempted

- **Option 4: Weather System with Gameplay Effects (+5)**
- **Option 6: Smarter Bundle Planner (+6)**
- **Total pre-made extra credit attempted: 11 points**

## Other Extra Features

- Multiple endings
- Random fishing results
- Random mine encounters
- Combat
- Friendship system
- Joja Influence system
- Item selling
- Final score
- Help menu
- End-of-game summary
- File input
- Inheritance
