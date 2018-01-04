#ifndef CBaseGame_H_
#define CBaseGame_H_
#include "CBaselist.h"
#include <map>
using namespace std;
class CBaseGame:public CBaselist
{
	public:
		CBaseGame();
		~CBaseGame();

	public:
		virtual	bool EnterGame(unsigned int uid, unsigned int &index) = 0;
		virtual unsigned int AllocIndex(unsigned int uid) = 0;
		virtual bool LeaveGame(unsigned int uid) = 0;

		bool m_bDestroy;
};

#endif
