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
using std::string;
using cinder::TextBox;
using namespace thuglib;

const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";

THUGApp::THUGApp()
    : terrain{},
      pixel_size_{kPixelSize},
      entity_block_size_{10},
      player_location_{kSpawnX, kSpawnY},
      terrainSurface(800, 800, cinder::SurfaceChannelOrder::RGBA),
      new_chunk_{true},
      player_{},
      draw_stats_{false} {}

void THUGApp::setup() {
    terrain.GenerateTerrain();
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
}

void THUGApp::update() {

}

void THUGApp::draw() {
    cinder::gl::clear();
    cinder::gl::enableAlphaBlending();
    DrawPlayer();
    DrawGameStats();
    DrawTerrain();
}

void THUGApp::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_F1) {
        draw_stats_ = !draw_stats_;
    }
    player_.UpdateLocation(event);
}

void THUGApp::DrawTerrain() {
    cinder::vec2 bounds = terrain.GetChunkBounds(player_.GetLocation());
    terrain.GenerateTerrain(bounds);

    int xstart = (int) bounds.x * kNumPixels;
    int ystart = (int) bounds.y * kNumPixels;
    int xend = kNumPixels * (1 + (int) bounds.x);
    int yend = kNumPixels * (1 + (int) bounds.y);

    for (int x = xstart; x < xend; x++) {
        for (int y = ystart; y < yend; y++) {
            float value = terrain.GetValue((x - xstart), (y - ystart));
            // Change color based on value, to make mountains and rivers and stuff
            if (value > .150) {
                cinder::gl::color(0, 0, 1 - value);
            } else if (value < .150 && value > .065) {
                cinder::gl::color(Color((1 - value) * (242/255.0), (1 - value) * 209/255.0, (1 - value) * 107/255.0));
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
    cinder::vec2 location = player_.GetLocation();
    cinder::gl::color(Color::white());
    // Render player location based on window coordinates, so we have to use %
    cinder::gl::drawSolidRect(Rectf( (int) location.x % kMapSize,
                                      (int) location.y % kMapSize,
                                     ((int) location.x % kMapSize) + kPlayerSize * pixel_size_,
                                     ((int) location.y % kMapSize) + kPlayerSize * pixel_size_));
}

// Code below derived from: CS126-SnakeApp
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
    cinder::gl::color(color);

    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 15))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x, loc.y};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}

void THUGApp::DrawGameStats() {
    if (draw_stats_) {
        cinder::vec2 location = player_.GetRelativePosition();
        cinder::vec2 coords = player_.GetLocation();
        cinder::vec2 size = {200,100};
        cinder::vec2 text_coords = {kMapSize - size.x, kMapSize - size.y};
        std::stringstream ss;
        // Build the string
        ss << "THUGS v.0.1\n"
        << "Coordinates:\n ("
        << coords.x << ", " << coords.y << ")\n"
        << "Health: "
        << player_.GetHealth() << "\n"
        << "Current Block Value: "
        << terrain.GetValue(location.x, location.y);
        PrintText(ss.str(), Color::white(), size, text_coords);
    }
}

}  // namespace thugapp
