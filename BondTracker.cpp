#include "BondTracker.h"

using namespace std;

void developBonds(vector<string>& names, vector<vector<int>>& bonds) {
    ifstream file;
    string tempA, tempB;
    int roll;

    vector<bool> upDown = { false, false };

    vector<string>noChange = { "Clarence Newmont", "Cicero Vernaar", "Iohann Stamer", "Ark Stamer", "Izayah Newmont", "Jezabel Angeliir" };

    for (int i = 0; i < names.size(); i++) {
        auto indexA = find(noChange.begin(), noChange.end(), names[i]);
        if (indexA - noChange.begin() < 6)
            continue;

        for (int j = 0; j < names.size(); j++) {
            if (i == j)
                continue;

            auto indexB = find(noChange.begin(), noChange.end(), names[j]);
            if (indexB - noChange.begin() < 6)
                continue;

            upDown = { false, false };
            roll = rand() % 100 + 1;

            if (roll > 20)
                continue;

            roll = rand() % 100 + 1;
            switch (bonds[i][j]) {
            case -3:
                upDown[0] = (roll <= 1);
                upDown[1] = (roll >= 90);
                break;
            case -2:
                upDown[0] = (roll <= 5);
                upDown[1] = (roll >= 85);
                break;
            case -1:
                upDown[0] = (roll <= 15);
                upDown[1] = (roll >= 80);
                break;
            case 0:
                upDown[0] = (roll <= 25);
                upDown[1] = (roll >= 75);
                break;
            case 1:
                upDown[0] = (roll <= 20);
                upDown[1] = (roll >= 85);
                break;
            case 2:
                upDown[0] = (roll <= 15);
                upDown[1] = (roll >= 95);
                break;
            case 3:
                upDown[0] = (roll <= 10);
                upDown[1] = (roll >= 100);
                break;
            case 4:
                upDown[0] = (roll <= 5);
                upDown[1] = (roll >= 100);
                break;
            case 5:
                continue;
            }

            if (upDown[0] || upDown[1]) {
                bool swit = true;
                while (swit) {
                    swit = false;
                    switch (upDown[0]) {
                    case true:
                        if (bonds[i][j] == 5)
                            continue;
                        else {
                            bonds[i][j]++;
                            bonds[j][i]++;
                            cout << "Rise: " << names[i] << " and " << names[j] << " (Now: " << bonds[i][j] << ")" << endl;
                        }
                        break;
                    case false:
                        if (bonds[i][j] == -3)
                            cout << "Drop: " << names[i] << " and " << names[j] << " (Now: Feuding)" << endl;
                        else {
                            bonds[i][j]--;
                            bonds[j][i]--;
                            cout << "Drop: " << names[i] << " and " << names[j] << " (Now: " << bonds[i][j] << ")" << endl;
                        }
                        break;
                    }

                    if (rand() % 100 + 1 <= 5)
                        swit = true;
                }
            }
        }
    }

    return;
}


void adjustGrid(sf::RectangleShape& square, int bond) {
    switch (bond) {
    case -3:
        square.setFillColor(sf::Color::Red);
        break;
    case -2:
        square.setFillColor(sf::Color::Yellow);
        break;
    case -1:
        square.setFillColor(sf::Color::White);
        break;
    case 0:
        square.setFillColor(sf::Color::White);
        break;
    case 1:
        square.setFillColor(sf::Color::White);
        break;
    case 2:
        square.setFillColor(sf::Color::Green);
        break;
    case 3:
        square.setFillColor(sf::Color::Cyan);
        break;
    case 4:
        square.setFillColor(sf::Color::Blue);
        break;
    case 5:
        square.setFillColor(sf::Color::Magenta);
        break;
    default:
        square.setFillColor(sf::Color::Black);
        break;
    }
}

void readBonds(vector<string>& names, vector<vector<int>>& bonds) {
    ifstream file;
    string tempA, tempB;

    file.open("bondsIn.txt");
    while (getline(file, tempA)) {
        istringstream line(tempA);

        getline(line, tempB, ':');
        auto indexA = find(names.begin(), names.end(), tempB);
        if (indexA == names.end())
            continue;

        getline(line, tempB, ':');
        auto indexB = find(names.begin(), names.end(), tempB);
        if (indexB == names.end())
            continue;

        getline(line, tempB, ':');
        bonds[indexA - names.begin()][indexB - names.begin()] = stoi(tempB);
        bonds[indexB - names.begin()][indexA - names.begin()] = stoi(tempB);
    }
    return;
}

