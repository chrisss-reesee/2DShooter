#include "SteeringBehaviour.h"
#include "Enemy.h"
#include "EntityManager.h"

extern EntityManager entityManager;

SteeringBehaviour::SteeringBehaviour(Enemy *owner)
{
	m_owner = owner;
	m_flee = false;
	m_seek = false;
	m_arrive = false;
	m_followPath = false;
	m_seperation = false;
	m_fleeTarget = NULL;
	m_seekTarget = NULL;
	m_arriveTarget = NULL;
	m_path = NULL;
}

SteeringBehaviour::~SteeringBehaviour(void)
{
	delete m_path;
	delete m_arriveTarget;
	delete m_seekTarget;
	delete m_fleeTarget;
}

Vector2D SteeringBehaviour::calculate() {
	double weightFlee = 1.0;
	double weightSeek = 1.0;
	double weightArrive = 1.0;
	double weightFollowPath = 1.0;
	double weightSeperation = 50.0;

	// Use Weighted Truncated Sum for now
	Vector2D steeringForce;

	if( m_flee ) {
		steeringForce += ( flee(*m_fleeTarget) * weightFlee );
	}
	if( m_seek ) {
		steeringForce += ( seek(*m_seekTarget) * weightSeek );
	}
	if( m_arrive ) {
		steeringForce += ( arrive(*m_arriveTarget,fast) * weightArrive );
	}
	if( m_followPath && !m_path->finished() ) {
		steeringForce += ( followPath() * weightFollowPath );
	}
	if( m_seperation ) {
		steeringForce += ( seperation() * weightSeperation );
	}

	steeringForce.Truncate( m_owner->getMaxForce() );
	return steeringForce;
}

Vector2D SteeringBehaviour::flee(Vector2D target) {
	Vector2D desiredVelocity = m_owner->getPosition() - target;
	desiredVelocity.Normalize();
	desiredVelocity = desiredVelocity * m_owner->getMaxSpeed();

	return desiredVelocity - m_owner->getVelocity();
}

void SteeringBehaviour::setFlee(bool value, Vector2D target) {
	delete m_fleeTarget;
	m_flee = value;
	m_fleeTarget = new Vector2D(target.x,target.y);
}

Vector2D SteeringBehaviour::seek(Vector2D target) {
	Vector2D desiredVelocity = target - m_owner->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity = desiredVelocity * m_owner->getMaxSpeed();

	return desiredVelocity - m_owner->getVelocity();
}

void SteeringBehaviour::setSeek(bool value, Vector2D target) {
	delete m_seekTarget;
	m_seek = value;
	m_seekTarget = new Vector2D(target.x,target.y);
}

Vector2D SteeringBehaviour::arrive(Vector2D target, Deceleration deceleration) {
	Vector2D toTarget = target - m_owner->getPosition();
	double distance = toTarget.Length();

	if( distance > 0.0 ) {
		const double DecelerationTweaker = 0.3;

		// calculate speed required to reach target
		double speed = distance / ( (double)deceleration * DecelerationTweaker );
		speed = min(speed, m_owner->getMaxSpeed());

		Vector2D desiredVelocity = toTarget * speed / distance;
		return (desiredVelocity - m_owner->getVelocity());
	}
	
	return Vector2D(0.0,0.0);
}

void SteeringBehaviour::setArrive(bool value, Vector2D target) {
	delete m_arriveTarget;
	m_arrive = value;
	m_arriveTarget = new Vector2D(target.x,target.y);
}

Vector2D SteeringBehaviour::followPath() {
	if( m_path->finished() )
		return Vector2D(0.0,0.0);

	double waypointSeekDistance = 5.0;

	Vector2D distVector = m_path->getCurrentWaypoint() - m_owner->getPosition();
	if( (distVector.Length() < waypointSeekDistance) && !m_path->finished() ) {
		m_path->setNextWaypoint();
	}

	if( !m_path->finished() ) {
		return seek( m_path->getCurrentWaypoint() );
	}
	else {
		// Just to get rid of any lingering momentum
		m_owner->setVelocity(Vector2D(0.0,0.0));
		return Vector2D(0.0,0.0);
	}
}

void SteeringBehaviour::setFollowPath(bool value, Path *path) {
	delete m_path;
	m_followPath = value;
	m_path = path;
}


Vector2D SteeringBehaviour::seperation() {
	std::list<BaseGameEntity*> neighbours = entityManager.getNeighbours(m_owner, 100.0);
	Vector2D steeringForce;

	for( std::list<BaseGameEntity*>::iterator iterator = neighbours.begin(); iterator!=neighbours.end(); iterator++ ) {
		Vector2D toAgent = m_owner->getPosition() - entityManager.getEntityFromID((*iterator)->getID())->getPosition();
		double length = toAgent.Length();
		toAgent.Normalize();
		steeringForce += toAgent/length;
	}

	return steeringForce;
}