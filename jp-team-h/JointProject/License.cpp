#include "License.h"
#include <iostream>

License::License(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)

{


}

License::~License()
{
	std::cout << "destructing License " << std::endl;
}

void License::update(sf::Time deltaTime)
{
	m_cumulativeTime += deltaTime;

	//if (m_cumulativeTime.asSeconds() > 3)
	//{
	//	m_game->setGameState(GameState::Splash);

	//}
}

void License::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.display();
}