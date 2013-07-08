#pragma once

#include "State.h"

class Camera;

class ExampleState : public State<Camera>
{
private:
	ExampleState() {}									// This is a singleton, so constructor is private
	ExampleState(const ExampleState&);					// as is the copy constructor
	ExampleState& operator=(const ExampleState&);		// and assignment operator

public:
	static ExampleState *getInstance();
	virtual void Enter(Camera *camera);
	virtual void Execute(Camera *camera);
	virtual void Exit(Camera *camera);
};