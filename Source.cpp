#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <time.h>

#include <SFML/Graphics.hpp> //https://www.sfml-dev.org/tutorials/2.5/start-vc.php

#include "Supports.h"
#include "BondTracker.h"
#include "CharacterGenerator.h"

using namespace std;

// Main Game Window
void gameMainMenu(sf::RenderWindow& window);
void debugMenu(sf::RenderWindow& window);
void testMenu(sf::RenderWindow& window);

// Global Variables
string version = "0.1.2";   // Current version number

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Character Manager v" + version, sf::Style::Close);
    mainMenu(window);
    return 0;
}

void mainMenu(sf::RenderWindow& window) {
    Menu newMenu(400, 400, 200, 600, { "Character Maker", "Bond Manager", "Exit" });

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    sf::Text title;
    title.setString("Character Manager Version " + version);
    title.setCharacterSize(37);
    title.setFont(font);
    title.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        int hoverVal = newMenu.hover(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                switch (hoverVal) {
                case 0:
                    charGenMainMenu(window);
                    break;
                case 1:
                    bonds::MainMenu(window);
                    break;
                case 2:
                    window.close();
                    break;
                }
        }

        // Draw the window
        window.clear();

        window.draw(title);
        newMenu.draw(window);
        
        window.display();
    }
}