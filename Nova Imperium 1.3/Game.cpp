#include "Game.h"

void Game::UpdateStage() {
	if (m_Empire.m_CurrentStage == 1) {
		if (m_Resources["Iron"] >= 100 && m_Resources["Energy"] >= 20 && m_Resources["Data"] >= 10) {
			if (m_Buildings["Solar Panel"] >= 1 && m_Buildings["Research Lab"] >= 1 && m_Buildings["Habitat Dome"] >= 3) {
				m_Empire.m_CurrentStage = 2;
			}
		}
	}

	else if (m_Empire.m_CurrentStage == 2) {
		if (m_Resources["Alloy"] >= 500 && m_Resources["Fuel"] >= 300 && m_Resources["Data"] >= 500 && m_Resources["Credits"] >= 5000) {
			if (m_Buildings["Fusion Reactor"] >= 2 && m_Buildings["Refinery"] >= 2 && m_Buildings["Quantum Lab"] >= 1) {
				m_Empire.m_CurrentStage = 3;
			}
		}
	}
}

bool Game::CanAfford(const BuildingCost& cost) {
	return m_Empire.m_Population >= cost.m_Population &&
		m_Resources["Credits"] >= cost.m_Credits &&
		m_Resources["Wood"] >= cost.m_Wood &&
		m_Resources["Stone"] >= cost.m_Stone &&
		m_Resources["Iron"] >= cost.m_Iron &&
		m_Resources["Fuel"] >= cost.m_Fuel &&
		m_Resources["Alloy"] >= cost.m_Alloys &&
		m_Resources["Silicon"] >= cost.m_Silicon &&
		m_Resources["Biomass"] >= cost.m_Biomass &&
		m_Resources["NanoCompounds"] >= cost.m_NanoCompounds &&
		m_Resources["Antimatter"] >= cost.m_Antimatter &&
		m_Resources["Helium-3"] >= cost.m_Helium3;
}

void Game::BuyBuilding(const std::string& name) {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);
	const BuildingCost& cost = m_BuildingCosts[name];
	if (CanAfford(cost)) {
		m_Empire.m_Population -= cost.m_Population;
		m_Resources["Credits"] -= cost.m_Credits;
		m_Resources["Wood"] -= cost.m_Wood;
		m_Resources["Stone"] -= cost.m_Stone;
		m_Resources["Iron"] -= cost.m_Iron;
		m_Resources["Fuel"] -= cost.m_Fuel;
		m_Resources["Alloy"] -= cost.m_Alloys;
		m_Resources["Silicon"] -= cost.m_Silicon;
		m_Resources["Biomass"] -= cost.m_Biomass;
		m_Resources["NanoCompounds"] -= cost.m_NanoCompounds;
		m_Resources["Antimatter"] -= cost.m_Antimatter;
		m_Resources["Helium-3"] -= cost.m_Helium3;

		m_Buildings[name]++;
	}
}

void Game::DrawMainMenu() {
	if (m_StartButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
		if (m_StartButton.m_OnClick) m_StartButton.m_OnClick();
	}
	if (m_ExitButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
		if (m_ExitButton.m_OnClick) m_ExitButton.m_OnClick();
	}

	m_Window.draw(m_StartButton.m_Rect);
	m_Window.draw(m_StartButton.m_Label);

	m_Window.draw(m_ExitButton.m_Rect);
	m_Window.draw(m_ExitButton.m_Label);

	m_Window.draw(m_TitleText);
}

