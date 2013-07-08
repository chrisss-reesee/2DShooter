#pragma once

#include "State.h"

class Camera;

class CameraGlobalState : public State<Camera>
{
private:
	CameraGlobalState() {}									// This is a singleton, so constructor is private
	CameraGlobalState(const CameraGlobalState&);					// as is the copy constructor
	CameraGlobalState& operator=(const CameraGlobalState&);		// and assignment operator

public:
	static CameraGlobalState *getInstance();
	virtual void Enter(Camera *camera);
	virtual void Execute(Camera *camera);
	virtual void Exit(Camera *camera);
};


class CameraFollowArrowKeysState : public State<Camera>
{
private:
	CameraFollowArrowKeysState() {}									// This is a singleton, so constructor is private
	CameraFollowArrowKeysState(const CameraFollowArrowKeysState&);					// as is the copy constructor
	CameraFollowArrowKeysState& operator=(const CameraFollowArrowKeysState&);		// and assignment operator

public:
	static CameraFollowArrowKeysState *getInstance();
	virtual void Enter(Camera *camera);
	virtual void Execute(Camera *camera);
	virtual void Exit(Camera *camera);
};


class CameraFollowWASDKeysState : public State<Camera>
{
private:
	CameraFollowWASDKeysState() {}									// This is a singleton, so constructor is private
	CameraFollowWASDKeysState(const CameraFollowWASDKeysState&);					// as is the copy constructor
	CameraFollowWASDKeysState& operator=(const CameraFollowWASDKeysState&);		// and assignment operator

public:
	static CameraFollowWASDKeysState *getInstance();
	virtual void Enter(Camera *camera);
	virtual void Execute(Camera *camera);
	virtual void Exit(Camera *camera);
};