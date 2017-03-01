#include "entityx/Entity.h"

class PathCreator : public ICreatable
{
public:

	PathCreator(std::string type,
		sf::Vector2f position,
		double rotation);

	void create(entityx::Entity& entity);

private:
	std::string m_type;
	sf::Vector2f m_position;
	double m_rotation;
};
