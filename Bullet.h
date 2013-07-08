#pragma once

#include "Vector2D.h"
#include "BaseGameEntity.h"

class Bullet : public BaseGameEntity
{
public:
	Bullet();
	Bullet(Vector2D position, Vector2D velocity);
	~Bullet(void);

	virtual void update(double timeElapsed);
	virtual void draw();
	void setVelocity( Vector2D velocity ) { m_velocity = velocity; }
	Vector2D getVelocity() { return m_velocity; }

private:
	Vector2D m_velocity;
};