void Game::DrawResourcePage() {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);

	m_ResourceTexts[0].setString("Available Population: " + std::to_string(m_Empire.m_Population));

	m_ResourceTexts[1].setString("Credits: " + std::to_string(static_cast<int>(std::floor(m_Resources["Credits"]))) + "C");

	m_ResourceTexts[2].setString("Food: " + std::to_string(static_cast<int>(std::floor(m_Resources["Food"]))));

	m_ResourceTexts[3].setString("Energy: " + std::to_string(static_cast<int>(std::floor(m_Resources["Energy"]))));

	m_ResourceTexts[4].setString("Data: " + std::to_string(static_cast<int>(std::floor(m_Resources["Data"]))));

	if (m_Empire.m_CurrentStage >= 1) {
		float outpostTextY = 230.0f;

		sf::Text stageText(NUNITO, "Outpost", 30U);
		stageText.setPosition(sf::Vector2f(20.0f, outpostTextY));
		m_Window.draw(stageText);

		m_ResourceTexts[5].setString("Wood: " + std::to_string(static_cast<int>(std::floor(m_Resources["Wood"]))));

		m_ResourceTexts[6].setString("Stone: " + std::to_string(static_cast<int>(std::floor(m_Resources["Stone"]))));

		m_ResourceTexts[7].setString("Iron: " + std::to_string(static_cast<int>(std::floor(m_Resources["Iron"]))));
	}
	if (m_Empire.m_CurrentStage >= 2) {
		float colonyTextY = 230.0f;
		sf::Text stageText(NUNITO, "Colony", 30U);
		stageText.setPosition(sf::Vector2f(250.0f, colonyTextY));
		m_Window.draw(stageText);

		m_ResourceTexts[8].setString("Fuel: " + std::to_string(static_cast<int>(std::floor(m_Resources["Fuel"]))));

		m_ResourceTexts[9].setString("Alloy: " + std::to_string(static_cast<int>(std::floor(m_Resources["Alloy"]))));

		m_ResourceTexts[10].setString("Silicon: " + std::to_string(static_cast<int>(std::floor(m_Resources["Silicon"]))));

		m_ResourceTexts[11].setString("Biomass: " + std::to_string(static_cast<int>(std::floor(m_Resources["Biomass"]))));
	}
	if (m_Empire.m_CurrentStage >= 3) {
		float empireTextY = 230.0f;
		sf::Text stageText(NUNITO, "Empire", 30U);
		stageText.setPosition(sf::Vector2f(500.0f, empireTextY));
		m_Window.draw(stageText);

		m_ResourceTexts[12].setString("NanoCompounds: " + std::to_string(static_cast<int>(std::floor(m_Resources["NanoCompounds"]))));

		m_ResourceTexts[13].setString("Antimatter: " + std::to_string(static_cast<int>(std::floor(m_Resources["Antimatter"]))));

		m_ResourceTexts[14].setString("Helium-3: " + std::to_string(static_cast<int>(std::floor(m_Resources["Helium-3"]))));
	}
	if (m_Resources["Knowledge"] >= 1) {
		m_ResourceTexts[15].setString("Knowledge: " + std::to_string(static_cast<int>(std::floor(m_Resources["Knowledge"]))));
	}

	m_Window.draw(m_ResourceTitle);

	for (int i = 0; i < m_ResourceTexts.size(); ++i) {
		if (i <= 4) {
			m_Window.draw(m_ResourceTexts[i]);
		}
		if (m_Empire.m_CurrentStage >= 1 && i > 4 && i < 8) {
			m_Window.draw(m_ResourceTexts[i]);
		}
		if (m_Empire.m_CurrentStage >= 2 && i >= 8 && i <= 11) {
			m_Window.draw(m_ResourceTexts[i]);
		}
		if (m_Empire.m_CurrentStage >= 3 && i > 11) {
			m_Window.draw(m_ResourceTexts[i]);
		}
	}
	if (m_Resources["Knowledge"] >= 1) {
		sf::Text stageText(NUNITO, "Galactic Empire", 30U);
		stageText.setPosition(sf::Vector2f(20.0f, 370.0f));
		m_Window.draw(stageText);
		m_Window.draw(m_ResourceTexts[15]);
	}
}

