#ifndef CBase_H_
#define CBase_H_
#include "CTimer.h"
#include <map>
using namespace std;



class CBase
{
	public:
		CBase();
		virtual	~CBase();

	public:
		virtual	unsigned int GetId();
		virtual	void SetId(unsigned int);
	protected:

		unsigned int m_nId;

		CTimer * m_pTimer;

	public:
		 int GetTimerId();

		virtual void OnTimer(int nTimerID);
		void SetTimer(int nTimeId, unsigned int ulElapse, bool bOnce);
		void KillTimer(int nTimeId); 
};

extern unsigned long long GetTickCountEx();
#endif
