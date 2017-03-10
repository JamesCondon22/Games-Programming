#pragma once
#ifndef HELP
#define HELP

#include<SFML\Graphics.hpp>
#include"Game.h"
#include "Xbox360Controller.h"

class Game;

class Help
{
public:
	Help(Game& game, sf::Font font);
	~Help();
	void update(sf::Time dt, Xbox360Controller&controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;
	sf::Font m_comicSans;
	sf::Font m_font;
	sf::Time m_cumulativeTime;
	sf::Text m_R1;
	sf::Text m_R2;
	sf::Text m_L1;
	sf::Text m_L2;
	sf::Text m_A;
	sf::Text m_X;
	sf::Text m_Y;
	sf::Text m_B;
	sf::Text m_rightAnalog;
	sf::Text m_leftAnalog;
	sf::Text m_dPad;
	sf::Text m_start;

	sf::Texture logoTexture;
	sf::Sprite logoSprite;
	sf::Sprite explosion;

	double alpha;
};

#endif // !Help
