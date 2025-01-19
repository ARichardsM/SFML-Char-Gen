#include "CharacterGenerator.h"

using namespace std;

void printCharGen(string(&text)[5], vector<vector<string>>& abilityList, vector<vector<string>>& weaknessList) {
    ofstream file;
    file.open("stats.txt");

    int health = 20, end = 20, def = 0, dodge = 10, resolve = 10, armor = 0, initi = 0;
    int acc = 0, melDX = 1, ranDX = 1, traDX = 1;

    for (int i = 0; i < abilityList.size(); i++) {
        if (abilityList[i][0] == "Tough") {
            health = health + (stoi(abilityList[i][1]) + floor(stoi(abilityList[i][1]) / 5)) * 5;
        }
        else if (abilityList[i][0] == "Vigorous") {
            end = end + (stoi(abilityList[i][1]) + floor(stoi(abilityList[i][1]) / 5)) * 5;
        }
        else if ((abilityList[i][0] == "Barrier") || (abilityList[i][0] == "Evasive")
            || (abilityList[i][0] == "Incorporeal Form") || (abilityList[i][0] == "Teleport")) { //defense roll
            def = max(def, stoi(abilityList[i][1]));
        }
        else if (abilityList[i][0] == "Quick") {
            initi = stoi(abilityList[i][1]) * 2;
            dodge = dodge + stoi(abilityList[i][1]);
        }
        else if (abilityList[i][0] == "Iron-Willed") {
            resolve = resolve + stoi(abilityList[i][1]);
        }
        else if ((abilityList[i][0] == "Agile") || (abilityList[i][0] == "Combat Expert")) { //attack roll
            acc = acc + stoi(abilityList[i][1]);
        }
        else if (abilityList[i][0] == "Attack") { //damage multipler
            melDX = melDX + stoi(abilityList[i][1]);
            ranDX = ranDX + stoi(abilityList[i][1]);
            traDX = traDX + stoi(abilityList[i][1]);
        }
        else if (abilityList[i][0] == "Telekinesis") { //damage multipler
            ranDX = ranDX + stoi(abilityList[i][1]);
        }
        else if (abilityList[i][0] == "Strong") { //damage multipler
            melDX = melDX + stoi(abilityList[i][1]);
        }
        else if (abilityList[i][0] == "Armored") {
            armor = stoi(abilityList[i][1]);
        }
    }

    dodge = dodge + def;
    resolve = resolve + def;

    for (int i = 0; i < weaknessList.size(); i++) {
        if (weaknessList[i][0] == "Frail") {
            health = health - stoi(weaknessList[i][1]) * 5;
        }
        else if (weaknessList[i][0] == "Languid") {
            end = end - stoi(weaknessList[i][1]) * 5;
        }
        else if ((weaknessList[i][0] == "Clumsy")) { //attack roll
            acc = acc - stoi(weaknessList[i][1]);
        }
        else if ((weaknessList[i][0] == "Slow")) { //defense roll
            dodge = dodge - stoi(weaknessList[i][1]);
            initi = stoi(weaknessList[i][1]) * -2;
        }
        else if ((weaknessList[i][0] == "Weak")) { //damage multipler
            melDX = melDX - stoi(weaknessList[i][1]);
        }
        else if (weaknessList[i][0] == "Weak-Willed") {
            resolve = resolve - stoi(weaknessList[i][1]);
        }
    }

    file << "Health: " << health << endl;
    file << "Endurance: " << end << endl;
    file << "Dodge: " << dodge << endl;
    file << "Resolve: " << resolve << endl;
    file << "Armor: " << armor << endl;
    file << "Initiative: " << initi << endl;

    file << endl << "Abilities" << endl;
    for (int i = 0; i < abilityList.size(); i++) {
        file << abilityList[i][0] << " " << abilityList[i][1] << endl;
    }

    file << endl << "Weaknesses" << endl;
    for (int i = 0; i < weaknessList.size(); i++) {
        file << weaknessList[i][0] << " " << weaknessList[i][1] << endl;
    }

    file << endl << "Attacks" << endl;
    file << "Attack (Melee Element) - Mod: " << acc << " DMG: " << melDX << " END: 0" << endl;
    file << "Attack (Ranged Element) - Mod: " << acc << " DMG: " << ranDX << " END: 0" << endl;
    file << "Attack (Trap Element) - Mod: " << acc << " DMG: " << traDX << " END: 0" << endl;
}