void Game::DrawBuildingPage() {
	sf::Text buildingText(NUNITO, "Building", 40U);
	buildingText.setPosition(sf::Vector2f(20.0f, 20.0f));
	m_Window.draw(buildingText);

	std::vector<sf::Text> buildingTexts;
	std::vector<sf::Text> buildingCostTexts;

	int startIndex = 0;
	int endIndex = 0;

	switch (m_StagePage) {
	case 1:
		startIndex = 0;
		endIndex = 6;
		break;
	case 2:
		startIndex = 6;
		endIndex = 13;
		break;
	case 3:
		startIndex = 13;
		endIndex = 17;
		break;
	default:
		break;
	}

	if (startIndex >= BUILDING_NAMES.size()) return;
	if (endIndex > BUILDING_NAMES.size()) endIndex = static_cast<int>(BUILDING_NAMES.size());

	float buttonY = 125.0f;

	if (m_BuildButtons.empty()) {
		for (int idx = 0; idx < 18; ++idx) {
			if (idx == 6 || idx == 13) buttonY = 125.0f;
			m_BuildButtons.emplace_back(NUNITO, "Build", sf::Vector2f(400.0f, buttonY), sf::Vector2f(75.0f, 25.0f), [this, idx]() {
				BuyBuilding(BUILDING_NAMES[idx]);
				});
			buttonY += 50.0f;
		}
	}

	std::string stageName = (m_StagePage == 1) ? "Outpost" : ((m_StagePage == 2) ? "Colony" : "Empire");
	sf::Text stageText(NUNITO, stageName, 30U);
	stageText.setPosition(sf::Vector2f(20.0f, 80.0f));

	float textY = 120.0f;
	float costY = 150.0f;

	for (size_t i = startIndex; i < endIndex; ++i) {
		int buildingIndex = static_cast<int>(i);

		if (buildingIndex >= BUILDING_NAMES.size()) continue;

		sf::Text bText(NUNITO, BUILDING_NAMES[buildingIndex] + ": " + std::to_string(m_Buildings[BUILDING_NAMES[buildingIndex]]), 25U);
		bText.setPosition(sf::Vector2f(20.0f, textY));
		m_Window.draw(bText);
		textY += 50.0f;

		if (buildingIndex < BUILDING_COSTS.size()) {
			sf::Text costText(NUNITO, BUILDING_COSTS[buildingIndex], 18U);
			costText.setPosition(sf::Vector2f(30.0f, costY));
			m_Window.draw(costText);
		}
		costY += 50.0f;

		if (!CanAfford(m_BuildingCosts[BUILDING_NAMES[i]])) {
			m_BuildButtons[i].m_Label.setFillColor(sf::Color(100, 100, 100, 255));
		}
		else {
			m_BuildButtons[i].m_Label.setFillColor(sf::Color(255, 255, 255, 255));
		}

		m_Window.draw(m_BuildButtons[i].m_Rect);
		m_Window.draw(m_BuildButtons[i].m_Label);

		if (m_BuildButtons[i].IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
			if (m_BuildButtons[i].m_OnClick) m_BuildButtons[i].m_OnClick();
		}
	}


	std::vector<Button> stageBar;

	if (m_Empire.m_CurrentStage >= 1) {
		stageBar.emplace_back(NUNITO, "Outpost", sf::Vector2f(2.0f, 500.0f), sf::Vector2f(123.0f, 50.0f), [this]() {
			m_StagePage = 1;
			});
	}
	if (m_Empire.m_CurrentStage >= 2) {
		stageBar.emplace_back(NUNITO, "Colony", sf::Vector2f(127.0f, 500.0f), sf::Vector2f(123.0f, 50.0f), [this]() {
			m_StagePage = 2;
			});
	}
	if (m_Empire.m_CurrentStage >= 3) {
		stageBar.emplace_back(NUNITO, "Empire", sf::Vector2f(252.0f, 500.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
			m_StagePage = 3;
			});
	}

	for (auto& button : stageBar) {
		m_Window.draw(button.m_Rect);
		m_Window.draw(button.m_Label);

		if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
			if (button.m_OnClick) button.m_OnClick();
		}
	}
}

