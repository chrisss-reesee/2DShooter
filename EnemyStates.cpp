#include "EnemyStates.h"
#include "Enemy.h"
#include "Path.h"
#include "EntityManager.h"
#include "Bullet.h"
#include <stdlib.h>

extern EntityManager entityManager;

// Methods for EnemyGlobalState ////////////////////////
EnemyGlobalState *EnemyGlobalState::getInstance() {
	static EnemyGlobalState instance;
	return &instance;
}

void EnemyGlobalState::Enter(Enemy *enemy) {}

void EnemyGlobalState::Execute(Enemy *enemy) {
	if( enemy->getHealth() <= 0.0 ) {
		enemy->markForDeletion();
	}
}

void EnemyGlobalState::Exit(Enemy *enemy) {}
////////////////////////////////////////////////////

// Methods for EnemyFollowPathThenDieState ////////////////////////
EnemyFollowPathThenDieState *EnemyFollowPathThenDieState::getInstance() {
	static EnemyFollowPathThenDieState instance;
	return &instance;
}

void EnemyFollowPathThenDieState::Enter(Enemy *enemy) {
	enemy->getSteeringBehaviour()->setFollowPath( true, enemy->getPath() );
}

void EnemyFollowPathThenDieState::Execute(Enemy *enemy) {
	if( enemy->getPath()->finished() ) {
		enemy->markForDeletion();
	}
	if( rand()%2000 == 0 )
		enemy->getStateMachine()->changeState( EnemyCollideWithPlayerState::getInstance() );

	
	if( enemy->readyToShoot() ) {
		if( enemy->hasClearShot() ) {
			enemy->fireAhead();
			//Vector2D position = enemy->getPosition() + (enemy->getHeading()*enemy->getBoundingRadius());
			//Vector2D velocity = enemy->getHeading() * 15.0;
			//Bullet *bullet = new Bullet(position, velocity);
			//entityManager.registerEntity( bullet );
		}
	}
}

void EnemyFollowPathThenDieState::Exit(Enemy *enemy) {
	enemy->getSteeringBehaviour()->setFollowPath( false );
}
////////////////////////////////////////////////////


// Methods for EnemyCollideWithPlayerState ////////////////////////
EnemyCollideWithPlayerState *EnemyCollideWithPlayerState::getInstance() {
	static EnemyCollideWithPlayerState instance;
	return &instance;
}

void EnemyCollideWithPlayerState::Enter(Enemy *enemy) {
	enemy->getSteeringBehaviour()->setSeek(true, entityManager.getPlayer()->getPosition() );
}

void EnemyCollideWithPlayerState::Execute(Enemy *enemy) {
	enemy->getSteeringBehaviour()->setSeek(true, entityManager.getPlayer()->getPosition() );
}

void EnemyCollideWithPlayerState::Exit(Enemy *enemy) {

}
////////////////////////////////////////////////////