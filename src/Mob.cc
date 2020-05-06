// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/Mob.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

using cinder::Rectf;

namespace thuglib {

    cinder::ImageSourceRef zombie_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/zombie.png");
    cinder::gl::Texture2dRef zombie_icon = cinder::gl::Texture2d::create(zombie_ref);

    cinder::ImageSourceRef spider_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/spider.png");
    cinder::gl::Texture2dRef spider_icon = cinder::gl::Texture2d::create(spider_ref);

    Mob::Mob(string name) {
        name_ = name;
        using std::chrono::system_clock;
        int randomseed = system_clock::now().time_since_epoch().count();
        std::srand(randomseed);
        // Put mob on map randomly
        location_ = {rand() % kWorldBoundary, rand() % kWorldBoundary};
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
}  // namespace thuglib
