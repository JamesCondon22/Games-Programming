#include "systems/LevelSystem.h"
#include "WallCreator.h"
#include "PathCreator.h"

LevelSystem::LevelSystem(entityx::EntityManager& entities,
						 entityx::EventManager& eventManager)
: m_entityManager(entities)
, m_eventManager(eventManager)
{
}

void LevelSystem::configure(entityx::EventManager &eventManager)
{
   eventManager.subscribe<EvInit>(*this);
}

void LevelSystem::update(entityx::EntityManager& entities,
						 entityx::EventManager& events,
                         double dt)
{
 

}

void LevelSystem::receive(const EvInit& e)
{
   
   BackgroundCreator(e.m_level.m_background.m_fileName).create(m_entityManager.create());

   entityx::Entity tankBaseEntity = m_entityManager.create();

   TankBaseCreator(e.m_level.m_tank.m_position, false).create(tankBaseEntity);

   TurretCreator(e.m_level.m_tank, tankBaseEntity, false).create(m_entityManager.create());
   // Create the AI tank opponent
   entityx::Entity aiTankBaseEntity = m_entityManager.create();

   // Emit the event so the AIControlSystem will get it's id - note how we can get an id from the entity.
   m_eventManager.emit<EvReportPlayerId>(tankBaseEntity.id());

   //create the AI tank Base 
   TankBaseCreator(e.m_level.m_aiTank.m_position, true).create(aiTankBaseEntity);

   //create the AI turret
   TurretCreator(e.m_level.m_aiTank, aiTankBaseEntity, true).create(m_entityManager.create());
   
   //create the walls
   for (ObstacleData const &obstacle : e.m_level.m_obstacles)
   {
	   WallCreator(obstacle.m_type, obstacle.m_position, obstacle.m_rotation).create(m_entityManager.create());
   }

   for (PathData const &path : e.m_level.m_path)
   {
	   PathCreator(path.m_type, path.m_position, path.m_rotation).create(m_entityManager.create());
   }

}

