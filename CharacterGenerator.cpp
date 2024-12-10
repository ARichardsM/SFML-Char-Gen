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

// buttonHover: checks wether a button is being hovered over
bool buttonHover(sf::RectangleShape button, sf::Vector2i mouse) {
    sf::FloatRect border = button.getGlobalBounds();
    sf::Vector2f point;

    point.x = mouse.x;
    point.y = mouse.y;

    if (border.contains(point)) {
        return true;
    }

    return false;
}

// setButton: Sets up a button
void setButton(sf::RectangleShape& background, sf::Text& text, float x, float y) {
    sf::FloatRect temp;

    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(24);
    temp = text.getLocalBounds();
    text.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    text.setPosition(x, y);


    background.setFillColor(sf::Color::Green);
    background.setOutlineColor(sf::Color::Red);
    temp = background.getLocalBounds();
    background.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    background.setPosition(x, y);
    return;
}

// organize the screen
void organize(sf::Sprite& imageSpr, sf::Text& name, vector<sf::Text>& bodyArray) {
    sf::FloatRect imageBor;

    // Adjust Origin Points and set fonts/scale
    name.setCharacterSize(40);
    imageBor = name.getGlobalBounds();
    name.setOrigin(sf::Vector2f(imageBor.width / 2, 0));

    imageBor = imageSpr.getGlobalBounds();
    imageSpr.setOrigin(sf::Vector2f(imageBor.width / 2, 0));
    imageSpr.setScale(sf::Vector2f(0.3f, 0.3f));

    for (int i = 0; i < bodyArray.size(); i++) {
        bodyArray[i].setCharacterSize(24);
        imageBor = bodyArray[i].getGlobalBounds();
        bodyArray[i].setOrigin(imageBor.width / 2, 0);
    }

    // Set positions relative to each other
    name.setPosition(400.f, 90.f);
    imageBor = name.getGlobalBounds();
    imageSpr.setPosition(400.f, imageBor.top + imageBor.height + 10.f);
    imageBor = imageSpr.getGlobalBounds();
    imageBor.top = imageBor.top + imageBor.height;
    for (int i = 0; i < bodyArray.size(); i++) {
        bodyArray[i].setPosition(400.f, imageBor.top + 20.f);
        imageBor = bodyArray[i].getGlobalBounds();
    }

    return;
}

// swapSelection: Swaps the selection
void swapSelection(string& option, vector<sf::Text>& bodyArray) {
    string linePart;
    istringstream iss(option);
    string curLine = "";
    int counter = 0;

    // Set all display features
    bodyArray.clear();
    while (getline(iss, linePart, ' ')) {
        curLine = curLine + linePart + " ";
        counter++;
        if (counter > 8) {
            bodyArray.push_back(sf::Text());
            bodyArray[bodyArray.size() - 1].setString(curLine);
            counter = 0;
            curLine = "";
        }
    }
    bodyArray.push_back(sf::Text());
    bodyArray[bodyArray.size() - 1].setString(curLine);

    return;
}

// SwapImage: Swaps the display
void swapImage(int category, string text, sf::Texture& image, sf::Sprite& imageSpr, sf::Text& name, vector<sf::Text>& bodyArray) {
    string filepath, line;
    ifstream fileIn;
    sf::Sprite newimageSpr;

    switch (category) {
        // Looking At Nations
    case 0:
        filepath = "nation/" + text;
        break;
        // Looking At Race
    case 1:
        filepath = "race/" + text;
        break;
        // Looking At Element
    case 2:
        filepath = "element/" + text;
        break;
        // Looking At Source
    case 3:
        filepath = "source/" + text;
        break;
        // Looking At Religion
    case 4:
        filepath = "religion/" + text;
        break;
    }

    fileIn.open(filepath + ".txt");
    image.loadFromFile(filepath + ".png");


    // Set all display features
    bodyArray.clear();
    while (getline(fileIn, line)) {
        bodyArray.push_back(sf::Text());
        bodyArray[bodyArray.size() - 1].setString(line);
    }

    newimageSpr.setTexture(image);
    imageSpr = newimageSpr;

    name.setString(text);

    return;
}

