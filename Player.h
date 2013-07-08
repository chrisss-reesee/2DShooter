#pragma once

#include "BaseGameEntity.h"

class Player : public BaseGameEntity
{
public:
	Player(void);
	~Player(void);
	virtual void update(double timeElapsed);
	virtual void draw();

	void setHealth(float health) { m_health = health; }
	float getHealth() { return m_health; }
	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
	void addToScore( int points ) { m_score += points; }

private:
	double m_lastShotFiredTime;
	double m_speed;
	double m_timeBetweenShots;
	float m_health;
	int m_score;
};
