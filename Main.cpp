
// Dark GDK - The Game Creators - www.thegamecreators.com

// the wizard has created a very simple 2D project that uses Dark GDK
// it can be used as a starting point in making your own 2D games

// whenever using Dark GDK you must ensure you include the header file
#include "DarkGDK.h"
#include "Image.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Bitmap.h"
#include "EnemyStates.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "MessageManager.h"
#include "Utils.h"



#define NUM_TEST_ENEMIES	0

// Function definitions
void drawScanlines(int linesBetween = 3);
void DrawTarget(Vector2D target);

// Global managers
EntityManager entityManager;

// Main entry point for the application
void DarkGDK ( void )
{
	dbSyncOn   ( );
	dbSyncRate ( FRAMES_PER_SECOND );
	dbSetWindowOff();
	dbSetDisplayMode( SCREEN_WIDTH, SCREEN_HEIGHT, 16 );
	dbDisableEscapeKey ( );
	dbHideMouse();
	dbSetImageColorKey ( 255, 0, 255 );	// Set transparency key for images
	dbDrawSpritesFirst();	// So that we can draw and write over sprites
							// Probably not necessary now since we don't actually use DGDK sprite objects

	dbLoadSound("bullet.wav",1);
	dbLoadSound("explosion.wav",2);
	
	// Load a new map
	Map *map = new Map();
	bool gotmap = map->loadFromFile( "testmap.txt" );
	assert( gotmap && "Loading map failed" );

	// Set up a camera looking at our map
	Camera camera;
	camera.setMap( map );
	camera.setScreenPosition( 10, 10 );
	camera.setSize( 380, 480 );

	// Camera2
	Camera camera2;
	camera2.setMap( map );
	camera2.setScreenPosition( 410, 10 );
	camera2.setSize( 380, 480 );
	camera2.getStateMachine()->changeState( CameraFollowWASDKeysState::getInstance() );

	

	// Set up some enemies
	for( int i=0; i<NUM_TEST_ENEMIES; i++ ) {
		Enemy *enemy = new Enemy();
		enemy->setPosition( Vector2D(rand()%SCREEN_WIDTH,rand()%SCREEN_HEIGHT) );

		// Set up a test path
		Path *path = new Path();
		path->addWaypoint( Vector2D(200.0,200.0) );
		path->addWaypoint( Vector2D(400.0,300.0) );
		path->addWaypoint( Vector2D(700.0,-30.0) );
		path->setLooped(true);
		enemy->setPath( path );

		// Create a new enemy using that path
		enemy->getStateMachine()->changeState( EnemyFollowPathThenDieState::getInstance() );
		//enemy->getStateMachine()->changeState( EnemyCollideWithPlayerState::getInstance() );
		//entityManager.registerEntity( enemy );

		MessageManager::getInstance()->dispatchMessage(0,0,messageCreateEntity,(i+1)*3,enemy);
	}

	dbPerformChecklistControlDevices();
	if( dbChecklistString(1) )
		dbSetControlDevice( dbChecklistString(1) );


	char debugText[100];

	// Set up variables to keep track of elapsed time
	double previousTime = (double)dbTimer();
	double currentTime;
	double elapsedTime;

	// Set up the target
	Vector2D target;
	target.x = 400;
	target.y = 300;

	
	double timeSinceLastSpawn = 10.0;
	double timeBetweenSpawns = 2.0;
	bool spacePressedLastFrame = false;

	Vector2D testPosition(1.0,3.0);
	Vector2D testHeading(1.0,0.0);
	Vector2D testSide = testHeading.Perp();
	Vector2D testPoint(-1.0,4.0);
	Vector2D testVector = TransformFromWorldToLocalSpace(testPoint,testHeading,testSide,testPosition);


	// main loop
	while ( LoopGDK ( ) )
	{
		// Calculate elapsed time
		currentTime = (double)dbTimer();
		elapsedTime = (currentTime - previousTime)/1000;
		previousTime = currentTime;

		MessageManager::getInstance()->update(elapsedTime);

		// Clear the screen white
		dbCLS( RGB( 0, 0, 0 ) );

		camera.update( 0.0 );
		//camera.draw();
		camera2.update( 0.0 );
		//camera2.draw();

		
		// Spawn a new enemy for testing
		
		timeSinceLastSpawn += elapsedTime;
		if( timeSinceLastSpawn > timeBetweenSpawns ) {
			timeSinceLastSpawn = 0.0;
			entityManager.spawnRandomWave();
			/*
			Enemy *enemy = new Enemy(Vector2D(100.0,-10.0));

			// Set up a test path
			Path *path = new Path();
			path->addWaypoint( Vector2D(200.0,200.0) );
			path->addWaypoint( Vector2D(400.0,300.0) );
			path->addWaypoint( Vector2D(700.0,-10.0) );
			path->setLooped(false);
			enemy->setPath( path );
			enemy->getStateMachine()->changeState( EnemyFollowPathThenDieState::getInstance() );
			entityManager.registerEntity( enemy );
			*/
		}
		
		


		// Update and draw the enemies
		entityManager.updateAllEntities( elapsedTime );
		entityManager.drawAllEntities();

		// Reset the first entities position
		if( dbMouseClick() == 2  ) {
			Vector2D position( dbMouseX(), dbMouseY() );
			Vector2D velocity( 0.0, -20.0 );
			//Vector2D velocity = target - position;
			//velocity.Normalize();
			//velocity *= 20.0;
			Bullet *bullet = new Bullet(position,velocity);
			entityManager.registerEntity( bullet );
		}

		// Reset the enemies randomly if space pressed
		if( dbSpaceKey() && spacePressedLastFrame == false ) {
			spacePressedLastFrame = true;
			Enemy *enemy = new Enemy();
			enemy->setPosition(Vector2D(100.0,-30.0));

			// Set up a test path
			Path *path = new Path();
			path->addWaypoint( Vector2D(200.0,200.0) );
			path->addWaypoint( Vector2D(400.0,300.0) );
			path->addWaypoint( Vector2D(700.0,-30.0) );
			path->setLooped(false);
			enemy->setPath( path );
			enemy->getStateMachine()->changeState( EnemyFollowPathThenDieState::getInstance() );

			entityManager.registerEntity( enemy );
		}
		
		if( !dbSpaceKey() )
			spacePressedLastFrame = false;

		// Update the target
		if( dbMouseClick() == 1 ) {
			target.x = dbMouseX();
			target.y = dbMouseY();
		}

		// Draw the target
		//DrawTarget( target );

		// Put any debugging messages here
		//sprintf( debugText, "Key code: %d", dbScanCode() );	// For finding keyboard scan codes
		//sprintf( debugText, "Elapsed time: %f", elapsedTime );
		//sprintf( debugText, "Entities: %d  FPS: %d", entityManager.getSize(), dbScreenFPS() );
		//sprintf( debugText, "%s", dbChecklistString (1) );
		//sprintf( debugText, "JoystickY: %d", joystickY );
		//sprintf( debugText, "FPS: %d", dbScreenFPS() );
		sprintf( debugText, "Score: %d", entityManager.getPlayer()->getScore() );
		//sprintf( debugText, "Player Position: %f,%f", entityManager.getPlayer()->getPosition().x, entityManager.getPlayer()->getPosition().y );
		//sprintf( debugText, "VectorX: %f VectorY: %f", testVector.x, testVector.y );
		//sprintf( debugText, "screenWidth: %d screenHeight: %d", dbScreenWidth(), dbScreenHeight() );

		// Print out the debug text
		dbInk( RGB(0,0,255), RGB(255,255,255) );
		dbText( 0, SCREEN_HEIGHT-20, debugText );

		// Draw scanlines
		//drawScanlines(3);

		// break out if escape has been pressed
		if ( dbEscapeKey ( ) )
			break;

		// update the contents of the screen
		dbSync ( );
	}

	// and now everything is ready to return back to Windows
	return;
}


void drawScanlines(int linesBetween ) {
	int screenHeight = dbScreenHeight();
	int screenWidth = dbScreenWidth();

	dbInk( RGB(0,0,0), RGB(0,0,0) );
	int currentLine = 0;
	while( currentLine < screenHeight ) {
		currentLine += linesBetween;
		dbLine( 0, currentLine, screenWidth, currentLine );
	}
}

void DrawTarget(Vector2D target) {
	int targetSize = 20;
	dbInk( RGB(0,0,255), RGB(0,0,255) );
	dbLine(target.x-20, target.y, target.x+20, target.y);
	dbLine(target.x, target.y-targetSize, target.x, target.y+20 ); 
}


