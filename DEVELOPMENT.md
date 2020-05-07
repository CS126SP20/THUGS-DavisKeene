# Development
---

- <i> 4/18/20 </i>

  - Added FastNoise library to project for terrain generation.
  - TODO:
    - [x] Add OpenGL to project, create basic map visual.
    - [x] Learn how FastNoise generates noise.
    - [x] Add noise to basic visual, color code based off of pixel color.

- <i> 4/19/20 </i>

  - Generated terrains for the first time!
  - Experimented with different RGB values and good float cutoff values to generate hills and lakes.
  - TODO:
    - [x] Further experiment with constants for terrain generation.
    - [x] Experiment with different types of noise for the best terrain.
    - [x] Add a character into the game that can "walk" around on the terrain.
    
  - Roadblocks
    - Having trouble with getting a character to be drawn on screen. Calling the draw function on the image of a player, but they're not
    rendering on screen. Will consult office hours tomorrow and ask on piazza.
    - Rendering was taking quite a while, so I had to scale back on the detail in order to make sure the framerate was optimal.
    
- <i> 4/20/20 </i>

  - Made player able to walk around the terrain!
  - Made a player class, with methods to get and update player location_ based on KeyEvent.
  - [X] Figured out bug when rendering player: needed to call DrawPlayer() first.
  - [X] Figured out how to optimize framerate when generating terrain
    - BREAKTHROUGH 4/21/20 1:12AM
      - Figured out how to change the frequency of the noise by reading the lib's documentation.
      - From this, I figured I can increase the frequency and decrease the number of pixels by the same scale factor to get
      semi-detailed terrains with only a fifth of the actual pixels.
      - This strategy ended up working super well! Game framerate is playable, although I'll experiment with a few other settings, and the terrains are increasingly fun to 
      walk through!
  - [X] Figured out how to load chunk when player walks off screen.
  
- <i> 4/21/20 </i>

    - Figured out the main tradeoff fix for rendering the terrain!
        - I was stuck on deciding whether to render many pixels or fewer pixels for a good terrain detail, but then I realized that
        I could increase the noise frequency at the same rate that I decrease the number of pixels for a
        lower res high frequency terrain. Solution works great and actually looks a lot like a real terrain plot!
  
- <i> 4/27/20 </i>

    - Haven't had a good dev day on this project in a while, so today will just be playing around with mob generation
and see if we can get player speed to vary depending on the current biome they're in.
    - Thinking about making a player image instead of a rectangle, with included walking animation.
    - Also need to figure out the best way to bound the world, and deploy game objective (ie. collect items to win)
    - Accomplished Today:
        - [x] Player moves at different speeds on different terrains
        - [x] Player cannot move past the world boundaries specified.
        - [x] Terrain deteriorates over 5 minutes, leading into the game objective (save the world).
        - [x] Player movement fix: user can press keystroke to change direction of player. Double click to stop them from moving.
        
- <i> 5/4/20 </i>

    - Been completely swamped with final project work for CS 199-KT and Stats homework, but getting back to the grind today.
    - My last commit had a few new changes, and this time around I plan to improve the game objective.
    - PIVOT: THUGS is no longer an open-world type game.
        - I thought that I would have enough time to create a game similar to minecraft, but I have to pivot to make my goals more realistic given my timeframe.
        - New challenge: Save The World!
            - The world is dying, and it's up to the player to save the world by collecting ingredients to an antidote to cure the land.
            - The players' score is determined on how fast they gather the ingredients to beat the game.
            - Player information should be stored on a database.
    - TODO:
        - [x] Add homescreen to give player instructions
        - [x] Make antidote items spawn on the map
        - [x] Allow the player to pick up antidote ingredients
        - [x] Make the players' health go down from certain events (swimming, mobs, etc.)
        - [x] End the game if the player gets all of the ingredients, or if they run out of time.
        - [x] Set up "doctors" that can give hints on the nearest antidote locations. (MAPS)
        
- <i> 5/5/20 </i>

    - Finished everything from 5/4/20 Checklist aside from adding doctors.
    - TODO
        - [x] Use random seed as currentTime for making randomness, or use random c++ library instead of rand().
        - [x] Add MAPS (some sort of entity that can point the user in the right direction).
        - [x] (Maybe) Add mobs like zombies or something that can harm the player if the player walks into them.
        - [x] Clean up some magic numbers and other pieces of the code that could look nicer.
    - Added maps which point the user to the closest ingredient for 5 seconds.
        - As of right now, maps and ingredients belong only to the terrain, and are not in their own separate classes.
        I'll probably fix this later, assuming I have time. Otherwise, I think it's still logical for these items to be
        a part of the terrain because they are objects that spawn on the terrain only.
        
- <i> 5/6/20 </i>

    - Having an aggravating issue trying to add Mobs as their own class. May have to do the same thing as I am with ingredients and maps, and have them
    just as static members of the terrain instead of decomposing them as their own objects. Really frustrating, especially since the deadline is close and
    I practically have the project finalized.
        - Issue resolved for now- putting the Mob.h contents into Terrain.h seems to be a workaround for the time being.
        - [x] Issue fixed! Re-created Mob.h file, seems to be working smoothly for now.
    - TODO
        - [x] Clean up code, add more comments and remove unnessecary / buggy fixes.
        - [x] Make beginning and end messages more descriptive.
        - [x] Add sound effects to game, perhaps make it slightly more interactive and/or interesting somehow before deadline.
    - Added everything I said I would, not much left to do for the project! Going to maybe clean up some visuals for the text boxes, but other than
    that I think everything turned out as good as I wanted it to.