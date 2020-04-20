// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>


namespace thugapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::gl::Texture;

THUGApp::THUGApp()
    : terrain{},
    pixel_size_{thuglib::kPixelSize},
    entity_block_size_{10},
    player_location_{thuglib::kSpawnX, thuglib::kSpawnY},
    terrainSurface(800, 800, cinder::SurfaceChannelOrder::RGBA),
    new_chunk_{true},
    steve_{} {}

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
    DrawPlayer();
    DrawTerrain();
}

void THUGApp::keyDown(KeyEvent event) {
    std::cout << event.getCode() << std::endl;
    steve_.UpdateLocation(event);
}

void THUGApp::DrawTerrain() {
    for (int x = 0; x < thuglib::kNumPixels; x++) {
        for (int y = 0; y < thuglib::kNumPixels; y++) {
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
    cinder::vec2 center = steve_.GetLocation();
//    auto player_image_ref = cinder::loadImage(cinder::app::loadAsset("man.png"));
//    player_img = cinder::gl::Texture2d::create(player_image_ref);
//    cinder::gl::draw(player_img, Rectf(center.x, center.y, center.x + 50, center.y + 50));
    cinder::gl::color(Color::white());
    cinder::gl::drawSolidRect(Rectf(center.x, center.y,
            center.x + pixel_size_, center.y + pixel_size_));
}

}  // namespace thugapp
