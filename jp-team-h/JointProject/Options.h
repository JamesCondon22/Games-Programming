#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;

class Options
{
public:
	Options(Game& Game, sf::Font font);
	~Options();
	void setPosition();
	void buttonUpdate();
	void update(sf::Time deltaTime, Xbox360Controller &controller);
	void render(sf::RenderWindow& window);
	void increaseVolume();
	void decreaseVolume();
private:
	Game *m_game;
	sf::Time m_cumulativeTime;
	sf::Font m_comicSans;
	sf::Texture m_buttonTexture;
	sf::Texture m_arrowTexture;
	sf::Texture m_checkBoxTexture[2];
	sf::Texture m_sliderTexture;
	sf::Sprite m_buttonSprite[2];
	sf::Sprite m_songSprite[3];
	sf::Texture m_songTextures[3];
	sf::Sprite m_arrowSprite;
	sf::Texture m_markerTexture;
	sf::Sprite m_markerSprite;
	sf::Sprite m_sliderSprite;
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	sf::Font m_font;
	sf::Text m_helpText;
	sf::Text m_highscoreText;
	sf::Text m_songtxt;;
	
	int value = 370;
	bool onHelp = true;
	bool onHighScores = false;
	bool onSong1 = false;
	bool onSong2 = false;
	bool onSong3 = false;
	bool onSlider = false;
};
#endif // !Options
