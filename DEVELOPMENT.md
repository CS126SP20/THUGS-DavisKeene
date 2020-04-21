# Development
---

- <i> 4/18/20 </i>

  - Added FastNoise library to project for terrain generation.
  - TODO:
    - Add OpenGL to project, create basic map_ visual.
    - Learn how FastNoise generates noise_.
    - Add noise_ to basic visual, color code based off of pixel color.

- <i> 4/19/20 </i>

  - Generated terrains for the first time!
  - Experimented with different RGB values and good float cutoff values to generate hills and lakes.
  - TODO:
    - Further experiment with constants for terrain generation. [X]
    - Experiment with different types of noise_ for the best terrain. [X]
    - Add a character into the game that can "walk" around on the terrain. [X]
    
  - Roadblocks
    - Having trouble with getting a character to be drawn on screen. Calling the draw function on the image of a player, but they're not
    rendering on screen. Will consult office hours tomorrow and ask on piazza.
    - Rendering was taking quite a while, so I had to scale back on the detail in order to make sure the framerate was optimal.
    
- <i> 4/20/20 </i>

  - Made player able to walk around the terrain!
  - Made a player class, with methods to get and update player location based on KeyEvent.
  - [X] Figured out bug when rendering player: needed to call DrawPlayer() first.
  - [X] Figured out how to optimize framerate when generating terrain
    - BREAKTHROUGH 4/21/20 1:12AM
      - Figured out how to change the frequency of the noise_ by reading the lib's documentation.
      - From this, I figured I can increase the frequency and decrease the number of pixels by the same scale factor to get
      semi-detailed terrains with only a fifth of the actual pixels.
      - This strategy ended up working super well! Game framerate is playable, although I'll experiment with a few other settings, and the terrains are increasingly fun to 
      walk through!
  - [X] Figured out how to load chunk when player walks off screen.