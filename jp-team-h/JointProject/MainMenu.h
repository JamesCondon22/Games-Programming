#ifndef MAINMENU
#define MAINMENU	
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Xbox360Controller.h"

class Game;
class MainMenu
{
public:
	MainMenu(Game& Game, sf::Font font);
	~MainMenu();
	void update(sf::Time deltaTime, Xbox360Controller& controller);
	void render(sf::RenderWindow& window);
private:
	Game *m_game;//pointer to games class 
	sf::Time m_cumulativeTime;//the time 
	sf::Font m_font;
	sf::Window m_window;
};
#endif // !