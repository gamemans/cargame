/*
 * CTimer.cpp
 *
 *  Created on: Mar 20, 2012
 *      Author: aaaa
 */

#include "CTimer.h"
#include <time.h>
unsigned long GetTickCount()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

   return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}


class CTimerInfo
{
public:
	int				TimerId;
	unsigned long 	ulTime;
	unsigned long	ulBgTime;

	bool			bOnce;

	CTimerInfo()
	{
		bOnce = true;
	}
};

CTimer::CTimer()
{
	m_bActivate = true;
}

CTimer::~CTimer()
{
	m_bActivate = false;
	map<int, CTimerInfo *>::iterator it = m_TimeList.begin();
	for(; it != m_TimeList.end(); it++ )
	{
		delete it->second;
		it->second = NULL;
	}
	m_TimeList.clear();
}
void CTimer::KillTimer(int iTimerId)
{
	if(m_TimeList.find(iTimerId) != m_TimeList.end())
	{
		delete m_TimeList[iTimerId];
		m_TimeList[iTimerId] = NULL;
		m_TimeList.erase(iTimerId);
	}
}

void CTimer::SetTimer(int iTimeId, unsigned long ulElapse, bool bOnce )
{
	if(m_TimeList.find(iTimeId) == m_TimeList.end())
	{
		CTimerInfo * p = new CTimerInfo;
		m_TimeList[iTimeId] = p;
	}

	unsigned long curTime = GetTickCount();
	m_TimeList[iTimeId]->TimerId = iTimeId;
	m_TimeList[iTimeId]->ulTime = ulElapse;
	m_TimeList[iTimeId]->ulBgTime = curTime;
	m_TimeList[iTimeId]->bOnce = bOnce;

//	m_dwElapse = dwElapse;
//	m_bOnce = bOnce;
//	m_dwStartTime = g_Server.GetTickCount();
//	m_bActivate = true;
}

int CTimer::OnTimer()
{
	if( !m_bActivate )
		return -1;

	unsigned long ulNowTime = GetTickCount();
	map<int, CTimerInfo *>::iterator it = m_TimeList.begin();
	for(; it != m_TimeList.end(); it++ )
	{
		if( ulNowTime - it->second->ulBgTime >= it->second->ulTime)
		{
			int timeId = it->first;
			if(it->second->bOnce)
			{
				KillTimer(timeId);
			}
			else
			{
				it->second->ulBgTime = ulNowTime;
			}
			return timeId;
		}
	}

	return -1;
}
