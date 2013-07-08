#include "Bullet.h"
#include "EntityManager.h"

extern EntityManager entityManager;


Bullet::Bullet(void)
{
	setEntityType( bullet_entity_type );
	setBoundingRadius( 3.0 );
}

Bullet::Bullet(Vector2D position, Vector2D velocity)
{
	setEntityType( bullet_entity_type );
	setBoundingRadius( 3.0 );

	setPosition( position );
	m_velocity = velocity;
}

Bullet::~Bullet(void)
{
}

void Bullet::update(double timeElapsed) {
	if( isOffScreen() ) {
		markForDeletion();
		return;
	}

	setPosition( getPosition()+m_velocity );
}


void Bullet::draw() {
	dbInk( RGB(0,0,255), RGB(0,0,255) );
	dbCircle( getPosition().x, getPosition().y, getBoundingRadius() );

	//static Image image("orkboy.bmp");
	//image.paste( getPosition().x, getPosition().y );
}