void swapOption(int category, string& text) { //, sf::Text title, sf::Text body, sf::Image image) {
    // "Nation", "Race", "Element", "Source", "Religion"
    string cate0[] = { "Skelstaris", "Blaycorrum", "Arim", "Native" };
    string cate1[] = { "Human", "Halfling", "Goliath" };
    string cate2[] = { "Fire", "Water", "Earth", "Wind", "Ice", "Lightning", "Shadow", "Light" };
    string cate3[] = { "Faith", "Magic", "Tech", "Instinct" };
    string cate4[] = { "Mythos", "Death", "Nature", "Deception", "Fate", "Conquest", "Wilds", "Security", "Desire", "Spring", "Summer", "Fall", "Winter", "Progression", "Monsters" };
    int count = 0;
    int len = 0;

    switch (category) {
        // Looking At Nations
    case 0:
        while (cate0[count] != text) {
            count++;
        }
        count++;

        len = sizeof(cate0) / sizeof(cate0[0]);
        if (count >= len) {
            text = cate0[0];
        }
        else {
            text = cate0[count];
        }

        //image.loadFromFile("images/nation" + text + ".png");

        break;

        // Looking At Race
    case 1:
        while (cate1[count] != text) {
            count++;
        }
        count++;

        len = sizeof(cate1) / sizeof(cate1[0]);
        if (count >= len) {
            text = cate1[0];
        }
        else {
            text = cate1[count];
        }

        break;

        // Looking At Element
    case 2:
        while (cate2[count] != text) {
            count++;
        }
        count++;

        len = sizeof(cate2) / sizeof(cate2[0]);
        if (count >= len) {
            text = cate2[0];
        }
        else {
            text = cate2[count];
        }

        break;

        // Looking At Source
    case 3:
        while (cate3[count] != text) {
            count++;
        }
        count++;

        len = sizeof(cate3) / sizeof(cate3[0]);
        if (count >= len) {
            text = cate3[0];
        }
        else {
            text = cate3[count];
        }

        break;
        // Looking At Religion
    case 4:
        while (cate4[count] != text) {
            count++;
        }
        count++;

        len = sizeof(cate4) / sizeof(cate4[0]);
        if (count >= len) {
            text = cate4[0];
        }
        else {
            text = cate4[count];
        }

        break;
    }
}

void charGenBackgroundMenu(sf::RenderWindow& window, string(&text)[5]) {
    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::Texture image;
    sf::Sprite imageSpr;
    int currentCate;
    vector<sf::Text> buttonText;
    vector<sf::Text> bodyArray;
    vector<sf::RectangleShape> buttonBlock;
    sf::Text title, name;

    string categories[] = { "Nation", "Race", "Element", "Source", "Religion" };
    sf::FloatRect imageBor = imageSpr.getGlobalBounds();

    for (int i = 0; i < 2; i++) {
        buttonText.push_back(sf::Text());
        buttonBlock.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
    }

    buttonText.push_back(sf::Text());
    buttonBlock.push_back(sf::RectangleShape(sf::Vector2f(700, 50)));

    image.loadFromFile("nation/Skelstaris.png");
    imageSpr.setTexture(image);

    font.loadFromFile("font/arial.ttf");

    title.setCharacterSize(37);
    title.setFont(font);
    name.setFont(font);
    title.setFillColor(sf::Color::Cyan);
    name.setFillColor(sf::Color::Cyan);
    title.setPosition(140.f, 0.f);

    buttonText[0].setString("<");
    buttonText[1].setString(">");
    buttonText[2].setString("Change");

    currentCate = 0;

    for (int i = 0; i < 2; i++) {
        buttonText[i].setCharacterSize(24);
        buttonText[i].setFont(font);

        setButton(buttonBlock[i], buttonText[i], 30.f + (60.f * i), 30.f);
    }

    buttonText[2].setFont(font);
    setButton(buttonBlock[2], buttonText[2], 400.0, 565.0);

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);
        int mouseX = mousePos.x;
        int mouseY = mousePos.y;

        title.setString(categories[currentCate]);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int i = 0; i < 3; i++) {
                if (buttonHover(buttonBlock[i], mousePos)) {
                    buttonBlock[i].setOutlineThickness(5);
                }
                else {
                    buttonBlock[i].setOutlineThickness(0);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (buttonHover(buttonBlock[0], mousePos)) {
                    currentCate -= 1;
                }
                else if (buttonHover(buttonBlock[1], mousePos)) {
                    currentCate += 1;
                }
                else if (buttonHover(buttonBlock[2], mousePos)) {
                    swapOption(currentCate, text[currentCate]);
                }
            }

            if (currentCate > 4 || currentCate < 0) {
                cout << text[0] << " " << text[1] << " " << text[2] << " " << text[3] << " " << text[4] << " " << endl;
                return;
            }
        }

        // Modify the details for the current selection
        swapImage(currentCate, text[currentCate], image, imageSpr, name, bodyArray);

        for (int i = 0; i < bodyArray.size(); i++) {
            bodyArray[i].setFont(font);
            bodyArray[i].setFillColor(sf::Color::Cyan);
        }

        organize(imageSpr, name, bodyArray);

        // Draw the window
        window.clear();

        for (int i = 0; i < bodyArray.size(); i++) {
            window.draw(bodyArray[i]);
        }

        window.draw(title);
        window.draw(name);
        window.draw(imageSpr);
        for (int i = 0; i < 3; i++) {
            window.draw(buttonBlock[i]);
            window.draw(buttonText[i]);
        }
        window.display();
    }
}

