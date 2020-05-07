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
        // Zombie image texture
        cinder::ImageSourceRef zombie_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/zombie.png");
        cinder::gl::Texture2dRef zombie_icon = cinder::gl::Texture2d::create(zombie_ref);

        // Spider image texture
        cinder::ImageSourceRef spider_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/spider.png");
        cinder::gl::Texture2dRef spider_icon = cinder::gl::Texture2d::create(spider_ref);

    public:
        // Default constructor, requires mob name
        explicit Mob(std::string name);
        // Constructor with location
        Mob(std::string name, cinder::vec2 location);
        // Draws the mob on screen
        void Draw();
        // Gets relative position on screen of mob
        cinder::vec2 GetRelativePosition();
        // Gets the absolute location of mob in world
        cinder::vec2 GetLocation();
        // Gets the damage the mob deals per frame of contact
        double GetDamage();
        // Update mob location
        void UpdateLocation();
        // Direction mob is moving in
        player::Direction direction;

    private:
        // Name of mob, either spider or zombie
        std::string name_;
        // Location of mob in world
        cinder::vec2 location_;
        // Damage mob deals per frame of contact
        double damage_;
        // How fast mob moves on screen
        float speed;
    };
}