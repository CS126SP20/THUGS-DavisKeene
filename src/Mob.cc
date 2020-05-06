// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/Terrain.h>
#include <random>

using cinder::Rectf;

using std::string;
using namespace player;

namespace terrain {

    Mob::Mob(string name) {
        name_ = name;
        using std::chrono::system_clock;
        int randomseed = system_clock::now().time_since_epoch().count();
//        std::srand(randomseed);
        // Put mob on map randomly
        std::default_random_engine generator;
        generator.seed(randomseed);
        std::uniform_int_distribution<int> distribution(0, kWorldBoundary/kPixelSize);
        location_ = {distribution(generator) * kPixelSize, distribution(generator) * kPixelSize};
        if (name == "spider") {
            direction = RIGHT;
            speed = 1.0f;
            damage_ = 2.0;
        } else {
            direction = UP;
            speed = .5f;
            damage_ = 2.50;
        }
    }

    Mob::Mob(string name, cinder::vec2 location) {
        name_ = name;
        location_ = location;
    }

    void Mob::Draw() {
        cinder::vec2 pos = GetRelativePosition();
        if (name_ == "spider") {
            // Draw a spider on screen
            cinder::gl::draw(spider_icon, Rectf(kPixelSize * (pos.x),
                                                kPixelSize * (pos.y),
                                                kPixelSize * (pos.x) + kMobSize * kPixelSize, // Make antidote ingredient same size as player
                                                kPixelSize * (pos.y) + kMobSize * kPixelSize));
        } else if (name_ == "zombie") {
            // Draw a spider on screen
            cinder::gl::draw(zombie_icon, Rectf(kPixelSize * (pos.x),
                                                kPixelSize * (pos.y),
                                                kPixelSize * (pos.x) + kMobSize * kPixelSize, // Make antidote ingredient same size as player
                                                kPixelSize * (pos.y) + kMobSize * kPixelSize));
        }
    }

    cinder::vec2 Mob::GetRelativePosition() {
        int relative_x = ((int) location_.x % kMapSize) / kPixelSize;
        int relative_y = ((int) location_.y % kMapSize) / kPixelSize;
        return {relative_x, relative_y};
    }

    cinder::vec2 Mob::GetLocation() {
        return location_;
    }

    void Mob::UpdateLocation() {
        // Zombies move horizontally, spiders move vertically.
        switch(direction) {
            case LEFT: {
                if (location_.x < 0) {
                    direction = RIGHT;
                    break;
                }
                location_.x -= speed * kPixelSize;
                break;
            }
            case RIGHT: {
                if (location_.x > kWorldBoundary - (kPixelSize * kMobSize)) { // Since location_ is measured from the top left block
                    direction = LEFT;
                    break;
                }
                location_.x += speed * kPixelSize;
                break;
            }
            case UP: {
                if (location_.y < 0) {
                    direction = DOWN;
                    break;
                }
                location_.y -= speed * kPixelSize;
                break;
            }
            case DOWN: {
                if (location_.y > kWorldBoundary - (kPixelSize * kMobSize) ) {
                    direction = UP;
                    break;
                }
                location_.y += speed * kPixelSize;
                break;
            }
        }
    }

    double Mob::GetDamage() {
        return damage_;
    }
}  // namespace terrain
