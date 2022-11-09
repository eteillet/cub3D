## cub3D
##### _My first RayCaster with miniLibX_
---
This project is inspired by the famous Wolfenstein 3D game which was the first FPS ever.
So the goal is to reproduce a basic FPS game by using the raycasting method.

#### A few words about raycasting ?
* It's a rendering technique capable of creating a 3D perspective using a 2D map.
* Ray casting is fast, as only a single computation is needed for every vertical line of the screen. This is one of the reasons why ray casting was the most popular rendering tool in early 3D video games.
* Main steps:
    1. The raycasting is capable of transforming a 2D map into a 3D projection by casting a ray for each pixel column. For example, if your window has a resolution of 640x480, we will cast 640 rays that starts at the player location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen.
    2. We then seek to know where they encounter an obstacle.
    3. we then calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen: the further away the wall, the smaller it's on screen, and the closer, the higher it appears to be.


#### Usage: 
* ``make && ./cub3d maps/map1.cub``

#### Ressources:
* https://fr.wikipedia.org/wiki/Raycasting
* https://lodev.org/cgtutor/raycasting.html
* https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
* http://www.playfuljs.com/a-first-person-engine-in-265-lines/
* http://users.atw.hu/wolf3d/

***

![](https://github.com/eteillet/cub3D/blob/main/screenshots/map1.png)
![](https://github.com/eteillet/cub3D/blob/main/screenshots/map4.png)
![](https://github.com/eteillet/cub3D/blob/main/screenshots/map5.png)