void Game::DrawTradePage() {
	sf::Text tradeText(NUNITO, "Trade", 40U);
	tradeText.setPosition(sf::Vector2f(20.0f, 20.0f));
	sf::Text creditText(NUNITO, "Credits: " + std::to_string(static_cast<int>(std::floor(m_Resources["Credits"]))) + "C", 30U);
	creditText.setPosition(sf::Vector2f(20.0f, 70.0f));

	std::vector<Button> stageBar;

	if (m_Empire.m_CurrentStage >= 1) {
		stageBar.emplace_back(NUNITO, "Outpost", sf::Vector2f(2.0f, 500.0f), sf::Vector2f(123.0f, 50.0f), [this]() {
			m_StagePage = 1;
			});
	}
	if (m_Empire.m_CurrentStage >= 2) {
		stageBar.emplace_back(NUNITO, "Colony", sf::Vector2f(127.0f, 500.0f), sf::Vector2f(123.0f, 50.0f), [this]() {
			m_StagePage = 2;
			});
	}
	if (m_Empire.m_CurrentStage >= 3) {
		stageBar.emplace_back(NUNITO, "Empire", sf::Vector2f(252.0f, 500.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
			m_StagePage = 3;
			});
	}

	float textY = 150.0f;
	float buttonY = 150.0f;

	if (m_StagePage == 1) {
		sf::Text stageText(NUNITO, "Outpost", 30U);
		stageText.setPosition(sf::Vector2f(20.0f, 115.0f));
		m_Window.draw(stageText);

		for (int i = 4; i < 7; ++i) {
			float buttonX = 200.0f;

			m_TradeTexts[i].setString(RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))));
			m_TradeTexts[i].setPosition(sf::Vector2f(20.0f, textY));
			m_Window.draw(m_TradeTexts[i]);
			textY += 30.0f;

			Button& button = m_SellButtons[i - 4];
			m_Window.draw(button.m_Rect);
			m_Window.draw(button.m_Label);

			if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (button.m_OnClick) button.m_OnClick();
			}

			Button& sellButton = m_SellAllButtons[i - 4];

			sellButton.m_Label.setString("Sell " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))) + " (" + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]] * static_cast<int>(std::floor(m_ResourcePrices[i]))))) + "C)");
			sellButton.UpdateTextPosition();

			m_Window.draw(sellButton.m_Rect);
			m_Window.draw(sellButton.m_Label);

			if (sellButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (sellButton.m_OnClick) sellButton.m_OnClick();
			}

			buttonY += 30.0f;
		}
	}
	else if (m_StagePage == 2) {
		textY = 150.0f;
		sf::Text stageText(NUNITO, "Colony", 30U);
		stageText.setPosition(sf::Vector2f(20.0f, 115.0f));
		m_Window.draw(stageText);

		for (int i = 7; i < 11; ++i) {
			float buttonX = 200.0f;
			
			m_TradeTexts[i - 4].setString(RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))));
			m_TradeTexts[i - 4].setPosition(sf::Vector2f(20.0f, textY));
			m_Window.draw(m_TradeTexts[i - 4]);

			textY += 30.0f;

			Button& button = m_SellButtons[i - 4];
			m_Window.draw(button.m_Rect);
			m_Window.draw(button.m_Label);

			if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (button.m_OnClick) button.m_OnClick();
			}

			Button& sellButton = m_SellAllButtons[i - 4];

			sellButton.m_Label.setString("Sell " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))) + " (" + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]] * static_cast<int>(std::floor(m_ResourcePrices[i]))))) + "C)");
			sellButton.UpdateTextPosition();

			m_Window.draw(sellButton.m_Rect);
			m_Window.draw(sellButton.m_Label);

			if (sellButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (sellButton.m_OnClick) sellButton.m_OnClick();
			}

			buttonY += 30.0f;
		}
	}
	else if (m_StagePage == 3) {
		sf::Text stageText(NUNITO, "Empire", 30U);
		stageText.setPosition(sf::Vector2f(20.0f, 115.0f));
		m_Window.draw(stageText);

		for (int i = 11; i < 14; ++i) {
			float buttonX = 300.0f;
			m_TradeTexts[i - 4].setString(RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))));
			m_Window.draw(m_TradeTexts[i - 4]);

			Button& button = m_SellButtons[i - 4];
			m_Window.draw(button.m_Rect);
			m_Window.draw(button.m_Label);

			if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (button.m_OnClick) button.m_OnClick();
			}

			Button& sellButton = m_SellAllButtons[i - 4];

			sellButton.m_Label.setString("Sell " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))) + " (" + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]] * static_cast<int>(std::floor(m_ResourcePrices[i]))))) + "C)");
			sellButton.UpdateTextPosition();

			m_Window.draw(sellButton.m_Rect);
			m_Window.draw(sellButton.m_Label);

			if (sellButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
				if (sellButton.m_OnClick) sellButton.m_OnClick();
			}

			buttonY += 30.0f;
		}
	}

	m_Window.draw(tradeText);
	m_Window.draw(creditText);

	for (auto& button : stageBar) {
		m_Window.draw(button.m_Rect);
		m_Window.draw(button.m_Label);

		if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
			if (button.m_OnClick) button.m_OnClick();
		}
	}
}

