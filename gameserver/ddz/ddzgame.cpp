/*
 * ddzgame.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#include "ddzgame.h"
#include "../Base/CBaseGame.h"
CDDZGameEx::CDDZGameEx() {
	// TODO Auto-generated constructor stub
	m_dwId = GAME_DDZ;

		SetGameType( GAME_TYPE_PK );
		SetGameDir( "ddz" );
		SetGameName( "斗地主" );

		for( int i = 0; i < 54; i++ )
		{
			g_DDZPaiInfo[i].id	= i / 4 + 13 * ( i % 4 );
			g_DDZPaiInfo[i].num	= i / 4 + 1;

			g_DDZPaiInfo[i].type = i % 4;


			if( g_DDZPaiInfo[i].num > 2 && g_DDZPaiInfo[i].num < 14 )
			{
				g_DDZPaiInfo[i].value = g_DDZPaiInfo[i].num - 3;
			}
			else if( g_DDZPaiInfo[i].num == 1 )
			{
				g_DDZPaiInfo[i].value = g_DDZPaiInfo[i].num + 10;
			}
			else if( g_DDZPaiInfo[i].num == 2 )
			{
				g_DDZPaiInfo[i].value = g_DDZPaiInfo[i].num + 20;
			}

			if( i>= 52 )
			{
				g_DDZPaiInfo[i].type = 4;
				g_DDZPaiInfo[52].value = 33;
				g_DDZPaiInfo[52].id = 52;
				g_DDZPaiInfo[53].value = 34;
				g_DDZPaiInfo[53].id = 53;
			}

		}
}

CDDZGameEx::~CDDZGameEx() {
	// TODO Auto-generated destructor stub
}
CBaseRoom * CDDZGameEx::AddRoom( char * szName, int iTableNum, int iUserNum )
{
	CBaseRoom * p = new CDDZ_Room();
	p->Init( m_dwRoomId, szName, iTableNum, iUserNum );
	p->SetGameId( m_dwId );
	p->SetMinWaitUserNum( 3 );
	m_pRooms.AddItem( p );
	m_dwRoomId++;
	return p;

}