void charGenStatsMainMenu(sf::RenderWindow& window, vector<vector<string>>& abilityList, vector<vector<string>>& weaknessList) {
    vector<Button> buttons;
    vector<sf::Text> titles;
    vector<sf::Text> actAbil;
    vector<sf::Text> actWeak;

    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::FloatRect temp;

    font.loadFromFile("font/arial.ttf");

    for (int i = 0; i < 4; i++) {
        buttons.push_back(Button(sf::Vector2f(340, 50)));
        buttons[i].text.setFont(font);
        buttons[i].setPosition(225.f + (350.f * floor(i / 2)), 445.f + (60.f * (i % 2)));
    }

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

    buttons.push_back(Button(sf::Vector2f(700, 50)));
    buttons[4].text.setFont(font);
    buttons[4].setPosition(400.0, 565.0);

    buttons[0].setString("Add");
    buttons[1].setString("Remove");
    buttons[2].setString("Add");
    buttons[3].setString("Remove");
    buttons[4].setString("Done");

    for (int i = 0; i < weaknessList.size(); i++) {
        actWeak.push_back(sf::Text());

        actWeak[i].setCharacterSize(20);
        actWeak[i].setFont(font);
        actWeak[i].setFillColor(sf::Color::Cyan);
        actWeak[i].setString(weaknessList[i][0] + " (Level " + weaknessList[i][1] + ")");
        temp = actWeak[i].getLocalBounds();
        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
        actWeak[i].setPosition(575.f, 40 + (22 * i));
    }

    for (int i = 0; i < abilityList.size(); i++) {
        actAbil.push_back(sf::Text());

        actAbil[i].setCharacterSize(20);
        actAbil[i].setFont(font);
        actAbil[i].setFillColor(sf::Color::Cyan);
        actAbil[i].setString(abilityList[i][0] + " (Level " + abilityList[i][1] + ")");
        temp = actAbil[i].getLocalBounds();
        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
        actAbil[i].setPosition(225.f, 40 + (22 * i));
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

            if (buttons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent = charGenStatsAddMenu(window, true);
                if (returnedContent.size() > 1) {
                    abilityList.push_back(returnedContent);
                    actAbil.clear();
                    for (int i = 0; i < abilityList.size(); i++) {
                        actAbil.push_back(sf::Text());

                        actAbil[i].setCharacterSize(20);
                        actAbil[i].setFont(font);
                        actAbil[i].setFillColor(sf::Color::Cyan);
                        actAbil[i].setString(abilityList[i][0] + " (Level " + abilityList[i][1] + ")");
                        temp = actAbil[i].getLocalBounds();
                        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                }
            }
            else if (buttons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                if (abilityList.size() > 0) {
                    charGenStatsRemoveMenu(window, true, abilityList);
                    actAbil.clear();
                    for (int i = 0; i < abilityList.size(); i++) {
                        actAbil.push_back(sf::Text());

                        actAbil[i].setCharacterSize(20);
                        actAbil[i].setFont(font);
                        actAbil[i].setFillColor(sf::Color::Cyan);
                        actAbil[i].setString(abilityList[i][0] + " (Level " + abilityList[i][1] + ")");
                        temp = actAbil[i].getLocalBounds();
                        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                }
            }
            else if (buttons[2].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent = charGenStatsAddMenu(window, false);
                if (returnedContent.size() > 1) {
                    weaknessList.push_back(returnedContent);
                    actWeak.clear();
                    for (int i = 0; i < weaknessList.size(); i++) {
                        actWeak.push_back(sf::Text());

                        actWeak[i].setCharacterSize(20);
                        actWeak[i].setFont(font);
                        actWeak[i].setFillColor(sf::Color::Cyan);
                        actWeak[i].setString(weaknessList[i][0] + " (Level " + weaknessList[i][1] + ")");
                        temp = actWeak[i].getLocalBounds();
                        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                }

            }
            else if (buttons[3].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                if (weaknessList.size() > 0) {
                    charGenStatsRemoveMenu(window, false, weaknessList);
                    actWeak.clear();
                    for (int i = 0; i < weaknessList.size(); i++) {
                        actWeak.push_back(sf::Text());

                        actWeak[i].setCharacterSize(20);
                        actWeak[i].setFont(font);
                        actWeak[i].setFillColor(sf::Color::Cyan);
                        actWeak[i].setString(weaknessList[i][0] + " (Level " + weaknessList[i][1] + ")");
                        temp = actWeak[i].getLocalBounds();
                        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                }

            }
            else if (buttons[4].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                return;
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

        for (int i = 0; i < 5; i++) {
            window.draw(buttons[i].box);
            window.draw(buttons[i].text);
        }
        window.display();
    }
}

/**
* bool - False is weakness, True is ability
* @param bool type -                    False is weakness, True is ability
* @param sf::RenderWindow window -     Window
*/
vector<string> charGenStatsAddMenu(sf::RenderWindow& window, bool type) {
    vector<Button> optionsButtons;
    vector<Button> selectionButtons;
    vector<Button> optionArrowButtons;
    vector<Button> alphabetButtons;

    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::FloatRect temp;

    vector<sf::Text> statText;
    vector<sf::Text> bodyText;
    int statVal = 1;
    int listPos = 0;
    int alphaPicked = 0;
    int selection = 0;
    string text[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    string crop = "";

    ifstream fileIn;

    switch (type) {
    case(true):
        fileIn.open("stats/Abilities.txt");
        break;
    case(false):
        fileIn.open("stats/Weaknesses.txt");
        break;
    }

    string line, linePart;
    vector<string> parts;
    vector<string> opt;
    vector<vector<string>> options;
    vector<vector<string>> activeOpts;

    while (getline(fileIn, line)) {
        istringstream iss(line);
        while (getline(iss, linePart, '|')) {
            parts.push_back(linePart);
        }
        options.push_back({ parts[0], parts[1] });
        activeOpts.push_back({ parts[0], parts[1] });
        parts.clear();
    }

    for (int i = 0; i < 26; i++) {
        alphabetButtons.push_back(Button(sf::Vector2f(25, 25)));
    }

    for (int i = 0; i < 5; i++) {
        optionsButtons.push_back(Button(sf::Vector2f(700, 50)));
    }

    for (int i = 0; i < 4; i++) {
        selectionButtons.push_back(Button(sf::Vector2f(100, 50)));
    }

    for (int i = 0; i < 2; i++) {
        optionArrowButtons.push_back(Button(sf::Vector2f(50, 25)));
        statText.push_back(sf::Text());
    }

    font.loadFromFile("font/arial.ttf");

    for (int i = 0; i < 26; i++) {
        alphabetButtons[i].text.setFont(font);
        alphabetButtons[i].setString(text[i]);
        alphabetButtons[i].setPosition(17.5f + 7.5f + (30.0f * i), 17.5f);
    }

    for (int i = 0; i < 2; i++) {
        optionArrowButtons[i].text.setFont(font);
        optionArrowButtons[i].setPosition(400, 22.5f + alphabetButtons[1].height + (305 * i));
        statText[i].setCharacterSize(24);
        statText[i].setFont(font);
        statText[i].setFillColor(sf::Color::Cyan);
    }

    optionArrowButtons[0].setString("^");
    optionArrowButtons[1].setString("v");

    for (int i = 0; i < 5; i++) {
        optionsButtons[i].text.setFont(font);
        optionsButtons[i].setPosition(400, 40.0f + alphabetButtons[1].height + optionArrowButtons[1].height + (55 * i));
    }

    for (int i = 0; i < 4; i++) {
        selectionButtons[i].text.setFont(font);
        selectionButtons[i].setPosition(100 + (200 * i), 570.0f);
    }

    selectionButtons[0].setString("Higher");
    selectionButtons[1].setString("Lower");
    selectionButtons[2].setString("Accept");
    selectionButtons[3].setString("Cancel");

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int i = 0; i < 26; i++) {
                if (alphabetButtons[i].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                    listPos = 0;
                    crop = text[i];
                    activeOpts.clear();
                    for (int j = 0; j < options.size(); j++) {
                        if (crop.front() == options[j][0].front()) {
                            activeOpts.push_back(options[j]);
                            alphaPicked = j;
                        }
                    }
                    alphaPicked = alphaPicked - activeOpts.size() + 1;
                }
            }

            if (optionArrowButtons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                listPos++;
                int math = activeOpts.size() - optionsButtons.size();
                if (listPos > math) {
                    listPos = max(math, 0);
                }
            }
            else if (optionArrowButtons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                listPos--;
                if (listPos < 1) {
                    listPos = 0;
                }
            }

            if (selectionButtons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                int cap;
                if (type) {
                    cap = 5;
                }
                else {
                    cap = 3;
                }

                statVal++;
                if (statVal > cap) {
                    statVal = cap;
                }
            }
            else if (selectionButtons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                statVal--;
                if (statVal < 1) {
                    statVal = 1;
                }
            }
            else if (selectionButtons[2].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent;
                returnedContent.push_back(options[selection][0]);
                returnedContent.push_back(to_string(statVal));
                return returnedContent;
            }
            else if (selectionButtons[3].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent;
                return returnedContent;
            }

            for (int i = 0; i < min(int(activeOpts.size()), 5); i++) {
                if (optionsButtons[i].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                    selection = alphaPicked + i + listPos;
                }
            }
        }

        // Draw the window
        window.clear();

        for (int i = 0; i < 26; i++) {
            window.draw(alphabetButtons[i].box);
            window.draw(alphabetButtons[i].text);
        }

        for (int i = 0; i < 2; i++) {
            window.draw(optionArrowButtons[i].box);
            window.draw(optionArrowButtons[i].text);
        }

        for (int i = 0; i < 4; i++) {
            window.draw(selectionButtons[i].box);
            window.draw(selectionButtons[i].text);
        }

        for (int i = 0; i < min(int(activeOpts.size()), 5); i++) {
            optionsButtons[i].setString(activeOpts[i + listPos][0]);
            window.draw(optionsButtons[i].box);
            window.draw(optionsButtons[i].text);
        }

        statText[0].setString(options[selection][0] + " Level " + to_string(statVal));
        swapSelection(options[selection][1], bodyText);
        statText[1].setString(options[selection][1]);

        for (int i = 0; i < bodyText.size(); i++) {
            bodyText[i].setCharacterSize(20);
            bodyText[i].setFont(font);
            bodyText[i].setFillColor(sf::Color::Cyan);
            temp = bodyText[i].getLocalBounds();
            bodyText[i].setOrigin(temp.left + temp.width / 2.0f, 0);
            bodyText[i].setPosition(400, 400 + (25 * i));
            window.draw(bodyText[i]);
        }


        for (int i = 0; i < 1; i++) {
            temp = statText[i].getLocalBounds();
            statText[i].setOrigin(temp.left + temp.width / 2.0f, 0);
            statText[i].setPosition(400, 370 + (30 * i));
            window.draw(statText[i]);
        }

        window.display();
    }
}

/**
* bool - False is weakness, True is ability
* @param bool type -                    False is weakness, True is ability
* @param sf::RenderWindow window -     Window
* @param vector<vector<string>> list -  List of abilities/weaknesses
*/
void charGenStatsRemoveMenu(sf::RenderWindow& window, bool type, vector<vector<string>>& list) {
    vector<Button> optionsButtons;
    vector<Button> selectionButtons;
    vector<Button> optionArrowButtons;
    vector<Button> alphabetButtons;

    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::FloatRect temp;

    vector<sf::Text> statText;
    vector<sf::Text> bodyText;
    int statVal = 1;
    int listPos = 0;
    int alphaPicked = 0;
    int selection = 0;
    string text[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    string crop = "";

    ifstream fileIn;

    switch (type) {
    case(true):
        fileIn.open("stats/Abilities.txt");
        break;
    case(false):
        fileIn.open("stats/Weaknesses.txt");
        break;
    }

    string line, linePart;
    vector<string> parts;
    vector<string> opt;
    vector<vector<string>> options;

    while (getline(fileIn, line)) {
        istringstream iss(line);
        while (getline(iss, linePart, '|')) {
            parts.push_back(linePart);
        }
        options.push_back({ parts[0], parts[1] });
        parts.clear();
    }

    for (int i = 0; i < 26; i++) {
        alphabetButtons.push_back(Button(sf::Vector2f(25, 25)));
        alphabetButtons[i].box.setFillColor(sf::Color::White);
    }

    for (int i = 0; i < 5; i++) {
        optionsButtons.push_back(Button(sf::Vector2f(700, 50)));
    }

    for (int i = 0; i < 4; i++) {
        selectionButtons.push_back(Button(sf::Vector2f(100, 50)));
    }

    for (int i = 0; i < 2; i++) {
        optionArrowButtons.push_back(Button(sf::Vector2f(50, 25)));
        statText.push_back(sf::Text());
    }

    font.loadFromFile("font/arial.ttf");

    for (int i = 0; i < 26; i++) {
        alphabetButtons[i].text.setFont(font);
        alphabetButtons[i].setString(text[i]);
        alphabetButtons[i].setPosition(17.5f + 7.5f + (30.0f * i), 17.5f);
    }

    for (int i = 0; i < 2; i++) {
        optionArrowButtons[i].text.setFont(font);
        optionArrowButtons[i].setPosition(400, 22.5f + alphabetButtons[1].height + (305 * i));
        statText[i].setCharacterSize(24);
        statText[i].setFont(font);
        statText[i].setFillColor(sf::Color::Cyan);
    }

    optionArrowButtons[0].setString("^");
    optionArrowButtons[1].setString("v");

    for (int i = 0; i < 5; i++) {
        optionsButtons[i].text.setFont(font);
        optionsButtons[i].setPosition(400, 40.0f + alphabetButtons[1].height + optionArrowButtons[1].height + (55 * i));
    }

    for (int i = 0; i < 4; i++) {
        selectionButtons[i].text.setFont(font);
        selectionButtons[i].setPosition(100 + (200 * i), 570.0f);
    }

    selectionButtons[0].setString("Higher");
    selectionButtons[1].setString("Lower");
    selectionButtons[2].setString("Accept");
    selectionButtons[3].setString("Cancel");

    statVal = stoi(list[0][1]);
    while (options[selection][0] != list[0][0])
        selection++;

    while (window.isOpen())
    {
        mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            for (int i = 0; i < 26; i++) {
                if (alphabetButtons[i].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                    continue;
                }
            }

            if (optionArrowButtons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                listPos++;
                int math = list.size() - optionsButtons.size();
                if (listPos > math) {
                    listPos = max(math, 0);
                }
            }
            else if (optionArrowButtons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                listPos--;
                if (listPos < 1) {
                    listPos = 0;
                }
            }

            if (selectionButtons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                int cap;
                if (type) {
                    cap = 5;
                }
                else {
                    cap = 3;
                }

                statVal++;
                if (statVal > cap) {
                    statVal = cap;
                }
            }
            else if (selectionButtons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                statVal--;
                if (statVal < 0) {
                    statVal = 0;
                }
            }
            else if (selectionButtons[2].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<vector<string>> prevContent = list;
                list.clear();

                for (int i = 0; i < prevContent.size(); i++) {
                    if (prevContent[i][0] != options[selection][0]) {
                        list.push_back(prevContent[i]);
                    }
                    else {
                        if (statVal != 0) {
                            //vector<string> w = ;
                            list.push_back({ prevContent[i][0], to_string(statVal) });
                        }
                    }
                }
                // = prevContent;
                //.push_back(options[selection][0]);
                //returnedContent.push_back(to_string(statVal));
                return;
            }
            else if (selectionButtons[3].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                return;
            }

            for (int i = 0; i < min(int(list.size()), 5); i++) {
                if (optionsButtons[i].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                    selection = alphaPicked + i + listPos;
                    statVal = stoi(list[selection][1]);
                    int count = 0;
                    while (options[count][0] != list[selection][0])
                        count++;
                    selection = count;
                }
            }
        }

        // Draw the window
        window.clear();

        for (int i = 0; i < 26; i++) {
            window.draw(alphabetButtons[i].box);
            window.draw(alphabetButtons[i].text);
        }

        for (int i = 0; i < 2; i++) {
            window.draw(optionArrowButtons[i].box);
            window.draw(optionArrowButtons[i].text);
        }

        for (int i = 0; i < 4; i++) {
            window.draw(selectionButtons[i].box);
            window.draw(selectionButtons[i].text);
        }

        for (int i = 0; i < min(int(list.size()), 5); i++) {
            optionsButtons[i].setString(list[i + listPos][0]);
            window.draw(optionsButtons[i].box);
            window.draw(optionsButtons[i].text);
        }

        statText[0].setString(options[selection][0] + " Level " + to_string(statVal));
        swapSelection(options[selection][1], bodyText);
        statText[1].setString(options[selection][1]);

        for (int i = 0; i < bodyText.size(); i++) {
            bodyText[i].setCharacterSize(20);
            bodyText[i].setFont(font);
            bodyText[i].setFillColor(sf::Color::Cyan);
            temp = bodyText[i].getLocalBounds();
            bodyText[i].setOrigin(temp.left + temp.width / 2.0f, 0);
            bodyText[i].setPosition(400, 400 + (25 * i));
            window.draw(bodyText[i]);
        }


        for (int i = 0; i < 1; i++) {
            temp = statText[i].getLocalBounds();
            statText[i].setOrigin(temp.left + temp.width / 2.0f, 0);
            statText[i].setPosition(400, 370 + (30 * i));
            window.draw(statText[i]);
        }

        window.display();
    }
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
        { "Add", "Add", "Remove", "Remove", "Main Menu"},
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
                    cout << "AA\n";
                    charGen::stats::addMenu(window, abilityList, "Abilities");
                    charGen::stats::reconfigDisplay(font, abilityList, actAbil);
                    for (int i = 0; i < actAbil.size(); i++) {
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                    
                    break;
                case 1:
                    // Add Weakness Button
                    cout << "AW\n";
                    charGen::stats::addMenu(window, weaknessList, "Weakness");
                    charGen::stats::reconfigDisplay(font, weaknessList, actWeak);
                    for (int i = 0; i < actWeak.size(); i++) {
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                    break;
                case 2:
                    // Remove Ability Button
                    cout << "RA\n";
                    charGen::stats::adjustMenu(window, abilityList);
                    charGen::stats::reconfigDisplay(font, abilityList, actAbil);
                    for (int i = 0; i < actAbil.size(); i++) {
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                    break;
                case 3:
                    // Remove Weakness Button
                    cout << "RW\n";
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
            /*
            if (buttons[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent = charGenStatsAddMenu(window, true);
                if (returnedContent.size() > 1) {
                    abilityList.push_back(returnedContent);
                    actAbil.clear();
                    for (int i = 0; i < abilityList.size(); i++) {
                        actAbil.push_back(sf::Text());

                        actAbil[i].setCharacterSize(20);
                        actAbil[i].setFont(font);
                        actAbil[i].setFillColor(sf::Color::Cyan);
                        actAbil[i].setString(abilityList[i][0] + " (Level " + abilityList[i][1] + ")");
                        temp = actAbil[i].getLocalBounds();
                        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                }
            }
            else if (buttons[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                if (abilityList.size() > 0) {
                    charGenStatsRemoveMenu(window, true, abilityList);
                    actAbil.clear();
                    for (int i = 0; i < abilityList.size(); i++) {
                        actAbil.push_back(sf::Text());

                        actAbil[i].setCharacterSize(20);
                        actAbil[i].setFont(font);
                        actAbil[i].setFillColor(sf::Color::Cyan);
                        actAbil[i].setString(abilityList[i][0] + " (Level " + abilityList[i][1] + ")");
                        temp = actAbil[i].getLocalBounds();
                        actAbil[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actAbil[i].setPosition(225.f, 40 + (22 * i));
                    }
                }
            }
            else if (buttons[2].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                vector<string> returnedContent = charGenStatsAddMenu(window, false);
                if (returnedContent.size() > 1) {
                    weaknessList.push_back(returnedContent);
                    actWeak.clear();
                    for (int i = 0; i < weaknessList.size(); i++) {
                        actWeak.push_back(sf::Text());

                        actWeak[i].setCharacterSize(20);
                        actWeak[i].setFont(font);
                        actWeak[i].setFillColor(sf::Color::Cyan);
                        actWeak[i].setString(weaknessList[i][0] + " (Level " + weaknessList[i][1] + ")");
                        temp = actWeak[i].getLocalBounds();
                        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                }

            }
            else if (buttons[3].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                if (weaknessList.size() > 0) {
                    charGenStatsRemoveMenu(window, false, weaknessList);
                    actWeak.clear();
                    for (int i = 0; i < weaknessList.size(); i++) {
                        actWeak.push_back(sf::Text());

                        actWeak[i].setCharacterSize(20);
                        actWeak[i].setFont(font);
                        actWeak[i].setFillColor(sf::Color::Cyan);
                        actWeak[i].setString(weaknessList[i][0] + " (Level " + weaknessList[i][1] + ")");
                        temp = actWeak[i].getLocalBounds();
                        actWeak[i].setOrigin(temp.left + temp.width / 2.0f, 0);
                        actWeak[i].setPosition(575.f, 40 + (22 * i));
                    }
                }

            }
            else if (buttons[4].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                return;
            }
            */
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

void charGen::stats::addMenu(sf::RenderWindow& window, std::vector<statBlock>& propList, const string& file) {
    statBlock newStat;

    newStat.description = "A";
    newStat.name = "A";
    newStat.value = 3;

    propList.push_back(newStat);
    return;
}

void charGen::stats::adjustMenu(sf::RenderWindow& window, std::vector<statBlock>& propList) {
    sf::Vector2<int> mousePos;
    sf::Font font;
    sf::FloatRect temp;

    int statVal = 1;
    int listPos = 0;
    int alphaPicked = 0;
    int selection = 0;
    string alpha[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    string crop = "";

    string line, linePart;
    vector<string> parts;
    vector<string> opt;
    
    // Convert the property list (Vector Statblock to Vector Vector String)
    vector<vector<string>> options;
    vector<string> optionsDisp;
    for (statBlock& proper : propList) {
        options.push_back({ proper.name, to_string(proper.value) });
        optionsDisp.push_back( proper.name + " " +  to_string(proper.value));
    }

    Menu alpMenu(400, 5, 35, 800, { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" }, { 26 });
    Menu optMenu(400, 500, 100, 800, { "Increase", "Decrease", "Exit" }, { 3 });
    ScrollMenu dispMenu(400, 45, 450, 600, optionsDisp);

    font.loadFromFile("font/arial.ttf");

    while (window.isOpen())
    {
        
        mousePos = sf::Mouse::getPosition(window);

        sf::Event event;
        int hoverOpt, hoverAlp, hoverDisp;

        while (window.pollEvent(event)) {
            hoverOpt = optMenu.hover(mousePos);
            hoverAlp = alpMenu.hover(mousePos);
            hoverDisp = dispMenu.hover(mousePos);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                // Return to the previous page if exit is clicked
                if (hoverOpt == 2)
                    return;

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

                if (dispMenu.optSelected != -1){
                    std::cout << "Option: " << dispMenu.optSelected + dispMenu.optOffset;
                    std::cout << "- " << dispMenu.Options[dispMenu.optSelected + dispMenu.optOffset] << "\n";
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
        alpMenu.draw(window);
        dispMenu.draw(window);
        window.display();
    }

    // Update the property list


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