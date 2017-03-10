#include "Xbox360Controller.h"

/// <summary>
/// set the previous values to the current and then set
/// the current values to the live data from the controller
/// </summary>
void Xbox360Controller::update()
{
	m_previousState.A = m_currentState.A; 
	m_previousState.B = m_currentState.B;
	m_previousState.X = m_currentState.X; 
	m_previousState.Y = m_currentState.Y; 
	m_previousState.LB = m_currentState.LB; 
	m_previousState.RB = m_currentState.RB; 
	m_previousState.Back = m_currentState.Back; 
	m_previousState.Start = m_currentState.Start;
	m_previousState.RightThumbStickClick = m_currentState.RightThumbStickClick; 
	m_previousState.LeftThumbStickClick = m_currentState.LeftThumbStickClick; 
	m_previousState.DpadUp = m_currentState.DpadUp;
	m_previousState.DpadDown = m_currentState.DpadDown;
	m_previousState.DpadLeft = m_currentState.DpadLeft; 
	m_previousState.DpadRight = m_currentState.DpadRight; 
	m_previousState.LTrigger = m_currentState.LTrigger; 
	m_previousState.RTrigger = m_currentState.RTrigger; 
	m_previousState.LeftThumbStick = m_currentState.LeftThumbStick; 
	m_previousState.RightThumbStick = m_currentState.RightThumbStick; 
	
	if (isConnected())
	{

		m_currentState.A = sf::Joystick::isButtonPressed(sf_Joystick_index, 0);
		m_currentState.B = sf::Joystick::isButtonPressed(sf_Joystick_index, 1);
		m_currentState.X = sf::Joystick::isButtonPressed(sf_Joystick_index, 2); 
		m_currentState.Y = sf::Joystick::isButtonPressed(sf_Joystick_index, 3);
		m_currentState.LB = sf::Joystick::isButtonPressed(sf_Joystick_index, 4); 
		m_currentState.RB = sf::Joystick::isButtonPressed(sf_Joystick_index, 5); 
		m_currentState.Back = sf::Joystick::isButtonPressed(sf_Joystick_index, 6); 
		m_currentState.Start = sf::Joystick::isButtonPressed(sf_Joystick_index, 7);

		m_currentState.LeftThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 8);
		m_currentState.RightThumbStickClick = sf::Joystick::isButtonPressed(sf_Joystick_index, 9);

		m_currentState.Xbox = sf::Joystick::isButtonPressed(sf_Joystick_index, 10); 
		m_currentState.DpadRight = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) > dPadThreshold) ? true : false;
		m_currentState.DpadLeft = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) < -dPadThreshold) ? true : false;
		m_currentState.DpadUp = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) > dPadThreshold) ? true : false;
		m_currentState.DpadDown = (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) < -dPadThreshold) ? true : false;

		m_currentState.LTrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);
		m_currentState.RTrigger = -sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Z);

		m_currentState.LeftThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::X),
			sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Y)); m_currentState.RightThumbStick =
			sf::Vector2f(sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::U), sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::R));
	}
}

/// <summary>
/// constructor find the first available controller
/// and set the index to be the controller number
/// </summary> 
Xbox360Controller::Xbox360Controller()
{
	for (int j = 0; j < sf::Joystick::Count; j++)
	{
		if (sf::Joystick::isConnected(j))
		{
			sf_Joystick_index = j;
		}
	}
}



/// <summary>
/// check if the controller is connected
/// </summary>
/// <returns>true is controller is still detected by system</returns> 
bool Xbox360Controller::isConnected()
{
	if (sf_Joystick_index < 0 || sf_Joystick_index > sf::Joystick::Count)
	{
		return false;
	}
	else
	{
		return sf::Joystick::isConnected(sf_Joystick_index);
	}
}




// try each controller slot until we find one
// not so good with multiple controllers 
bool Xbox360Controller::connect()
{
	for (int j = 0; j < sf::Joystick::Count; j++)
	{
		if (sf::Joystick::isConnected(j))
		{
			sf_Joystick_index = j; 
			return true;
		}
	}
	return false;
}

/// <summary>
/// empty destructor
/// </summary> 
Xbox360Controller::~Xbox360Controller()
{

}
