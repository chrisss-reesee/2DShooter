#pragma once

#include "Vector2D.h"
#include "BaseGameEntity.h"
#include "Vector2D.h"
#include "Utils.h"
#include "Image.h"
#include "StateMachine.h"
#include "SteeringBehaviour.h"
#include "Path.h"

class Enemy : public BaseGameEntity
{
public:
	Enemy();
	~Enemy(void);
	virtual void update(double elapsedTime);
	virtual void draw();

	// Game specific stuff
	bool hasClearShot();
	bool readyToShoot();
	void fireAhead();

	// Getters and setters
	void setMaxForce(double maxForce) { m_maxForce = maxForce; }
	double getMaxForce() { return m_maxForce; }
	void setMaxSpeed(double maxSpeed) { m_maxSpeed = maxSpeed; }
	double getMaxSpeed() { return m_maxSpeed; }
	void setVelocity(Vector2D velocity) { m_velocity = velocity; }
	Vector2D getVelocity() { return m_velocity; }
	SteeringBehaviour *getSteeringBehaviour() { return m_steering; }
	void setPath(Path *path) { m_path = path; }
	Path *getPath() { return m_path; }
	StateMachine<Enemy> *getStateMachine() { return m_state; }
	void setHealth(float health) { m_health = health; }
	float getHealth() { return m_health; }
	void setHeading(Vector2D heading) { m_heading = heading; }
	Vector2D getHeading() { return m_heading; }
	void setSide(Vector2D side) { m_side = side; }
	Vector2D getSide() { return m_side; }
	

private:
	float m_health;
	double m_mass;
	double m_maxSpeed;
	double m_maxForce;		// The amount of force this unit can exert on itself
	double m_maxTurnRate;
	Vector2D m_velocity;

	Vector2D m_heading;	// Together these two form a coordinate system
	Vector2D m_side;

	StateMachine<Enemy> *m_state;
	SteeringBehaviour *m_steering;
	Path *m_path;

	// Points for shape to draw
	std::vector<Vector2D> points;
	Vector2D m_scale;

	double m_timeSinceLastShot;
	double m_pauseBetweenShots;
};
