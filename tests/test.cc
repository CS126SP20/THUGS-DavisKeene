// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/example.h>
#include <mylibrary/Terrain.h>


TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Terrain does generate", "[terrain]") {
    thuglib::Terrain terrain;
    terrain.GenerateTerrain();
    terrain.PrintTerrain();
    REQUIRE(true);
}

TEST_CASE("Get Value from Terrain", "[terrain]") {
    thuglib::Terrain terrain;
    terrain.GenerateTerrain();
    std::cout << "-----" <<std::endl;
    std::cout << terrain.GetValue(0, 0);
    REQUIRE(true);
}