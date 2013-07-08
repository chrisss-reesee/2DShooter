#pragma once
#include "DarkGDK.h"
#include <set>
#include "Telegram.h"

typedef enum {
	messageCreateEntity
};

class MessageManager
{
public:
	~MessageManager(void);

	static MessageManager *getInstance();
	void dispatchMessage(int sender,int receiver, int message, double delay, void *extraInfo);
	void update(double elapsedTime);

private:
	MessageManager() { m_creationTime = (double)dbTimer(); }
	MessageManager(MessageManager&);
	MessageManager& operator=(MessageManager());
	
	std::set<Telegram> m_queue;
	double m_creationTime;
	double m_currentTime;

	void sendMessage(Telegram &telegram);
	void handleSystemMessage(Telegram &telegram);
};
