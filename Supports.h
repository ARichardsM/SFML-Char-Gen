#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <SFML/Graphics.hpp> //https://www.sfml-dev.org/tutorials/2.5/start-vc.php

// GUI Button Class
class Button {
public:
	sf::Text text;
	sf::RectangleShape box;

	float height;
	float width;

	// Initializer
	Button(sf::Vector2f size);

	// Determines If The Mouse Is Hovering This Button
	bool hover(sf::Vector2i& mousePt);
	void setString(std::string textString);
	void setPosition(float x, float y);
	void setFont(sf::Font& font);
};

// GUI Menu CLass
class Menu {
public:
	std::vector<Button> Buttons;
	std::vector<std::string> Options;
	sf::Font TxtFont;

	// Initializer
	Menu(int x, int y, int height, float width, std::vector<std::string> options);

	// Determines If The Mouse Is Hovering Any Element In The Menu
	int hover(sf::Vector2i& mousePt);
	// Handles Drawing All Parts of the Menu
	void draw(sf::RenderWindow& window);
};


// GUI Selection Window
class selectScreen {
public:
	int w() { return 10; };
};