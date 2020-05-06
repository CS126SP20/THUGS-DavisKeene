//
// Created by davis on 5/6/20.
//

#ifndef FINALPROJECT_MOB_H
#define FINALPROJECT_MOB_H

#endif //FINALPROJECT_MOB_H
#include <cinder/gl/gl.h>
#include <mylibrary/Player.h>

namespace terrain {

    // Number of mobs on map
    const int kNumMobs = 50;
    // Size of mobs on screen
    const int kMobSize = 3;

    class Mob {
        cinder::ImageSourceRef zombie_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/zombie.png");
        cinder::gl::Texture2dRef zombie_icon = cinder::gl::Texture2d::create(zombie_ref);

        cinder::ImageSourceRef spider_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/spider.png");
        cinder::gl::Texture2dRef spider_icon = cinder::gl::Texture2d::create(spider_ref);

    public:
        explicit Mob(std::string name);
        Mob(std::string name, cinder::vec2 location);
        void Draw();
        cinder::vec2 GetRelativePosition();
        cinder::vec2 GetLocation();
        double GetDamage();
        void UpdateLocation();
        player::Direction direction;

    private:
        std::string name_;
        cinder::vec2 location_;
        double damage_;
        float speed;
    };
}