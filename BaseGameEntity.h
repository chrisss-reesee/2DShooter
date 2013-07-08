#pragma once

#include "Vector2D.h"

class EntityManager;

typedef enum {
	default_entity_type,
	enemy_entity_type,
	bullet_entity_type,
	player_entity_type
} entity_type_t;

static int g_dbBaseGameEntityNextInstanceNum = 1;

class BaseGameEntity
{
public:
	BaseGameEntity();
	BaseGameEntity(entity_type_t entityType);
	BaseGameEntity(entity_type_t entityType, Vector2D position, double radius);
	virtual ~BaseGameEntity(void);

	virtual void update(double timeElapsed) {}
	virtual void draw() {}

	// Setters and getters
	void setPosition(Vector2D position) { m_position = position; }
	Vector2D getPosition() { return m_position; }
	void setBoundingRadius(double radius) { m_boundingRadius = radius; }
	double getBoundingRadius() { return m_boundingRadius; }
	int getID() { return m_ID; }
	void setEntityType(entity_type_t entityType) { m_entityType = entityType; }
	entity_type_t getEntityType() { return m_entityType; }
	void markForDeletion(bool value = true) { m_deleteNextCycle = value; }
	bool readyForDeletion() { return m_deleteNextCycle; }
	bool checkForCollision(BaseGameEntity *entity);
	bool isOffScreen();
	void setLifespan( double lifespan ) { m_lifespan = lifespan; }
	double getLifespan() { return m_lifespan; }

private:
	int m_ID;
	entity_type_t m_entityType;
	Vector2D m_position;
	double m_boundingRadius;
	bool m_deleteNextCycle;		// Set this when the object is ready for deletion
	double m_lifespan;
};
