/*
 * ddzroom.h
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#ifndef DDZ_DDZROOM_H_
#define DDZ_DDZROOM_H_

#pragma once

#include "../Base/CBaseRoom.h"
#include "ddztable.h"

class CDDZ_Room:public CBaseRoom
{
public:
	CDDZ_Room(void);
	~CDDZ_Room(void);
public:
	void UpdateAllUserInfo();
	void Init( unsigned int dwId, char * szName, int iTableNum, int iMaxUserNum );

	void NowAllot();
	//void EnterTable( CUser * pUser, unsigned int dwTableId, unsigned int dwChairId );
	/*void UserReady( CUser * pUser );*/
	//void UserChat( CUser * pUser );
	//void LeaveTable( CUser * pUser );

	//void EnterRoom( CUser * pUser );
	void LeaveRoom( unsigned int dwUserId );


	void MatchScore();
	void MatchOut();

//	void SetMatchPeopleNum();

	//定局积分保存前n名
	unsigned int	dwPer12[12];
	unsigned int	dwPer6[6];
};

#endif /* DDZ_DDZROOM_H_ */
