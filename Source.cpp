#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <time.h>

#include <SFML/Graphics.hpp> //https://www.sfml-dev.org/tutorials/2.5/start-vc.php

#include "Supports.h"
#include "CharacterGenerator.h"

using namespace std;

// Global Variables
string version = "0.1.38";   // Current version number

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Character Manager v" + version, sf::Style::Close);
    charGen::mainMenu(window);
    return 0;
}