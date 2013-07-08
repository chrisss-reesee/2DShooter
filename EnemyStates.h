#pragma once

#include "State.h"

class Enemy;

class EnemyGlobalState : public State<Enemy>
{
private:
	EnemyGlobalState() {}									// This is a singleton, so constructor is private
	EnemyGlobalState(const EnemyGlobalState&);					// as is the copy constructor
	EnemyGlobalState& operator=(const EnemyGlobalState&);		// and assignment operator

public:
	static EnemyGlobalState *getInstance();
	virtual void Enter(Enemy *enemy);
	virtual void Execute(Enemy *enemy);
	virtual void Exit(Enemy *enemy);
};

class EnemyFollowPathThenDieState : public State<Enemy>
{
private:
	EnemyFollowPathThenDieState() {}									// This is a singleton, so constructor is private
	EnemyFollowPathThenDieState(const EnemyFollowPathThenDieState&);					// as is the copy constructor
	EnemyFollowPathThenDieState& operator=(const EnemyFollowPathThenDieState&);		// and assignment operator

public:
	static EnemyFollowPathThenDieState *getInstance();
	virtual void Enter(Enemy *enemy);
	virtual void Execute(Enemy *enemy);
	virtual void Exit(Enemy *enemy);
};

class EnemyCollideWithPlayerState : public State<Enemy>
{
private:
	EnemyCollideWithPlayerState() {}									// This is a singleton, so constructor is private
	EnemyCollideWithPlayerState(const EnemyCollideWithPlayerState&);					// as is the copy constructor
	EnemyCollideWithPlayerState& operator=(const EnemyCollideWithPlayerState&);		// and assignment operator

public:
	static EnemyCollideWithPlayerState *getInstance();
	virtual void Enter(Enemy *enemy);
	virtual void Execute(Enemy *enemy);
	virtual void Exit(Enemy *enemy);
};