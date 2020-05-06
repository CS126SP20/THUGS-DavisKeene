//
// Created by davis on 4/20/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <cinder/app/KeyEvent.h>
#include "cinder/Vector.h"
#include <vector>

namespace thuglib {

    // Scale factor of how large the player is going to be
    const int kPlayerSize = 3;

    enum Direction {
        LEFT, RIGHT, UP, DOWN
    };

    class Player {

      private:
        // Player's location
        cinder::vec2 location;
        // Player's health
        float health;
        // How fast the player traverses the map_, in pixels / second
        int player_speed_;
        bool is_moving_;
        Direction playerDirection;
        // Player inventory, contains coordinates of antidotes discovered.
        std::vector<cinder::vec2> inventory;
      public:
        // Gets absolute player position
        cinder::vec2 GetLocation();
        // Gets relative player position (on screen)
        cinder::vec2 GetRelativePosition();
        // Add to inventory
        void AddToInventory(cinder::vec2 antidote_location);
        // Get inventory size
        int GetInventorySize();
        float GetHealth();
        bool IsMoving();
        // Speed increase / decrease
        void SetSpeed(double terrainValue);
        int GetSpeed();
        void ToggleMovement();
        // Update player location based on what key was pressed
        void UpdateLocation();
        void SetDirection(Direction d);
        Direction GetDirection();
        // Default constructor
        Player();
    };
}

#endif //FINALPROJECT_PLAYER_H
