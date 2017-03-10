#pragma once
#ifndef  GAME
#define GAME
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "Splash.h"
#include "Xbox360Controller.h"
#include "License.h"
#include "MainMenu.h"
#include "Help.h"
#include "Options.h"


//each class is declared
class License;
class Splash;
class MainMenu;
class Help;
class Options;

enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Options,
	Upgrade,
	Exit,
	HighScores,
	Help,
	GameScreen
};
class Game
{
public:
	Game();
	~Game();
	void run();
	GameState m_currentGameState;
	GameState m_previousGameState;
	void setGameState(GameState gameState);
	
protected:
	
	void update(sf::Time deltaTime);
	void render();
	void processEvents();
	
	Xbox360Controller *controller;
	// main window
	sf::RenderWindow m_window;
	//pointers set for all screens
	License *m_licenseScreen;
	Splash *m_splashScreen;
	MainMenu * m_mainMenu;
	Help * m_helpScreen;
	Options *m_options;
	sf::Font m_comicSans;//font 
	
	
	
	

};
#endif // !GAME