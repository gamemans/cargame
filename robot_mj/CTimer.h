/*
 * CTimer.h
 *
 *  Created on: Mar 20, 2012
 *      Author: aaaa
 */

#ifndef CTIMER_H_
#define CTIMER_H_
#include <map>
using namespace std;
class CTimerInfo;
class CTimer {
public:
	CTimer();
	virtual ~CTimer();


protected:

	unsigned long	m_dwStartTime;
	unsigned long	m_dwElapse;


	bool			m_bOnce;
	bool			m_bActivate;

public:

	void SetTimer(int iTimeId, unsigned long dwElapse, bool bOnce = true );

	void KillTimer(int iTimerId);

	int OnTimer();

	unsigned int GetStartTime(){ return m_dwStartTime; }

	map<int ,CTimerInfo *> m_TimeList;
};

#endif /* CTIMER_H_ */
