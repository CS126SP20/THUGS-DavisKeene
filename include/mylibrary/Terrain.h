//
// Created by davis on 4/18/20.
//

#ifndef FINALPROJECT_TERRAIN_H
#define FINALPROJECT_TERRAIN_H

#include "FastNoise.h"

namespace mylibrary {

    const int kMapSize = 800;

    class Terrain {
    public:
        Terrain();
        float GetValue(int x, int y);
        void GenerateTerrain();
        void PrintTerrain();

    private:
        FastNoise noise;
        float map[kMapSize][kMapSize] = { };
    };
} // namespace terrain

#endif //FINALPROJECT_TERRAIN_H
