#include "CharacterGenerator.h"

using namespace std;

void charGen::mainMenu(sf::RenderWindow& window) {
    // Prepare variables
    sf::Vector2<int> mousePos;
    sf::Font font; 
    sf::Text title;
    sf::Event event;
    int hoverVal;

    vector<statBlock> abilityList;
    vector<statBlock> weaknessList;
    vector<string> background;
    std::vector<std::vector<string>> backCateOpt;

    std::vector<string> backCate = { "Nation", "Race", "Element", "Source", "Religion" };

    Menu newMenu(400, 400, 200, 600, { "Background", "Stats", "Print", "Exit" });

    // Add background options
    backCateOpt.push_back({ "Skelstaris", "Blaycorrum", "Arim", "Native" });
    backCateOpt.push_back({ "Human", "Halfling", "Goliath" });
    backCateOpt.push_back({ "Fire", "Water", "Earth", "Wind", "Ice", "Lightning", "Shadow", "Light" });
    backCateOpt.push_back({ "Faith", "Magic", "Tech", "Instinct" });
    backCateOpt.push_back({ "Mythos", "Death", "Nature", "Deception", "Fate", "Conquest", "Wilds", "Security", "Desire", "Spring", "Summer", "Fall", "Winter", "Progression", "Monsters" });

    // Set Font
    font.loadFromFile("font/arial.ttf");

    // Prepare title
    title.setString("Character Maker Main Menu");
    title.setCharacterSize(37);
    title.setFont(font);
    title.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        // Determine mouse position
        mousePos = sf::Mouse::getPosition(window);
        hoverVal = newMenu.hover(mousePos);

        while (window.pollEvent(event))
        {
            // Close Window on Close
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                switch (hoverVal) {
                case 0:
                    // Start the Backgound Creator
                    background = charGen::backgroundMenu(window, backCate, backCateOpt);
                    break;
                case 1:
                    // Start Stat Menu
                    charGen::statsMenu(window, abilityList, weaknessList);
                    break;
                case 2:
                   // Print to screen
                    cout << charGen::output(backCate, background, abilityList, weaknessList);
                    cout << charGen::stat(abilityList, weaknessList);
                    break;
                case 3:
                    // Exit
                    return;
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
    // Initialize Variables
    string returnStr;

    // Add background
    if (!background.empty()) {
        if (background.size() == cates.size())
            for (int i = 0; i < background.size(); i++)
                returnStr += cates[i] + ": " + background[i] + "\n";

        returnStr += "\n";
    }
    // Add abilities
    if (!abilityList.empty()) {
        returnStr += "Ability List\n";

        for (int i = 0; i < abilityList.size(); i++)
            returnStr += abilityList[i].name +" [" + to_string(abilityList[i].value) + "] - " + abilityList[i].description + "\n";

        returnStr += "\n";
    }

    // Add weaknesses
    if (!weaknessList.empty()) {
        returnStr += "Weakness List\n";

        for (int i = 0; i < weaknessList.size(); i++)
            returnStr += weaknessList[i].name + " [" + to_string(weaknessList[i].value) + "] - " + weaknessList[i].description + "\n";
        
        returnStr += "\n";
    }
    
    // Return the result
    return returnStr;
}

std::string charGen::stat(std::vector<statBlock>& abilityList, std::vector<statBlock>& weaknessList) {
    // Initialize Variables
    string returnStr;

    vector<int> attStat = { 0 , 0 };         // To-Hit, DV
    vector<int> barStat = { 20 , 20 };       // HP, END
    vector<int> avoidStat = { 5 , 5 };       // Dodge, Resolve
   
    int armorStat = 0;                       // Armor


    // Prepare a vector of stat effecting abilities
    vector<string> statAbility;
    statAbility.insert(statAbility.end(), { "Agile" , "Combat Expert" });
    statAbility.insert(statAbility.end(), { "Strong" , "Attack" });
    statAbility.insert(statAbility.end(), { "Tough" , "Vigorous" });
    statAbility.insert(statAbility.end(), { "Evasive" , "Quick" , "Iron-Willed" });
    statAbility.insert(statAbility.end(), { "Armored" });

    // Prepare a vector of stat effecting weaknesses
    vector<string> statWeakness;
    statWeakness.insert(statWeakness.end(), { "Clumsy" , "Weak" });
    statWeakness.insert(statWeakness.end(), { "Frail" , "Languid" });
    statWeakness.insert(statWeakness.end(), { "Slow" , "Weak-Willed" });

    // For every ability
    for (statBlock abil : abilityList) {
        // Find the ability
        auto iter = find(statAbility.begin(), statAbility.end(), abil.name);

        // Find the ability
        int select = -1;
        if (iter != statAbility.end())
            select = distance(statAbility.begin(), iter);
        // Continue if not found
        else
            continue;

        switch (select) {
        case 0: // Agile
        case 1: // Combat Expert
            attStat[0] += abil.value;
            break;
        case 2: // Strong
        case 3: // Attack
            attStat[1] += abil.value;
            break;
        case 4: // Tough
            barStat[0] += trunc(((float)abil.value / 5.0) * 6.0) * 5.0;
            break;
        case 5: // Vigorous
            barStat[1] += trunc(((float)abil.value / 5.0) * 6.0) * 5.0;
            break;
        case 6: // Evasive
            avoidStat[0] += abil.value;
            avoidStat[1] += abil.value;
            break;
        case 7: // Quick
            avoidStat[0] += abil.value;
            break;
        case 8: // Iron-Willed
            avoidStat[1] += abil.value;
            break;
        case 9: // Armored
            armorStat += abil.value;
            break;
        }
    }

    // For every weakness
    for (statBlock weak : weaknessList) {
        // Find the ability
        auto iter = find(statWeakness.begin(), statWeakness.end(), weak.name);

        // Find the ability
        int select = -1;
        if (iter != statWeakness.end())
            select = distance(statWeakness.begin(), iter);
        // Continue if not found
        else
            continue;

        switch (select) {
        case 0: // Clumsy
            attStat[0] -= weak.value;
            break;
        case 1: // Weak
            attStat[1] -= weak.value;
            break;
        case 2: // Frail
            barStat[0] -= weak.value * 5.0;
            break;
        case 3: // Languid
            barStat[1] -= weak.value * 5.0;
            attStat[1] += weak.value;
            break;
        case 4: // Slow
            avoidStat[0] -= weak.value;
            break;
        case 5: // Weak-Willed
            avoidStat[1] -= weak.value;
            break;
        }
    }

    // Add bar stat information
    returnStr += "Health: " + to_string(barStat[0]) + ", End: " + to_string(barStat[1]) + " \n";

    // Add avoid stat information
    returnStr += "Dodge: " + to_string(avoidStat[0]) + ", Resolve: " + to_string(avoidStat[1]) + " \n";

    // Add block stat information
    returnStr += "Armor: " + to_string(armorStat) + " \n\n";

    // Add basic attack information
    returnStr += "Attacks\nBasic - " + to_string(attStat[0]) + " To-Hit, " + to_string(attStat[1]) + " DV, 0 END";

    // Return the result
    return returnStr;
}