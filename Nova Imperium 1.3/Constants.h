#pragma once

// Use pragma to get rid of that annoying ass warning.
#pragma warning(push)
#pragma warning(disable : 4275)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <functional>
#include <thread>
#include <chrono>
#include <mutex>

constexpr bool DEBUG_MODE = false;

const std::array<std::string, 16> RESOURCE_NAMES = {
	"Credits", "Food", "Energy", "Data",
	"Wood", "Stone", "Iron",
	"Fuel", "Alloy", "Silicon", "Biomass",
	"NanoCompounds", "Antimatter", "Helium-3",
	"Influence", "Knowledge"
};

const std::array<std::string, 18> BUILDING_NAMES = {
	"Solar Panel", "Mine", "Forestry Station", "Habitat Dome", "Hydroponics Farm", "Research Lab",
	"Refinery", "Fuel Synthesizer", "Biomass Generator", "Silicon Factory", "Factory Complex", "Quantum Lab", "Fusion Reactor",
	"Orbital Shipyard", "Dyson Swarm", "Stellar Forge", "Orbital Habitat Ring", "Interstellar Gateway"
};

const std::array<std::string, 18> BUILDING_COSTS = {
	// Outpost
	"50C, 5W",                  // Solar Panel
	"5P, 75C, 10W, 5S",             // Mine
	"5P, 75C, 10W, 5S",             // Forestry Station
	"100C, 20W, 10S, 5I",       // Habitat Dome
	"5P, 80C, 10W, 5S",             // Hydroponic Farm
	"5P, 120C, 15W, 10S, 5I",       // Research Lab

	// Colony
	"10P, 150C, 20I, 10A",           // Refinery
	"10P, 100C, 10I, 5F",            // Fuel Synthesizer
	"10P, 150C, 10I, 10F, 5A",		// Biomass Generator
	"10P, 200C, 20I, 10F, 10A",		// Silicon Factory
	"10P, 200C, 20I, 10F",           // Factory Complex
	"10P, 250C, 10I, 5F, 15S",       // Quantum Lab
	"10P, 300C, 20I, 10F, 20S",      // Fusion Reactor

	// Empire
	"50P, 500C, 50A, 50S",                   // Orbital Shipyard
	"50P, 1000C, 100A, 50S",                 // Dyson Swarm
	"50P, 800C, 100A, 50S, 25NC, 10AM, 5He3", // Stellar Forge
	"50P, 1200C, 150A, 100S, 50Bio, 25NC, 10AM", // Interstellar Gateway
	"900C, 100A, 50S, 25NC, 10AM, 5He3"  // Orbital Habitat Ring
};

const int SCR_WIDTH = 800, SCR_HEIGHT = 600;

const sf::Font NUNITO("NunitoSans-SemiBold.ttf");