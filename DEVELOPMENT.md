# Development
---

- <i> 4/18/20 </i>

  - Added FastNoise library to project for terrain generation.
  - TODO:
    - Add OpenGL to project, create basic map visual.
    - Learn how FastNoise generates noise.
    - Add noise to basic visual, color code based off of pixel color.

- <i> 4/19/20 </i>

  - Generated terrains for the first time!
  - Experimented with different RGB values and good float cutoff values to generate hills and lakes.
  - TODO:
    - Further experiment with constants for terrain generation. [X]
    - Experiment with different types of noise for the best terrain. [X]
    - Add a character into the game that can "walk" around on the terrain. []
    
  - Roadblocks
    - Having trouble with getting a character to be drawn on screen. Calling the draw function on the image of a player, but they're not
    rendering on screen. Will consult office hours tomorrow and ask on piazza.
    - Rendering was taking quite a while, so I had to scale back on the detail in order to make sure the framerate was optimal.