void charGen::mainMenu(sf::RenderWindow& window) {
    sf::Vector2<int> mousePos;
    sf::CircleShape shape(100.f);
    sf::Font font;

    vector<statBlock> abilityList;
    vector<statBlock> weaknessList;

    std::vector<string> backCate = { "Nation", "Race", "Element", "Source", "Religion" };
    std::vector<std::vector<string>> backCateOpt;

    backCateOpt.push_back({ "Skelstaris", "Blaycorrum", "Arim", "Native" });
    backCateOpt.push_back({ "Human", "Halfling", "Goliath" });
    backCateOpt.push_back({ "Fire", "Water", "Earth", "Wind", "Ice", "Lightning", "Shadow", "Light" });
    backCateOpt.push_back({ "Faith", "Magic", "Tech", "Instinct" });
    backCateOpt.push_back({ "Mythos", "Death", "Nature", "Deception", "Fate", "Conquest", "Wilds", "Security", "Desire", "Spring", "Summer", "Fall", "Winter", "Progression", "Monsters" });

    std::vector<string> returnBack;

    string text[] = { "Skelstaris", "Human", "Fire", "Faith", "Mythos" };

    Menu newMenu(400, 400, 200, 600, { "Background", "Stats", "Print", "Exit" });

    shape.setFillColor(sf::Color::Green);
    
    font.loadFromFile("font/arial.ttf");

    sf::Text title;

    title.setString("Character Maker Main Menu");
    title.setCharacterSize(37);
    title.setFont(font);
    title.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        int hoverVal = newMenu.hover(mousePos);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                switch (hoverVal) {
                case 0:
                    // Start the Backgound Creator
                    returnBack = charGen::backgroundMenu(window, backCate, backCateOpt);

                    // Print the Result to the Console
                    for (string i : returnBack)
                        cout << i << " ";
                    break;
                case 1:
                    charGen::statsMenu(window, abilityList, weaknessList);
                    break;
                case 2:
                   // printCharGen(text, abilityList, weaknessList);
                    break;
                case 3:
                    return;
                    break;
                }
        }

        // Draw the window
        window.clear();
        //window.draw(shape);
        window.draw(title);

        newMenu.draw(window);

        window.display();
    }
}

std::vector<std::string> charGen::backgroundMenu(sf::RenderWindow& window, std::vector<std::string> cates, std::vector<std::vector<std::string>> cateOpts) {
    // Validate Categories Have Values
    if (cates.size() == 0) {
        cout << "No Categories Found\n";
        return {};
    }

    // Validate Categories And Category Options Match
    if (cates.size() != cateOpts.size()) {
        cout << "Categories And Category Options Mismatch\n";
        return {};
    }
    
    // Initialize Variables
    Menu newMenu(400, 400, 200, 600, { "Change", "Next", "Back" });
    backgroundScreen newScreen(cates[0], cateOpts[0]);
    sf::Vector2<int> mousePos;
    int cateCurr = 0, cateSize = cates.size(), hoverVal;
    sf::Event event;

    // Initialize returnVal to The First Category Option
    std::vector<string> returnVal;
    for (std::vector<std::string> optsPoss : cateOpts)
        returnVal.push_back(optsPoss[0]);
    
    // Break loop is the window is closed
    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        hoverVal = newMenu.hover(mousePos);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                switch (hoverVal) {
                // "Change" Button
                case 0:
                    // Change to another option 
                    newScreen.swapOptions();
                    break;
                // "Next" Button
                case 1:
                    // Update the return val
                    returnVal[cateCurr] = cateOpts[cateCurr][newScreen.optSel];

                    // Go to the next category
                    cateCurr++;
                    if (cateCurr < cateSize) {
                        newScreen.swapData(cates[cateCurr], cateOpts[cateCurr]);
                    }
                    break;
                // "Back" Button
                case 2:
                    // Update the return val
                    returnVal[cateCurr] = cateOpts[cateCurr][newScreen.optSel];

                    // Go to the previous category
                    cateCurr--;
                    if (cateCurr >= 0) {
                        newScreen.swapData(cates[cateCurr], cateOpts[cateCurr]);
                    }
                    break;
                }
            }

            
        }
        // Break the loop when out of categories
        if (cateCurr >= cateSize || cateCurr < 0) {
            break;
        }

        // Draw the window
        window.clear();
        newMenu.draw(window);
        newScreen.draw(window);
        window.display();
    }
    
    return returnVal;
}

