#include "CBase.h"
/**
   * 时间处理
    */
#include <time.h>
#include "CTimer.h"
unsigned long long GetTickCountEx() {
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return ((unsigned long long) ts.tv_sec * 1000
			+ (unsigned long long) ts.tv_nsec / 1000000);
}
CBase::CBase()
{
	m_pTimer = new CTimer();
}
CBase::~CBase()
{
	delete m_pTimer;
	m_pTimer = 0;
}


unsigned int CBase::GetId()
{
	return m_nId;
}


void CBase::SetId(unsigned int id)
{
	m_nId = id;
}

int CBase::GetTimerId()
{
	return m_pTimer->OnTimer();
}
void CBase::OnTimer(int iTimerID) {

}
void CBase::SetTimer(int iTimeId, unsigned int ulElapse, bool bOnce) {
	m_pTimer->SetTimer(iTimeId, ulElapse, bOnce);
}
void CBase::KillTimer(int iTimeId) {
	m_pTimer->KillTimer(iTimeId);
}
