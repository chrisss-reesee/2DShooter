#pragma once

#include "DarkGDK.h"
#include "Map.h"
#include "Image.h"
#include "Bitmap.h"
#include "Utils.h"
#include "StateMachine.h"
#include "CameraStates.h"


class Camera
{
public:
	Camera(void);
	~Camera(void);

	void draw();		// Draw everything
	void update(double elapsedTime);		// Update the camera
	
	// Setters and getters
	void setMap( Map *map ) { m_map = map; }
	void setScreenPosition(int x, int y ) { m_screenX = x; m_screenY = y; }
	void setPosition( int x, int y );
	int getX() { return m_x; }
	int getY() { return m_y; }
	void setSize( int width, int height ) { m_width = width; m_height = height; m_bitmap->resize(width,height); }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	StateMachine<Camera> *getStateMachine() { return m_behaviourState; }



private:
	int m_screenX, m_screenY;		// Position of the camera on the monitor
	int m_height, m_width;	// Height and width of the camera on monitor

	StateMachine<Camera> *m_behaviourState;
	
	Map *m_map;
	float m_x, m_y;	// Position within a map, ie what is being looked at

	Bitmap *m_bitmap;	// We draw to this, then copy it to the screen. This allows us to have cameras that are less
					// than the screen size and still paste images that would go over the camera boundaries

	Image m_images[2];
};