#include "Game.h"
#include "Tank.h"
#include "KeyHandler.h"
#include "CollisionDetector.h"
#include "SFML/Audio.hpp"
/// <summary>
/// @author James Condon		
/// @id	    C00207200
/// @brief This is a game in which the tank moves around the game screen using the arrow keys, the objective of the game is to shoot
/// the targets as they appear on the screen when the target is hit the player recieves a score fo each. this highscore 
/// has to be set before the timer will run out 
/// @date & time 
/// 22/12/2016: 13:00 - 17:00
///	23/12/2016: 13:00 - 17:00
///	29/12/2016: 13:00 - 17:00
/// 30/12/2016: 13:00 - 17:00
/// 05/12/2016: 13:00 - 15:00
/// 06/12/2016: 13:00 - 17:00
/// 07/12/2016: 13:00 - 17:00
/// 08/12/2016: 13:00 - 16:00
/// 09/12/2016: 11:00 - 13:00
/// Total Time: 29 hours
/// </summary>
static double const MS_PER_UPDATE = 10.0;
sf::IntRect targetRectOne(61, 129, 46, 46);

Game::Game()
	: m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)

{
	sf::SoundBuffer buffer;

	
	m_window.setVerticalSyncEnabled(true);

	m_targetRect = targetRectOne;
	int currentLevel = 1;
	m_targetsHit = 0;
	m_shotCount = 0;
	m_accuracy = 0;
	//initialsing the countdown to 60
	m_countdown = 30;
	m_ss << m_countdown;//placing the coundown in the string 

						//initialising the score to 0
	m_score = 0;
	m_sscore << m_score;//placing the score in the string 


	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}
	//loads the background texture 
	if (!m_backgroundTexture.loadFromFile("./resources/images/Background.jpg"))

	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	//loads the spritesheet texture 
	if (!m_spriteSheetTexture.loadFromFile("./resources/images/Spritesheet.png"))

	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	//loads the font texture 
	if (!m_comicSans.loadFromFile("c:/windows/fonts/comic.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	/// loads the spritesheet texture 
	if (!m_texture.loadFromFile("./resources/images/Spritesheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	/// <summary>
	/// the sounds in the game are loaded 
	/// </summary>
	m_bufferOne.loadFromFile("./resources/sounds/explosion.wav");
	m_explosion.setBuffer(m_bufferOne);
	m_bufferTwo.loadFromFile("./resources/sounds/gameOver.wav");
	m_gameOverSong.setBuffer(m_bufferTwo);
	m_bufferThree.loadFromFile("./resources/sounds/gameMusic.wav");
	m_inGame.setBuffer(m_bufferThree);
	if (m_gameOver == true)
	{
		m_gameOverSong.play();
		m_inGame.setLoop(false);
	}
	if (m_gameOver == false)
	{
		m_inGame.play();
		m_inGame.setLoop(true);
	}
	/// <summary>
	/// setting the textures to the sprite objects
	/// </summary>
	m_sprite.setTexture(m_texture);
	m_sprite2.setTexture(m_spriteSheetTexture);
	m_background.setTexture(m_backgroundTexture);
	m_tank.reset(new Tank(m_texture, m_level.m_tank.m_position, m_keyHandler));
	generateWalls();//generates walls initially 
	generateTargets();//generates the targets initially

}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
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
		processGameEvents(event);
	}
}
/// <summary>
/// this is where the walls are generated and created 
/// </summary>
void Game::generateWalls()
{
	//the rectangle for the wall from the spritesheet 
	sf::IntRect wallRect(2, 129, 33, 23);
	for (ObstacleData const &obstacle : m_level.m_obstacles)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(wallRect);
		sprite->setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite->setPosition(obstacle.m_position);
		sprite->setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(std::move(sprite));

	}
}
/// <summary>
/// generates the targets at the position which is created in the yaml file 
/// uses a range based loop to generate the targets 
/// </summary>
void Game::generateTargets()
{
	//the rectangle for the target from the spritesheet 
	
	for (TargetData const &target : m_level.m_targets)
	{
		//sets each individual component of the targets to the corresponding 
		//in the yaml file 
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(m_targetRect);
		sprite->setOrigin(m_targetRect.width / 2.0, m_targetRect.height / 2.0);
		sprite->setPosition(target.m_position);
		sprite->setRotation(target.m_rotation);
		m_targetSprites.push_back(std::move(sprite));

	}
}
/// <summary>
/// checks for the collision between the tank and the wall 
/// if there is collision between the tank and the wall the pointer points
/// to the tanks stop function
/// </summary>
/// <returns></returns>
bool Game::checkTankWallCollision()
{
	for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
	{
		//checks for collision between the turret and the walls sprites 
		if (CollisionDetector::collision(m_tank->getTurretSprite(), *sprite))
		{
			m_tank->stop();//calls the tanks stop function
			return true;

		}
		//checks for collision between the tank and the walls sprites 
		if (CollisionDetector::collision(m_tank->getBaseSprite(), *sprite))
		{
			m_tank->stop();//calls the tanks stop function
			return true;

		}
	}
	return false;
}
/// <summary>
/// Collision between the bullet and the wall 
/// uses a range based loop to return true on collixion
/// </summary>
/// <returns></returns>
bool Game::checkBulletWallCollision()
{
	for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_tank->getBulletSprite(), *sprite))
		{
			m_shotCount++;
			m_tank->resetBullet();//calls for the bullet to be reset
			return true;

		}
	}
	return false;//else return false
}
/// <summary>
/// Collision between the bullet and the target
/// uses a range based for loop returning true upon collision 
/// </summary>
/// <returns></returns>
bool Game::checkBulletTargetCollision()
{
	sf::IntRect targetRectTwo(0, 0, 0, 0);
	
	for (std::unique_ptr<sf::Sprite> const & sprite : m_targetSprites)
	{
		if (CollisionDetector::collision(m_tank->getBulletSprite(), *sprite))
		{
			if (m_targetRect == targetRectOne)
			{
				m_shotCount++;
				sprite->setTextureRect(targetRectTwo);
				sprite->setOrigin(targetRectTwo.width / 2.0, targetRectTwo.height / 2.0);
				m_targetsHit++;
				m_score = m_score + 100;
				m_sscore.str("");//empties the string
				m_sscore << m_score;//adds the new score to the string 	
				m_explosion.play();
			}
		
			if (m_targetsHit == 6 || m_targetsHit == 12)
			{
				generateTargets ();
			}
			//adds 100 to the score if the collision is true
			m_tank->resetBullet();//calls for the bullet to be reset
			return true;

		}
	}
	return false;//if no collision returns false
}

