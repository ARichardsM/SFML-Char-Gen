#pragma once
#include <sstream>
#include "Supports.h"

namespace charGen {
	struct statBlock{
		std::string name;
		std::string description;
		int value;	
	};

	void mainMenu(sf::RenderWindow& window);
	std::vector<std::string> backgroundMenu(sf::RenderWindow& window, std::vector<std::string> cates, std::vector<std::vector<std::string>> cateOpts);
	void statsMenu(sf::RenderWindow& window, std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList);

	namespace stats {
		void addMenu(sf::RenderWindow& window, std::vector<statBlock>& propList, const bool& forAbility);
		void adjustMenu(sf::RenderWindow& window, std::vector<statBlock>& propList);

		// Adjust a display text list based on a statBlock list
		void reconfigDisplay(sf::Font& font, std::vector<statBlock>& propList, std::vector<sf::Text>& dispList);
	}

	// Return a string of character information
	std::string output(std::vector<std::string> cates, std::vector<std::string> background, std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList);

	// Return a string derived from character information
	std::string stat(std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList);
}