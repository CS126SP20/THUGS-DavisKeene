// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/Terrain.h>
#include <cinder/gl/gl.h>


namespace thugapp {

class THUGApp : public cinder::app::App {
 public:
  THUGApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
    void DrawTerrain();
    void DrawPlayer();
    void ResetGame();


private:
    mylibrary::Terrain terrain;
    const size_t pixel_size_;
};

}  // namespace thugapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
