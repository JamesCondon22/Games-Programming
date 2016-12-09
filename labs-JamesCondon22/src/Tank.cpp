#include "Tank.h"
#include "KeyHandler.h"

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;
/// <summary>
/// default constructer for the tank variables 
/// </summary>
/// <param name="texture"></param>
/// <param name="pos"></param>
/// <param name="keyhandler"></param>
Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler & keyhandler)
	: m_texture(texture), m_rotation(0), m_speed(0), m_bulletSpeed(0), m_turretRotation(0), m_bulletRotation(0), m_keyhandlerCurrent(keyhandler)
{
	initSprites(pos);
	bufferOne.loadFromFile("./resources/sounds/shot.wav");
	shot.setBuffer(bufferOne);
}

void Tank::update(double dt)
{
	//call for handle key input 
	handleKeyInput();
	//setting the position for the tank //tank rotation
	m_tankBase.setPosition(m_tankBase.getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
		m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000));
	m_tankBase.setRotation(m_rotation);
	//turret position and rotation
	m_turret.setPosition(m_tankBase.getPosition());
	m_turret.setRotation(m_rotation + m_turretRotation);
	//if bool is true 
	if (shotsFired)
		updateBullet(dt);
}
/// <summary>
/// draws the tank, turret, and bullet sprites
/// </summary>
/// <param name="window"></param>
void Tank::render(sf::RenderWindow & window)
{
	//only draws if the bullet is alive 
	if (bulletAlive == true)
	{
		window.draw(m_bullet);
	}
	window.draw(m_tankBase);
	window.draw(m_turret);

}


void Tank::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);

	//initialises the bullet
	m_bullet.setTexture(m_texture);
	sf::IntRect bulletRect(10, 180, 8, 15);
	m_bullet.setTextureRect(bulletRect);
	m_bullet.setOrigin(bulletRect.width / 2.0, bulletRect.height / 2.0);
	m_bullet.setPosition(pos);


}
/// <summary>
/// returns the turret sprite once called 
/// </summary>
/// <returns></returns>
sf::Sprite const & Tank::getTurretSprite() const
{
	return m_turret;
}
/// <summary>
/// returns the tank bases sprite once called 
/// </summary>
/// <returns></returns>
sf::Sprite const & Tank::getBaseSprite() const
{
	return m_tankBase;
}
/// <summary>
/// returns the bullet sprite once called 
/// </summary>
/// <returns></returns>
sf::Sprite const & Tank::getBulletSprite() const
{
	return m_bullet;
}
/// <summary>
/// inceases the speed of the tank 
/// </summary>
void Tank::increaseSpeed()
{
	if (m_speed < 100.0)
	{
		m_speed += 1;
	}
}
/// <summary>
/// decreses the the speed of the tank
/// </summary>
void Tank::decreaseSpeed()
{
	if (m_speed > -100.0)
	{
		m_speed -= 1;
	}
}
/// <summary>
/// increases the rotation of the tank
/// </summary>
void Tank::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 0;
	}
}
/// <summary>
/// decreases the rotation of the tank
/// </summary>
void Tank::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}
/// <summary>
/// increases the turret rotation
/// </summary>
void Tank::increaseTurretRotation()
{
	m_turretRotation += 1;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 0;
	}
}
/// <summary>
/// decreases the turret rotation 
/// </summary>
void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 1;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}
/// <summary>
/// sets the turret rotation back to a rotation of 0
/// </summary>
void Tank::snapBack()
{
	m_turretRotation = 0;
}
/// <summary>
/// sets the bulletRotation to the osition of the tank and turret;
/// sets the both bools to true
/// </summary>
void Tank::shoot()
{
	shot.play();
	m_bulletRotation = m_turretRotation + m_rotation;
	m_bullet.setRotation(m_bulletRotation);
	bulletAlive = true;
	shotsFired = true;
}
/// <summary>
/// updates the position of the bullet  and adds speed to
/// the bullet 
/// </summary>
/// <param name="dt"></param>
void Tank::updateBullet(double dt)
{
	m_bullet.setPosition(m_turret.getPosition().x + cos(m_bulletRotation*DEG_TO_RAD) * m_bulletSpeed * (dt / 1000),
		m_turret.getPosition().y + sin(m_bulletRotation * DEG_TO_RAD) * m_bulletSpeed * (dt / 1000));
	m_bulletSpeed += 200;
}
/// <summary>
/// keyhandler function which handles all the the key inputs in the game 
/// </summary>
void Tank::handleKeyInput()
{

	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Up))
	{
		increaseSpeed();//function call to increase speed
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Down))
	{
		decreaseSpeed();//function call to decrease speed
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Left))
	{
		decreaseRotation();//function call to decrease tank rotation
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Right))
	{
		increaseRotation();//function call to increase tank rotation
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Z))
	{
		decreaseTurretRotation();//function call to decrease turret rotation
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::X))
	{
		increaseTurretRotation();//function call to increase turret rotation
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::C))
	{
		snapBack();//function call to repositon
	}
	if (m_keyhandlerCurrent.isPressed(sf::Keyboard::Key::Space) && bulletAlive == false)
	{
		shoot();//function call to shoot
	}

}

/// <summary>
/// this sets the tanks speed to 0 once called 
/// </summary>
void Tank::stop()
{
	m_speed = 0;
}
/// <summary>
/// resets the bullet to original position
/// </summary>
void Tank::resetBullet()
{
	m_bulletSpeed = 0;
	shotsFired = false;
	bulletAlive = false;
}


void Tank::resetTankPos()
{
	m_tankBase.setPosition(850,100);
	m_speed = 0;
}
