# THUGS: The Half-Baked Unimportant Game (Singleplayer)

Author: Davis Keene

---
My final project idea is a massive singleplayer game similar to the likes of 'Terreria' or 'Minecraft'.
THUGS, or "The Half-Baked Unimportant Game (Singleplayer)", is a sandbox game that uses
procedural terrain generation to give a player an infinite world to explore. Randomly generated are small merchants, items,
mobs and side-games that allows your character to build his/her xp. The ultimate goal of the game is to
find and defeat the boss, at which point you will have completed the game.

LIBRARIES:
Since this is going to be created using Cinder, I figured that I should take advantage of c++ game libraries to make this task
easier on myself. One of the libraries I stumbled upon is libnoise, a library that produces all sorts of random noise, including Perlin Noise 
(which is common in game design for procedural terrain).

(Ended up going with FastNoise, a C++ Library for generating various noise types.)

I also plan on using OpenGL (cinder::gl) for graphics processing.

I'm currently using Ubuntu 16/19.04 (16 on my desktop, 19 on my laptop), and both libraries are compatible with my system. 

MOTIVATION/BACKGROUND:

I have had experience with game design before, namely in Unity 3D with C#, but I've never done a project that involves procedural terrain. I figured that this is a good opportunity to
step out of my comfort zone a little bit and work on developing a fun and endless 2D singleplayer game. Prior to this project, I've made 3D quizlet games 
using unity plugins and other small VR apps, so making a 2D singleplayer game with objectives and therefore shouldn't be too unattainable for my skillset.
We've also accomplished a similar objective with Amazing Adventures earlier this year, except that was using a schema to display worlds. In this project, I hoped to generate
the terrain automatically.

A rough timeline for what I hope to accomplish is as follows:

Week 1: By the end of the first week, I hope to have procedural terrain generation completed. I also hope to have a character that can traverse procedurally generated terrain and move in cardinal directions.

Week 2: By the end of the second week, I hope to have finished creating interactive game components, such as merchants, mobs and the final boss.

Week 3: By the end of the project, I hope to have a database set up to store player data. Players can sign in and use their own accounts, and (hopefully) save their game progress. This would be done through either firebase or
running a c++ native socket server.

Should I finish this project early, I want to try to get a server system set up for multiple players to interact with each other online. I think it would also be cool to allow players to adjust the terrain by digging or building.
This would prompty turn the game into THUGSWIM (The Half-Baked Unimportant Game, Singleplayer with Interesting Multiplayer).

It would also be interesting to add bots into the game, or to use some sort of reinforcement learning algorithm to get the bots to beat the game in as little time as possible.