int Game::CalculatePrestige() {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);

	const double wCredits = 0.001;
	const double wEnergy = 1.0;
	const double wAlloy = 10.0;
	const double wNano = 100.0;
	const double wAntimatter = 1000.0;
	const double wHe = 500.0;
	const double wBuildings = 25.0;
	const double wStage = 1000.0;

	double totalBuildings = 0.0;
	for (const auto& [k, v] : m_Buildings) totalBuildings += static_cast<double>(v);

	double W = 0.0;
	W += m_Resources["Credits"] * wCredits;
	W += m_Resources["Energy"] * wEnergy;
	W += m_Resources["Alloy"] * wAlloy;
	W += m_Resources["NanoCompounds"] * wNano;
	W += m_Resources["Antimatter"] * wAntimatter;
	W += m_Resources["Helium-3"] * wHe;
	W += totalBuildings * wBuildings;


	const double scaleFactor = 10.0;
	int gained = static_cast<int>(std::floor(std::log(1.0 + W) * scaleFactor));
	if (gained < 0) gained = 0;
	return gained;
}

void Game::DoPrestige(int gainedKnowledge) {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);

	m_Resources["Knowledge"] += gainedKnowledge;

	for (auto& [key, value] : m_Resources) {
		if (key != "Knowledge" && key != "Influence") value = 0;
	}

	for (auto& [key, value] : m_Buildings) {
		value = 0;
	}

	m_Buildings["Habitat Dome"] = 1;

	m_Empire.m_CurrentStage = 1;
	m_Empire.m_Population = 10;

	m_Resources["Credits"] = 100;
	m_Resources["Food"] = 50;
	m_Resources["Wood"] = 25;
	m_Resources["Stone"] = 10;
	m_Resources["Iron"] = 5;
	m_Resources["Fuel"] = 10;
	m_Resources["Alloy"] = 10;
	m_Resources["NanoCompounds"] = 25;
	m_Resources["Antimatter"] = 10;
	m_Resources["Helium-3"] = 5;

	m_CurrentPage = 1;
}

void Game::DrawPrestigePage() {
	sf::Text prestigeText(NUNITO, "Prestige", 40U);
	prestigeText.setPosition(sf::Vector2f(20.0f, 20.0f));
	m_Window.draw(prestigeText);

	int gainedKnowledge = CalculatePrestige();
	Button prestigeButton(NUNITO, "Move to new planet for " + std::to_string(gainedKnowledge) + " knowledge.", sf::Vector2f(20.0f, 100.0f), sf::Vector2f(400.0f, 100.0f), [this, gainedKnowledge]() {
		DoPrestige(gainedKnowledge);
		});

	m_Window.draw(prestigeButton.m_Rect);
	m_Window.draw(prestigeButton.m_Label);

	if (prestigeButton.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
		if (prestigeButton.m_OnClick) prestigeButton.m_OnClick();
	}
}

