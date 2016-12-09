#pragma once
#include <SFML/Graphics.hpp>
#include <Thor\Math.hpp>
#include "KeyHandler.h"
#include "SFML/Audio.hpp"

/// <summary>
/// @author James Condon
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:
	Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler & keyhandler);
	sf::Sprite const & getTurretSprite() const;
	sf::Sprite const & getBaseSprite() const;
	sf::Sprite const & getBulletSprite() const;
	void update(double dt);
	void render(sf::RenderWindow & window);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	void increaseTurretRotation();
	void decreaseTurretRotation();
	void snapBack();
	void shoot();
	void updateBullet(double dt);
	void handleKeyInput();
	void stop();
	void resetBullet();
	void resetTankPos();
	bool bulletAlive = false;
	
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Sprite m_bullet;
	sf::Texture const & m_texture;
	sf::SoundBuffer bufferOne;
	sf::Sound shot;
	//sf::Texture const & m_bulletTexture;

	bool shotsFired = false;
	bool theGun = false;
	double m_speed;
	double m_bulletSpeed;
	double m_rotation;
	double m_bulletRotation;
	double m_turretRotation;
	double static const DEG_TO_RAD;
	KeyHandler & m_keyhandlerCurrent;
};
