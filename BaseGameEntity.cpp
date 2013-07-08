#include "BaseGameEntity.h"
#include "Vector2D.h"

BaseGameEntity::BaseGameEntity(void)
{
	m_ID = g_dbBaseGameEntityNextInstanceNum;
	g_dbBaseGameEntityNextInstanceNum++;
	m_boundingRadius = 0.0;
	m_position.x = m_position.y = 0.0;
	m_entityType = enemy_entity_type;
	m_deleteNextCycle = false;
	m_lifespan = 0.0;
}

BaseGameEntity::BaseGameEntity(entity_type_t entityType)
{
	m_ID = g_dbBaseGameEntityNextInstanceNum;
	g_dbBaseGameEntityNextInstanceNum++;
	m_boundingRadius = 0.0;
	m_position.x = m_position.y = 0.0;
	m_entityType = entityType;
}

BaseGameEntity::BaseGameEntity(entity_type_t entityType, Vector2D position, double radius)
{
	m_ID = g_dbBaseGameEntityNextInstanceNum;
	g_dbBaseGameEntityNextInstanceNum++;
	m_boundingRadius = radius;
	m_position = position;
	m_entityType = entityType;
}

bool BaseGameEntity::checkForCollision(BaseGameEntity *entity) {
	Vector2D distanceVector = m_position - entity->getPosition();
	double distanceSquared = distanceVector.LengthSq();		// Working in squared space avoids a square root evaluation
	if( distanceSquared < (m_boundingRadius + entity->getBoundingRadius())*(m_boundingRadius + entity->getBoundingRadius()) )
		return true;
	else
		return false;
	
}

bool BaseGameEntity::isOffScreen() {
	if( (m_position.x + m_boundingRadius) < 0 ) {
		return true;
	}
	else if( (m_position.x - m_boundingRadius) > SCREEN_WIDTH ) {
		return true;
	}
	if( (m_position.y + m_boundingRadius) < 0 ) {
		return true;
	}
	else if( (m_position.y - m_boundingRadius) > SCREEN_HEIGHT ) {
		return true;
	}
	else {
		return false;
	}
}

BaseGameEntity::~BaseGameEntity(void)
{
}



