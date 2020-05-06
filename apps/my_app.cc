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
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
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
      draw_stats_{false},
      world_decay_{0.0},
      has_started_{false} {}

void THUGApp::setup() {
    terrain.GenerateTerrain();
    start_time_ = system_clock::now();
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
}

void THUGApp::update() {
    const auto time = system_clock::now();
    double terrainValue = terrain.GetValue(player_.GetRelativePosition().x, player_.GetRelativePosition().y);
    player_.SetSpeed(terrainValue);
    if (player_.IsMoving() && time - last_time_ > std::chrono::milliseconds(player_.GetSpeed())) {
        player_.UpdateLocation();
        last_time_ = time;
    }
    using std::chrono::milliseconds;
    const double elapsed_time =
            duration_cast<milliseconds>(system_clock::now() - start_time_)
                    .count();
    const double countdown_time = milliseconds(world_end).count();
    const double percentage = elapsed_time / countdown_time;
    world_decay_ = percentage;
    game_won_ = player_.GetInventorySize() == thuglib::kAntidoteIngredients;
    // Check to see if the time is up, or if we have won the game
    if ((duration_cast<milliseconds>(world_end - (system_clock::now() - start_time_))
                 .count()/1000 == 0) || game_won_) {
        game_over_ = true;
    }
}

void THUGApp::draw() {
    // Have to fake transparency because of cinder drawing
    cinder::vec2 location = player_.GetRelativePosition();
    float value = terrain.GetValue(location.x, location.y);
    cinder::gl::clear(GetPixelColor(value));
    cinder::gl::enableAlphaBlending();
    if (!has_started_) {
        drawInstructions();
    } else if (game_over_) {
        DrawGameOver();
    } else {
        DrawPlayer();
        DrawAntidotes();
        DrawGameStats();
        DrawTerrain();
    }
}

Direction KeyToDirection(const KeyEvent& event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_LEFT : {
            return Direction::LEFT;
        }
        case KeyEvent::KEY_RIGHT : {
            return Direction::RIGHT;
        }
        case KeyEvent::KEY_UP : {
            return Direction::UP;
        }
        case KeyEvent::KEY_DOWN : {
            return Direction::DOWN;
        }
    }
}

void THUGApp::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_F1) {
        draw_stats_ = !draw_stats_;
        return;
    }
    if (!has_started_) {
        has_started_ = !has_started_;
        terrain.GenerateAntidotes();
        start_time_ = system_clock::now();
    }
    Direction d = KeyToDirection(event);
    if (d == player_.GetDirection() || !player_.IsMoving()) {
        player_.ToggleMovement();
    }
    player_.SetDirection(d);
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
            cinder::gl::color(GetPixelColor(value));
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
    cinder::gl::draw(icon, Rectf( (int) location.x % kMapSize,
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

template <typename C>
void PrintTextMenu(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
    cinder::gl::color(color);

    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 20))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}

void THUGApp::DrawGameStats() {
    if (draw_stats_) {
        using std::chrono::milliseconds;
        cinder::vec2 location = player_.GetRelativePosition();
        cinder::vec2 coords = player_.GetLocation();
        cinder::vec2 size = {200,200};
        cinder::vec2 text_coords = {kMapSize - size.x, kMapSize - size.y};
        std::stringstream ss;
        // Build the string
        ss << "THUGS v.0.1\n"
        << "Coordinates:\n ("
        << coords.x << ", " << coords.y << ")\n"
        << "Health: "
        << player_.GetHealth() << "\n"
        << "Current Block Value: "
        << terrain.GetValue(location.x, location.y)
        << "\nCurrent Speed:\n"
        << player_.GetSpeed()
        << "\nTime Left\n"
        << (duration_cast<milliseconds>(world_end - (system_clock::now() - start_time_))
                .count()/1000)
                << "\nIngredients Left\n"
                <<kAntidoteIngredients - player_.GetInventorySize();
        PrintText(ss.str(), Color::white(), size, text_coords);
    }
}

void THUGApp::drawInstructions() {
    cinder::gl::clear(Color(0,0,0)); // Color screen black
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    PrintTextMenu("Hello, and welcome to THUGS: The Half-baked Unimportant Game (Singleplayer). Think minecraft and terreria from a top-down view.\n\n"
                  "The world is in danger! A deadly pathogen is killing the land, and it's up to you to stop it! You need to collect all 5 pieces of the antidote in order "
                  "to save the land and the world! Be speedy, because you have 5 minutes to collect the pieces before the terrain dies forever!\n\n"
                  "Antidote ingredients are scattered around the map, but are all visible among the terrain. Doctors will also spawn around the map, and can tell you "
                  "which direction to go to get to the closest ingredient. If you fail to collect all 5 ingredients by the end of the game, you lose!\n\n"
                  "Press any key to start your adventure.", color, size, center);
}

void THUGApp::DrawAntidotes() {
    std::vector<cinder::vec2> antidote_locations = terrain.AntidoteInChunk(player_.GetLocation());
    for (cinder::vec2 antidote_location : antidote_locations) {
        int relative_x = ((int) antidote_location.x % kMapSize) / kPixelSize;
        int relative_y = ((int) antidote_location.y % kMapSize) / kPixelSize;
        if (player_.GetRelativePosition().x == relative_x &&
        player_.GetRelativePosition().y == relative_y) {
            terrain.RemoveAntidote(antidote_location);
            player_.AddToInventory(antidote_location);
        }
        // Get random antidote image
        int random = rand() % 4;
        cinder::ImageSourceRef a_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/antidote-1.png");
        cinder::gl::Texture2dRef a_icon = cinder::gl::Texture2d::create(a_ref);
        cinder::gl::color(rand() % 2, rand() % 2, rand() % 2);
        cinder::gl::draw(a_icon, Rectf(pixel_size_ * (relative_x),
                                        pixel_size_ * (relative_y),
                                        pixel_size_ * (relative_x) + kPlayerSize * pixel_size_, // Make antidote ingredient same size as player
                                        pixel_size_ * (relative_y) + kPlayerSize * pixel_size_));
    }
}

void THUGApp::DrawGameOver() {
    cinder::gl::clear(Color(0,0,0)); // Color screen black
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 500};
    const Color color = Color::white();
    if (game_won_) {
        PrintTextMenu("Congrats! You Won!", color, size, center);
    } else {
        PrintTextMenu("You ran out of time! Game over :(", color, size, center);
    }
}

    cinder::Color THUGApp::GetPixelColor(float value) {
        if (value > kBlueThreshold) {
            // Ocean
            return Color(0, 0, 1 - value);
        } else if (value < kBlueThreshold && value > kSandThreshold) {
            // Sand
            return (Color((1 - value) * kSandRed, (1 - value) * kSandGreen, (1 - value) * kSandBlue));
        } else {
            // Grass
            float red = (world_decay_ * (kGrassRedValue) + kGrassRedValue);
            float green = (1 - value) * (kGrassGreenRatio) -
                    ((world_decay_*kGrassGreenDecayRatio) * (1 - value) * (kGrassGreenRatio));
            return Color(red, green, 0);
        }
    }

}  // namespace thugapp
