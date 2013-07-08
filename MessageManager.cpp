#include "MessageManager.h"
#include "EntityManager.h"
#include "BaseGameEntity.h"
#include "Telegram.h"

extern EntityManager entityManager;

MessageManager *MessageManager::getInstance()
{
	static MessageManager instance;
	return &instance;
}

MessageManager::~MessageManager(void)
{
}

void MessageManager::update(double elapsedTime) {
	while( (m_queue.begin()!=m_queue.end()) && (m_queue.begin()->getDelay() <= 0.0) ) {
		sendMessage( (*m_queue.begin()) );
		m_queue.erase(m_queue.begin());
	}
	for( std::set<Telegram>::iterator iterator = m_queue.begin(); iterator!=m_queue.end(); iterator++ ) {
		iterator->setDelay( iterator->getDelay() - elapsedTime );
	}
}

void MessageManager::dispatchMessage(int sender,int receiver, int message, double delay, void *extraInfo)
{
	Telegram telegram(sender, receiver, message, delay, extraInfo);

	if( delay == 0.0 )
		sendMessage(telegram);
	else
		m_queue.insert(telegram);
}

void MessageManager::sendMessage(Telegram &telegram) {
	if( telegram.getReceiver() == 0 ) {
		handleSystemMessage( telegram );
	}/*
	else {
		BaseGameEntity *receiver = entityManager.getEntityFromID(telegram.getReceiver());
		bool messageWasHandled = false;
		if( receiver )
			messageWasHandled = receiver->handleMessage(telegram);
	}*/
}


void MessageManager::handleSystemMessage(Telegram &telegram)
{
	if( telegram.getMessage() == messageCreateEntity ) {
		entityManager.registerEntity( (BaseGameEntity *)telegram.getExtraInfo() );
	}
}