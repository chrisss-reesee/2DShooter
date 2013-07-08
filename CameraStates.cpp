#include "DarkGDK.h"
#include "CameraStates.h"
#include "Camera.h"

// The global state does nothing at present
// Methods for CameraGlobalState ////////////////////////
CameraGlobalState *CameraGlobalState::getInstance() {
	static CameraGlobalState instance;
	return &instance;
}

void CameraGlobalState::Enter(Camera *camera) {
	
}

void CameraGlobalState::Execute(Camera *camera) {

}

void CameraGlobalState::Exit(Camera *camera) {

}
////////////////////////////////////////////////////


// This state makes the camera move around with the arrow keys
// Methods for CameraFollowArrowKeysState ////////////////////////
CameraFollowArrowKeysState *CameraFollowArrowKeysState::getInstance() {
	static CameraFollowArrowKeysState instance;
	return &instance;
}

void CameraFollowArrowKeysState::Enter(Camera *camera) {
	
}

void CameraFollowArrowKeysState::Execute(Camera *camera) {
	if( dbUpKey() ) {
		camera->setPosition( camera->getX(), camera->getY() - 5.0 );
	}
	if( dbDownKey() ) {
		camera->setPosition( camera->getX(), camera->getY() + 5.0 );
	}
	if( dbLeftKey() ) {
		camera->setPosition( camera->getX() - 5.0, camera->getY() );
	} 
	if( dbRightKey() ) {
		camera->setPosition( camera->getX() + 5.0, camera->getY() );
	}
}

void CameraFollowArrowKeysState::Exit(Camera *camera) {

}
////////////////////////////////////////////////////



// This state makes the camera move around with the arrow keys
// Methods for CameraFollowArrowKeysState ////////////////////////
CameraFollowWASDKeysState *CameraFollowWASDKeysState::getInstance() {
	static CameraFollowWASDKeysState instance;
	return &instance;
}

void CameraFollowWASDKeysState::Enter(Camera *camera) {
	
}

void CameraFollowWASDKeysState::Execute(Camera *camera) {
	if( dbKeyState(17) ) {
		camera->setPosition( camera->getX(), camera->getY() - 5.0 );
	}
	if( dbKeyState(31) ) {
		camera->setPosition( camera->getX(), camera->getY() + 5.0 );
	}
	if( dbKeyState(30) ) {
		camera->setPosition( camera->getX() - 5.0, camera->getY() );
	} 
	if( dbKeyState(32) ) {
		camera->setPosition( camera->getX() + 5.0, camera->getY() );
	}
}

void CameraFollowWASDKeysState::Exit(Camera *camera) {

}
////////////////////////////////////////////////////