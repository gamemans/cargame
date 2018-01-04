#include "CBaseGame.h"
#include "CBaseRoom.h"

CBaseGame::CBaseGame()
{

	m_bDestroy = false;
	m_dwRoomId = 0;

	m_bIsCanRejoinGame = true;
}

void CBaseGame::DelRoom(unsigned int dwRoomId )
{
	for( int i = 0; i < m_pRooms.Num(); ++ i )
	{
		if( m_pRooms[i]->GetId() == dwRoomId )
		{
			m_pRooms.Remove( i );
			break;
		}
	}
}
CBaseGame::~CBaseGame()
{

}
