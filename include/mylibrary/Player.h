//
// Created by davis on 4/20/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <cinder/app/KeyEvent.h>
#include "cinder/Vector.h"

namespace thuglib {

    class Player {

      private:
        cinder::vec2 location;
        float health;
        int player_speed_;
      public:
        cinder::vec2 GetLocation();
        float GetHealth();
        void SpeedUp();
        void SlowDown();
        void UpdateLocation(const cinder::app::KeyEvent& event);
        Player();
    };
}

#endif //FINALPROJECT_PLAYER_H
