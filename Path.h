#pragma once

#include <list>
#include <assert.h>
#include "Vector2D.h"

class Path
{
public:
	Path(void);
	~Path(void);

	void addWaypoint( Vector2D waypoint );
	void setNextWaypoint();
	bool finished() { return ( (m_currentWaypoint == m_path.end()) && (m_looped == false) ); }
	Vector2D getCurrentWaypoint();

	void setLooped(bool looped) { m_looped = looped; }

private:
	std::list<Vector2D> m_path;
	std::list<Vector2D>::iterator m_currentWaypoint;
	bool m_looped;
};