void printBonds(vector<vector<int>>& bonds) {
    for (int i = 0; i < bonds.size(); i++) {
        for (int j = 0; j < bonds.size(); j++) {
            cout << bonds[i][j] << " ";
        }
        cout << endl;
    }
}

void printReadableBonds(vector<string>& names, vector<vector<int>>& bonds) {
    for (int i = 0; i < bonds.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (bonds[i][j] < 6 && bonds[i][j] != 0)
                cout << names[i] << ":" << names[j] << ":" << bonds[i][j] << endl;
        }
    }
}

void printHumanBonds(vector<string>& names, vector<vector<int>>& bonds) {
    for (int i = 0; i < bonds.size(); i++) {
        cout << "Bonds For " << names[i] << endl;
        for (int j = 0; j < bonds.size(); j++) {
            if (bonds[i][j] < 6 && bonds[i][j] != 0)
                cout << names[j] << " (Level " << bonds[i][j] << ")" << endl;
        }
        cout << endl;
    }
}

void bonds::MainMenu(sf::RenderWindow& window) {
    vector<string> names;
    vector<vector<int>> bonds;
    vector<vector<sf::RectangleShape>> squares;
    fstream file;
    string tempA, tempB, tempC;
    vector<Button> button;
    sf::Font font;
    sf::Vector2<int> mousePos;

    file.open("bonds.txt");
    font.loadFromFile("font/arial.ttf");

    // Character Names
    getline(file, tempA, '|');
    istringstream holderCN(tempA);
    while (getline(holderCN, tempB))
        names.push_back(tempB);

    for (int i = 0; i < names.size(); i++) {
        bonds.push_back(vector<int>());
        squares.push_back(vector<sf::RectangleShape>());
        for (int j = 0; j < names.size(); j++) {
            if (j == i)
                bonds[i].push_back(6);
            else
                bonds[i].push_back(0);


            squares[i].push_back(sf::RectangleShape(sf::Vector2f(5, 5)));
            adjustGrid(squares[i][j], bonds[i][j]);
            squares[i][j].setPosition(0.f + (6.f * i), 0.f + (6.f * j));
        }
    }

    // Bond Levels
    getline(file, tempA, '|');
    istringstream holderB(tempA);
    int count = 0;
    while (getline(holderB, tempB)) {
        istringstream holderInn(tempB);
        int countInn = 0;
        while (getline(holderInn, tempC, '\t')) {
            bonds[count][countInn] = stoi(tempC);
            adjustGrid(squares[count][countInn], bonds[count][countInn]);
            countInn++;
        }
        count++;
    }

    for (int i = 0; i < 4; i++) {
        button.push_back(Button(sf::Vector2f(700, 50)));
        button[i].text.setFont(font);
        button[i].setPosition(400.f, 400.f + (55.f * i));
    }

    button[0].setString("Print");
    button[1].setString("Read");
    button[2].setString("Develop");
    button[3].setString("Exit");

    bool swit = true;

    while (window.isOpen())
    {
        sf::Event event;
        mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (button[0].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                if (swit) {
                    printBonds(bonds);
                    printReadableBonds(names, bonds);
                }
                else
                    printHumanBonds(names, bonds);

                swit = !swit;
            }
            else if (button[1].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                readBonds(names, bonds);
                for (int i = 0; i < names.size(); i++) {
                    for (int j = 0; j < names.size(); j++) {
                        adjustGrid(squares[i][j], bonds[i][j]);
                    }
                }
            }
            else if (button[2].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                developBonds(names, bonds);
                for (int i = 0; i < names.size(); i++) {
                    for (int j = 0; j < names.size(); j++) {
                        adjustGrid(squares[i][j], bonds[i][j]);
                    }
                }
            }
            else if (button[3].hover(mousePos) && event.type == sf::Event::MouseButtonPressed) {
                return;
            }
        }
        // Draw the window
        window.clear();
        for (int i = 0; i < 4; i++) {
            window.draw(button[i].box);
            window.draw(button[i].text);
        }
        for (int i = 0; i < names.size(); i++) {
            for (int j = 0; j < names.size(); j++) {
                window.draw(squares[i][j]);
            }
        }
        window.display();
    }
    return;
}