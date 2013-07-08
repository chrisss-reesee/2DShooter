#include "EntityManager.h"
#include <vector>
#include "MessageManager.h"
#include "Enemy.h"
#include "EnemyStates.h"

extern EntityManager entityManager;

EntityManager::EntityManager(void)
{
}

EntityManager::~EntityManager(void)
{
}

void EntityManager::registerEntity(BaseGameEntity *entity) {
	m_entityMap.insert(std::make_pair(entity->getID(), entity));
}

// Get an entity from its ID, return NULL if entity not found
BaseGameEntity* EntityManager::getEntityFromID(int id) {
	std::map<int, BaseGameEntity*>::iterator entity = m_entityMap.find(id);

	// Return NULL if the entity was not found
	if( entity == m_entityMap.end() )
		return NULL;
	else
		return entity->second;
}


void EntityManager::removeEntity(BaseGameEntity *entity) {
	m_entityMap.erase( m_entityMap.find(entity->getID()) );
	delete entity;
}


void EntityManager::updateAllEntities(double elapsedTime) {
	for( std::map<int, BaseGameEntity*>::iterator iterator = m_entityMap.begin(); iterator != m_entityMap.end(); iterator++ ) {
		iterator->second->update(elapsedTime);
	}
	m_player.update(elapsedTime);

	// Check for enemy-enemy collisions
	/*
	std::list<BaseGameEntity *> enemies1 = getAllEntitiesOfType(enemy_entity_type);
	std::list<BaseGameEntity *> enemies2 = getAllEntitiesOfType(enemy_entity_type);
	for( std::list<BaseGameEntity *>::iterator entityType1Iterator = enemies1.begin(); entityType1Iterator != enemies1.end(); entityType1Iterator++ ) {
		for( std::list<BaseGameEntity *>::iterator entityType2Iterator = enemies2.begin(); entityType2Iterator != enemies2.end(); entityType2Iterator++ ) {
			if( ((*entityType1Iterator)->getID()!= (*entityType2Iterator)->getID()) &&  (*entityType1Iterator)->checkForCollision((*entityType2Iterator)) ) {
				(*entityType1Iterator)->markForDeletion();
				(*entityType2Iterator)->markForDeletion();
			}
		}
	}
	*/

	// Check for bullet-enemy collisions
	std::list<BaseGameEntity *> enemies1 = getAllEntitiesOfType(enemy_entity_type);
	std::list<BaseGameEntity *> enemies2 = getAllEntitiesOfType(bullet_entity_type);
	for( std::list<BaseGameEntity *>::iterator entityType1Iterator = enemies1.begin(); entityType1Iterator != enemies1.end(); entityType1Iterator++ ) {
		for( std::list<BaseGameEntity *>::iterator entityType2Iterator = enemies2.begin(); entityType2Iterator != enemies2.end(); entityType2Iterator++ ) {
			if( ((*entityType1Iterator)->getID()!= (*entityType2Iterator)->getID()) &&  (*entityType1Iterator)->checkForCollision((*entityType2Iterator)) ) {
				((Enemy *)(*entityType1Iterator))->setHealth( ((Enemy *)(*entityType1Iterator))->getHealth()-1.0 );
				(*entityType2Iterator)->markForDeletion();
				entityManager.getPlayer()->addToScore( 10 );
				dbPlaySound(2);
			}
		}
	}

	// Check for player-enemy collisions
	enemies1 = getAllEntitiesOfType(enemy_entity_type);
	for( std::list<BaseGameEntity *>::iterator entityType1Iterator = enemies1.begin(); entityType1Iterator != enemies1.end(); entityType1Iterator++ ) {
		if( m_player.checkForCollision((*entityType1Iterator)) ) {
			(*entityType1Iterator)->markForDeletion();
			m_player.setHealth( m_player.getHealth() - 1.0 );
			dbPlaySound(2);
		}
	}

	// Check for player-bullet collisions
	enemies1 = getAllEntitiesOfType(bullet_entity_type);
	for( std::list<BaseGameEntity *>::iterator entityType1Iterator = enemies1.begin(); entityType1Iterator != enemies1.end(); entityType1Iterator++ ) {
		if( m_player.checkForCollision((*entityType1Iterator)) ) {
			(*entityType1Iterator)->markForDeletion();
			m_player.setHealth( m_player.getHealth() - 1.0 );
			dbPlaySound(2);
		}
	}

	deleteMarkedEntities();
}

void EntityManager::drawAllEntities() {
	for( std::map<int, BaseGameEntity*>::iterator iterator = m_entityMap.begin(); iterator != m_entityMap.end(); iterator++ ) {
		iterator->second->draw();
	}
	m_player.draw();
}


