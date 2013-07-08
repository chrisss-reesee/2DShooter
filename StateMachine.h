#pragma once

#include "State.h"

// NOTE All template class methods must be defined in the header
// see this page: http://www.parashift.com/c%2B%2B-faq-lite/templates-defn-vs-decl.html

template <class entity_type>
class StateMachine
{
public:
	
	StateMachine( entity_type *owner ) {
		m_owner = owner;
		m_currentState = NULL;
		m_previousState = NULL;
		m_globalState = NULL;
	}

	~StateMachine(void) {}

	void update() {
		if( m_globalState )
			m_globalState->Execute( m_owner );
		if( m_currentState )
			m_currentState->Execute( m_owner );
	}

	void changeState( State<entity_type> *newState ) {

		// Record previous state
		if( m_currentState ) {
			m_previousState = m_currentState;
			m_currentState->Exit( m_owner );
		}
		m_currentState = newState;
		m_currentState->Enter( m_owner );
	}

	void revertToPreviousState() {
		changeState( m_previousState );
	}

	bool isInState( State<entity_type> &state ) {
		return typeid(*m_pCurrentState) == typeid(state);
	}

	// Getters
	State<entity_type> *getCurrentState() { return m_currentState; }
	State<entity_type> *getPreviousState() { return m_previousState; }
	State<entity_type> *getGlobalState() { return m_globalState; }

	// Setters should only be used at initialization
	void setCurrentState( State<entity_type> *newState ) { m_currentState = newState; }
	void setPreviousState( State<entity_type> *newState ) { m_previousState = newState; }
	void setGlobalState( State<entity_type> *newState ) { m_globalState = newState; }

private:
	entity_type *m_owner;
	State<entity_type> *m_currentState;
	State<entity_type> *m_previousState;
	State<entity_type> *m_globalState;
};
