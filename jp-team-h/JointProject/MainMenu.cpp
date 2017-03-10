#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(Game & game, sf::Font font) :
	m_game(&game),
	m_font(font)	
{

}

MainMenu::~MainMenu()
{
	std::cout << "destructing Splash" << std::endl;

}


void MainMenu::update(sf::Time deltaTime, Xbox360Controller& controller)
{
	
}

void MainMenu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	
	window.display();
}

