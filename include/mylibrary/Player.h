//
// Created by davis on 4/20/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <cinder/app/KeyEvent.h>
#include "cinder/Vector.h"

namespace thuglib {

    // Scale factor of how large the player is going to be
    const int kPlayerSize = 2;

    class Player {

      private:
        // Player's location
        cinder::vec2 location;
        // Player's health
        float health;
        // How fast the player traverses the map, in pixels / second
        int player_speed_;
      public:
        cinder::vec2 GetLocation();
        float GetHealth();
        // Speed increase / decrease
        void SpeedUp();
        void SlowDown();
        // Update player location based on what key was pressed
        void UpdateLocation(const cinder::app::KeyEvent& event);
        // Default constructor
        Player();
    };
}

#endif //FINALPROJECT_PLAYER_H
