#pragma once

template <class entity_type>
class State
{
public:
	virtual ~State() {}		// Destructor is virtual that the subclass's specific destructor will be called when it is destroyed

	virtual void Enter( entity_type * ) = 0;
	virtual void Execute( entity_type * ) = 0;
	virtual void Exit( entity_type * ) = 0;
};