bool Game::restart()
{
	if (m_gameOver)
	{

		generateTargets();//generates the targets once restarted 
		//empties the strings 
		m_tank->resetTankPos();//resets thge tank position
		m_targetsHit = 0;
		m_score = 0;
		m_countdown = 60;//resets 
		m_text[1].setString("");
		m_text[2].setString("");
		m_text[3].setString("");
		m_text[5].setString("");
		m_gameOver = false;
		return true;
	}
	return false;
}
/// <summary>
/// checks the collision for the bullet and the boountries 
/// if the bullet leaves the borders of the screen the bullet reset function is called 
/// </summary>
void Game::checkBulletBoundryCollision()
{
	if (m_tank->getBulletSprite().getPosition().x > 1440)
	{
		m_tank->resetBullet();
	}
	if (m_tank->getBulletSprite().getPosition().x <= 0)
	{
		m_tank->resetBullet();
	}
	if (m_tank->getBulletSprite().getPosition().y > 900)
	{
		m_tank->resetBullet();
	}
	if (m_tank->getBulletSprite().getPosition().y <= 0)
	{
		m_tank->resetBullet();
	}
	m_shotCount++;
}
/// <summary>
/// checks for the collision between the boundaries of the screen and the tank
/// if the tank is outside the boundaries the tank will cqall the tank stop function
/// </summary>
void Game::checkTankBoundryCollision()
{
	if (m_tank->getTurretSprite().getPosition().x - 100 > 1440 || m_tank->getBaseSprite().getPosition().x > 1440)
	{
		m_tank->stop();
	}
	if (m_tank->getTurretSprite().getPosition().x <= 0 || m_tank->getBaseSprite().getPosition().x > 1440)
	{
		m_tank->stop();
	}
	if (m_tank->getTurretSprite().getPosition().y > 900 || m_tank->getBaseSprite().getPosition().x > 1440)
	{
		m_tank->stop();
	}
	if (m_tank->getTurretSprite().getPosition().y <= 0 || m_tank->getBaseSprite().getPosition().x > 1440)
	{
		m_tank->stop();
	}
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{

	// check if the event is a a mouse button release

	switch (event.type)
	{
	case sf::Event::KeyPressed:
		m_keyHandler.updateKey(event.key.code, true);
		break;

	case sf::Event::KeyReleased:
		m_keyHandler.updateKey(event.key.code, false);
		break;
	default:
		break;

	}


}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	
	sf::Time deltaTime;
	//milliseconds are added to the timeSinceLast variable 
	m_timeSinceLast += m_clock.restart().asMilliseconds();
	//if more than 1000
	if (m_timeSinceLast > 1000)
	{
		if (m_countdown > 0)
		{
			m_countdown--;//countdown subtracts one 
			m_timeSinceLast = 0;//reset to 0
			m_ss.str("");//empties string 
			m_ss << m_countdown;//countdown placed into string 

		}


	}
	if (m_countdown > 0)//if the game runs 
	{
		m_tank->update(dt);
		checkTankWallCollision();
		checkBulletWallCollision();
		checkTankBoundryCollision();
		//only checks if the bullet is alive 
		if (m_tank->bulletAlive == true)
		{
			checkBulletTargetCollision();
			checkBulletBoundryCollision();
		}

	}
	else
	{
		m_gameOver = true;

	}
	
	if (m_keyHandler.isPressed(sf::Keyboard::R))
	{
		restart();
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{

	/// <summary>
	/// only applies if the game is not over 
	/// </summary>
	if (!m_gameOver)
	{

		m_text[0].setCharacterSize(36);
		m_text[4].setCharacterSize(36);
		m_text[4].setCharacterSize(36);
		m_text[0].setString("Time: " + m_ss.str());
		m_text[4].setString("Score: " + m_sscore.str());
		m_text[0].setColor(sf::Color::Black);
		m_text[4].setColor(sf::Color::Black);
		m_text[0].setPosition(100, 10);
		m_text[4].setPosition(900, 10);
	}
	m_window.draw(m_background);
	for (auto &m_sprites2 : m_targetSprites)
	{
		m_window.draw(*m_sprites2);

	}
	m_tank->render(m_window);

	for (auto &m_sprite : m_wallSprites)
	{
		m_window.draw(*m_sprite);

	}

	/// <summary>
	/// if the game is over 
	/// </summary>
	if (m_gameOver)
	{
		m_window.clear(sf::Color::Black);
		m_text[1].setString("Time Is Up!");
		m_text[2].setString("HighScore: " + m_sscore.str());
		m_text[3].setString("Targets Hit: " + std::to_string(m_targetsHit));
		m_text[4].setString("Press R to restart");
		m_text[1].setPosition(400, 275);
		m_text[2].setPosition(20, 20);
		m_text[3].setPosition(600, 20);
		m_text[4].setPosition(570, 500);
		m_text[1].setCharacterSize(100);
		m_text[2].setCharacterSize(36);
		m_text[3].setCharacterSize(36);
		m_text[4].setCharacterSize(25);
		m_text[5].setCharacterSize(40);
		m_text[1].setColor(sf::Color::Red);
		m_text[2].setColor(sf::Color::Red);
		m_text[3].setColor(sf::Color::Red);
		m_text[4].setColor(sf::Color::Red);

	}
	for (int i = 0; i < 10; i++) {
		m_text[i].setFont(m_comicSans);
		m_text[i].setStyle(sf::Text::Regular | sf::Text::Bold);
		m_window.draw(m_text[i]);
	}

	m_window.display();
}


