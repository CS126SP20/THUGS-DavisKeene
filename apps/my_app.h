// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/Surface.h>
#include <mylibrary/Terrain.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>
#include <cinder/Color.h>


namespace thugapp {

class THUGApp : public cinder::app::App {
    // Color constants
    float kBlueThreshold = .150f;
    float kSandThreshold = .065f;
    // Sand
    float kSandRed = 242/255.0f;
    float kSandGreen = 209/255.0f;
    float kSandBlue = 107/255.0f;
    // Grass
    float kGrassRedValue = 30/255.0f;
    float kGrassRedShift = 80/255.0f;
    float kGrassGreenRatio = (1/1.20f);
    float kGrassGreenDecayRatio = .85f;


 public:
  THUGApp();
  // Set up game
  void setup() override;
  // Update variables each frame
  void update() override;
  // Draw each frame
  void draw() override;
  // Respond to keys being pressed
  void keyDown(cinder::app::KeyEvent) override;
  // Person image
    cinder::ImageSourceRef ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/man_2.png");
    cinder::gl::Texture2dRef icon = cinder::gl::Texture2d::create(ref);
    // Map image
    cinder::ImageSourceRef map_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/map.png");
    cinder::gl::Texture2dRef map_icon = cinder::gl::Texture2d::create(map_ref);



private:
    // Draw the procedurally generated terrain
    void DrawTerrain();
    // Draw the player on screen
    void DrawPlayer();
    // Display game stats after pressing F1
    void DrawGameStats();
    // Draw the beginning window to display instructions to user
    void DrawInstructions();
    // Draw the antidote ingredients on screen
    void DrawAntidotes();
    // Draw the game over screen, whether the user won or lost
    void DrawGameOver();
    // Draw the maps on screen
    void DrawMaps();
    // Draw mobs
    void DrawMobs();
    // Get color of pixel on terrain from value at that point
    cinder::Color GetPixelColor(float value);

private:
    // Terrain instance
    terrain::Terrain terrain;
    // Size of the pixels on screen
    const size_t pixel_size_;
    // Stores last time the player moved one pixel
    std::chrono::time_point<std::chrono::system_clock> last_time_;
    // Stores the time the player started the game
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    // Time player picked up a map
    std::chrono::time_point<std::chrono::system_clock> hint_start_time_;
    // Time we finished in
    std::chrono::time_point<std::chrono::system_clock> finish_time_;
    // Constant time player needs to finish by
    const std::chrono::seconds world_end = std::chrono::seconds(60 * 4); // 4 minutes
    // Constant number of seconds that the hint stays on screen
    const std::chrono::seconds hint_end = std::chrono::seconds(5); // 5 seconds
    float world_decay_;
    const size_t entity_block_size_;
    cinder::vec2 player_location_;
    cinder::Surface8u terrainSurface;
    bool new_chunk_;
    player::Player player_;
    bool draw_stats_;
    bool has_started_;
    bool game_won_;
    bool game_over_;
    bool show_hint_;
    bool collision_;
    int image_index_ = 1;
};

}  // namespace thugapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
