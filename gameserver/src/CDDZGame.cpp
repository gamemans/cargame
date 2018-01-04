/*
 * CDDZGame.cpp
 *
 *  Created on: 2017年4月11日
 *      Author: aaaa
 */

#include "CDDZGame.h"

#include "CUser.h"

CDDZGame::CDDZGame() {
	// TODO Auto-generated constructor stub

}

CDDZGame::~CDDZGame() {
	// TODO Auto-generated destructor stub
}

bool CDDZGame::ProHostMsgByStream(unsigned int uid, unsigned char * data, unsigned int len)
{


	return false;
}
bool CDDZGame::Net_Ready(unsigned int uid)
{

	return false;
}
void CDDZGame::ChuPai(CPlayer *pUser, int pai[], int len)
{

}

void CDDZGame::PassPai(CPlayer *pUser)
{

}

void CDDZGame::JiaoPai(CPlayer *pUser, int num)
{

}






SDDZPai g_DDZPaiInfo[54];
SDDZPai * GetDDZPaiInfo( int wId )
{
	for( int i = 0; i < 54; i++ )
	{
		if( g_DDZPaiInfo[i].id == wId )
			return &g_DDZPaiInfo[i];
	}
	return NULL;
}
