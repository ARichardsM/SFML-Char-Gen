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
string version = "0.1.1";   // Current version number

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Character Manager v" + version);
    //gameMainMenu(window);
    //debugMenu(window);
    testMenu(window);
    return 0;
}

void testMenu(sf::RenderWindow& window) {
    Menu newMenu(400, 300, 200, 200, { "Character Maker", "Bond Manager", "Exit" });

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
                    std::cout << "0\n";
                    break;
                case 1:
                    std::cout << "1\n";
                    break;
                case 2:
                    std::cout << "2\n";
                    break;
                }
        }

        // Draw the window
        window.clear();

        newMenu.draw(window);
        
        window.display();
    }
}

void debugMenu(sf::RenderWindow& window) {
    sf::Vector2<int> mousePos;
    sf::CircleShape shape(100.f);
    sf::Font font;

    shape.setFillColor(sf::Color::Green);
    vector<Button> tempName; 
    font.loadFromFile("font/arial.ttf");

    for (int i = 0; i < 3; i++) {
        tempName.push_back(Button(sf::Vector2f(620, 50)));
    }

    sf::Text title;

    title.setString("Character Manager Version " + version);
    title.setCharacterSize(37);
    title.setFont(font);
    title.setFillColor(sf::Color::Cyan);

    for (int i = 0; i < 3; i++) {
        tempName[i].setPosition(320.f, 325.f + (60.f * i));
        tempName[i].setFont(font);
    }

    tempName[0].setString("Character Maker");
    tempName[1].setString("Bond Manager");
    tempName[2].setString("Exit");

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int i = 0; i < 3; i++) {
                tempName[i].hover(window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 300 && mousePos.y < 350) {
                    cout << "CHAR GEN \n";
                }
                else if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 360
                    && mousePos.y < 410) {
                    cout << "BONDS \n";
                }
                else if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 420
                    && mousePos.y < 470) {
                    window.close();
                }
            }
        }

        // Draw the window
        window.clear();
        window.draw(shape);
        window.draw(title);
        for (int i = 0; i < tempName.size(); i++) {
            window.draw(tempName[i].box);
            window.draw(tempName[i].text);
        }
        window.display();
    }
}

void gameMainMenu(sf::RenderWindow& window) {
    sf::Vector2<int> mousePos;
    sf::CircleShape shape(100.f);
    sf::Font font;

    shape.setFillColor(sf::Color::Green);
    vector<sf::Text> buttonText;
    vector<sf::RectangleShape> buttonBlock;
    font.loadFromFile("font/arial.ttf");

    for (int i = 0; i < 3; i++) {
        buttonText.push_back(sf::Text());
        buttonBlock.push_back(sf::RectangleShape(sf::Vector2f(620, 50)));
    }

    sf::Text title;

    title.setString("Character Manager Version " + version);
    title.setCharacterSize(37);
    title.setFont(font);
    title.setFillColor(sf::Color::Cyan);
    buttonText[0].setString("Character Maker");
    buttonText[1].setString("Bond Manager");
    buttonText[2].setString("Exit");

    for (int i = 0; i < 3; i++) {
        buttonText[i].setCharacterSize(24);
        buttonText[i].setFont(font);
        buttonText[i].setPosition(320.f, 325.f + (60.f * i));
        buttonText[i].setFillColor(sf::Color::Blue);
        buttonBlock[i].setFillColor(sf::Color::Green);
        buttonBlock[i].setOutlineColor(sf::Color::Red);
        buttonBlock[i].setPosition(10.f, 300.f + (60.f * i));
        sf::FloatRect temp = buttonText[i].getLocalBounds();
        buttonText[i].setOrigin(temp.left + temp.width / 2.0f,
            temp.top + temp.height / 2.0f);
    }

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int i = 0; i < 3; i++) {
                if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 300 + (60.f * i)
                    && mousePos.y < 350 + (60.f * i)) {
                    buttonBlock[i].setOutlineThickness(5);
                }
                else {
                    buttonBlock[i].setOutlineThickness(0);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 300 && mousePos.y < 350) {
                    charGenMainMenu(window);
                }
                else if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 360
                    && mousePos.y < 410) {
                    bonds::MainMenu(window);
                }
                else if (mousePos.x > 10 && mousePos.x < 630 && mousePos.y > 420
                    && mousePos.y < 470) {
                    window.close();
                }
            }
        }

        // Draw the window
        window.clear();
        window.draw(shape);
        window.draw(title);
        for (int i = 0; i < 3; i++) {
            window.draw(buttonBlock[i]);
            window.draw(buttonText[i]);
        }
        window.display();
    }
}