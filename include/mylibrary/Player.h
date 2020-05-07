//
// Created by davis on 4/20/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <cinder/app/KeyEvent.h>
#include "cinder/Vector.h"
#include <vector>

namespace player {

    // Scale factor of how large the player is going to be
    const int kPlayerSize = 3;

    // Where is the player moving?
    enum Direction {
        LEFT, RIGHT, UP, DOWN, NONE
    };

    class Player {

      private:
        // Player's location_
        cinder::vec2 location_;
        // Player's health
        double health_;
        // How fast the player traverses the map_, in pixels / second
        int player_speed_;
        // Is the player moving?
        bool is_moving_;
        // Direction player is currently moving
        Direction player_direction_;
        // Player inventory, contains coordinates of antidotes discovered.
        std::vector<cinder::vec2> inventory_;
      public:
        // Gets absolute player position
        cinder::vec2 GetLocation();
        // Gets relative player position (on screen)
        cinder::vec2 GetRelativePosition();
        // Add to inventory
        void AddToInventory(cinder::vec2 antidote_location);
        // Get inventory size
        int GetInventorySize();
        // Gets player health
        float GetHealth();
        // Deals damage to player (subtracts from health)
        void DealDamage(double damage);
        // Is the player currently moving?
        bool IsMoving();
        // Speed increase / decrease
        void SetSpeed(double terrainValue);
        // Gets the players speed
        int GetSpeed();
        // Starts / stops player from moving
        void ToggleMovement();
        // Update player location_ based on what key was pressed
        void UpdateLocation();
        // Set player direction
        void SetDirection(Direction d);
        // Get direction player is moving in
        Direction GetDirection();
        // Default constructor
        Player();
        // Reset player
        void Reset();
    };
}

#endif //FINALPROJECT_PLAYER_H
