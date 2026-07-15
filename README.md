# CSCI 1300 Final Project - Farm Survival

Farm Survival is a text-based survival game written in C++. The player controls a farmer who manages health, energy, food, and crops while surviving as many days as possible.

## Features

- Interactive main menu and game loop
- Farming, resting, exploration, and combat
- Health, energy, food, crops, and day progression
- Three classes: Character, Farmer, and Monster
- Inheritance: Farmer and Monster inherit from Character
- File input from `monsters.txt`

## Compile

```bash
g++ -std=c++17 main.cpp Character.cpp Farmer.cpp Monster.cpp -o game
```

## Run

```bash
./game
```
