#pragma once

#include "Constants.h"
#include "Button.h"

class Game {
private:
	struct BuildingCost {
		float m_Population = 0.0f;
		float m_Credits = 0.0f;
		float m_Wood = 0.0f;
		float m_Stone = 0.0f;
		float m_Iron = 0.0f;
		float m_Fuel = 0.0f;
		float m_Alloys = 0.0f;
		float m_Silicon = 0.0f;
		float m_Biomass = 0.0f;
		float m_NanoCompounds = 0.0f;
		float m_Antimatter = 0.0f;
		float m_Helium3 = 0.0f;
	};

	struct Empire {
		int m_Population = 10;
		int m_CurrentStage = 1;
	};

private:
	std::map<std::string, float> m_Resources = {
		{"Credits", 100.0f},		// The international currency in Nova Imperium. Used to build buildings and buy resources.
		{"Food", 50.0f},			// Population will not grow if food requirement is not met
		{"Energy", 0.0f},			// Each building consumes power, if energy requirement is not met, production will be halved.
		{"Data", 0.0f},			// Used for increasing stage.

		{"Wood", 25.0f},			// Basic stage one building material. Sold for 2 credits.
		{"Stone", 10.0f},			// Another building material. Sold for 4 credits.
		{"Iron", 5.0f},			// Another building material. Sold for 8 credits.

		{"Fuel", 10.0f},			// Consumed by fusion reactor. Sold for 20 credits.
		{"Alloy", 10.0f},			// Stage 2 building material. Sold for 40 credits.
		{"Silicon", 0.0f},			// Another stage 2 building material. Sold for 60 credits.
		{"Biomass", 0.0f},			// Another stage 2 building material. Sold for 80 credits.

		{"NanoCompounds", 25.0f},	// Stage 3 building material. Sold for 200 credits.
		{"Antimatter", 10.0f},		// Needed to colonize new planets. Sold for 400 credits.
		{"Helium-3", 5.0f},		// Stage 3 building material. Sold for 600 credits.

		{"Knowledge", 0.0f},		// Prestige resource. Increases resource production.
		{"Influence", 0.0f},		// Increases trade profits.
	};

	std::map<std::string, int> m_Buildings = {
		{"Solar Panel", 0},				// Produces 1 energy / sec. 
		{"Mine", 0},					// Produces 1 iron / sec and 1 stone / sec.
		{"Forestry Station", 0},		// Produces 1 wood / sec.
		{"Habitat Dome", 1},			// Increases population by 10.
		{"Hydroponics Farm", 0},		// Produces 1 food / sec.
		{"Research Lab", 0},			// Produces 1 data / sec.

		{"Refinery", 0},				// Produces 1 alloy / sec.
		{"Fuel Synthesizer", 0},		// Produces 1 fuel / sec.
		{"Biomass Generator", 0},
		{"Silicon Factory", 0},
		{"Factory Complex", 0},			// Increases production by 10%. Max of 1 building.
		{"Quantum Lab", 0},				// Produces 2 data / sec.
		{"Fusion Reactor", 0},			// Produces 3 energy / sec.

		{"Orbital Shipyard", 0},		// Unlocks the ability to settle new planet, gives knowledge on prestige.
		{"Dyson Swarm", 0},				// Produces 10 energy / sec.
		{"Stellar Forge", 0},			// Gives 1 NanoCompounds / sec and 1 antimatter / sec.
		{"Orbital Habitat Ring", 0},	// Increases population by 50.
		{"Interstellar Gateway", 0}		// Unlocks true prestige, gives influence on prestige.
	};

	std::map<std::string, BuildingCost> m_BuildingCosts = {
		{"Solar Panel", {0.0f, 50.0f, 5.0f, 0.0f, 0.0f, 0.0f}},			// 50C, 5W
		{"Mine", {5.0f, 75.0f, 10.0f, 5.0f, 0.0f, 0.0f}},				// 75C, 10W, 5S
		{"Forestry Station", {5.0f, 75.0f, 10.0f, 5.0f, 0.0f, 0.0f}},	// 60C, 5S, 2I
		{"Habitat Dome", {-10.0f, 100.0f, 20.0f, 10.0f, 5.0f, 0.0f}},		// 100C, 20W, 10S, 5I
		{"Hydroponics Farm", {5.0f, 80.0f, 10.0f, 5.0f, 0.0f, 0.0f}},		// 80C, 10W, 5S
		{"Research Lab", {5.0f, 120.0f, 15.0f, 10.0f, 5.0f, 0.0f}},		// 120C, 15W, 10S, 5I

		// Stage 2
		{"Refinery", {10.0f, 150.0f, 0.0f, 0.0f, 20.0f, 0.0f, 10.0f}},
		{"Fuel Synthesizer", {10.0f, 100.0f, 0.0f, 0.0f, 10.0f, 5.0f, 0.0f}},
		{"Fusion Reactor", {10.0f, 300.0f, 0.0f, 0.0f, 20.0f, 10.0f, 20.0f}},
		{"Biomass Generator", {10.0f, 150.0f, 0.0f, 0.0f, 10.0f, 10.0f, 5.0f}},
		{"Silicon Factory", {10.0f, 200.0f, 0.0f, 0.0f, 20.0f, 10.0f, 10.0f}},
		{"Factory Complex", {200.0f, 0.0f, 0.0f, 20.0f, 10.0f, 0.0f}},
		{"Quantum Lab", {10.0f, 250.0f, 0.0f, 0.0f, 10.0f, 5.0f, 15.0f}},

		// Stage 3
		{"Orbital Shipyard", {50.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f}},
		{"Dyson Swarm", {50.0f, 1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f, 50.0f}},
		{"Stellar Forge", {50.0f, 800.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f, 50.0f, 25.0f, 10.0f, 5.0f}},
		{"Interstellar Gateway", {50.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 150.0f, 100.0f, 50.0f, 25.0f, 10.0f}},
		{"Orbital Habitat Ring", {-100.0f, 900.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f, 50.0f, 25.0f, 10.0f, 5.0f}}
	};

	sf::RenderWindow m_Window;
	int m_CurrentPage;
	bool m_ProgramRunning;
	Empire m_Empire;
	int m_StagePage;
	const std::array<float, 14> m_ResourcePrices = {
		0.0f, 1.0f, 2.0f, 5.0f,
		2.0f, 4.0f, 8.0f, 20.0f, 40.0f,
		60.0f, 80.0f, 200.0f, 400.0f, 600.0f
	};
	std::vector<Button> m_BuildButtons;

	std::vector<sf::Text> m_TradeTexts;
	std::vector<Button> m_SellButtons;
	std::vector<Button> m_SellAllButtons;

	std::thread m_UpdateThread;
	std::mutex m_ResourceMutex;

	Button m_StartButton;
	Button m_ExitButton;
	sf::Text m_TitleText;

	sf::Text m_ResourceTitle;
	std::vector<sf::Text> m_ResourceTexts;


private:
	void UpdateStage();

	bool CanAfford(const BuildingCost& cost);
	void BuyBuilding(const std::string& name);
	int CalculatePrestige();
	void DoPrestige(int gainedKnowledge);

	void DrawMainMenu();
	void DrawResourcePage();
	void DrawBuildingPage();
	void DrawTradePage();
	void DrawPrestigePage();

	void SaveGame(const std::string& filename);
	void LoadGame(const std::string& filename);

	void UpdateThread();

public:
	Game();
	~Game();

	void Run();
};