#pragma once

#include "EntityManager.h"

#define worldManager WorldManager::getInstance();

class WorldManager
{
public:
	WorldManager *getInstance();
	void update( double elapsedTime ) { m_entityManager.updateAllEntities(elapsedTime); }
	EntityManager *getEntityManager() { return &m_entityManager; }

private:
	WorldManager(void);
	~WorldManager(void);
	EntityManager m_entityManager;
};
