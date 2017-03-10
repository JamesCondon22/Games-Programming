#pragma once
#ifndef SPLASH
#define SPLASH	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;

class Splash
{
public:
	Splash(Game& game, sf::Font font);
	~Splash();
	Xbox360Controller controller;
	//void changeScreen();//changes the sprite on screen 
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void anyKeyPress();
	void initialise(sf::Font font);
	
private:
	Game *m_game;//pointer to games class 
	sf::Time m_cumulativeTime;//the time 
	sf::Sprite m_globeSprite;//first sprite
	sf::Texture m_globeTexture;//first texture 
	sf::Text m_globeText;
	sf::Text m_globeTextTwo;
	sf::Font m_font;
	
};
#endif // !