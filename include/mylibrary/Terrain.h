//
// Created by davis on 4/18/20.
//

#ifndef FINALPROJECT_TERRAIN_H
#define FINALPROJECT_TERRAIN_H

#include <cinder/Vector.h>
#include "FastNoise.h"

namespace thuglib {

    // Size of the map, window is kMapSize x kMapSize pixels
    const int kMapSize = 800;
    // Spawn X coordinate
    const int kSpawnX = 40000;
    // Spawn Y Coordinate
    const int kSpawnY = 40000;
    // Size of the pixels we want to render on screen
    const int kPixelSize = 8;
    // Number of pixels of our map, there are kNumPixels x kNumPixels
    // total pixels on the screen.
    const int kNumPixels = kMapSize / kPixelSize;

    class Terrain {
      public:
        // Default Constructor
        Terrain();
        // Returns the value (from -1 to 1) of a pixel on our terrain
        float GetValue(int x, int y);
        // Generate a terrain at spawn
        void GenerateTerrain();
        // Generates a terrain given our player's location
        void GenerateTerrain(const cinder::vec2& bounds);
        // Gets the bounds of our chunk based on the player's location
        cinder::vec2 GetChunkBounds(const cinder::vec2& playerLocation);
        // Prints the values of our terrain as a matrix
        void PrintTerrain();

      private:
        // Our FastNoise object that we use to get the noise
        FastNoise noise;
        // Map to store all of our terrain items.
        float map[kNumPixels][kNumPixels] = { };
    };
} // namespace terrain

#endif //FINALPROJECT_TERRAIN_H
