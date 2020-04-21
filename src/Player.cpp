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

     void Player::SpeedUp() {
         player_speed_++;
     }

     void Player::SlowDown() {
         player_speed_--;
     }

     void Player::UpdateLocation(const KeyEvent& event) {
         switch(event.getCode()) {
             case KeyEvent::KEY_LEFT: {
                 location.x -= kPixelSize;
                 break;
             }
             case KeyEvent::KEY_RIGHT: {
                 location.x += kPixelSize;
                 break;
             }
             case KeyEvent::KEY_UP: {
                 location.y -= kPixelSize;
                 break;
             }
             case KeyEvent::KEY_DOWN: {
                 location.y += kPixelSize;
                 break;
             }
         }
     }

     Player::Player() {
         player_speed_ = 5;
         health = 100.0;
         location = {thuglib::kSpawnX, thuglib::kSpawnY};
     }
}