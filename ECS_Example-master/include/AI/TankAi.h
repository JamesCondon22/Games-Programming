#pragma once
#include "entityx/Entity.h"
#include "systems/Events.h"
#include "components/Turret.h"
#include "components/Parent.h"
#include "components/Position.h"
#include "components/Path.h"
#include "components/Motion.h"
#include "utils/BTMath.h"
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include <iostream>
#include <queue>

class TankAi 
{
public:

   TankAi(std::vector<sf::CircleShape> const & obstacles, entityx::Entity::Id id, std::vector<sf::CircleShape> & path);


   void update(entityx::Entity::Id pathId,  
	           entityx::Entity::Id aiId,
               entityx::EntityManager& entities,
               double dt);
 
   enum class AiType
   {
	   AI_ID_NONE, 
	   AI_ID_SEEK_SHOOT_AT_PLAYER
   };
   int currentNode = 0;
   std::vector<sf::CircleShape> const & m_obstacles;
   std::vector<sf::CircleShape> & m_nodes;
private:
	sf::Vector2f seek(entityx::Entity::Id pathId,
					  entityx::Entity::Id aiId,
					  entityx::EntityManager& entities);

	sf::Vector2f pathFollowing(entityx::Entity::Id aiId, entityx::Entity::Id pathId,
		entityx::EntityManager& entities);

	sf::Vector2f collisionAvoidance(entityx::Entity::Id aiId, 
						            entityx::EntityManager& entities);

	const sf::CircleShape findMostThreateningObstacle(entityx::Entity::Id aiId,
													  entityx::EntityManager& entities) ;

	sf::Vector2f m_velocity;

	sf::Vector2f m_steering;

	sf::Vector2f m_ahead;

	sf::Vector2f m_halfAhead;

	Path m_path;
	
	
	const float MAX_SEE_AHEAD = 50.0f;

	const float MAX_AVOID_FORCE = 50.0f;

	const float MAX_FORCE = 10.0f;

	float MAX_SPEED = 50.0f;

	bool collision = false;

	

	
	

	enum class AiBehaviour
	{
		PATH_FOLLOWING,
		SEEK_PLAYER,
		STOP,
		RETREAT
	} m_aiBehaviour;
  

};

