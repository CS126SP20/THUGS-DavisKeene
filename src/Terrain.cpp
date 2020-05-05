//
// Created by davis on 4/18/20.
//

#include <iostream>
#include "mylibrary/Terrain.h"
namespace thuglib {

    void Terrain::GenerateTerrain() {
        for (int i = 0; i < kNumPixels; i++) {
            for (int j = 0; j < kNumPixels; j++) {
                // Without parameters, construct the terrain from spawn
                map_[i][j] = noise_.GetNoise(i + kSpawnX, j + kSpawnY);
            }
        }
    }

    void Terrain::GenerateTerrain(const cinder::vec2& bounds) {
        // Set values of array back to zero
        memset(map_, 0.0, sizeof(map_[0][0]) * kNumPixels * kNumPixels);
        int x = (int) bounds.x;
        int y = (int) bounds.y;
        for (int i = 0; i < kNumPixels; i++) {
            for (int j = 0; j < kNumPixels; j++) {
                // Construct the values of the map_ from our chunk bounds
                map_[i][j] = noise_.GetNoise(i + (x * kNumPixels), j + (kNumPixels * y));
            }
        }
    }

    float Terrain::GetValue(int x, int y) {
        return map_[x][y];
        // return noise_.GetNoise(x, y);
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

    Terrain::Terrain(FastNoise::NoiseType type, int seed, float frequency) {
        seed_ = seed;
        frequency_ = frequency;
        noise_.SetNoiseType(type);
        noise_.SetFrequency(frequency);
    }

    Terrain::Terrain() {
        noise_.SetNoiseType(FastNoise::ValueFractal);
        noise_.SetSeed(1337);
        noise_.SetFrequency(.05f);
    }

    int Terrain::GetSeed() {
        return seed_;
    }

    float Terrain::GetFrequency() {
        return frequency_;
    }

    std::vector<cinder::vec2> Terrain::AntidoteInChunk(const cinder::vec2 &bounds) {
        cinder::vec2 chunkBounds = GetChunkBounds(bounds); // Upper left bounds
        std::vector<cinder::vec2> antidoes;
        for (cinder::vec2 location : antidoteLocations) {
            int antidote_x = location.x / kMapSize;
            int antidote_y = location.y / kMapSize;
            if (antidote_x == chunkBounds.x && antidote_y == chunkBounds.y) {
                antidoes.push_back(location);
            }
        }
        return antidoes;
    }

    void Terrain::GenerateAntidotes() {
        for (int i = 0; i < kAntidoteIngredients; i++) {
            int randomseed = rand() % 100;
            std::srand(randomseed);
            // Generate random number pair between 0 and kWorldBoundary
            antidoteLocations.emplace_back(rand() % kWorldBoundary, rand() % kWorldBoundary);
        }
        for (cinder::vec2 location : antidoteLocations) {
            std::cout << location << std::endl;
        }
    }
}