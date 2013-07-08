#include "StateExamples.h"
#include "Camera.h"

// Methods for ExampleState ////////////////////////
ExampleState *ExampleState::getInstance() {
	static ExampleState instance;
	return &instance;
}

void ExampleState::Enter(Camera *camera) {
	
}

void ExampleState::Execute(Camera *camera) {

}

void ExampleState::Exit(Camera *camera) {

}
////////////////////////////////////////////////////