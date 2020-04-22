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

     void Player::SpeedUp() {
         player_speed_++;
     }

     void Player::SlowDown() {
         player_speed_--;
     }

     void Player::SetDirection(Direction d) {
         playerDirection = d;
     }

     void Player::UpdateLocation() {
         switch(playerDirection) {
             case LEFT: {
                 location.x -= kPixelSize;
                 break;
             }
             case RIGHT: {
                 location.x += kPixelSize;
                 break;
             }
             case UP: {
                 location.y -= kPixelSize;
                 break;
             }
             case DOWN: {
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
         player_speed_ = 5;
         health = 100.0;
         location = {thuglib::kSpawnX, thuglib::kSpawnY};
     }
}