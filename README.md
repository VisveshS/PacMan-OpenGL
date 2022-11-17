# PACMAN inspired game


![Image of Yaktocat](https://raw.githubusercontent.com/VisveshS/PacMan-OpenGL/master/20171133_Assign1/pm1.png)

Recursively randomly generated maze:

![Image of Yaktocat](https://raw.githubusercontent.com/VisveshS/PacMan-OpenGL/master/20171133_Assign1/maze.png)

<u>compiliing:</u>

`make all` &rarr; compile

`make clean` &rarr; cleans directory

`./ssignment1` &rarr; execute

<u>controls:</u>

 * arrow-keys &rarr; movement
 * + &rarr; zoom in
 * &rarr; zoom out
 * &rarr; default zoom

<u>Features:</u>

* Randomly generated realistic maze whose complexity is given by user and is
guarenteed to have a path between start and finish

 * Enemy that behaves randomly when away from player but follows players movement
when player comes right next to the enemy

 * lighting up only the surroundings of the player and light's range decreases with time

 * batteries to recharge light (lightning symbol) → recharges player's torch

 * coins (yellow circles) → increases points

 * obstacles (warning symbol) → decreases player health

 * first aid (red cross symbol) → repairs health

 * gods eye view powerup (eye of providence symbol) → shows the entire illuminated maze for a few seconds

 * <u>scoreboard</u>

    * health bar (orange)

    * torch battery charge bar(blue)

    * coin collection count (in digital form)

    * time left after enabling god's eye view powerup (appears at bottom right after
aquiring powerup: looks like pie-chart)
