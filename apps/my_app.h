// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/Surface.h>
#include <mylibrary/Terrain.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>
#include <cinder/Color.h>
#include <cinder/audio/Voice.h>


namespace app {

class THUGApp : public cinder::app::App {
    // Color constants
    float kBlueThreshold = .150f;
    float kSandThreshold = .065f;
    // Sand Constants
    float kSandRed = 242/255.0f;
    float kSandGreen = 209/255.0f;
    float kSandBlue = 107/255.0f;
    // Grass Constants
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
    cinder::ImageSourceRef ref = cinder::loadImage(cinder::app::loadAsset("man_2.png"));
    cinder::gl::Texture2dRef player_icon_ = cinder::gl::Texture2d::create(ref);
    // Map image
    cinder::ImageSourceRef map_ref = cinder::loadImage(cinder::app::loadAsset("map.png"));
    cinder::gl::Texture2dRef map_icon_ = cinder::gl::Texture2d::create(map_ref);
    // Restarts the game
    void ResetGame();

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
    terrain::Terrain terrain_;
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
    const std::chrono::seconds world_end_ = std::chrono::seconds(60 * 4); // 4 minutes
    // Constant number of seconds that the hint stays on screen
    const std::chrono::seconds hint_end_ = std::chrono::seconds(5); // 5 seconds
    // Sounds
    cinder::audio::VoiceRef bg_music_;
    cinder::audio::VoiceRef collision_noise_;
    cinder::audio::VoiceRef map_noise_;
    cinder::audio::VoiceRef ingredient_noise_;
    cinder::audio::VoiceRef victory_noise_;
    cinder::audio::VoiceRef loss_noise_;



    // Ratio of how much the terrain has decayed
    float world_decay_;
    // Player in the game
    player::Player player_;
    // Boolean to trigger drawing game stats
    bool draw_stats_;
    // Boolean to trigger start of game
    bool has_started_;
    // Has the player won the game?
    bool game_won_;
    // Is the game over?
    bool game_over_;
    // Boolean to trigger showing hint from map
    bool show_hint_;
    // Boolean to trigger collision
    bool collision_;
    // Starting index for cycling through antidote images
    int image_index_ = 1;
};

}  // namespace app

#endif  // FINALPROJECT_APPS_MYAPP_H_
