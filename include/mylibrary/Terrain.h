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

namespace thuglib {
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
    // Number of mobs on map
    const int kNumMobs = 50;

    const int kMobSize = 3;

    class Mob {
        cinder::ImageSourceRef zombie_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/zombie.png");
        cinder::gl::Texture2dRef zombie_icon = cinder::gl::Texture2d::create(zombie_ref);

        cinder::ImageSourceRef spider_ref = cinder::loadImage("/home/davis/Cinder/my-projects/final-project-daviskeene/assets/spider.png");
        cinder::gl::Texture2dRef spider_icon = cinder::gl::Texture2d::create(spider_ref);

    public:
        Mob(std::string name);
        Mob(std::string name, cinder::vec2 location);
        void Draw();
        cinder::vec2 GetRelativePosition();
        cinder::vec2 GetLocation();
        void UpdateLocation();
        Direction direction;

    private:
        std::string name_;
        cinder::vec2 location_;
        double damage_;
        float speed;
    };

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
        // Generates a terrain given our player's location
        void GenerateTerrain(const cinder::vec2& bounds);
        // Gets the bounds of our chunk based on the player's location
        // Bounds are defined in terms of x y coordinate pairs, representing the coordinate of the chunk
        cinder::vec2 GetChunkBounds(const cinder::vec2& playerLocation);
        // Prints the values of our terrain as a matrix
        void PrintTerrain();
        // Antidote Location methods
        void GenerateAntidotes();
        // Returns a list (vector) of antidote locations in a given chunk.
        std::vector<cinder::vec2> AntidoteInChunk(const cinder::vec2& bounds);
        // Removes an antidote given a location.
        void RemoveAntidote(const cinder::vec2& location);
        // Gets closest antidote to a location
        double GetDistanceToClosestAntidote(const cinder::vec2& location);
        // Map methods
        void GenerateMaps();
        // Get all maps in a chunk
        std::vector<cinder::vec2> MapsInChunk(const cinder::vec2& bounds);
        // Remove maps from world
        void RemoveMap(const cinder::vec2& location);
        // Getters
        std::vector<Mob> GetMobsInChunk(const cinder::vec2& bounds);
        void GenerateMobs();
        bool IsMobInChunk(Mob m, const glm::vec2 &bounds);
        int GetSeed();
        float GetFrequency();

        bool IsInRange(cinder::vec2 obj1, cinder::vec2 obj2, int obj1size, int obj2size);

        std::vector<Mob> mobs;
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
        std::vector<cinder::vec2> antidoteLocations;
        std::vector<cinder::vec2> mapLocations;
    };

} // namespace terrain

#endif //FINALPROJECT_TERRAIN_H