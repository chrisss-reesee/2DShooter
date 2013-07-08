#pragma once

#define MINIMUM_DELAY_DIFFERENCE 0.000001

class Telegram
{
public:
	Telegram(int sender, int receiver, int message, double delay, void *extraInfo);
	~Telegram(void);
	bool operator==(Telegram& t1) const;
	bool operator<(const Telegram &t1) const;
	double m_delay;


	int getSender() { return m_sender; }
	int getReceiver() { return m_receiver; }
	int getMessage() { return m_message; }
	void setDelay(double delay) { m_delay = delay; }
	double getDelay() { return m_delay; }
	void *getExtraInfo() { return m_extraInfo; }


private:
	int m_sender;
	int m_receiver;
	int m_message;
	void *m_extraInfo;
};
