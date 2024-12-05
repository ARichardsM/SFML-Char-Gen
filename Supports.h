#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <time.h>
#include <SFML/Graphics.hpp> //https://www.sfml-dev.org/tutorials/2.5/start-vc.php

// GUI Button Class
class Button {
public:
	sf::Text text;
	sf::RectangleShape box;

	float height;
	float width;
	bool isClicked = false;

	// Initializer
	Button(sf::Vector2f size);

	// Determines If The Mouse Is Hovering This Button
	bool hover(sf::Vector2i& mousePt);

	// Toggle the clicked effect
	void toggleClick();

	void setString(std::string textString);
	void setPosition(float x, float y);
	void setFont(sf::Font& font);
};

// GUI Menu Class
class Menu {
public:
	std::vector<Button> Buttons;
	std::vector<std::string> Options;
	sf::Font TxtFont;

	// Initializer
	Menu(int x, int y, int height, float width, std::vector<std::string> options);
	Menu(int x, int y, int height, float width, std::vector<std::string> options, std::vector<int> position);
	Menu() = default;

	// Determines If The Mouse Is Hovering Any Element In The Menu
	int hover(sf::Vector2i& mousePt);
	// Handles Drawing All Parts of the Menu
	void draw(sf::RenderWindow& window);
};

// GUI Menu Class
class ScrollMenu : public Menu {
private:
	// Adjust the available buttons
	void updateDisplay();

public:
	int optSelected = -1, optOffset = 0;

	// Initializer
	ScrollMenu(int x, int y, int height, float width, std::vector<std::string> options);
	
	// Toggle the clicked effect
	void toggleClick(int button);
	// Scroll the menu
	void scroll(bool scrollUp);
	// Swap the options
	void swapOptions(std::vector<std::string> newOptions);

	// Handles Drawing All Parts of the Menu
	void draw(sf::RenderWindow& window);
};

// GUI Selection Window For Background
class backgroundScreen {
public:
	struct {
		sf::Text title;
		sf::Text name;
		std::vector<sf::Text> bodyArray;
		sf::Texture image;
		sf::Sprite imageSpr;
	} display;

	std::string title;
	std::vector<std::string> options;
	sf::Font TxtFont;
	int optSel;
	bool imageBool, txtBool;

	// Initializer
	backgroundScreen(std::string topText, std::vector<std::string> optText);

	// Change Title and Options
	void swapData(std::string topText, std::vector<std::string> optText);

	// Go To Another Option
	void swapOptions();

	// Update the display with the current selections
	void updateDisplay();

	// Handles Drawing All Parts of the Screen
	void draw(sf::RenderWindow& window);
};

// GUI Selection Window For Stats
class statScreen {
public:
	struct {
		sf::Text abilTitle, weakTitle;
		std::vector<sf::Text> abilBody, weakBody;
	} display;

	std::vector<std::string> abilArray, weakArray;
	sf::Font TxtFont;

	// Initializer
	statScreen(std::vector<std::vector<std::string>> abilList, std::vector<std::vector<std::string>> weakList);

	// Change Title and Body
	void swapData(std::vector<std::string> abilList, std::vector<std::string> weakList);
};