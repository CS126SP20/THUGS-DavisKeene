// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>


namespace thugapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::gl::Texture;

THUGApp::THUGApp()
    : terrain{},
    pixel_size_{mylibrary::kPixelSize},
    entity_block_size_{10},
    player_location_{mylibrary::kSpawnX, mylibrary::kSpawnY},
    terrainSurface(800, 800, cinder::SurfaceChannelOrder::RGBA),
    new_chunk_{true} {}

void THUGApp::setup() {
    terrain.GenerateTerrain();
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
}

void THUGApp::update() {

}

void THUGApp::draw() {
    cinder::gl::enableAlphaBlending();
    cinder::gl::clear();
    DrawTerrain();
    DrawPlayer();
}

void THUGApp::keyDown(KeyEvent event) { }

void THUGApp::DrawTerrain() {
    for (int x = 0; x < mylibrary::kNumPixels; x++) {
        for (int y = 0; y < mylibrary::kNumPixels; y++) {
            float value = terrain.GetValue(x, y);
            // Change color based on value, to make mountains and rivers and stuff
            if (value > .150) {
                cinder::gl::color(0, 0, 1 - value);
            } else {
                cinder::gl::color(80/255.0, (1 - value)*(1/1.20), 0);
            }
            cinder::gl::drawSolidRect(Rectf(pixel_size_ * x,
                    pixel_size_ * y,
                    pixel_size_*x + pixel_size_,
                    pixel_size_*y + pixel_size_));
        }
    }

}

void THUGApp::DrawPlayer() {
    const cinder::vec2 center = getWindowCenter();
//    auto player_image_ref = cinder::loadImage(cinder::app::loadAsset("man.png"));
//    player_img = cinder::gl::Texture2d::create(player_image_ref);
//    cinder::gl::draw(player_img, Rectf(center.x, center.y, center.x + 50, center.y + 50));
}

}  // namespace thugapp
