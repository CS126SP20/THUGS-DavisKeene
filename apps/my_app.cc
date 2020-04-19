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

THUGApp::THUGApp()
    : terrain{},
    pixel_size_{1} {}

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
}

void THUGApp::keyDown(KeyEvent event) { }

void THUGApp::DrawTerrain() {
    for (int x = 0; x < mylibrary::kMapSize; x++) {
        for (int y = 0; y < mylibrary::kMapSize; y++) {
            float value = terrain.GetValue(x, y);
            cinder::gl::color(0, 0, value);
            cinder::gl::drawSolidRect(Rectf(pixel_size_ * x,
                    pixel_size_ * y,
                    pixel_size_*x + pixel_size_,
                    pixel_size_*y + pixel_size_));
        }
    }

}

}  // namespace thugapp
