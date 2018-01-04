#include "../Base/CBaseGame.h"
#include "ddzroom.h"


class CDDZGameEx : public CBaseGame
{
public:
	CDDZGameEx(void);
	~CDDZGameEx(void);
public:
	CBaseRoom * AddRoom( char * szName, int iTableNum, int iUserNum );
};
