#include<iostream>
#include"Help.h"

Help::Help(Game & game, sf::Font font) :
	m_game(&game),
	m_comicSans(font)
{
	m_font.loadFromFile("AGENTORANGE.TTF");

	m_R1.setFont(m_font);
	m_R1.setString("Gear Up");
	m_R1.setColor(sf::Color::Black);
	m_R1.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_R1.setCharacterSize(22);
	m_R1.setPosition(670, 180);

	m_R2.setFont(m_font);
	m_R2.setString("Accelerate");
	m_R2.setColor(sf::Color::Black);
	m_R2.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_R2.setCharacterSize(22);
	m_R2.setPosition(540, 140);

	m_L1.setFont(m_font);
	m_L1.setString("Gear down");
	m_L1.setColor(sf::Color::Black);
	m_L1.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_L1.setCharacterSize(22);
	m_L1.setPosition(160, 180);

	m_L2.setFont(m_font);
	m_L2.setString("Decelerate");
	m_L2.setColor(sf::Color::Black);
	m_L2.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_L2.setCharacterSize(22);
	m_L2.setPosition(280, 140);

	m_A.setFont(m_font);
	m_A.setString("Select");
	m_A.setColor(sf::Color::Black);
	m_A.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_A.setCharacterSize(22);
	m_A.setPosition(670, 240);

	m_X.setFont(m_font);
	m_X.setString("Dank memes");
	m_X.setColor(sf::Color::Black);
	m_X.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_X.setCharacterSize(22);
	m_X.setPosition(600, 280);

	m_Y.setFont(m_font);
	m_Y.setString("Danker memes");
	m_Y.setColor(sf::Color::Black);
	m_Y.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_Y.setCharacterSize(22);
	m_Y.setPosition(700, 250);

	m_B.setFont(m_font);
	m_B.setString("Return");
	m_B.setColor(sf::Color::Black);
	m_B.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_B.setCharacterSize(22);
	m_B.setPosition(670, 290);

	m_rightAnalog.setFont(m_font);
	m_rightAnalog.setString("Dankest memes");
	m_rightAnalog.setColor(sf::Color::Black);
	m_rightAnalog.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_rightAnalog.setCharacterSize(22);

	m_leftAnalog.setFont(m_font);
	m_leftAnalog.setString("Steering");
	m_leftAnalog.setColor(sf::Color::Black);
	m_leftAnalog.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_leftAnalog.setCharacterSize(22);

	m_dPad.setFont(m_font);
	m_dPad.setString("Navigation");
	m_dPad.setColor(sf::Color::Black);
	m_dPad.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_dPad.setCharacterSize(22);

	m_start.setFont(m_font);
	m_start.setString("Pause");
	m_start.setColor(sf::Color::Black);
	m_start.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_start.setCharacterSize(22);

	if (!logoTexture.loadFromFile("help.png"))
	{
		std::string s("Error Loading Texture");
		throw std::exception(s.c_str());
	}

	logoSprite.setTexture(logoTexture);
	logoSprite.setPosition(100, 420);


}

Help::~Help()
{
	std::cout << "destructing Help" << std::endl;
}

void Help::update(sf::Time dt, Xbox360Controller&controller)
{
	m_cumulativeTime += dt;

	/*if (m_cumulativeTime.asSeconds() > 1)
	{
	m_game->setGameState(State::Splash);
	}*/

	if (logoSprite.getPosition().y > -421 && logoSprite.getPosition().y > 0)
	{
		alpha = alpha + 2.8;
		logoSprite.move(0, -5);
		logoSprite.setColor(sf::Color(255, 255, 255, alpha));
	}

	if (logoSprite.getPosition().y == 0)
	{
		logoSprite.move(0, 0);
		logoSprite.setColor(sf::Color(255, 255, 255, 255));
	}
	// Button to go back to previous menu
	if (controller.m_currentState.Y)
	{
		m_game->setGameState(GameState::Splash);
	}
}

void Help::render(sf::RenderWindow & window)
{

	window.clear(sf::Color::Green);
	window.draw(logoSprite);
	window.draw(m_R1);
	window.draw(m_R2);
	window.draw(m_L1);
	window.draw(m_L2);
	window.draw(m_A);
	window.draw(m_X);
	window.draw(m_Y);
	window.draw(m_B);
	window.draw(m_rightAnalog);
	window.draw(m_leftAnalog);
	window.draw(m_dPad);
	window.draw(m_start);

	window.display();
}