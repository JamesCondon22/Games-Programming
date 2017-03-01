#pragma once
#include "entityx/Entity.h"

/*enum class PathType
{
	PT_Small,
};
*/

struct Path : public entityx::Component<Path>
{
	//Path(PathType type = PathType::PT_Small);
	Path();
	//PathType m_type;
	//std::vector<sf::CircleShape>  m_nodes;
	//void addNode(sf::CircleShape node);
	//std::vector<sf::CircleShape> getNodes();

	
};
