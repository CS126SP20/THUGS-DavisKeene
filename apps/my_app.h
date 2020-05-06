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
    float kBlueThreshold = .150;
    float kSandThreshold = .065;
    // Sand
    float kSandRed = 242/255.0;
    float kSandGreen = 209/255.0;
    float kSandBlue = 107/255.0;
    // Grass
    float kGrassRedValue = 30/255.0;
    float kGrassRedShift = 80/255.0;
    float kGrassGreenRatio = (1/1.20);
    float kGrassGreenDecayRatio = .85;


 public:
  THUGApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  // Person image
    cinder::ImageSourceRef ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/man.png");
    cinder::gl::Texture2dRef icon = cinder::gl::Texture2d::create(ref);

    cinder::ImageSourceRef map_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/map.png");
    cinder::gl::Texture2dRef map_icon = cinder::gl::Texture2d::create(map_ref);



private:
    void DrawTerrain();
    void DrawPlayer();
    void DrawGameStats();
    void toggleDrawGameStats();
    void drawInstructions();
    void DrawAntidotes();
    void ResetGame();
    void DrawGameOver();
    void DrawMaps();
    cinder::Color GetPixelColor(float value);

private:
    thuglib::Terrain terrain;
    const size_t pixel_size_;
    std::chrono::time_point<std::chrono::system_clock> last_time_;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    std::chrono::time_point<std::chrono::system_clock> hint_start_time_;
    std::chrono::seconds world_end = std::chrono::seconds(60 * 5); // 5 minutes
    std::chrono::seconds hint_end = std::chrono::seconds(5); // 5 seconds
    float world_decay_;
    const size_t entity_block_size_;
    cinder::vec2 player_location_;
    cinder::Surface8u terrainSurface;
    bool new_chunk_;
    thuglib::Player player_;
    bool draw_stats_;
    bool has_started_;
    bool game_won_;
    bool game_over_;
    bool show_hint_;
    int image_index_ = 1;
};

}  // namespace thugapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
