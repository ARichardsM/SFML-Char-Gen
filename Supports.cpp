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
		box.setOutlineThickness(5);
		return true;
	}

	box.setOutlineThickness(0);
	return false;
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
	float trueHeight = (height - (options.size() * 10)) / options.size();

	Options = options;
	TxtFont.loadFromFile("font/arial.ttf");

	for (std::string text: options) {
		Buttons.push_back(Button({ width, trueHeight }));
	}

	for (int i = 0; i < Buttons.size(); i++){
		Buttons[i].setPosition(x, y + (i * (height / options.size())));
		Buttons[i].setFont(TxtFont);
		Buttons[i].setString(Options[i]);
	}
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

selectScreen::selectScreen(std::string topText, std::vector<std::string> optText) {
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

	updateDisplay();

	//name.setFont(font);
	//name.setFillColor(sf::Color::Cyan);

	return;
}

void selectScreen::updateDisplay() {
	// Update the title
	display.title.setString(title);
	sf::FloatRect temp = display.title.getLocalBounds();
	display.title.setOrigin(temp.left + temp.width / 2.0f, 0);

	// Update the option name
	display.name.setString(options[optSel]);
	temp = display.name.getLocalBounds();
	display.name.setOrigin(temp.left + temp.width / 2.0f, 0);
}

void selectScreen::swapOptions() {
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

void selectScreen::swapData(std::string topText, std::vector<std::string> optText) {
	title = topText;
	options = optText;
	optSel = 0;

	updateDisplay();
	return;
}

void selectScreen::draw(sf::RenderWindow& window) {
	window.draw(display.title);
	window.draw(display.name);
	return;
}