void charGen::statsMenu(sf::RenderWindow& window, std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList) {
    // Prepare the screen
    Menu newMenu(400, 400, 200, 600, 
        { "New", "New", "Adjust", "Adjust", "Main Menu"},
        { 2, 2, 1 });

    std::vector<std::vector<std::string>> ListA;
    std::vector<std::vector<std::string>> ListW;
    statScreen newStat(ListA, ListW);

    
    vector<sf::Text> titles;
    vector<sf::Text> actAbil;
    vector<sf::Text> actWeak;

    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::FloatRect temp;

    int hoverVal;

    font.loadFromFile("font/arial.ttf");

    string titleText[] = { "ABILITIES", "WEAKNESSES" };
    for (int i = 0; i < 2; i++) {
        titles.push_back(sf::Text());
        titles[i].setCharacterSize(24);
        titles[i].setFont(font);
        titles[i].setFillColor(sf::Color::Cyan);
        titles[i].setString(titleText[i]);
        temp = titles[i].getLocalBounds();
        titles[i].setOrigin(temp.left + temp.width / 2.0f, 0);
        titles[i].setPosition(225.f + (350 * i), 15);
    }

    for (int i = 0; i < weaknessList.size(); i++) {
        actWeak.push_back(sf::Text());

        actWeak[i].setCharacterSize(20);
        actWeak[i].setFont(font);
        actWeak[i].setFillColor(sf::Color::Cyan);
        actWeak[i].setString(weaknessList[i].name + " (Level " + to_string(weaknessList[i].value) + ")");
        temp = actWeak[i].getLocalBounds();
        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
        actWeak[i].setPosition(575.f, 40 + (22 * i));
    }

    for (int i = 0; i < abilityList.size(); i++) {
        actAbil.push_back(sf::Text());

        actAbil[i].setCharacterSize(20);
        actAbil[i].setFont(font);
        actAbil[i].setFillColor(sf::Color::Cyan);
        actAbil[i].setString(abilityList[i].name + " (Level " + to_string(abilityList[i].value) + ")");
        temp = actAbil[i].getLocalBounds();
        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
        actAbil[i].setPosition(225.f, 40 + (22 * i));
    }


    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;

        hoverVal = newMenu.hover(mousePos);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                switch (hoverVal) {
                case 0:
                    // Add Ability Button
                    charGen::stats::addMenu(window, abilityList, true);
                    charGen::stats::reconfigDisplay(font, abilityList, actAbil);
                    for (int i = 0; i < actAbil.size(); i++) {
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                    
                    break;
                case 1:
                    // Add Weakness Button
                    charGen::stats::addMenu(window, weaknessList, false);
                    charGen::stats::reconfigDisplay(font, weaknessList, actWeak);
                    for (int i = 0; i < actWeak.size(); i++) {
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                    break;
                case 2:
                    // Remove Ability Button
                    charGen::stats::adjustMenu(window, abilityList);
                    charGen::stats::reconfigDisplay(font, abilityList, actAbil);
                    for (int i = 0; i < actAbil.size(); i++) {
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                    break;
                case 3:
                    // Remove Weakness Button
                    charGen::stats::adjustMenu(window, weaknessList);
                    charGen::stats::reconfigDisplay(font, weaknessList, actWeak);
                    for (int i = 0; i < actWeak.size(); i++) {
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                    break;
                case 4:
                    // Main Menu Button
                    return;
                    break;
                }
            }
        }

        // Draw the window
        window.clear();

        for (int i = 0; i < actAbil.size(); i++) {
            window.draw(actAbil[i]);
        }

        for (int i = 0; i < actWeak.size(); i++) {
            window.draw(actWeak[i]);
        }

        for (int i = 0; i < 2; i++) {
            window.draw(titles[i]);
        }

        newMenu.draw(window);
        window.display();
    }
    return;
}

void charGen::stats::addMenu(sf::RenderWindow& window, std::vector<statBlock>& propList, const bool& forAbility) {
    // Declare Variables
    statBlock newStat;
    sf::Vector2<int> mousePos;
    sf::Event event;

    int hoverOpt, hoverDisp;
    bool loopFunc = window.isOpen();

    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    sf::FloatRect temp;

    int statVal = 1;

    // Determine input file
    ifstream fileIn;
    switch (forAbility) {
    case(true):
        fileIn.open("stats/Abilities.txt");
        break;
    case(false):
        fileIn.open("stats/Weaknesses.txt");
        break;
    }

    // Pull data from file
    string line, linePart;
    vector<string> parts;
    vector<string> optionNames;
    vector<vector<string>> options;

    while (getline(fileIn, line)) {
        istringstream iss(line);
        while (getline(iss, linePart, '|')) {
            parts.push_back(linePart);
        }
        optionNames.push_back(parts[0]);
        options.push_back({ parts[0], parts[1] });
        parts.clear();
    }

    // Create Menus
    Menu optMenu(400, 500, 100, 800, { "Increase", "Decrease", "Add", "Exit" }, { 4 });
    ScrollMenu dispMenu(400, 25, 400, 600, optionNames);

    // Create On-Screen Text
    sf::Text onScreenText;
    onScreenText.setCharacterSize(45);
    onScreenText.setFont(font);
    onScreenText.setFillColor(sf::Color::Red);
    onScreenText.setString("At Level: X");
    temp = onScreenText.getLocalBounds();
    onScreenText.setOrigin(temp.left + temp.width / 2.0f, temp.height / 2.0f);
    onScreenText.setPosition(400, 450);

    // Loop the menu
    while (loopFunc)
    {
        loopFunc = window.isOpen();
        mousePos = sf::Mouse::getPosition(window);

        onScreenText.setString("At Level: " + to_string(statVal));

        while (window.pollEvent(event)) {
            // Pull hover values
            hoverOpt = optMenu.hover(mousePos);
            hoverDisp = dispMenu.hover(mousePos);

            // Window Close
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // Handle menu options
                switch (hoverOpt) {
                case 0:                             // Increase the stat value
                    statVal = min(statVal + 1, 5);
                    break;
                case 1:                             // Decrease the stat value
                    statVal = max(statVal - 1, 1);
                    break;
                case 2:                             // Add stat and return to the previous page
                    if (dispMenu.optSelected != -1) {
                        int selectedStat = dispMenu.optSelected + dispMenu.optOffset;
                        newStat.description = options[selectedStat][1];
                        newStat.name = options[selectedStat][0];
                        newStat.value = statVal;

                        propList.push_back(newStat);
                        loopFunc = false;
                    }
                    
                    break;
                case 3:                             // Return to the previous page
                    loopFunc = false;
                    break;
                }

                // Handle scroll menu options
                switch (hoverDisp) {
                case -1:
                    break;
                case 0:
                    dispMenu.scroll(true);
                    break;
                case 6:
                    dispMenu.scroll(false);
                    break;
                default:
                    dispMenu.toggleClick(hoverDisp);
                    break;
                }
            }
        }

        // Draw the window
        window.clear();
        optMenu.draw(window);
        dispMenu.draw(window);
        window.draw(onScreenText);
        window.display();
    }

    return;
}

