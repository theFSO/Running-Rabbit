# Team 17 3GC3 Project

## How to run
Simple download everything from the repo.(be aware of directory, main.cpp is not in the src) Make sure you are in the same directory as makefile. Then just type 'make'.

## Description
This is a Parkour game similar to Chameleon Run, which requires concentration and agility.  
The Basic idea is that you can control a player to run on the lanes. You are able to control the player to switch between the three lanes.  
The color of the lanes and obstacles generated ahead may be in three different colors. You can change the color of the player by pressing number keys. The player has in total three health points. Each time the color of player is not the same as the lane it is on, it will lose one health point. When the player hits an obstacle of the same color from it, it will directly pass through the obstacle. Otherwise, it will lose one health point. If the player loses all the health points, the game is over.  
The longer distance the player runs, the higher the score is.

## Content
This prototype includes the following:
• The obj file of the player.  
• The *.obj file parser.  
• The obj file of the player.  
• An object class, which is a general class of player, obstacle and lane.  
• A player class.  
• An obstacle class.  
• A lane class.  
• A utility class.  
• A light class.  
• Basic keyboard controls.

## Interface
| Command  | Description  |
|---|---|
| q, Q  | quit  |
| p, P  | pause the game  |
| r, R  | restart the game  |
| a, A, left arrow  | move the player to the left lane |
| d, D, right arrow  | move the player to the right lane  |
| n, N | change to first person view |
| l, L | enable light |
| space  | jump  |   
| 1  | change the player's color to red  |   
| 2  | change the player's color to green  |   
| 3  | change the player's color to blue  |   

## Notice:
First person view is not good for playing.

## Project References: 
cat obj: https://free3d.com/3d-model/cat-v1--522281.html  
Cube.obj: referred from www.blender.org.  
PPM loader from tutorial files.
