#include "Camera.h"
#include "StateMachine.h"

Camera::Camera(void)
{
	m_x = m_y = 0.0;
	m_screenX = m_screenY = 0;
	m_height = dbScreenHeight();
	m_width = dbScreenWidth();

	// Create the bitmap that the camera viewpoint will be drawn to
	m_bitmap = new Bitmap( dbScreenWidth(), dbScreenHeight() );

	// Set up the behaviour state machine
	m_behaviourState = new StateMachine<Camera>(this);
	m_behaviourState->setGlobalState( CameraGlobalState::getInstance() );
	m_behaviourState->setCurrentState( CameraFollowArrowKeysState::getInstance() );

	m_images[0].load( "grass.bmp" );
	m_images[1].load( "dirt.bmp" );
}

Camera::~Camera(void)
{
}

void Camera::draw() {
	int topLeftTileX = (int)(m_x/TILE_WIDTH);
	int topLeftTileY = (int)(m_y/TILE_HEIGHT);
	int bottomRightTileX = (int)((m_x+m_width)/TILE_WIDTH);
	int bottomRightTileY = (int)((m_y+m_height)/TILE_HEIGHT);
	int cameraX = (int)m_x;
	int cameraY = (int)m_y;

	m_bitmap->setAsActiveTarget();	// Draw the camera perspective to a bitmap

	for( int i=topLeftTileX; i<=bottomRightTileX; i++ ) {
		for( int j=topLeftTileY; j<=bottomRightTileY; j++ ) {
			m_images[m_map->getTileType(i,j)].paste( (TILE_WIDTH*i)-cameraX, (TILE_HEIGHT*j)-cameraY );
		}
	}
	/* Old version, before we started pasting to a bitmap
	for( int i=topLeftTileX; i<=bottomRightTileX; i++ ) {
		for( int j=topLeftTileY; j<=bottomRightTileY; j++ ) {
			m_images[m_map->getTileType(i,j)].paste( (TILE_WIDTH*i)-cameraX+m_screenX, (TILE_HEIGHT*j)-cameraY+m_screenY );
		}
	}
	*/

	m_bitmap->draw( m_screenX, m_screenY );	// Draw the bitmap to the sceen
	m_bitmap->setAsActiveTarget(false);	// Reset so drawing functions target the screen again

	dbInk( RGB(0,255,0), RGB(0,255,0) );
	dbRectangle(m_screenX, m_screenY, m_screenX+m_width, m_screenY+m_height );
}

// Automatically stays within the boundaries of the map
void Camera::setPosition( int x, int y ) {
	if( x < 0 )
		x = 0;
	if( y < 0 )
		y = 0;
	if( x+m_width+1 > (m_map->getWidth() * TILE_WIDTH ) )
		x = (m_map->getWidth()*TILE_WIDTH) - m_width - 1;
	if( y+m_height+1 > (m_map->getHeight() * TILE_HEIGHT ) )
		y = (m_map->getHeight()*TILE_HEIGHT) - m_height - 1;

	m_x = x;
	m_y = y;
}


void Camera::update(double elapsedTime) {
	m_behaviourState->update();
}

