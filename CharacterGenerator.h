#pragma once
#include <sstream>
#include "Supports.h"

namespace charGen {
	void mainMenu(sf::RenderWindow& window);
	void backgroundMenu(sf::RenderWindow& window, std::string(&text)[5]);
}

void charGenBackgroundMenu(sf::RenderWindow& window, std::string(&text)[5]);
void charGenStatsMainMenu(sf::RenderWindow& window, std::vector<std::vector<std::string>>& abilityList, std::vector<std::vector<std::string>>& weaknessList);
std::vector<std::string> charGenStatsAddMenu(sf::RenderWindow& window, bool type);
void charGenStatsRemoveMenu(sf::RenderWindow& window, bool type, std::vector<std::vector<std::string>>& list);