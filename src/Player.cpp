//
// Created by davis on 4/20/20.
//

#include <mylibrary/Terrain.h>
#include "mylibrary/Player.h"

using namespace terrain;
namespace player {

    using cinder::app::KeyEvent;

     cinder::vec2 Player::GetLocation() {
         return location_;
     }

     float Player::GetHealth() {
         return health_;
     }

     bool Player::IsMoving() {
         return is_moving_;
     }

     void Player::SetDirection(Direction d) {
         player_direction_ = d;
     }

     void Player::UpdateLocation() {
         switch(player_direction_) {
             case LEFT: {
                 if (location_.x == 0) {
                     return;
                 }
                 location_.x -= kPixelSize;
                 break;
             }
             case RIGHT: {
                 if (location_.x == kWorldBoundary - (kPixelSize * kPlayerSize)) { // Since location_ is measured from the top left block
                     return;
                 }
                 location_.x += kPixelSize;
                 break;
             }
             case UP: {
                 if (location_.y == 0) {
                     return;
                 }
                 location_.y -= kPixelSize;
                 break;
             }
             case DOWN: {
                 if (location_.y == kWorldBoundary - (kPixelSize * kPlayerSize) ) {
                     return;
                 }
                 location_.y += kPixelSize;
                 break;
             }
         }
     }

     void Player::ToggleMovement() {
         is_moving_ = !is_moving_;
     }

     cinder::vec2 Player::GetRelativePosition() {
         int relative_x = ((int) location_.x % kMapSize) / kPixelSize;
         int relative_y = ((int) location_.y % kMapSize) / kPixelSize;
         return {relative_x, relative_y};
     }

     Player::Player() {
         player_speed_ = 100;
         health_ = 100.0;
         location_ = {kSpawnX, kSpawnY};
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
        return player_direction_;
    }

    void Player::AddToInventory(cinder::vec2 antidote_location) {
        inventory_.push_back(antidote_location);
    }

    int Player::GetInventorySize() {
        return inventory_.size();
    }

    void Player::DealDamage(double damage) {
         health_ -= damage;
         if (health_ < 0) {
             health_ = 0;
         }
    }

    void Player::Reset() {
         location_ = {kSpawnX, kSpawnY};
         health_ = 100;
         inventory_.clear();
    }
}