void charGen::stats::adjustMenu(sf::RenderWindow& window, std::vector<statBlock>& propList) {
    // Declare Variables
    sf::Vector2<int> mousePos;
    sf::Event event;

    int hoverOpt, hoverDisp;
    bool loopFunc = window.isOpen();
    
    // Convert the property list (Vector Statblock to Vector Vector String)
    vector<vector<string>> options;
    vector<string> optionsDisp;
    for (statBlock& proper : propList) {
        options.push_back({ proper.name, to_string(proper.value) });
        optionsDisp.push_back( proper.name + " " +  to_string(proper.value));
    }

    // Create Menus
    Menu optMenu(400, 500, 100, 800, { "Increase", "Decrease", "Exit" }, { 3 });
    ScrollMenu dispMenu(400, 25, 450, 600, optionsDisp);

    // Loop the menu
    while (loopFunc)
    {
        loopFunc = window.isOpen();
        mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            // Pull hover values
            hoverOpt = optMenu.hover(mousePos);
            hoverDisp = dispMenu.hover(mousePos);

            // Window Close
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                // Return to the previous page if exit is clicked
                if (hoverOpt == 2)
                    loopFunc = false;

                // Handle scroll menu options
                switch (hoverDisp) {
                case -1:
                    break;
                case 0:
                    dispMenu.scroll(true);
                    break;
                case 6:
                    dispMenu.scroll(false);
                    break;
                default:
                    dispMenu.toggleClick(hoverDisp);
                    break;
                }

                // Only if an option is currently selected
                if (dispMenu.optSelected != -1) {
                    // Variables for the option selected
                    int optSelect = dispMenu.optSelected;
                    int optVal = stoi(options[optSelect][1]);

                    // Handle increasing and decreasing values
                    switch (hoverOpt) {
                    case -1:
                        break;
                    case 0:
                        // Ensure options are 5 or less
                        if (optVal < 5)
                            optVal++;

                        // Update the option variables
                        options[optSelect][1] = to_string(optVal);
                        optionsDisp[optSelect] = options[optSelect][0] + " " + options[optSelect][1];

                        // Adjust the display
                        dispMenu.swapOptions(optionsDisp);
                        break;
                    case 1:
                        // Ensure options are 0 or more
                        if (optVal > 0)
                            optVal--;

                        // Update the option variables
                        options[optSelect][1] = to_string(optVal);
                        optionsDisp[optSelect] = options[optSelect][0] + " " + options[optSelect][1];

                        // Adjust the display
                        dispMenu.swapOptions(optionsDisp);
                        break;
                    }

                }
            }
        }

        // Draw the window
        window.clear();
        optMenu.draw(window);
        dispMenu.draw(window);
        window.display();
    }

    // Update the property list
    for (int i = propList.size() - 1; i >= 0; i--) {
        if (stoi(options[i][1]) != 0)
            propList[i].value = stoi(options[i][1]);
        else
            propList.erase(propList.begin());
    }
    return;
}

void charGen::stats::reconfigDisplay(sf::Font& font, std::vector<statBlock>& propList, std::vector<sf::Text>& dispList) {
    // Clear the display
    dispList.clear();

    // Initalize Variables
    sf::FloatRect temp;

    // For each statBlock in the vector
    for (int i = 0; i < propList.size(); i++) {
        // Push a new display text
        dispList.push_back(sf::Text());

        // Adjust the display text to match the property
        dispList[i].setCharacterSize(20);
        dispList[i].setFont(font);
        dispList[i].setFillColor(sf::Color::Cyan);
        dispList[i].setString(propList[i].name + " (Level " + to_string(propList[i].value) + ")");
        temp = dispList[i].getLocalBounds();
        dispList[i].setOrigin(temp.left + temp.width / 2.0f, 0);
    }

    return;
}

std::string charGen::output(std::vector<std::string> cates, std::vector<std::string> background, std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList) {
    return NULL;
}