# Projet Tower Defense

![Image](assets/textures/Marie-Antoine.png)

This project's goal is to create a *Tower Defense* game in 2D written in C++. 

In this game, you have to defend a base against waves of enemies that follow a road.
To acheive this goal, you have different types of tower which you can place on the map.
These towers will attack this enemies et kill them before they can reach your base.
If the enemies reach the base, it is damaged and if too many of them reach it, you lose.
Your goal is to survive 25 waves without having your base destroyed.

This game was made by **Quentin Lepine, Umut Osmanoglu and Antoine Mordant** with raylib library.

---
# Introduction's cinematic
>*Left-click* to skip it.

---
# Main menu

After the cinematic, you arrive in the `Main Menu`. You have 4 options :

## Play
You open the `Menu Play`.

## Options
You open the `Options` where you can adjust the **sound** of the game and the **difficulty**.

## Credits
You open the `Credits`.

## Exit
You leave the game.

## Easter eggs
*Left-click* on our logo in the bottom right corner of the menu to **play again** the introduction's cinematic.

*Left-click* on the sun in the background to launch a music **a bit special**.

![Image](assets/textures/Marie-Antoine.png)


---
# Play Menu
## New
You open the `Level selection Menu`.

## Load
You open the `Load Menu` where you can **load your own map**.

## Editor
You open the `Map editor` where you can **create your own map**.

## Return
You come back in the `Main menu`.


# Level selection Menu
You have **10 different levels** that you can test.

You also can go in the `Custom maps Menu` where you can play on your **home made maps**.

When you have selected the map you want to play with, you enter the **game**.


# Gameplay
In this game, you must defend your base represent by the green building of the enemies that come from the red building.
Different enemies will attack your base :
- the **Classic**, not really resistant, medium speed
- the **Big**, really resistant, slow
- the **Healer**, vulnerable, fast, **heal** others enemies around him

>The enemies become more and more **stronger** with time

>For those who survive enough to see the end, **be careful**, a **terrifying shadow** flies over the battlefield...

To place towers, you must first choose between your 3 towers :
- the **Classic**, cheap, low damage, quick attack speed
- the **Slowing**, really low damage but **slow** the enemy on hit, medium attack speed
- the **Explosive**, expensive, high damage in explosion, slow attack speed

>If you don't have **enough money** to buy it, you can't place it.

Once you chose your tower, *left-click* on its image in the right side of the screen, *maintain your click* and *release it* when your cursor is on the place you want to place your tower.

Once your towers are on the battlefield, you can **upgrade** them. 
For that, left click on a tower. It will open the upgrade menu in the right side of the screen.
You have now the option to upgrade your tower and its cost and to delete this tower. This last option will give you back a part of the money you used to buy and upgrade this tower.
To leave this menu, you just have to click on any tile of the map since it doesn't have a tower on.

You can set the speed of the game with the direction arrows. The right one will increase it and the left one will slow it.

>You can accelerate the game to x16 or you can stop the game while putting it in x0. It allows you to place, delete or upgrade towers without care of the waves.

In the bottom right corner, you can open the pause menu. It will stop the game and you will have 3 options:
- **Return** : come back to the game.
- **Option** : go in the option where you can adjust the sound.
- **Main menu** : Come back to main menu. It will erase your current game.

# Map Editor
You have here all the tools to make your own map.
For that, you have three different categories of tiles :
- **Terrain** :  You can choose between grass and sand.
- **Road element** : You have the road with all building : enemies spawn, player base and tunnels. 
>You can have **only one enemies spawn and one player base**.
- **Decoration** : trees, scrap ect to make your map greater.

To place element in the map, you just have to select it with *left click* on it in the pannel on the left side.
The selected element will surrounded by red anf you just have to *left-click* where you want to put it on the map. 

>You cannot place Decoration on Road element and if you place Road element on Decoration, it will **erase** it.

Place the road has a special functioning : you must *maintain the click* and draw the road that you want. To erase it, this is the same.

For the Decoration, if you *right-click* on it, it will **change** its **style**.

# Sources

