//
// Created by davis on 4/18/20.
//

#include <iostream>
#include <chrono>
#include "mylibrary/Terrain.h"
#include <cinder/Rand.h>

namespace terrain {

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
        using std::chrono::system_clock;
        noise_.SetNoiseType(FastNoise::ValueFractal);
        noise_.SetSeed(system_clock::now().time_since_epoch().count());
        noise_.SetFrequency(.03f);
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
            using std::chrono::system_clock;
            int randomseed = system_clock::now().time_since_epoch().count();
            std::srand(randomseed);
            // Generate random number pair between 0 and kWorldBoundary
            antidoteLocations.emplace_back(rand() % kWorldBoundary, rand() % kWorldBoundary);
        }
    }

    void Terrain::RemoveAntidote(const cinder::vec2& location) {
        for (size_t i = 0; i < antidoteLocations.size(); i++) {
            cinder::vec2 temp_location = antidoteLocations.at(i);
            if (temp_location == location) {
                antidoteLocations.erase(antidoteLocations.begin()+(int) i);
                return;
            }
        }
    }

    double Terrain::GetDistanceToClosestAntidote(const cinder::vec2& location) {
        // Get closest antidote to location_
        cinder::vec2 closest = antidoteLocations.at(0);
        double closest_d = sqrt((pow(closest.x - location.x, 2) + pow(closest.y - location.y, 2)));
        for (size_t i = 0; i < antidoteLocations.size(); i++) {
            cinder::vec2 temp_location = antidoteLocations.at(i);
            double temp_distance = sqrt((pow(temp_location.x - location.x, 2) + pow(temp_location.y - location.y, 2)));
            double closest_distance = sqrt((pow(closest.x - location.x, 2) + pow(closest.y - location.y, 2)));
            if (temp_distance < closest_distance) {
                closest = temp_location;
                closest_d = temp_distance;
            }
        }
        return closest_d;
    }

    void Terrain::GenerateMaps() {
        for (int i = 0; i < kNumMaps; i++) {
            using std::chrono::system_clock;
            int randomseed = system_clock::now().time_since_epoch().count();
            std::srand(randomseed);
            // Generate random number pair between 0 and kWorldBoundary
            mapLocations.emplace_back(rand() % kWorldBoundary, rand() % kWorldBoundary);
        }
    }

    std::vector<cinder::vec2> Terrain::MapsInChunk(const cinder::vec2 &bounds) {
        cinder::vec2 chunkBounds = GetChunkBounds(bounds); // Upper left bounds
        std::vector<cinder::vec2> maps;
        for (cinder::vec2 location : mapLocations) {
            int map_x = location.x / kMapSize;
            int map_y = location.y / kMapSize;
            if (map_x == chunkBounds.x && map_y == chunkBounds.y) {
                maps.push_back(location);
            }
        }
        return maps;
    }

    void Terrain::RemoveMap(const cinder::vec2 &location) {
        for (size_t i = 0; i < mapLocations.size(); i++) {
            cinder::vec2 temp_location = mapLocations.at(i);
            if (temp_location == location) {
                mapLocations.erase(mapLocations.begin()+(int) i);
                return;
            }
        }
    }

    void Terrain::GenerateMobs() {
        for (int i = 0; i < kNumMobs; i++) {
            float rand = cinder::randFloat();
            if (rand < .5) {
                Mob m("spider");
                mobs.push_back(m);
            } else {
                Mob m("zombie");
                mobs.push_back(m);
            }
        }
    }

    bool Terrain::IsMobInChunk(Mob m, const cinder::vec2& bounds) {
        cinder::vec2 chunkBounds = GetChunkBounds(bounds); // Upper left bounds
        int mob_x = m.GetLocation().x / kMapSize;
        int mob_y = m.GetLocation().y / kMapSize;
        return (mob_x == chunkBounds.x && mob_y == chunkBounds.y);
    }

    bool isOverlapping1D(cinder::vec2 box1, cinder::vec2 box2) {
        return box1.y > box2.x && box2.y > box1.x;
    }

    bool Terrain::IsOverlapping(cinder::vec2 obj1, cinder::vec2 obj2,
                                int obj1size, int obj2size) {
        cinder::vec2 playerLocationMax = {obj1.x + kPixelSize * obj1size, obj1.y + kPixelSize * obj1size};
        cinder::vec2 mobLocationEndMax = {obj2.x + kPixelSize * obj2size, obj2.y + kPixelSize * obj2size};

        // Check for any overlap from the northwest to southeast coordinates.
        return (isOverlapping1D({obj1.x, playerLocationMax.x}, {obj2.x, mobLocationEndMax.x}) &&
                isOverlapping1D({obj1.y, playerLocationMax.y}, {obj2.y, mobLocationEndMax.y}));
    }
}