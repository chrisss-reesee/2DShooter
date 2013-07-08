#include "Telegram.h"
#include "math.h"

Telegram::Telegram(int sender, int receiver, int message, double delay, void *extraInfo)
{
	m_sender = sender;
	m_receiver = receiver;
	m_message = message;
	m_delay = delay;
	m_extraInfo = extraInfo;
}

Telegram::~Telegram(void)
{
}

bool Telegram::operator==(Telegram &t1) const
{
	if( m_sender != t1.getSender() )
		return false;
	else if( m_receiver != t1.getReceiver() )
		return false;
	else if( m_message != t1.getMessage() )
		return false;
	else if( fabs(m_delay-t1.getDelay()) > MINIMUM_DELAY_DIFFERENCE ) {
		return false;
	}
	else
		return true;
}

bool Telegram::operator<(const Telegram &t1) const
{
	if ( m_delay < t1.m_delay )
		return true;
	else
		return false;
}
