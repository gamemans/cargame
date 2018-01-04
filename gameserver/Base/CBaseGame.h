#ifndef CBaseGame_H_
#define CBaseGame_H_
#include "CBaselist.h"
#include "Array.h"
#include <map>



using namespace std;


class CBaseRoom;

class CBaseGame:public CBaselist
{
	public:
		CBaseGame();
		~CBaseGame();

	public:
		virtual	bool EnterGame(unsigned int uid, unsigned int &index) = 0;
		virtual unsigned int AllocIndex(unsigned int uid) = 0;
		virtual bool LeaveGame(unsigned int uid) = 0;

		virtual bool Net_Ready(unsigned int uid) = 0;


		bool m_bDestroy;

		virtual bool ProHostMsgByStream(unsigned int uid, unsigned char * data, unsigned int len) = 0;

		Array<CBaseRoom *>			m_pRooms;

	protected:

		unsigned int					m_dwId;

		unsigned int					m_dwRoomId;

		char					m_szGameDir[20];
		char					m_szGameName[20];

		bool					m_bIsCanRejoinGame;

		int					m_wGameType;

	public:

		void HornOfChat( void * data, unsigned int size );

		virtual CBaseRoom * AddRoom( char * szName, int iTableNum, int iUserNum ){return NULL;}

		void DelRoom( unsigned int dwRoomId );

		unsigned int GetId(){ return m_dwId; }
		int  GetGameType( ){ return m_wGameType;}
		int GetRoomNum(){ return m_pRooms.Num(); }
		CBaseRoom * GetRoom( unsigned int dwId )
		{
			if( (int)dwId < m_pRooms.Num() && (int)dwId >= 0 )
				return m_pRooms[dwId];
			else
				return NULL;
		}

		void SetGameType( int type )
		{
			m_wGameType = type;
		}
		void SetGameDir( char * pDir )
		{
			strcpy( m_szGameDir, pDir );
		}
		void SetGameName( char * pName )
		{
			strcpy( m_szGameName, pName );
		}
		char * GetGameDir()
		{
			return m_szGameDir;
		}
		char * GetGameName()
		{
			return m_szGameName;
		}

		bool IsCanRejoinGame(){ return m_bIsCanRejoinGame; }
		void SetCanRejoinGame( bool bCan ){ m_bIsCanRejoinGame = bCan; }
};

#endif
