//
// Created by davis on 4/18/20.
//

#include <iostream>
#include "mylibrary/Terrain.h"
namespace thuglib {

    void Terrain::GenerateTerrain() {
        // Set the noise type and seed
        noise.SetNoiseType(FastNoise::Value);
        noise.SetSeed(1337);
        for (int i = 0; i < kNumPixels; i++) {
            for (int j = 0; j < kNumPixels; j++) {
                // Without parameters, construct the terrain from spawn
                map[i][j] = noise.GetNoise(i + kSpawnX, j + kSpawnY);
            }
        }
    }

    void Terrain::GenerateTerrain(const cinder::vec2& bounds) {
        noise.SetNoiseType(FastNoise::Value);
        noise.SetSeed(1337);
        // Set values of array back to zero
        memset(map, 0.0, sizeof(map[0][0]) * kNumPixels * kNumPixels);
        int x = (int) bounds.x;
        int y = (int) bounds.y;
        for (int i = 0; i < kNumPixels; i++) {
            for (int j = 0; j < kNumPixels; j++) {
                // Construct the values of the map from our chunk bounds
                map[i][j] = noise.GetNoise(i + (x * kNumPixels), j + (kNumPixels * y));
            }
        }
    }

    float Terrain::GetValue(int x, int y) {
        return map[x][y];
        // return noise.GetNoise(x, y);
    }

    void Terrain::PrintTerrain() {
        for (int x = 0; x < kMapSize; x++) {
            for (int y = 0; y < kMapSize; y++) {
                std::cout << GetValue(x, y) <<
                          " \n"[y == kMapSize - 1];
            }
        }
    }

    cinder::vec2 Terrain::GetChunkBounds(const cinder::vec2& playerLocation) {
        float x = playerLocation.x;
        float y = playerLocation.y;

        // Utilize integer floor division
        int boundX = (int) x / kMapSize;
        int boundY = (int) y / kMapSize;

        return {boundX, boundY};
    }

    Terrain::Terrain() = default;

}