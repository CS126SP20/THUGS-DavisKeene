//
// Created by davis on 4/18/20.
//

#ifndef FINALPROJECT_TERRAIN_H
#define FINALPROJECT_TERRAIN_H

#include <cinder/Vector.h>
#include <vector>
#include "FastNoise.h"
#include "Player.h"
#include <cinder/gl/gl.h>
#include "Mob.h"

using terrain::Mob;
namespace terrain {
    // Size of the map_, window is kMapSize x kMapSize pixels
    const int kMapSize = 800;
    // World boundaries
    const int kWorldBoundary = 8000;
    // Spawn X coordinate
    const int kSpawnX = kWorldBoundary / 2 + kMapSize / 2;
    // Spawn Y Coordinate
    const int kSpawnY = kWorldBoundary / 2 + kMapSize / 2;
    // Size of the pixels we want to render on screen
    const int kPixelSize = 16;
    // Number of pixels of our map_, there are kNumPixels x kNumPixels
    // total pixels on the screen.
    const int kNumPixels = kMapSize / kPixelSize;
    // Number of antidote ingredients
    const int kAntidoteIngredients = 5;
    // Number of maps, proportional to number of ingredients
    const int kNumMaps = kAntidoteIngredients * 5;

    class Terrain {
    public:
        // Default Constructor
        Terrain();
        // Constructor with params
        Terrain(FastNoise::NoiseType type, int seed, float frequency);
        // Returns the value (from -1 to 1) of a pixel on our terrain
        float GetValue(int x, int y);
        // Generate a terrain at spawn
        void GenerateTerrain();
        // Generates a terrain given our player's location_
        void GenerateTerrain(const cinder::vec2& bounds);
        // Gets the bounds of our chunk based on the player's location_
        // Bounds are defined in terms of x y coordinate pairs, representing the coordinate of the chunk
        cinder::vec2 GetChunkBounds(const cinder::vec2& playerLocation);
        // Prints the values of our terrain as a matrix
        void PrintTerrain();
        // Antidote Location methods
        void GenerateAntidotes();
        // Returns a list (vector) of antidote locations in a given chunk.
        std::vector<cinder::vec2> AntidoteInChunk(const cinder::vec2& bounds);
        // Removes an antidote given a location_.
        void RemoveAntidote(const cinder::vec2& location);
        // Gets closest antidote to a location_
        double GetDistanceToClosestAntidote(const cinder::vec2& location);
        // Map methods
        void GenerateMaps();
        // Get all maps in a chunk
        std::vector<cinder::vec2> MapsInChunk(const cinder::vec2& bounds);
        // Remove maps from world
        void RemoveMap(const cinder::vec2& location);
        // Fill terrain with mobs
        void GenerateMobs();
        // Determine if a mob is inside of a given chunk
        bool IsMobInChunk(Mob m, const glm::vec2 &bounds);
        // Checks to see if two objects on the map are overlapping.
        bool IsOverlapping(cinder::vec2 obj1, cinder::vec2 obj2, int obj1size, int obj2size);
        // Reset Terrain
        void Reset();

    public:
        // Public vector containing mobs, so their locations can be updated in-game
        std::vector<Mob> mobs_;

    private:
        // Our FastNoise object that we use to get the noise
        FastNoise noise_;
        // Noise Type
        FastNoise::NoiseType noise_type_;
        // Map to store all of our terrain items.
        float map_[kNumPixels][kNumPixels] = { };
        // Seed of the terrain
        int seed_;
        // Noise frequency
        float frequency_;
        // Antidote ingredient locations
        std::vector<cinder::vec2> antidote_locations_;
        // Map locations
        std::vector<cinder::vec2> map_locations_;
    };

} // namespace terrain

#endif //FINALPROJECT_TERRAIN_H