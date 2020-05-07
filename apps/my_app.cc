// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>
#include <mylibrary/Terrain.h>

namespace app {

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

using namespace terrain;
using namespace player;

const char kNormalFont[] = "Arial Unicode MS";

THUGApp::THUGApp()
    : terrain_{},
      pixel_size_{kPixelSize},
      world_decay_{0.0},
      player_{},
      draw_stats_{false},
      has_started_{false} {}

void THUGApp::setup() {
    terrain_.GenerateTerrain();
    start_time_ = system_clock::now();
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
    // Setup sounds
    cinder::audio::SourceFileRef src = cinder::audio::load(cinder::app::loadAsset("bg-music.mp3"));
    bg_music_ = cinder::audio::Voice::create(src);
    cinder::audio::SourceFileRef src_map = cinder::audio::load(cinder::app::loadAsset("map.mp3"));
    map_noise_ = cinder::audio::Voice::create(src_map);
    cinder::audio::SourceFileRef src_col = cinder::audio::load(cinder::app::loadAsset("hit.mp3"));
    collision_noise_ = cinder::audio::Voice::create(src_col);
    cinder::audio::SourceFileRef src_ing = cinder::audio::load(cinder::app::loadAsset("collect-ingredient.mp3"));
    ingredient_noise_ = cinder::audio::Voice::create(src_ing);
    cinder::audio::SourceFileRef src_win = cinder::audio::load(cinder::app::loadAsset("victory.mp3"));
    victory_noise_ = cinder::audio::Voice::create(src_win);
    cinder::audio::SourceFileRef src_loss = cinder::audio::load(cinder::app::loadAsset("loss.mp3"));
    loss_noise_ = cinder::audio::Voice::create(src_loss);
    bg_music_->start();
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

void THUGApp::update() {
    const auto time = system_clock::now();
    double terrainValue = terrain_.GetValue(player_.GetRelativePosition().x, player_.GetRelativePosition().y);
    player_.SetSpeed(terrainValue);
    // If the player is moving, update their location.
    if (player_.IsMoving() && time - last_time_ > std::chrono::milliseconds(player_.GetSpeed())) {
        player_.UpdateLocation();
        last_time_ = time;
    }
    // Update mob locations
    for (Mob &m : terrain_.mobs_) {
        m.UpdateLocation();
        // If a mob contacts the player, deal damage
        if (terrain_.IsOverlapping(player_.GetLocation(), m.GetLocation(),
                                   kPlayerSize, kMobSize)) {
            player_.DealDamage(m.GetDamage());
            collision_ = true;
            collision_noise_->start();
        }
    }

    using std::chrono::milliseconds;
    const double elapsed_time =
            duration_cast<milliseconds>(system_clock::now() - start_time_)
                    .count();
    const double countdown_time = milliseconds(world_end_).count();
    const double percentage = elapsed_time / countdown_time;
    // Set world decay only if the game is not over
    if (!game_over_) {
        world_decay_ = percentage;
    }
    game_won_ = player_.GetInventorySize() == kAntidoteIngredients;
    // Check to see if the time is up, or if we have won the game
    if ((duration_cast<milliseconds>(world_end_ - (system_clock::now() - start_time_))
                 .count()/1000 == 0) || game_won_ || player_.GetHealth() == 0) {
        if (!game_over_) {
            finish_time_ = system_clock::now();
        }
        game_over_ = true;
        bg_music_->stop();
        if (game_won_) {
            victory_noise_->start();
        } else {
            loss_noise_->start();
        }
    }
    // Showing the hint logic
    if (show_hint_) {
        if (duration_cast<milliseconds>(system_clock::now() - hint_start_time_).count() > duration_cast<milliseconds>(hint_end_).count()) {
            show_hint_ = false;
        }
    }
}

void THUGApp::draw() {
    // Clear background with color of tile the player is on to feign transparency
    cinder::vec2 location = player_.GetRelativePosition();
    float value = terrain_.GetValue(location.x, location.y);
    if (collision_) {
        cinder::gl::clear(Color(1,0,0));
        collision_ = false;
    } else {
        cinder::gl::clear(GetPixelColor(value));
    }
    cinder::gl::enableAlphaBlending();
    if (!has_started_) {
        DrawInstructions();
        DrawTerrain();
    } else if (game_over_) {
        DrawGameOver();
        DrawTerrain();
    } else {
        DrawPlayer();
        if (show_hint_) {
            std::stringstream ss;
            ss << "Closest ingredient is " << terrain_.GetDistanceToClosestAntidote(player_.GetLocation()) << " blocks away.";
            PrintText(ss.str(), Color::white(), {250, 50}, {0, 0});
        }
        DrawMobs();
        DrawAntidotes();
        DrawMaps();
        DrawGameStats();
        DrawTerrain();
    }
}

// Convert key pressed to a direction
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
    if (event.getCode() == KeyEvent::KEY_SPACE) {
        ResetGame();
    }

    if (event.getCode() == KeyEvent::KEY_F1) {
        draw_stats_ = !draw_stats_;
        return;
    }
    if (!has_started_) {
        // Start the game after any key has been pressed
        has_started_ = !has_started_;
        terrain_.GenerateAntidotes();
        terrain_.GenerateMaps();
        terrain_.GenerateMobs();
        start_time_ = system_clock::now();
    }
    Direction d = KeyToDirection(event);
    if (d == player_.GetDirection() || !player_.IsMoving()) {
        player_.ToggleMovement();
    }
    // Set player movement after key is pressed
    player_.SetDirection(d);
}

void THUGApp::DrawTerrain() {
    cinder::vec2 bounds = terrain_.GetChunkBounds(player_.GetLocation());
    terrain_.GenerateTerrain(bounds);

    int xstart = (int) bounds.x * kNumPixels;
    int ystart = (int) bounds.y * kNumPixels;
    int xend = kNumPixels * (1 + (int) bounds.x);
    int yend = kNumPixels * (1 + (int) bounds.y);

    for (int x = xstart; x < xend; x++) {
        for (int y = ystart; y < yend; y++) {
            float value = terrain_.GetValue((x - xstart), (y - ystart));
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
    // Get player location_
    cinder::vec2 location = player_.GetLocation();
    cinder::gl::color(Color::white());
    // Render player location_ based on window coordinates, so we have to use %
    cinder::gl::draw(player_icon_, Rectf((int) location.x % kMapSize,
                                      (int) location.y % kMapSize,
                                     ((int) location.x % kMapSize) + kPlayerSize * pixel_size_,
                                     ((int) location.y % kMapSize) + kPlayerSize * pixel_size_));
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
        << player_.GetHealth()
        << "\nCurrent Speed:\n"
        << player_.GetSpeed()
        << "\nTime Left\n"
        << (duration_cast<milliseconds>(world_end_ - (system_clock::now() - start_time_))
                .count()/1000)
                << "\nIngredients Left\n"
                <<kAntidoteIngredients - player_.GetInventorySize();
        PrintText(ss.str(), Color::white(), size, text_coords);
    }
}

void THUGApp::DrawInstructions() {
    cinder::gl::clear(Color(0,0,0)); // Color screen black
    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 650};
    const Color color = Color::white();
    PrintTextMenu("Hello, and welcome to THUGS: The Half-baked Unimportant Game (Singleplayer), a procedurally generated campaign game.\n\n"
                  "The world is in danger! A deadly zombie outbreak has killed most of the humans on earth, and now the virus has mutated and started to kill the land! You must "
                  "collect ingredients left by scientists to make an antidote to save the people, the land and the world! Be speedy, because you have 4 minutes to collect the pieces before the terrain dies forever!\n\n"
                  "Antidote ingredients are scattered around the world, but are all visible among the terrain. Guiding maps will also spawn around the terrain, and can tell you "
                  "which direction to go to get to the closest ingredient. If you fail to collect all 5 ingredients by the end of the game, you lose!\n\n"
                  "Be careful of zombies and spiders, which constantly patrol the map. Running into one will cause your health to go down.\n\n"
                  "CONTROLS: arrow keys to move (start / stop by double pressing), F1 to open and close your game stats.\n"
                  "Press any key to start your adventure.", color, size, center);
}

void THUGApp::DrawAntidotes() {
    // Get all antidote locations in the player's current chunk
    std::vector<cinder::vec2> antidote_locations = terrain_.AntidoteInChunk(player_.GetLocation());
    // Draw each ingredient in player chunk
    for (cinder::vec2 antidote_location : antidote_locations) {
        int relative_x = ((int) antidote_location.x % kMapSize) / kPixelSize;
        int relative_y = ((int) antidote_location.y % kMapSize) / kPixelSize;
        // If a player has collided with an ingredient, delete it and move it to player inventory
        if (terrain_.IsOverlapping(player_.GetLocation(), antidote_location,
                                   kPlayerSize, kPlayerSize)) {
            terrain_.RemoveAntidote(antidote_location);
            player_.AddToInventory(antidote_location);
            image_index_ = (image_index_ + 1) % (kAntidoteIngredients);
            ingredient_noise_->start();
        }
        // Cycle through antidote images
        cinder::ImageSourceRef a_ref = cinder::loadImage(cinder::app::loadAsset("antidote-"+std::to_string(image_index_)+".png"));
        cinder::gl::Texture2dRef a_icon = cinder::gl::Texture2d::create(a_ref);
        // Make it sparkle
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
    const cinder::ivec2 win_size = {500, 150};
    const cinder::ivec2 lose_size = {500, 50};
    const Color color = Color::white();
    player_.SetDirection(NONE);
    if (game_won_) {
        victory_noise_->start();
        world_decay_ = 0.0;
        std::stringstream ss;
        using std::chrono::milliseconds;
        ss << "Congrats, you won! The earth is saved!\n"
        << "You gathered all ingredients in "
        << (duration_cast<milliseconds>((finish_time_ - start_time_))
                    .count()/1000)
        << " seconds!\n"
        << "To play again, press the space bar.";
        PrintTextMenu(ss.str(), color, win_size, center);
    } else if (player_.GetHealth() == 0) {
        PrintTextMenu("You died! Game over :(\nPress space to play again!", color, lose_size, center);
    } else {
        PrintTextMenu("You ran out of time! Game over :(\nPress space to play again!", color, lose_size, center);
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
        float red = (world_decay_ * (kGrassRedValue) + kGrassRedShift);
        float green = (1 - value) * (kGrassGreenRatio) -
                ((world_decay_*kGrassGreenDecayRatio) * (1 - value) * (kGrassGreenRatio));
        return Color(red, green, 0);
    }
}

void THUGApp::DrawMaps() {
    // Get all maps in a player's chunk
    std::vector<cinder::vec2> map_locations = terrain_.MapsInChunk(player_.GetLocation());
    // Draw maps in player's chunk
    for (cinder::vec2 map_location : map_locations) {
        int relative_x = ((int) map_location.x % kMapSize) / kPixelSize;
        int relative_y = ((int) map_location.y % kMapSize) / kPixelSize;
        // If a player has collided with a map, display hint and remove map
        if (terrain_.IsOverlapping(player_.GetLocation(), map_location,
                                   kPlayerSize, kPlayerSize)) {
            terrain_.RemoveMap(map_location);
            show_hint_ = true;
            hint_start_time_ = system_clock::now();
            map_noise_->start();
        }
        // Make it sparkle
        cinder::gl::color(rand() % 2, rand() % 2, rand() % 2);
        cinder::gl::draw(map_icon_, Rectf(pixel_size_ * (relative_x),
                                       pixel_size_ * (relative_y),
                                       pixel_size_ * (relative_x) + kPlayerSize * pixel_size_, // Make antidote ingredient same size as player
                                       pixel_size_ * (relative_y) + kPlayerSize * pixel_size_));
    }
}

void THUGApp::DrawMobs() {
    for (Mob &m : terrain_.mobs_) {
        if (terrain_.IsMobInChunk(m, player_.GetLocation())) {
            m.Draw();
        }
    }
}

void THUGApp::ResetGame() {
    // Reset terrain
    terrain_.Reset();
    // Generate mobs, antidotes and maps
    terrain_.GenerateAntidotes();
    terrain_.GenerateMaps();
    terrain_.GenerateMobs();
    // Reset player
    player_.Reset();
    // Reset app variables
    start_time_ = system_clock::now();
    world_decay_ = 0.0f;
    game_over_ = false;
    image_index_ = 1;
    bg_music_->start();
    loss_noise_->stop();
    victory_noise_->stop();
}

}  // namespace app
