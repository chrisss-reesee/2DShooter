#include "DarkGDK.h"
#include "Player.h"
#include "BaseGameEntity.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "Image.h"

extern EntityManager entityManager;

Player::Player(void)
{
	setEntityType( player_entity_type );
	setPosition(Vector2D(400.0,500.0));
	setBoundingRadius( 20 );
	m_lastShotFiredTime = 0.0;
	m_timeBetweenShots = 0.15;
	m_speed = 6.0;
	m_health = 1.0;
}

Player::~Player(void)
{
}

void Player::update(double timeElapsed) {
	setLifespan( getLifespan() + timeElapsed );

	int joystickX = dbJoystickX();
	int joystickY = dbJoystickY();

	if( (dbUpKey()||joystickY<-10) && getPosition().y - getBoundingRadius() > 0.0 )
		setPosition( getPosition() + Vector2D(0.0,-m_speed) );
	if( (dbDownKey()||joystickY>10) && getPosition().y + getBoundingRadius() < SCREEN_HEIGHT )
		setPosition( getPosition() + Vector2D(0.0,m_speed) );
	if( (dbLeftKey()||joystickX<-10) && getPosition().x - getBoundingRadius() > 0.0 )
		setPosition( getPosition() + Vector2D(-m_speed,0.0) );
	if( (dbRightKey()||joystickX>10) && getPosition().x + getBoundingRadius() < SCREEN_WIDTH )
		setPosition( getPosition() + Vector2D(m_speed,0.0) );

	if( (dbSpaceKey()||dbJoystickFireC()) && getLifespan() > (m_lastShotFiredTime+m_timeBetweenShots)   ) {
		Bullet *bullet = new Bullet();
		Vector2D bulletPosition = getPosition();
		bulletPosition.y = bulletPosition.y - getBoundingRadius() - bullet->getBoundingRadius();
		Vector2D bulletVelocity = Vector2D(0.0,-25.0);
		bullet->setPosition(bulletPosition);
		bullet->setVelocity(bulletVelocity);
		entityManager.registerEntity( bullet );
		m_lastShotFiredTime = getLifespan();
		//dbPlaySound(1);
	}

}


void Player::draw() {
	static Image image("ship01.bmp");
	image.paste( getPosition().x-16, getPosition().y-16 );

	if( m_health > 0.0 )
		dbInk( RGB(0,255,0), RGB(0,255,0) );
	else
		dbInk( RGB(0,0,255), RGB(0,0,255) );
	dbCircle( getPosition().x, getPosition().y, getBoundingRadius() );
}
