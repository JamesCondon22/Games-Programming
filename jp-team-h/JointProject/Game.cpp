#include "Game.h"
#include <iostream>

/// <summary>
/// Aaron Curry //James Condon
/// C00207200
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game():
	m_window(sf::VideoMode(1000, 650, 32), "Button Game James"),
	m_currentGameState(GameState::Splash)


{
	if (!m_comicSans.loadFromFile("c:/windows/fonts/comic.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_licenseScreen = new License(*this, m_comicSans);
	m_splashScreen = new Splash(*this, m_comicSans);
	m_helpScreen = new Help(*this, m_comicSans);
	m_options = new Options(*this, m_comicSans);
	controller = new Xbox360Controller();
	
}
Game::~Game()
{
	delete(m_splashScreen);
	delete(m_licenseScreen);
	delete(m_helpScreen);
	delete(m_options);
	std::cout << "destructing game" << std::endl;
}

/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}
/// <summary>
/// setd the current game state 
/// </summary>
/// <param name="gameState"></param>
void Game::setGameState(GameState gameState)
{
	m_currentGameState = gameState;
}

/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		//To check for the Akeypress to transition from splash screen to main menu
		if (controller->m_currentState.A == true && m_currentGameState == GameState::Splash)
		{
			m_splashScreen->anyKeyPress();
		}
		

	}
}


/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(sf::Time time)
{
	switch (m_currentGameState)
	{
	case GameState::None:
	//	m_splashScreen->print(time);
		std::cout << "no GameState" << std::endl;
		break;
	case GameState::Splash:
		controller->update();
		m_splashScreen->update(time);
		break;
	case GameState::License:
		m_licenseScreen->update(time);
		break;
	case GameState::MainMenu:
		m_mainMenu->update(time, *controller);
		break;
		controller->update();
		m_helpScreen->update(time, *controller);
	case GameState::Options:
		controller->update();
		m_options->update(time, *controller);
		break;
	case GameState::GameScreen:
		break;
	default:
		break;
		
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	
	switch (m_currentGameState)
	{
	case GameState::Splash:
		m_splashScreen->render(m_window);
		break;
	case GameState::License:
		m_licenseScreen->render(m_window);
		break;
	case GameState::MainMenu:
		m_mainMenu->render(m_window);
		break;
	case GameState::Help:
		m_helpScreen->render(m_window);
		break;
	case GameState::Options:
		m_options->render(m_window);
		break;
	case GameState::GameScreen:
		break;
	default:
		m_window.clear(sf::Color::Blue);
		m_window.display();
		break;

	}

	
}


