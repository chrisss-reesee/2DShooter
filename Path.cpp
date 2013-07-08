#include "Path.h"

Path::Path(void)
{
	m_looped = false;
}

Path::~Path(void)
{
}

void Path::addWaypoint( Vector2D waypoint ) {
	m_path.push_back( waypoint );
	if( m_path.size() == 1 ) {
		m_currentWaypoint = m_path.begin();
	}
}

Vector2D Path::getCurrentWaypoint() {
	return Vector2D((*m_currentWaypoint).x, (*m_currentWaypoint).y);
}

void Path::setNextWaypoint() {
	m_currentWaypoint++;
	if( m_currentWaypoint == m_path.end() ) {
		if( m_looped )
			m_currentWaypoint = m_path.begin();
	}
}
