#pragma once

#include "Vector2D.h"
#include "Utils.h"
#include "Path.h"

class Enemy;

typedef enum Deceleration {slow=3, normal=2, fast=1};

class SteeringBehaviour
{
public:
	SteeringBehaviour(Enemy *owner);
	~SteeringBehaviour(void);

	Vector2D calculate();
	Vector2D flee(Vector2D target);
	Vector2D seek(Vector2D target);
	Vector2D arrive(Vector2D target,  Deceleration deceleration);
	Vector2D followPath();
	Vector2D seperation();

	// Setters and getters
	void setFlee(bool value, Vector2D target = Vector2D(0.0,0.0));
	void setSeek(bool value, Vector2D target = Vector2D(0.0,0.0));
	void setArrive(bool value, Vector2D target = Vector2D(0.0,0.0));
	void setFollowPath(bool value, Path *path = NULL);
	void setSeperation(bool value) { m_seperation = value; }

private:
	bool m_flee;
	bool m_seek;
	bool m_arrive;
	bool m_followPath;
	bool m_seperation;
	Enemy *m_owner;
	Vector2D *m_fleeTarget;
	Vector2D *m_seekTarget;
	Vector2D *m_arriveTarget;
	Path *m_path;
};
