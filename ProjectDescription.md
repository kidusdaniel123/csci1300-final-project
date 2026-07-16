# Project Planning — Farm Survival: The Final Bundle

## 1. Classes

1. `Character`
2. `Farmer`
3. `Item`
4. `Villager`
5. `Monster`
6. `Game`

## 2. Class Descriptions

- **Character:** Base class for characters with a name and health.
- **Farmer:** The player. Manages resources, time, location, and inventory.
- **Item:** Represents collectible inventory objects and bundle categories.
- **Villager:** Represents meaningful NPCs who provide dialogue and rewards.
- **Monster:** Represents enemies that may appear in the mines.
- **Game:** Runs the game loop and manages the map, bundle, menus, and endings.

## 3. Important Member Variables

### Character

- `name`
- `health`
- `maxHealth`

### Farmer

- `energy`, `maxEnergy`
- `money`
- `day`, `maxDays`
- `actionsRemaining`
- `friendship`
- `jojaInfluence`
- `currentLocation`
- `vector<Item> inventory`

### Item

- `name`
- `type`
- `value`
- `bundleItem`
- `energyRestore`

### Villager

- `name`
- `location`
- `role`
- `dialogue`
- `Item reward`
- `interacted`

### Monster

- `attackDamage`

### Game

- `Farmer player`
- `vector<Villager> villagers`
- `vector<Monster> monsters`
- `vector<Item> bundleItems`
- `vector<bool> bundleDonated`
- `quitGame`
- `currentWeather`

## 4. Important Member Functions

### Farmer

- `spendEnergy()`
- `restoreEnergy()`
- `spendMoney()`
- `useAction()`
- `endDay()`
- `moveTo()`
- `addItem()`
- `hasItemType()`
- `removeItemType()`
- `displayInventory()`

### Villager

- `interact()`

### Game

- `run()`
- `displayDashboard()`
- `displayMap()`
- `moveMenu()`
- `performLocationAction()`
- `donateItems()`
- `buyMissingBundleItem()`
- `battle()`
- `displayEnding()`
- `generateWeather()`
- `displayBundlePlanner()`

## 5. Game Loop

1. Display the formatted dashboard and map.
2. Ask the player for a menu choice.
3. Move, take a location action, view information, end the day, or quit.
4. Update energy, money, inventory, actions, friendship, or bundle progress.
5. Automatically end a day after three actions.
6. Continue until the player completes the bundle, runs out of days, loses all health, or quits.
7. Display an ending and final score.

## 6. Terminal UI and Map Sketch

```text
====================================================
              THE FINAL BUNDLE
====================================================
Day: 3 / 10    Actions: 2 / 3
Health: 100    Energy: 70    Money: 65g
Location: Town Square
Bundle Progress: 2 / 5

                         [Mines]
                              |
[Farm] -- [*Town Square] -- [Community Center] -- [Beach]
    |              |                    |
[Forest]   [Marnie's Ranch]        [JojaMart]
====================================================
```

## 7. Characters and Interactions

- **Mayor Lewis:** Explains the final objective and gives 15g.
- **Willy:** Gives a Sunfish.
- **Linus:** Gives a Wild Horseradish.
- **Clint:** Gives Copper Ore.
- **Marnie:** Gives an Egg.
- **Morris:** Sells shortcuts that increase Joja Influence.

## 8. Items and Bundle Requirements

Required categories:

- Crop — example: Parsnip
- Fish — example: Sunfish
- Mineral — example: Copper Ore
- Animal Product — example: Egg
- Forage — example: Wild Horseradish

## 9. Win and Loss Conditions

- **Win:** Donate all five categories by the end of Day 10.
- **Loss:** Enter Day 11 without completing the bundle or lose all health.
- **Different endings:** Community Hero, Restored Center, Joja Shadow, Almost There, Season Over, Defeat, or Early Departure.

## 10. Extra Credit Plan

### Option 4 — Weather System (+5)

The game creates Sunny, Rainy, or Stormy weather each day. Weather changes farming energy cost, bonus crop chance, fishing energy cost and success chance, forage rewards, and mine availability.

### Option 6 — Smarter Bundle Planner (+6)

The planner checks donated bundle categories and the player inventory, then recommends the best location or interaction for each missing item. It also changes advice based on the current weather and warns about Joja Influence.
