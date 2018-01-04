#ifndef CPlayer_H_
#define CPlayer_H_
#include "RakNetTypes.h"
#include "CBaseUser.h"
class CPlayer:public CBaseUser
{
	public:
		CPlayer();
		~CPlayer();


		void Reset();
	public:
		unsigned int	m_nChairId;
		bool			m_bReady;

		unsigned int	m_nGameId;///<在哪个游戏内,主机内

		RakNet::RakNetGUID m_Guid;

		unsigned int	m_nProxyServerId;


		bool			m_bDisconnect;

};

#endif
