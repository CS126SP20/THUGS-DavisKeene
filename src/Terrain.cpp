//
// Created by davis on 4/18/20.
//

#include <iostream>
#include "mylibrary/Terrain.h"
namespace mylibrary {

    void Terrain::GenerateTerrain() {
        noise.SetNoiseType(FastNoise::ValueFractal);
        for (int i = 0; i < kMapSize / kPixelSize; i++) {
            for (int j = 0; j < kMapSize / kPixelSize; j++) {
                map[i][j] = noise.GetNoise(i + kSpawnX, j + kSpawnY);
            }
        }
    }

    float Terrain::GetValue(int x, int y) {
        return map[x][y];
    }

    void Terrain::PrintTerrain() {
        for (int x = 0; x < kMapSize; x++) {
            for (int y = 0; y < kMapSize; y++) {
                std::cout << GetValue(x, y) <<
                          " \n"[y == kMapSize - 1];
            }
        }
    }

    Terrain::Terrain() = default;

}