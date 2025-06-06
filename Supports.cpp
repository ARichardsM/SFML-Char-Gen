#include "Supports.h"

using namespace std;

Button::Button(sf::Vector2f size) {
	height = size.y;
	width = size.x;

	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Blue);
	sf::FloatRect temp = text.getLocalBounds();
	text.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
	//text.setOrigin(temp.left + temp.width / 2.0f, temp.top);

	box.setSize(size);
	box.setFillColor(sf::Color::Green);
	box.setOutlineColor(sf::Color::Red);
	temp = box.getLocalBounds();
	//box.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
	box.setOrigin(temp.left + temp.width / 2.0f, temp.top);
}

bool Button::hover(sf::Vector2i& mousePt) {
	sf::FloatRect border = box.getGlobalBounds();

	if (border.contains(static_cast<sf::Vector2f>(mousePt))) {
		if (!isClicked) {
			box.setOutlineThickness(5);
		}
		
		return true;
	}

	if (!isClicked) {
		box.setOutlineThickness(0);
	}

	return false;
}

void Button::toggleClick() {
	isClicked = !isClicked;

	if (isClicked) {
		box.setOutlineThickness(5);
		box.setOutlineColor(sf::Color::Blue);
		return;
	}

	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(0);
}

void Button::setString(string textString) {
	text.setString(textString);

	sf::FloatRect temp = text.getLocalBounds();
	text.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
}

void Button::setPosition(float x, float y) {
	sf::FloatRect temp1 = box.getLocalBounds();
	sf::FloatRect temp = text.getLocalBounds();

	text.setPosition(x, y + temp1.height / 2.0f - temp.height / 2.0f);
	box.setPosition(x, y);
}

void Button::setFont(sf::Font& font) {
	text.setFont(font);
}

Menu::Menu(int x, int y, int height, float width, std::vector<std::string> options) {
	// Determine button height
	float trueHeight = (height - (options.size() * 10)) / options.size();

	// Save menu data
	Options = options;
	TxtFont.loadFromFile("font/arial.ttf");

	// Create and configure all buttons
	for (std::string text: options) {
		int buttonNum = Buttons.size();
		Buttons.push_back(Button({ width, trueHeight }));
		Buttons[buttonNum].setPosition(x, y + (buttonNum * (height / options.size())));
		Buttons[buttonNum].setFont(TxtFont);
		Buttons[buttonNum].setString(Options[buttonNum]);
	}
}

// TBD Menu with custom configurations
Menu::Menu(int x, int y, int height, float width, std::vector<std::string> options, std::vector<int> position) {
	// Verify Positioning
	int sumOpts = 0;
	for (int num : position)
		sumOpts += num;

	if (sumOpts != options.size()) {
		cout << "Improper Positioning\n";
		return;
	}

	// Determine button height
	float trueHeight = (height - (position.size() * 10)) / position.size();

	// Save menu data
	Options = options;
	TxtFont.loadFromFile("font/arial.ttf");

	// Create all buttons
	for (int i = 0; i < position.size(); i++) {
	//for (int numEnt: position) {
		float trueWidth = (width - (position[i] * 10)) / position[i];
		for (int j = 0; j < position[i]; j++) {
			int buttonNum = Buttons.size();
			Buttons.push_back(Button({ trueWidth, trueHeight }));
			Buttons[buttonNum].setPosition(((x - width / 2) + (width / (2 * position[i]))) + (j * (width / position[i])), y + (i * (height / position.size())));
			Buttons[buttonNum].setFont(TxtFont);
			Buttons[buttonNum].setString(Options[buttonNum]);
		}
	}
	return;
}

int Menu::hover(sf::Vector2i& mousePt) {
	int returnVal = -1;

	for (int i = 0; i < Buttons.size(); i++) {
		if (Buttons[i].hover(mousePt))
			returnVal = i;
	}

	return returnVal;
}

void Menu::draw(sf::RenderWindow& window) {
	for (Button button : Buttons) {
		window.draw(button.box);
		window.draw(button.text);
	}
}

ScrollMenu::ScrollMenu(int x, int y, int height, float width, std::vector<std::string> options) {
	// Track the current button
	int buttonNum = 0;

	// Determine button height
	float trueHeight = (height - 70) / 7;

	// Save menu data
	Options = options;
	TxtFont.loadFromFile("font/arial.ttf");

	// Create an up button for scolling
	buttonNum = Buttons.size();
	Buttons.push_back(Button({ width/2, trueHeight }));
	Buttons[buttonNum].setPosition(x, y + (buttonNum * (height / 7)));
	Buttons[buttonNum].setFont(TxtFont);
	Buttons[buttonNum].setString("Up");

	// Create and configure all buttons
	for (int i = 0; i < 5; i++) {
		buttonNum = Buttons.size();
		Buttons.push_back(Button({ width, trueHeight }));
		Buttons[buttonNum].setPosition(x, y + (buttonNum * (height / 7)));
		Buttons[buttonNum].setFont(TxtFont);
	}

	// Add text to the buttons
	for (int i = 0; i < min(5, (int) Options.size()); i++) {
		Buttons[i + 1].setString(Options[i]);
	}

	// Create a down button for scolling
	buttonNum = Buttons.size();
	Buttons.push_back(Button({ width/2, trueHeight }));
	Buttons[buttonNum].setPosition(x, y + (buttonNum * (height / 7)));
	Buttons[buttonNum].setFont(TxtFont);
	Buttons[buttonNum].setString("Down");
}

void ScrollMenu::toggleClick(int button) {
	if (button - 1 < Options.size()){
		if (optSelected != -1)
			Buttons[optSelected + 1].toggleClick();

		optSelected = button  - 1;
		Buttons[button].toggleClick();
	}
}

