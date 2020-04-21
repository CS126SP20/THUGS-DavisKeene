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
    cinder::vec2 bounds = terrain.GetChunkBounds(steve_.GetLocation());
    terrain.GenerateTerrain(bounds);

    int xstart = (int) bounds.x * thuglib::kNumPixels;
    int ystart = (int) bounds.y * thuglib::kNumPixels;
    int xend = thuglib::kNumPixels * (1 + (int) bounds.x);
    int yend = thuglib::kNumPixels * (1 + (int) bounds.y);

    for (int x = xstart; x < xend; x++) {
        for (int y = ystart; y < yend; y++) {
            float value = terrain.GetValue((x - xstart), (y - ystart));
            // Change color based on value, to make mountains and rivers and stuff
            if (value > .150) {
                cinder::gl::color(0, 0, 1 - value);
            } else {
                cinder::gl::color(80/255.0, (1 - value)*(1/1.20), 0);
            }
            cinder::gl::drawSolidRect(Rectf(pixel_size_ * (x - xstart),
                    pixel_size_ * (y - ystart),
                    pixel_size_* (x - xstart) + pixel_size_,
                    pixel_size_* (y - ystart) + pixel_size_));
        }
    }
}

void THUGApp::DrawPlayer() {
    // Get player location
    cinder::vec2 location = steve_.GetLocation();
    cinder::gl::color(Color::white());
    // Render player location based on window coordinates, so we have to use %
    cinder::gl::drawSolidRect(Rectf( (int) location.x % thuglib::kMapSize, (int) location.y % thuglib::kMapSize,
                                     ((int) location.x % thuglib::kMapSize) + 4*pixel_size_, ((int) location.y % thuglib::kMapSize) + 4*pixel_size_));
}

}  // namespace thugapp
