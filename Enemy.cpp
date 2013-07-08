#include <vector>
#include "Enemy.h"
#include "Vector2D.h"
#include "EnemyStates.h"
#include "EntityManager.h"
#include "Bullet.h"

extern EntityManager entityManager;

Enemy::Enemy()
{
	setEntityType( enemy_entity_type );
	setBoundingRadius( 20 );
	m_health = 1.0;
	m_mass = 0.1;
	m_maxSpeed = 500.0;
	m_maxForce = 200.0;
	m_maxTurnRate = 0.1;
	m_heading.x = 0.0;
	m_heading.y = 1.0;
	m_side = m_heading.Perp();
	m_steering = new SteeringBehaviour(this);
	m_state = new StateMachine<Enemy>(this);
	m_state->setGlobalState(EnemyGlobalState::getInstance());

	m_timeSinceLastShot = 1.0;
	m_pauseBetweenShots = 1.0;

	// Flathead
	/*
	points.push_back( Vector2D(-0.5f,1.5f) ); //1
	points.push_back( Vector2D(0.5f,1.5f) ); //2
	points.push_back( Vector2D(0.5f,-1.5f) ); //3
	points.push_back( Vector2D(-0.5f,-1.5f) ); //4
	points.push_back( Vector2D(-0.5f,1.5f) ); //5
	points.push_back( Vector2D(-1.5f,0.5f) ); //6
	points.push_back( Vector2D(-1.5f,-1.5f) );//7
	points.push_back( Vector2D(1.5f,-1.5f) );//8
	points.push_back( Vector2D(1.5f,0.5f) );//9
	points.push_back( Vector2D(0.5f,1.5f) ); //10
	m_scale.x = getBoundingRadius();
	m_scale.y = getBoundingRadius();
	*/
	// Arrowhead
	points.push_back( Vector2D(-0.5f,1.0f) ); //1
	points.push_back( Vector2D(-0.5f,0.0f) ); //2
	points.push_back( Vector2D(0.5f,0.0f) ); //3
	points.push_back( Vector2D(0.5f,1.0f) ); //4
	points.push_back( Vector2D(0.0f,2.0f) ); //5
	points.push_back( Vector2D(-1.5f,-1.0f) ); //6
	points.push_back( Vector2D(-0.5f,-2.0f) );//7
	points.push_back( Vector2D(0.5f,-2.0f) );//8
	points.push_back( Vector2D(1.5f,-1.0f) );//9
	points.push_back( Vector2D(0.5f,1.0f) ); //10
	m_scale.x = getBoundingRadius() * 0.5;
	m_scale.y = getBoundingRadius() * 0.5;
}


Enemy::~Enemy(void)
{
	delete m_steering;
	delete m_state;
}


void Enemy::update(double elapsedTime) {
	setLifespan( getLifespan() + elapsedTime );
	m_timeSinceLastShot += elapsedTime;

	m_state->update();
	Vector2D steeringForce = m_steering->calculate();

	//Vector2D localSteeringForce = PointToLocalSpace(steeringForce, m_heading, m_side, getPosition());
	//if( localSteeringForce.y < 0.0 )
	//	localSteeringForce.y = 0.0;
	//steeringForce = WorldTransform(localSteeringForce, m_heading, m_side, getPosition(),Vector2D(1.0,1.0));

	Vector2D acceleration = steeringForce/m_mass;
	m_velocity += (acceleration * elapsedTime);
	m_velocity.Truncate(m_maxSpeed);

	

	// Update the heading
	if( m_velocity.LengthSq() > 0.00000001 ) {
		m_heading = m_velocity;
		m_heading.Normalize();
		m_side = m_heading.Perp();
	}

	//m_velocity = m_heading * m_maxSpeed;

	setPosition( getPosition()+(m_velocity*elapsedTime) );

	
}

void Enemy::draw() {
	dbInk( RGB(200,50,50), RGB(255,255,255) );
	//dbCircle( getPosition().x, getPosition().y, getBoundingRadius() );
	Vector2D endpoint(getPosition().x,getPosition().y);
	endpoint += m_heading * getBoundingRadius();
	dbLine( getPosition().x, getPosition().y, endpoint.x, endpoint.y );
	//dbCircle( getPosition().x, getPosition().y, 100.0 );


	// Draw the shape
	std::vector<Vector2D> translatedPoints = TransformFromLocalToWorldSpace( points, getPosition(), m_heading, m_side, m_scale );
	std::vector<Vector2D>::iterator i = translatedPoints.begin();
	Vector2D previousPoint = (*i);
	for( i++; i != translatedPoints.end(); i++ ) {
		dbLine( previousPoint.x, previousPoint.y, i->x, i->y );
		previousPoint = (*i);
	}


	static Image image("ship02.bmp");
	int width = 34; int height = 40;
	Vector2D putImageHere( getPosition().x-width/2, getPosition().y-height/2 );

	//image.paste( putImageHere.x, putImageHere.y );
	//dbRectangle( getPosition().x, getPosition().y, getPosition().x+getBoundingRadius(), getPosition().y+getBoundingRadius() );
}

bool Enemy::hasClearShot() {

	Vector2D playerLocalPosition = TransformFromWorldToLocalSpace( entityManager.getPlayer()->getPosition(), m_heading, m_side, getPosition() );
	if( playerLocalPosition.y < 0.0 )
		return false;
	if( abs(playerLocalPosition.x) > getBoundingRadius() )
		return false;

	// Deal with enemies later
	std::list<BaseGameEntity *> enemies = entityManager.getAllEntitiesOfType( enemy_entity_type );
	std::list<BaseGameEntity *>::iterator i = enemies.begin();
	while( i != enemies.end() ) {
		Vector2D localPosition = TransformFromWorldToLocalSpace( (*i)->getPosition(), ((Enemy *)(*i))->getHeading(), ((Enemy *)(*i))->getSide(), ((Enemy *)(*i))->getPosition() );
		if( (localPosition.y > 0.0) ) {	// Throw away anybody behind us
			if( abs(localPosition.y)>(*i)->getBoundingRadius() ) {	// Check to see if they're in the line of fire
				if( localPosition.y < playerLocalPosition.y ) {	// Make sure they're behind the player
					return false;
				}
			}
		}
		i++;
	}

	return true;
}

bool Enemy::readyToShoot() {
	if( m_timeSinceLastShot < m_pauseBetweenShots )
		return false;
	else
		return true;
}

void Enemy::fireAhead() {
	Vector2D position = getPosition() + (m_heading*getBoundingRadius());
	Vector2D velocity = m_heading * 12.0;
	Bullet *bullet = new Bullet(position, velocity);
	entityManager.registerEntity( bullet );
	m_timeSinceLastShot = 0.0;
}