void ScrollMenu::scroll(bool scrollUp) {
	// Don't Scroll if there aren't enough options
	if (Options.size() <= 5)
		return;

	// Adjust the Offset
	if (scrollUp)
		optOffset--;
	else 
		optOffset++;

	// Check bounds
	optOffset = min(optOffset, (int)Options.size() - 5);
	optOffset = max(optOffset, 0);

	// Uncheck the button
	if (optSelected != -1) {
		Buttons[optSelected + 1].toggleClick();
		optSelected = -1;
	}

	// Adjust the buttons
	updateDisplay();

	return;
}

void ScrollMenu::updateDisplay() {
	for (int i = 0; i < min(5, (int)Options.size()); i++) {
		int buttonNum = i + optOffset;
		Buttons[i + 1].setString(Options[buttonNum]);
	}
}

void ScrollMenu::swapOptions(std::vector<std::string> newOptions) {
	// Update the options
	Options = newOptions;

	// Adjust the buttons
	updateDisplay();
}

void ScrollMenu::draw(sf::RenderWindow& window) {
	
	for (int i = 0; i < min(5, (int) Options.size()); i++) {
		window.draw(Buttons[i+1].box);
		window.draw(Buttons[i+1].text);
	}

	if (Options.size() > 5) {
		window.draw(Buttons[0].box);
		window.draw(Buttons[0].text);

		window.draw(Buttons[6].box);
		window.draw(Buttons[6].text);
	}

	return;
}

backgroundScreen::backgroundScreen(std::string topText, std::vector<std::string> optText) {
	TxtFont.loadFromFile("font/arial.ttf");
	title = topText;
	options = optText;
	optSel = 0;

	display.title.setCharacterSize(42);
	display.title.setFont(TxtFont);
	display.title.setFillColor(sf::Color::Cyan);
	display.title.setString(topText);
	sf::FloatRect temp = display.title.getLocalBounds();
	display.title.setOrigin(temp.left + temp.width / 2.0f, 0);
	display.title.setPosition(400.f, 0.f);

	display.name.setFont(TxtFont);
	display.name.setFillColor(sf::Color::Cyan);
	display.name.setString(options[optSel]);
	temp = display.name.getLocalBounds();
	display.name.setOrigin(temp.left + temp.width / 2.0f, 0);
	display.name.setPosition(400.f, 50.f);

	display.imageSpr.setScale(sf::Vector2f(0.3f, 0.3f));
	display.imageSpr.setPosition(400.f, 100.f);

	updateDisplay();

	//name.setFont(font);
	//name.setFillColor(sf::Color::Cyan);

	return;
}

void backgroundScreen::updateDisplay() {
	// Update the title
	display.title.setString(title);
	sf::FloatRect temp = display.title.getLocalBounds();
	display.title.setOrigin(temp.left + temp.width / 2.0f, 0);

	// Update the option name
	display.name.setString(options[optSel]);
	temp = display.name.getLocalBounds();
	display.name.setOrigin(temp.left + temp.width / 2.0f, 0);

	// Update the image
	std::filesystem::path imagePath = std::filesystem::current_path() / title / (options[optSel] + ".png");
	if (exists(imagePath)) {
		display.image.loadFromFile(imagePath.string());
		display.imageSpr.setTexture(display.image, true);
		temp = display.imageSpr.getLocalBounds();
		display.imageSpr.setOrigin(sf::Vector2f(temp.left + temp.width / 2, 0));
		imageBool = true;
	}
	else {
		imageBool = false;
	}

	// Update the body text
	std::filesystem::path txtPath = std::filesystem::current_path() / title / (options[optSel] + ".txt");
	if (exists(txtPath)) {
		ifstream fileIn;
		string line;
		fileIn.open(txtPath);

		int i = 0;
		display.bodyArray.clear();
		while (getline(fileIn, line)) {
			display.bodyArray.push_back(sf::Text());
			display.bodyArray[display.bodyArray.size() - 1].setString(line);
			display.bodyArray[display.bodyArray.size() - 1].setCharacterSize(24);
			display.bodyArray[display.bodyArray.size() - 1].setFont(TxtFont);
			display.bodyArray[display.bodyArray.size() - 1].setFillColor(sf::Color::Cyan);
			temp = display.bodyArray[display.bodyArray.size() - 1].getLocalBounds();
			display.bodyArray[display.bodyArray.size() - 1].setOrigin(temp.left + temp.width / 2.0f, 0);
			display.bodyArray[display.bodyArray.size() - 1].setPosition(400.f, 275.f + (25.f * i));
			i++;
		}
		txtBool = true;
	}
	else {
		txtBool = false;
	}
	
}

void backgroundScreen::swapOptions() {
	//display.title.setString(topText);

	if (optSel < options.size() - 1) {
		optSel++;
	}
	else {
		optSel = 0;
	}

	updateDisplay();
	return;
}

void backgroundScreen::swapData(std::string topText, std::vector<std::string> optText) {
	title = topText;
	options = optText;
	optSel = 0;

	updateDisplay();
	return;
}

void backgroundScreen::draw(sf::RenderWindow& window) {
	window.draw(display.title);
	window.draw(display.name);

	if (imageBool)
		window.draw(display.imageSpr);

	if (txtBool)
		for (int i = 0; i < display.bodyArray.size(); i++)
			window.draw(display.bodyArray[i]);

	return;
}

statScreen::statScreen(std::vector<std::vector<std::string>> abilList, std::vector<std::vector<std::string>> weakList) {
	return;
}

void statScreen::swapData(std::vector<std::string> abilList, std::vector<std::string> weakList) {
	return;
}