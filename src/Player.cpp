//
// Created by davis on 4/20/20.
//

#include <mylibrary/Terrain.h>
#include "mylibrary/Player.h"

namespace thuglib {

    using cinder::app::KeyEvent;

     cinder::vec2 Player::GetLocation() {
         return location;
     }

     float Player::GetHealth() {
         return health;
     }

     bool Player::IsMoving() {
         return is_moving_;
     }

     void Player::SetDirection(Direction d) {
         playerDirection = d;
     }

     void Player::UpdateLocation() {
         switch(playerDirection) {
             case LEFT: {
                 if (location.x == 0) {
                     return;
                 }
                 location.x -= kPixelSize;
                 break;
             }
             case RIGHT: {
                 if (location.x == kWorldBoundary - (kPixelSize * kPlayerSize)) { // Since location is measured from the top left block
                     return;
                 }
                 location.x += kPixelSize;
                 break;
             }
             case UP: {
                 if (location.y == 0) {
                     return;
                 }
                 location.y -= kPixelSize;
                 break;
             }
             case DOWN: {
                 if (location.y == kWorldBoundary - (kPixelSize * kPlayerSize) ) {
                     return;
                 }
                 location.y += kPixelSize;
                 break;
             }
         }
     }

     void Player::ToggleMovement() {
         is_moving_ = !is_moving_;
     }

     cinder::vec2 Player::GetRelativePosition() {
         int relative_x = ((int) location.x % kMapSize) / kPixelSize;
         int relative_y = ((int) location.y % kMapSize) / kPixelSize;
         return {relative_x, relative_y};
     }

     Player::Player() {
         player_speed_ = 100;
         health = 100.0;
         location = {thuglib::kSpawnX, thuglib::kSpawnY};
     }

    void Player::SetSpeed(double terrainValue) {
         // If we are on water
        if (terrainValue > .150) {
            player_speed_ = 100; // Milliseconds per move one block
        } else if (terrainValue < .150 && terrainValue > .065) { // If we are on sand
            player_speed_ = 50;
        } else {
            player_speed_ = 25;
        }
    }

    int Player::GetSpeed() {
        return player_speed_;
    }

    Direction Player::GetDirection() {
        return playerDirection;
    }
}