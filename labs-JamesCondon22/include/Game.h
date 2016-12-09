#pragma once

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Tank.h"
/// <summary>
/// @brief Main class for the SFML Playground project.
/// author James Condon
/// This will be a single class framework for learning about SFML.
/// </summary>
class Game
{
public:
	Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	void generateWalls();
	void generateTargets();
	//collsiom functions
	bool checkTankWallCollision();
	bool checkBulletWallCollision();
	bool checkBulletTargetCollision();
	void checkBulletBoundryCollision();
	void checkTankBoundryCollision();
	bool restart();
	// main window
	sf::RenderWindow m_window;//game windoew
	sf::SoundBuffer m_bufferOne;//buffer for eexplosion
	sf::Sound m_explosion;//explosion sound 
	sf::SoundBuffer m_bufferTwo;//buffer for game over
	sf::Sound m_gameOverSong;//song for game over 
	sf::SoundBuffer m_bufferThree;//buffer for game 
	sf::Sound m_inGame;//song for game  
	sf::Sprite m_sprite;//spritesheet
	sf::Sprite m_sprite2;//spritesheet 
	sf::Texture m_texture;
	sf::Texture m_backgroundTexture;
	sf::Texture m_spriteSheetTexture;
	sf::Texture m_overTexture;
	sf::Sprite m_background;//backgoround sprite 
	sf::Font m_comicSans;//font file 
	sf::Time m_cumulativeTime;
	sf::Text m_text[10];
	sf::IntRect m_targetRect;//target recatngle 
	sf::Clock m_clock;//game clock 
	std::unique_ptr<Tank>m_tank;
	std::vector<std::unique_ptr<sf::Sprite>> m_wallSprites;//memeber variuable for wall sprites 
	std::vector<std::unique_ptr<sf::Sprite>> m_targetSprites;//member for target sprites
	KeyHandler m_keyHandler;
	LevelData m_level;
	std::stringstream m_ss;
	std::stringstream m_sscore;
	int m_countdown;//countdown tiumer 
	int m_score;//score is stored
	double m_timeSinceLast;
	bool m_gameOver = false;
	int m_targetsHit;
	int m_shotCount;
	int m_accuracy;
};
