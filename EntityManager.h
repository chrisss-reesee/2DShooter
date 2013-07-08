#pragma once

#include <map>
#include <list>
#include "BaseGameEntity.h"
#include "Player.h"

class EntityManager
{
public:
	EntityManager(void);
	~EntityManager(void);
	void registerEntity(BaseGameEntity *entity);

	// Game specific stuff here
	void spawnRandomWave();

	// Get an entity from its ID, return NULL if entity not found
	BaseGameEntity *getEntityFromID(int id);
	void removeEntity(BaseGameEntity *pEntity);
	void updateAllEntities(double elapsedTime);
	void drawAllEntities();
	void deleteMarkedEntities();
	int getSize() { return m_entityMap.size(); }
	std::list<BaseGameEntity *> getAllEntitiesOfType(entity_type_t type);
	std::list<BaseGameEntity *> getNeighbours(BaseGameEntity *entity, float radius);
	Player *getPlayer() { return &m_player; }

private:
	std::map<int, BaseGameEntity*> m_entityMap;
	Player m_player;
};