void Game::UpdateThread() {
	while (m_ProgramRunning) {
		{
			std::lock_guard<std::mutex> lock(m_ResourceMutex);

			UpdateStage();

			float productionMultiplier = 1.0f + m_Resources["Knowledge"] / 100.0f;

			if (m_Buildings["Factory Complex"] >= 1) {
				float factoryMulti = 0.1f;
				for (int i = 0; i < m_Buildings["Factory Complex"]; ++i) {
					factoryMulti += factoryMulti / 2.0f;
				}
				productionMultiplier += factoryMulti;
			}

			m_Resources["Energy"] += m_Buildings["Solar Panel"] * productionMultiplier;
			m_Resources["Iron"] += m_Buildings["Mine"] * productionMultiplier;
			m_Resources["Stone"] += m_Buildings["Mine"] * productionMultiplier;
			m_Resources["Wood"] += m_Buildings["Forestry Station"] * productionMultiplier;
			m_Resources["Food"] += m_Buildings["Hydroponics Farm"] * productionMultiplier;
			m_Resources["Data"] += m_Buildings["Research Lab"] * productionMultiplier;

			m_Resources["Alloy"] += m_Buildings["Refinery"] * productionMultiplier;
			m_Resources["Fuel"] += m_Buildings["Fuel Synthesizer"] * productionMultiplier;
			m_Resources["Biomass"] += m_Buildings["Biomass Generator"] * productionMultiplier;
			m_Resources["Silicon"] += m_Buildings["Silicon Factory"] * productionMultiplier;
			m_Resources["Data"] += (m_Buildings["Quantum Lab"] * 3) * productionMultiplier;
			m_Resources["Energy"] += (m_Buildings["Fusion Reactor"] * 3) * productionMultiplier;

			m_Resources["Energy"] += (m_Buildings["Dyson Swarm"] * 10) * productionMultiplier;
			m_Resources["NanoCompounds"] += m_Buildings["Stellar Forge"] * productionMultiplier;
			m_Resources["Antimatter"] += m_Buildings["Stellar Forge"] * productionMultiplier;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Game::SaveGame(const std::string& filename) {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);
	nlohmann::json j;

	j["Empire"]["CurrentStage"] = m_Empire.m_CurrentStage;
	j["Empire"]["Population"] = m_Empire.m_Population;

	j["Resources"] = m_Resources;

	j["Buildings"] = m_Buildings;

	try {
		std::ofstream file(filename);
		file << std::setw(4) << j;
		file.close();
		std::cout << "Saved game to " << filename << "." << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error saving game: " << e.what() << std::endl;
	}

}
void Game::LoadGame(const std::string& filename) {
	std::lock_guard<std::mutex> lock(m_ResourceMutex);
	nlohmann::json j;

	try {
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cerr << "No save file found.\n";
			return;
		}
		file >> j;
		file.close();

		if (!j.contains("Empire") || !j.contains("Resources") || !j.contains("Buildings")) {
			std::cerr << "Invalid or corrupted save file. Starting new game.\n";
			return;
		}

		m_Empire.m_CurrentStage = j["Empire"]["CurrentStage"].get<int>();
		m_Empire.m_Population = j["Empire"]["Population"].get<int>();

		for (auto& [key, value] : j["Resources"].items()) {
			m_Resources[key] = value.get<float>();
		}

		for (auto& [key, value] : j["Buildings"].items()) {
			m_Buildings[key] = value.get<int>();
		}

		std::cout << "Game loaded from " << filename << ".\n";
	}
	catch (const std::exception& e) {
		std::cerr << "Error loading game: " << e.what() << std::endl;
	}
}

Game::Game()
	: m_CurrentPage(0), m_Window(sf::RenderWindow(sf::VideoMode({ SCR_WIDTH, SCR_HEIGHT }), "Nova Imperium")), m_ProgramRunning(true), m_StagePage(1), m_TitleText(sf::Text(NUNITO, "Nova Imperium", 50U)), m_StartButton(NUNITO, "Enter Game", sf::Vector2f(20.0f, 250.0f), sf::Vector2f(150.0f, 40.0f), [this]() { m_CurrentPage = 1; }), m_ExitButton(NUNITO, "Exit Game", sf::Vector2f(20.0f, 310.0f), sf::Vector2f(150.0f, 40.0f), [this]() { m_ProgramRunning = false; m_Window.close(); }),
	  m_ResourceTitle(sf::Text(NUNITO, "Resources", 40U)) {
	m_UpdateThread = std::thread(&Game::UpdateThread, this);

	LoadGame("savegame.json");

	if (DEBUG_MODE) {
		m_Resources.clear();
		m_Resources = {
			{"Credits", 100000.0f},		// The international currency in Nova Imperium. Used to build buildings and buy resources.
			{"Food", 100000.0f},			// Population will not grow if food requirement is not met
			{"Energy", 100000.0f},			// Each building consumes power, if energy requirement is not met, production will be halved.
			{"Data", 100000.0f},			// Used for increasing stage.

			{"Wood", 100000.0f},			// Basic stage one building material. Sold for 2 credits.
			{"Stone", 100000.0f},			// Another building material. Sold for 4 credits.
			{"Iron", 100000.0f},			// Another building material. Sold for 8 credits.

			{"Fuel", 100000.0f},			// Consumed by fusion reactor. Sold for 20 credits.
			{"Alloy", 100000.0f},			// Stage 2 building material. Sold for 40 credits.
			{"Silicon", 100000.0f},			// Another stage 2 building material. Sold for 60 credits.
			{"Biomass", 100000.0f},			// Another stage 2 building material. Sold for 80 credits.

			{"NanoCompounds", 100000.0f},	// Stage 3 building material. Sold for 200 credits.
			{"Antimatter", 100000.0f},		// Needed to colonize new planets. Sold for 400 credits.
			{"Helium-3", 100000.0f},		// Stage 3 building material. Sold for 600 credits.

			{"Knowledge", 0.0f},		// Prestige resource. Increases resource production.
			{"Influence", 0.0f},		// Increases trade profits.
		};
	}

	m_TitleText.setPosition(sf::Vector2f(18.0f, 160.0f));
	m_ResourceTitle.setPosition(sf::Vector2f(20.0f, 20.0f));

	float buttonY = 150.0f;
	for (int i = 4; i < 14; ++i) {
		if (i == 7 || i == 11) buttonY = 150.0f;
		float buttonX = 200.0f;
		if (i >= 11 && i < 14) buttonX = 300.0f;
		int index = i;
		m_SellButtons.emplace_back(NUNITO, "Sell (" + std::to_string(static_cast<int>(std::floor(m_ResourcePrices[i]))) + "C)", sf::Vector2f(buttonX, buttonY), sf::Vector2f(100.0f, 25.0f), [this, index]() {
			std::lock_guard<std::mutex> lock(m_ResourceMutex);
			if (m_Resources[RESOURCE_NAMES[index]] >= 1) {
				m_Resources[RESOURCE_NAMES[index]]--;
				m_Resources["Credits"] += m_ResourcePrices[index];
			}
			});
		m_SellAllButtons.emplace_back(NUNITO, "Sell " + std::to_string(m_Resources[RESOURCE_NAMES[i]]) + " (" + std::to_string(m_Resources[RESOURCE_NAMES[i]] * m_ResourcePrices[i]) + "C)", sf::Vector2f(buttonX + 115.0f, buttonY), sf::Vector2f(150.0f, 25.0f), [this, index]() {
			std::lock_guard<std::mutex> lock(m_ResourceMutex);
			float numResources = m_Resources[RESOURCE_NAMES[index]];
			m_Resources[RESOURCE_NAMES[index]] = 0.0f;
			m_Resources["Credits"] += m_ResourcePrices[index] * numResources;
			});

		buttonY += 30.0f;
	}

	m_Window.setFramerateLimit(60);

	float textY = 70.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Available Population: " + std::to_string(m_Empire.m_Population), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, textY));

	textY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Credits: " + std::to_string(static_cast<int>(std::floor(m_Resources["Credits"]))) + "C", 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, textY));

	textY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Food: " + std::to_string(static_cast<int>(std::floor(m_Resources["Food"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, textY));

	textY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Energy: " + std::to_string(static_cast<int>(std::floor(m_Resources["Energy"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, textY));

	textY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Data: " + std::to_string(static_cast<int>(std::floor(m_Resources["Data"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, textY));

	textY += 40.0f;

	float outpostTextY = textY;

	outpostTextY += 40.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Wood: " + std::to_string(static_cast<int>(std::floor(m_Resources["Wood"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, outpostTextY));

	outpostTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Stone: " + std::to_string(static_cast<int>(std::floor(m_Resources["Stone"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, outpostTextY));

	outpostTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Iron: " + std::to_string(static_cast<int>(std::floor(m_Resources["Iron"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, outpostTextY));

	float colonyTextY = textY;

	colonyTextY += 40.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Fuel: " + std::to_string(static_cast<int>(std::floor(m_Resources["Fuel"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(250.0f, colonyTextY));

	colonyTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Alloy: " + std::to_string(static_cast<int>(std::floor(m_Resources["Alloy"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(250.0f, colonyTextY));

	colonyTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Silicon: " + std::to_string(static_cast<int>(std::floor(m_Resources["Silicon"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(250.0f, colonyTextY));

	colonyTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Biomass: " + std::to_string(static_cast<int>(std::floor(m_Resources["Biomass"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(250.0f, colonyTextY));

	float empireTextY = textY;
	sf::Text stageText(NUNITO, "Empire", 30U);
	stageText.setPosition(sf::Vector2f(500.0f, empireTextY));
	m_Window.draw(stageText);

	empireTextY += 40.0f;

	m_ResourceTexts.emplace_back(NUNITO, "NanoCompounds: " + std::to_string(static_cast<int>(std::floor(m_Resources["NanoCompounds"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(500.0f, empireTextY));

	empireTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Antimatter: " + std::to_string(static_cast<int>(std::floor(m_Resources["Antimatter"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(500.0f, empireTextY));

	empireTextY += 30.0f;

	m_ResourceTexts.emplace_back(NUNITO, "Helium-3: " + std::to_string(static_cast<int>(std::floor(m_Resources["Helium-3"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(500.0f, empireTextY));

	m_ResourceTexts.emplace_back(NUNITO, "Knowledge: " + std::to_string(static_cast<int>(std::floor(m_Resources["Knowledge"]))), 25U);
	m_ResourceTexts.back().setPosition(sf::Vector2f(20.0f, 370.0f + 40.0f));

	textY = 150.0f;
	for (int i = 4; i < 7; ++i) {
		m_TradeTexts.emplace_back(NUNITO, RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))), 25U);
		m_TradeTexts.back().setPosition(sf::Vector2f(20.0f, textY));
		m_Window.draw(m_TradeTexts.back());
		textY += 30.0f;
	}

	textY = 150.0f;
	for (int i = 7; i < 11; ++i) {
		m_TradeTexts.emplace_back(NUNITO, RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))), 25U);
		m_TradeTexts.back().setPosition(sf::Vector2f(20.0f, textY));
		m_Window.draw(m_TradeTexts.back());
		textY += 30.0f;
	}

	textY = 150.0f;
	for (int i = 11; i < 14; ++i) {
		m_TradeTexts.emplace_back(NUNITO, RESOURCE_NAMES[i] + ": " + std::to_string(static_cast<int>(std::floor(m_Resources[RESOURCE_NAMES[i]]))), 25U);
		m_TradeTexts.back().setPosition(sf::Vector2f(20.0f, textY));
		m_Window.draw(m_TradeTexts.back());
		textY += 30.0f;
	}
}

Game::~Game() {
	m_ProgramRunning = false;
	if (m_UpdateThread.joinable())
		m_UpdateThread.join();
	else
		std::cerr << "Failed to join thread!" << std::endl;

	SaveGame("savegame.json");
}

void Game::Run() {
	std::vector<Button> pageBar;
	pageBar.emplace_back(NUNITO, "Resources", sf::Vector2f(2.0f, 550.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
		m_CurrentPage = 1;
		});
	pageBar.emplace_back(NUNITO, "Buildings", sf::Vector2f(127.0f, 550.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
		m_CurrentPage = 2;
		m_StagePage = 1;
		});
	pageBar.emplace_back(NUNITO, "Trade", sf::Vector2f(252.0f, 550.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
		m_CurrentPage = 3;
		m_StagePage = 1;
		});
	pageBar.emplace_back(NUNITO, "????????", sf::Vector2f(377, 550.0f), sf::Vector2f(125.0f, 50.0f), [this]() {
		if (m_Buildings["Orbital Shipyard"] >= 1)
			m_CurrentPage = 4;
		});

	while (m_Window.isOpen()) {
		while (const std::optional event = m_Window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				m_Window.close();
				m_ProgramRunning = false;
			}
		}

		m_Window.clear();

		if (m_CurrentPage == 0) {
			DrawMainMenu();
		}
		else if (m_CurrentPage == 1) {
			DrawResourcePage();
		}
		else if (m_CurrentPage == 2) {
			DrawBuildingPage();
		}
		else if (m_CurrentPage == 3) {
			DrawTradePage();
		}
		else if (m_CurrentPage == 4) {
			DrawPrestigePage();
		}

		if (m_Buildings["Orbital Shipyard"] >= 1) {
			pageBar[3].m_Label.setString("Colonize");
		}
		else {
			pageBar[3].m_Label.setString("????????");
		}

		if (m_CurrentPage != 0) {
			for (auto& button : pageBar) {
				m_Window.draw(button.m_Rect);
				m_Window.draw(button.m_Label);

				if (button.IsPressed(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
					if (button.m_OnClick) button.m_OnClick();
				}
			}
		}

		m_Window.display();
	}
}