void EntityManager::deleteMarkedEntities() {
	std::vector<int> toDelete;
	for( std::map<int, BaseGameEntity*>::iterator iterator = m_entityMap.begin(); iterator != m_entityMap.end(); iterator++ ) {
		if( iterator->second->readyForDeletion() )
			toDelete.push_back(iterator->second->getID());
	}
	for( std::vector<int>::iterator iterator = toDelete.begin(); iterator != toDelete.end(); iterator++ ) {
		removeEntity( getEntityFromID( *iterator ) );
	}
}

std::list<BaseGameEntity *> EntityManager::getAllEntitiesOfType(entity_type_t type) {
	std::list<BaseGameEntity *> list;

	for( std::map<int, BaseGameEntity*>::iterator iterator = m_entityMap.begin(); iterator != m_entityMap.end(); iterator++ ) {
		if( iterator->second->getEntityType() == type )
			list.push_back(iterator->second);
	}

	return list;
}


std::list<BaseGameEntity *> EntityManager::getNeighbours(BaseGameEntity *entity, float radius) {
	std::list<BaseGameEntity *> list;
	double radiusSquared = radius * radius;
	for( std::map<int, BaseGameEntity*>::iterator iterator = m_entityMap.begin(); iterator != m_entityMap.end(); iterator++ ) {
		if( iterator->second->getID() != entity->getID() ) {
			Vector2D distanceVector = iterator->second->getPosition() - entity->getPosition();
			if( distanceVector.LengthSq() < radiusSquared ) {
				list.push_back(iterator->second);
			}
		}
	}

	return list;
}



void EntityManager::spawnRandomWave() {

	int pathSelection = rand()%8;
	double pauseBetweenEnemies = 0.2;
	int numberOfEnemies = 6;


	for( int i=0; i<numberOfEnemies; i++ ) {
		// Set up a test path
		Path *path = new Path();
		Enemy *enemy = new Enemy();

		// Random chance of having 2 health
		if(rand()%100 < 0)
			enemy->setHealth(2.0);

		Vector2D startingPosition;
		switch( pathSelection ) {
			case 0:
				// Top left to right left U shape
				startingPosition = Vector2D(100.0,-10.0);
				path->addWaypoint( Vector2D(200.0,200.0) );
				path->addWaypoint( Vector2D(400.0,300.0) );
				path->addWaypoint( Vector2D(700.0,-10.0) );
				break;
			case 1:
				// Bottom left to bottom right U shape
				startingPosition = Vector2D(100.0,610.0);
				path->addWaypoint( Vector2D(200.0,400.0) );
				path->addWaypoint( Vector2D(400.0,300.0) );
				path->addWaypoint( Vector2D(700.0,610.0) );
				break;
			case 2:
				// Top right to top left U shape
				startingPosition = Vector2D(700.0,-10.0);
				path->addWaypoint( Vector2D(600.0,200.0) );
				path->addWaypoint( Vector2D(400.0,300.0) );
				path->addWaypoint( Vector2D(100.0,-10.0) );
				break;
			case 3:
				// Bottom right to bottom left U shape
				startingPosition = Vector2D(700.0,610.0);
				path->addWaypoint( Vector2D(600.0,400.0) );
				path->addWaypoint( Vector2D(400.0,300.0) );
				path->addWaypoint( Vector2D(100.0,610.0) );
				break;
			case 4:
				// Top left to top right straight down
				pauseBetweenEnemies = 0.4;;
				startingPosition = Vector2D( 100.0+(i*100.0), -10.0 );
				path->addWaypoint( Vector2D(100.0+(i*100.0), 610.0) );
				break;
			case 5:
				// Top right to top left straight down
				pauseBetweenEnemies = 0.4;
				startingPosition = Vector2D( 700.0-(i*100.0), -10.0 );
				path->addWaypoint( Vector2D( 700.0-(i*100.0), 610.0) );
				break;
			case 6:
				// Top left to bottom left straight across
				startingPosition = Vector2D(-10.0,60.0+(i*80));
				path->addWaypoint( Vector2D(810.0,60.0+(i*80)) );
				break;
			case 7:
				// Top right to bottom right straight across
				startingPosition = Vector2D(810.0,60.0+(i*80));
				path->addWaypoint( Vector2D(-10.0,60.0+(i*80)) );
				break;
		}
		path->setLooped(false);

		enemy->setPosition(startingPosition);
		enemy->setPath( path );
		enemy->getStateMachine()->changeState( EnemyFollowPathThenDieState::getInstance() );
		MessageManager::getInstance()->dispatchMessage(0,0,messageCreateEntity,i*pauseBetweenEnemies,enemy);
	}

}
