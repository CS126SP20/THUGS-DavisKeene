// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/Surface.h>
#include <mylibrary/Terrain.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>


namespace thugapp {

class THUGApp : public cinder::app::App {
 public:
  THUGApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  cinder::gl::Texture2dRef player_img;

private:
    void DrawTerrain();
    void DrawPlayer();
    void DrawGameStats();
    void toggleDrawGameStats();
    void ResetGame();


private:
    thuglib::Terrain terrain;
    const size_t pixel_size_;
    const size_t entity_block_size_;
    cinder::vec2 player_location_;
    cinder::Surface8u terrainSurface;
    bool new_chunk_;
    thuglib::Player player_;
    bool draw_stats_;
};

}  // namespace thugapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
