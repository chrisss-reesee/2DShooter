#include "WorldManager.h"

WorldManager *WorldManager::getInstance() {
	static WorldManager instance;
	return &instance;
}

WorldManager::WorldManager(void)
{
}

WorldManager::~WorldManager(void)
{
}
