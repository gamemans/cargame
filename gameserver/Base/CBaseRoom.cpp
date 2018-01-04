/*
 * CBaseRoom.cpp
 *
 *  Created on: 2017年4月9日
 *      Author: aaaa
 */

#include "CBaseRoom.h"


//#include "stdafx.h"
#include "CBaseRoom.h"
//#include "socketapp.h"
//#include "log.h"
//#include "servermanager.h"
//#include "inifileloader.h"

#include "commdefine.h"
#include "errordefine.h"
CBaseRoom::CBaseRoom()
{
	m_iCurUserNum = 0;

	m_fTax = 0;

	m_bCanEnterTable = true;

	m_iMinWaitUserNum = 4;
	m_iMaxWaitUserNum = 12;

	m_iCurMatchCount = 0;
	m_iCurMatchState = 0;

	m_dwAllotTableId = 0;

	m_bAllotTableLocked = false;

	m_iBoutOfScore = 3;


	//m_iMatchPeopleNum = 0;//参加比赛的人数
	m_iLunNum = 0;
	m_iLoopMatch = 0;

	//////////////add by mx 2009.7.30
	m_bEnterGameMode = false;
	m_wLevelType = LEVEL_TYPE_SCORE;//默认为积分模式
	///////////////////////////////////

	m_bMatchStart = false;
	m_iMatchTimeType = -1;

	m_iCurMatchPeopleNum = 60;

	//add by mx 2009.9.15 邀请、旁观的开关功能
	m_bCanInvite = true;				//默认能邀请
	m_bCanLookAt = true;					//默认能旁观
	m_bCanNoWelCome = true;
	m_bCanPleaseLeave = true;


	m_iAddScore[0] = 0;
	m_iAddScore[1] = 200;
	m_iAddScore[2] = 400;
	m_iAddScore[3] = 600;
	m_iAddScore[4] = 900;
	m_iAddScore[5] = 1300;
	m_iAddScore[6] = 1800;
	m_iAddScore[7] = 2400;
	m_iAddScore[8] = 3100;

	m_iMatchMoney = 0;				//金币
	m_iMatchLeDou = 0;				//乐豆
	m_iMatchRose = 0;				//玫瑰
	m_iMatchHonor = 0;				//勋章
	m_iMatchCharm = -999999;				//魅力

}

CBaseRoom::~CBaseRoom()
{
	for(vector<CDateTimeEx *>::iterator it= m_MatchTimeList.begin(); it!= m_MatchTimeList.end(); it++)
	{
		delete( *it );
		*it = NULL;
	}
	m_MatchTimeList.clear();
}

void CBaseRoom::SetCanEnterTable( bool bCan )
{
	m_bCanEnterTable = bCan;
	if( !bCan )
	{
		if( m_iScoreType == SCORE_MATCH )
			SetTimer( MATCH_TIME_COUNT ,MATCH_TIME_ID, false );
		else
			SetTimer( MAX_WAIT_TABLE_TIME * 1000,WAIT_ALLOT_ID, false );
	}
	else
		KillTimer();
}

void CBaseRoom::Init( unsigned int dwId, char * szName, int iTableNum, int iMaxUserNum )
{
	m_dwId = dwId;
	strcpy( m_szName, szName );
	m_iMaxUserNum = iMaxUserNum;
	m_pUserList = new CUserHash();

	m_pAllotTables = new CTableHash();

	m_pMemberList = new CMemberHash();

	m_pTeamList = new CTeamHash();
}

void CBaseRoom::Release()
{
//	CUser * pp;
//	for( POS pos = m_pUserList->GetFirstPos(); pos; )
//	{
//		pp = m_pUserList->GetNext( pos );
//		//delete pp;
//		SAFE_DELETE( pp );
//	}
//	//delete m_pUserList;
//	SAFE_DELETE( m_pUserList );
//
//
//
//	CBaseTable * pTable;
//	for( POS pos = m_pAllotTables->GetFirstPos(); pos; )
//	{
//		pTable = m_pAllotTables->GetNext( pos );
//		//delete pTable;
//		SAFE_DELETE( pTable );
//	}
//	//delete m_pAllotTables;
//	SAFE_DELETE( m_pAllotTables );
//
//
//	SMemberInfo * pMember;
//	for( POS pos = m_pMemberList->GetFirstPos(); pos; )
//	{
//		pMember = m_pMemberList->GetNext( pos );
//
//		SAFE_DELETE( pMember );
//	}
//	SAFE_DELETE( m_pMemberList );
//
//	STeamInfo * pTeam;
//	for( POS pos = m_pTeamList->GetFirstPos(); pos; )
//	{
//		pTeam = m_pTeamList->GetNext( pos );
//		if(!pTeam)
//			continue;
//		SAFE_DELETE( pTeam );
//	}
//	SAFE_DELETE( m_pTeamList );
//
//
//
//	for( int i = 0; i < m_pTables.Num(); i++ )
//		//delete m_pTables[i];
//		SAFE_DELETE( m_pTables[i] );
}

int CBaseRoom::CanEnter( long long lMoney, long long lHappyBean )
{
	if( m_iScoreType == SCORE_BEAN )
	{
		if( lHappyBean < m_iMinScore )
			return ERR_ENTERROOM_NOTENOUGHBEAN;
		else
			return ERR_ENTERROOM_ACCEPT;
	}
	else if( m_iScoreType == SCORE_GOLD )
	{
		if( lMoney < m_iMinScore )
			return ERR_ENTERROOM_NOTENOUGHMONEY;
		else
			return ERR_ENTERROOM_ACCEPT;
	}
	else if( m_iScoreType == SCORE_MATCH )//wm match
	{
		if( lMoney < m_iMinScore )
			return ERR_ENTERROOM_NOTENOUGHMONEY;
		else
			return ERR_ENTERROOM_ACCEPT;
	}
	//end
	return -1;
}


void CBaseRoom::EnterRoom( CUser * pUser )
{
//	if( m_bCanSeeOtherUser )
//	{
//		PT_USER_ENTER_ROOM_INFO data;
//		data.info.dwUserId = pUser->m_dwUserId;
//		data.info.dwWin = pUser->m_iWin;
//		data.info.dwLost = pUser->m_iLost;
//		data.info.dwDogfall = pUser->m_iDogfall;
//		data.info.dwDisconnect = pUser->m_iDisconnect;
//		data.info.dwEscape = pUser->m_iEscape;
//		data.info.iScore = pUser->m_iScore;
//		data.info.dwHeadId = pUser->m_dwHeadId;
//		data.info.iState = pUser->m_iState;
//		data.info.bVIP = pUser->m_bVIP;
//		_tcscpy( data.info.szName, pUser->m_szUserName );
//
//		data.info.dwHonor = pUser->m_dwHonor;
//		data.info.bSex = pUser->m_bSex;
//		data.info.iCharm = pUser->m_iCharm;
//		data.info.lHappyBean = pUser->m_lHappyBean;
//		data.info.lMoney = pUser->m_lMoney;
//		data.info.dwHeadId = pUser->m_dwHeadId;
//		data.info.dwNumericAccount = pUser->m_dwNumericAccount;
//		data.info.dwFlower = pUser->m_dwFlower;
//		data.info.dwCountLoginTime = pUser->m_dwCountLoginTime;
//		data.info.dwPropHornBigNum = pUser->m_dwPropHornBigNum;
//		//	_tcscpy( data.info.szAccount, pUser->m_szAccount );
//		//	_tcscpy( data.info.szAnswer, pUser->m_szAnswer );
//		//	_tcscpy( data.info.szCity, pUser->m_szCity);
//		//	_tcscpy( data.info.szEmail, pUser->m_szEmail );
//		//	_tcscpy( data.info.szIDCard, pUser->m_szIDCard );
//		//	_tcscpy( data.info.szLove, pUser->m_szLove );
//		//	_tcscpy( data.info.szNominatePeople, pUser->m_szNominatePeople );
//		//	_tcscpy( data.info.szQuestion, pUser->m_szQuestion );
//
//		//	_tcscpy( data.info.szPerSigned, pUser->m_szPerSigned );
//
//		_tcscpy( data.info.szHeadImgName, pUser->m_szHeadImgName );//wz add upload
//
//		//add by mx 2009.9.24
//		data.info.bVidicon = pUser->m_bVidicon;
//		data.info.iRealSex = pUser->m_iRealSex;
//		data.info.bSuperCharm = pUser->m_bSuperCharm;
//
//		//将用户信息发给所有人
//		SendToAllUser( &data, sizeof(data) );
//
//		//将所有人信息发给用户
//		SendAllUserInfoToOne( pUser );
//	}

}

void CBaseRoom::LeaveRoom( unsigned int dwUserId )
{
	CUser * pUser = GetUser( dwUserId );
	if( !pUser )
	{
//		_ftprintf( g_ErrLog.m_pFile, L"LeaveRoom:未找到用户:%d\n", dwUserId );
		return;
	}

	if( pUser->m_bMatch )
	{
		pUser->m_bDrop = true;
		return;
	}

	//RemovePlayerFromMatch( pUser->m_dwUserId );
	//if( GetScoreType() == SCORE_MATCH && GetMatchState() != MATCH_STATE_END_MATCH && GetMatchState() != MATCH_STATE_IN_MATCH )
	if( pUser->m_bExitMatch )
	{
		ExitMatch( pUser );
		RemoveSignUpUser( pUser->m_dwUserId );
	}


	if( !m_bCanEnterTable && m_iScoreType != SCORE_MATCH  )
	{
		if( pUser->m_iState >= US_INTABLE )
			LeaveTable( pUser );
		else
			RemovePalyUser( pUser );//删除金币区随即等待用户
	}
	else
	{
		if( pUser->m_iState >= US_INTABLE )
			LeaveTable( pUser );
	}

	//PT_GAMESTATE_RESET_INFO data;
	//data.dwUserId = dwUserId;
	//data.iState = US_FREE;
	//g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex, &data, sizeof(data) );

	RemoveUser( pUser );


}

void CBaseRoom::KickOut( unsigned int dwUserId, int iError )
{
	CUser * pUser = GetUser( dwUserId );
	if( !pUser )
		return;

//	PT_FORCE_LEAVE_ROOM_INFO data;
//	data.iError = iError;
//	data.dwUserId = dwUserId;
//	g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex, &data, sizeof(data) );


}


void CBaseRoom::SendToAllUser( void * data, unsigned int size, CUser * pExcept )
{

}

void CBaseRoom::SendToUser( void * data, unsigned int size, CUser * pOnly )
{
//	PT_PACKED_MSG_INFO * msg[AGENT_SERVER_NUM];
//
//	for( int i = 0; i < AGENT_SERVER_NUM; ++ i )
//	{
//		msg[i] = &g_ServerApp.m_PackedMsgInfo[i];
//		msg[i]->SetMsg( (char *)data, size );
//	}
//
//	//for( POS pos = m_pUserList->GetFirstPos();pos; )
//	//{
//	//	CUser * pUser = m_pUserList->GetNext( pos );
//	//	if( pUser == pOnly )
//	//	{
//	for( int j = 0; j < AGENT_SERVER_NUM; ++ j )
//	{
//		if( pOnly->m_dwAgentIndex == g_pServerManager->m_ServerList[j].dwConnectIndex )
//		{
//			msg[j]->AddUser( pOnly->m_dwUserId );
//			break;
//		}
//	}
//	//		break;
//	//	}
//	//}
//
//	for( int i = 0; i < AGENT_SERVER_NUM; ++ i )
//	{
//		if( msg[i]->wUserNum == 0 )
//		{
//			msg[i]->ResetMsg();
//			continue;
//		}
//		g_ServerApp.SendToAgentServer( g_pServerManager->m_ServerList[i].dwConnectIndex, msg[i], msg[i]->GetSize() );
//		msg[i]->ResetMsg();
//	}
}

void CBaseRoom::ChatToAllUser( void * data, unsigned int size )
{

}


void CBaseRoom::SendAllMemberInfoToOne( SMemberInfo * pMember )
{

}

void CBaseRoom::SendAllUserInfoToOne( CUser * pUser )
{

}

void CBaseRoom::EnterTable( CUser * pUser, unsigned int dwTableId, unsigned int dwChairId,bool bCheckPass, char *p )
{

}

void CBaseRoom::CheckAllot()
{


}






void CBaseRoom::LeaveTable( CUser * pUser )
{
	if( !pUser )
		return;

}

//////////强退时的处理策略（米欣） Begin
void CBaseRoom::ForceLeaveTable( CUser * pUser ,float iPunishNum )
{


}
//////////强退时的处理策略（米欣） End
void CBaseRoom::UserReady( CUser * pUser )
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////
/////////

void  CBaseRoom::InsertWaitUser( CUser * pUser )
{

}



void  CBaseRoom::RemovePalyUser( CUser * pUser )
{

}

void CBaseRoom::SendToAllWaitUser( void * data, unsigned int size )
{

}
//==
int CBaseRoom::GetWaitTableTime()
{

}

//立即分配座位
void CBaseRoom::NowAllot()
{
	//int Count = m_pWaitGameUserList.GetCount();
	//if( Count > 12 )
	//	Count = 12;

	//m_bSendWaitMsg = true ;
	//KillTimer();
	//int TableID = FindNullTable();
	////if( TableID < 0)
	////{
	////	///桌子已满，返回信息提示提示用户
	////	PT_ENTER_TABLE_ALLOT_ERR_INFO info;
	////	info.bIsFull = true;
	////	SendToUser( &info, sizeof(info) ,user ); ///发送给用户分配信息
	////	return ;
	////}
	//CBaseTable * pTable = GetTable( TableID );
	//int UserCount = pTable->m_iUserNum;

	//int j=0;
	//for( int i = 0 ; i < UserCount ; i++ )
	//{

	//	Count = m_pWaitGameUserList.GetCount();

	//	j = rand()%Count;
	//	CUser *user = m_pWaitGameUserList.GetAt(j);
	//	user->m_iTableId = TableID ;
	//	user->m_iChairId = i ;
	//	PT_ENTER_TABLE_ALLOT_INFO  info;
	//	info.dwUserId = user->m_dwUserId;
	//	info.dwTableId = TableID;
	//	info.dwChairId = i;
	//	if( TableID < 0 )
	//		info.bIsFull = true ;
	//	else
	//		info.bIsFull = false ;
	//	g_ServerApp.SendToAgentServer( user->m_dwAgentIndex ,&info,sizeof(info) );

	//	pTable->m_pUsers[i] = user;
	//	user->m_iState = US_INTABLE;


	//	RemovePalyUser(user);
	//}

	//for( int i = 0 ; i < pTable->m_iUserNum; i++ )
	//{
	//	CUser *user = pTable->m_pUsers[i];
	//	PT_USER_ENTER_ROOM_INFO info;
	//	info.info.bSex = user->m_bSex ;
	//	info.info.bVIP =user->m_bVIP;
	//	info.info.dwCountGameTime = user->m_dwCountGameTime ;
	//	info.info.dwDisconnect = user->m_iDisconnect;
	//	info.info.dwDogfall = user->m_iDogfall;
	//	info.info.dwEscape = user->m_iEscape;
	//	info.info.dwFlower = user->m_dwFlower;
	//	info.info.lHappyBean = user->m_lHappyBean;
	//	info.info.dwHeadId = user->m_dwHeadId;
	//	//info.info.dwLookAt = user->m_dwLookAt;
	//	info.info.dwLost = user->m_iLost ;
	//	info.info.lMoney = user->m_lMoney;
	//	info.info.dwNumericAccount = user->m_dwNumericAccount;
	//	info.info.dwPropFlowerNum = user->m_dwPropFlowerNum;
	//	info.info.dwPropHornBigNum = user->m_dwPropHornBigNum;
	//	info.info.dwPropVipBigNum = user->m_dwPropVipBigNum ;
	//	info.info.dwPropVipNum = user->m_dwPropVipNum;
	//	info.info.dwPropVipSupperNum = user->m_dwPropVipSupperNum;
	//	info.info.dwUserId = user->m_dwUserId;
	//	info.info.dwWin = user->m_iWin;
	//	info.info.iChairId = user->m_iChairId;
	//	info.info.iCharm = user->m_iCharm;
	//	info.info.iScore = user->m_iScore;
	//	info.info.iState = user->m_iState;
	//	info.info.iTableId = user->m_iTableId;
	//	_tcscpy( info.info.szName, user->m_szUserName );
	//	info.info.wSubsidyNum = user->m_wSubsidyNum;


	//	pTable->SendToAllUser( &info, sizeof(info) ,user );
	//}

	///*for( int i = 0 ; i < pTable->m_iUserNum; i++ )
	//{
	//	CUser *user = pTable->m_pUsers[i];
	//	PT_ENTER_TABLE_ALLOT_INFO  info;
	//	info.dwUserId = user->m_dwUserId;
	//	info.dwTableId = TableID;
	//	info.dwChairId = i;
	//	if( TableID < 0 )
	//		info.bIsFull = true ;
	//	else
	//		info.bIsFull = false ;
	//	g_ServerApp.SendToAgentServer( user->m_dwAgentIndex ,&info,sizeof(info) );
	//}*/


	////pTable->StartGame();


	///////检测是否还可以分配
	//if( m_pWaitGameUserList.GetCount() >= pTable->m_iUserNum )
	//	CheckAllot(NULL);
}

void CBaseRoom::SetTimer( unsigned int dwElapse, int iType ,bool bOnce )
{
	m_Timer.SetTimer( dwElapse, bOnce );
	m_iTimerType = iType;
}

void CBaseRoom::OnTimer()
{
	switch( m_iTimerType )
	{
	case WAIT_ALLOT_ID:
		{

		}
		break;
	case MATCH_TIME_ID:
		{
			if( m_iScoreType != SCORE_MATCH )
				return;

			int type = CompareTime( m_MatchTime );

			if( type < 0 )
				return ;

			switch( type )
			{
			case TIME_END:
				{
					///改变服务器房间属性
					m_iCurMatchState = MATCH_STATE_END_MATCH;


				}
				break;
			case TIME_NONE:
				{



				}
				break;
			case TIME_SECOND_THIRTY:
				{



				}
				break;
			case TIME_MINUTE_THREE:
				{


				}
				break;
			case TIME_SECOND_THIRTY_EX:
				{

				}
				break;
			case TIME_MINUTE_ONE:
				{

				}
				break;
			case TIME_OVER_TEN_MINUTE:
				{


				}
				break;
			case TIME_OUT:
				{


				}
				break;
			}


		}
		break;
	}
}
void CBaseRoom::RemovePlayerFromAllPlayer( unsigned int dwUserId )
{

}

void CBaseRoom::SendPlaceList()
{

}
void CBaseRoom::RandomMatchPeople()
{

}
//是否正在比赛中
bool CBaseRoom::IsAtMatch( CUser * pUser )
{
//	for( int i = 0; i < m_pAllPlayer.GetCount(); i++ )
//	{
//		if( !m_pAllPlayer[i] )
//			continue;
//		if( m_pAllPlayer[i]->m_dwUserId == pUser->m_dwUserId )
//		{
//			return true;
//		}
//	}
	return false;

}

//大奖赛不够资格，用金币报名
void CBaseRoom::SignUpMatchEx( CUser * pUser )
{

}

void CBaseRoom::SignUpMatch( CUser * pUser )
{


}
void CBaseRoom::ExitMatch( CUser * pUser )
{

}
void CBaseRoom::KillTimer()
{
	//m_Timer.KillTimer();
}
unsigned int CBaseRoom::GetSecondByDay( CDateTimeEx time )
{
	unsigned int dwSecond = (time.wHour * 60 + time.wMinute) * 60 + time.wSecond;
	return dwSecond;
}
int CBaseRoom::CompareTime( CDateTimeEx match )
{


	return -1;
}




//获取排名
int CBaseRoom::GetPlace( unsigned int dwUserId )
{
	int iPlace = -1;

//	for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//	{
//		if( m_pPlayOfOut[i] == dwUserId )
//		{
//			iPlace = m_pPlayOfOut.GetCount() + m_pAllPlayer.GetCount() - i - 1;
//		}
//	}
//	if( iPlace == -1 )//没有被淘汰
//	{
//		for( int i = 0; i < m_pAllPlayer.GetCount(); i++ )
//		{
//			if( m_pAllPlayer[i]->m_dwUserId == dwUserId )
//			{
//				iPlace = i;
//				break;
//			}
//		}
//	}

	return iPlace;

}
bool CBaseRoom::IsOut( unsigned int dwUserId )
{
//	for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//	{
//		if( m_pPlayOfOut[i] == dwUserId )
//		{
//			return true;
//		}
//	}
	return false;
}

//比赛总排名
void CBaseRoom::SortAllPlayer()
{
//	CUser ** ppi = m_pAllPlayer.GetData();
//	for( int i = 0; i < m_pAllPlayer.GetCount(); i++ )
//	{
//		CUser **ppk = ppi;
//
//		CUser **ppj = ppi + 1;
//		for( int j = i + 1; j < m_pAllPlayer.GetCount(); j++ )
//		{
//			if( (*ppk)->m_iMatchScore < (*ppj)->m_iMatchScore )
//				ppk = ppj;
//			else if( (*ppk)->m_iMatchScore == (*ppj)->m_iMatchScore )
//			{
//				if( (*ppk)->m_iSignUp > (*ppj)->m_iSignUp )
//				{
//					ppk = ppj;
//				}
//			}
//
//			ppj++;
//
//		}
//		if( ppk != ppi )
//		{
//			CUser *pt = (*ppk);
//			(*ppk) = (*ppi);
//			(*ppi) = pt;
//		}
//
//		ppi++;
//	}
}

int CBaseRoom::GetSignUpOrder( unsigned int dwUserId )
{
//	for( int i = 0; i < m_MathSignUpList.GetCount(); i++ )
//	{
//		if( m_MathSignUpList[i] == dwUserId )
//			return i;
//	}
	return -1;
}
int CBaseRoom::GetFreeTable()
{
	for( int i = 0; i < GetTableNum(); i++ )
	{
		if( m_pTables[i]->IsNoUser() &&  m_pTables[i]->m_bUse )
		{
			m_pTables[i]->m_bUse = false;
			return i;
		}
	}
	return -1;
}
int CBaseRoom::GetFreeChair( int iTableId )
{
	for( int i = 0; i < m_iChairNum; i++ )
	{
		if( m_pTables[iTableId]->m_pUsers[i] != NULL )
			return i;
	}
	return -1;
}

void CBaseRoom::RemoveSignUpUser( unsigned int dwUserId )
{
//	for( int i = 0; i < m_MathSignUpList.GetCount(); i++ )
//	{
//		if( m_MathSignUpList[i] == dwUserId )
//		{
//			m_MathSignUpList.RemoveAt(i);
//			break;
//		}
//	}
}
void CBaseRoom::RemoveMatchTeamToReadyMatch( unsigned int dwTeamId )
{

//
}
void CBaseRoom::RemoveReadyTeamToMatchTeam( unsigned int dwTeamId )
{

}
void CBaseRoom::RemoveMatchTeamToTeamOut( unsigned int dwTeamId )
{


}
//void CBaseRoom::RemoveMatchToGame( unsigned int dwUserId )
//{
//	CUser **pp = m_pPlayOfMatching.GetData();
//	for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//	{
//		if( !(*pp) )
//			continue;
//		if( (*pp)->m_dwUserId == dwUserId )
//		{
//			(*pp)->m_bMatch = true;
//
//			PT_GAMESTATE_RESET_INFO data2;
//			data2.dwUserId = dwUserId;
//			data2.iState = US_INTABLE;
//			g_ServerApp.SendToAgentServer((*pp)->m_dwAgentIndex, &data2, sizeof(data2) );
//
//			m_pPlayOfGaming.Add( (*pp) );
//			m_pPlayOfMatching.RemoveAt(i);
//
//			break;
//		}
//
//		pp++;
//	}
//}
//void CBaseRoom::RemoveGameToMatch( unsigned int dwUserId )
//{
//	CUser *pUser = GetUser( dwUserId );
//	if( pUser )
//	{
//		PT_MATCH_PROMOTION_INFO data;
//		data.dwUserId = dwUserId;
//		g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex ,&data ,sizeof(data) );
//	}
//
//	CUser **pp = m_pPlayOfGaming.GetData();
//
//	for( int i = 0; i < m_pPlayOfGaming.GetCount(); i++ )
//	{
//		if( !(*pp) )
//			continue;
//		if( (*pp)->m_dwUserId == dwUserId/* && !m_pPlayOfGaming[i]->m_bDrop */)
//		{
//			//m_pPlayOfGaming[i]->m_bMatch = false;
//
//			/*PT_MATCH_REMOVE_WAITLIST_INFO data;
//			data.dwUserId = dwUserId;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );*/
//
//			PT_GAMESTATE_RESET_INFO data2;
//			data2.dwUserId = dwUserId;
//			data2.iState = US_FREE;
//			g_ServerApp.SendToAgentServer(pUser->m_dwAgentIndex, &data2, sizeof(data2) );
//			m_pPlayOfMatching.Add( (*pp) );
//			m_pPlayOfGaming.RemoveAt(i);
//
//			break;
//		}
//
//		pp++;
//	}
//}
//void CBaseRoom::RemovePlayerFromGame( unsigned int dwUserId )
//{
//	for( int i = 0; i < m_pPlayOfGaming.GetCount(); i++ )
//	{
//		if( !m_pPlayOfGaming[i] )
//			continue;
//		if( m_pPlayOfGaming[i]->m_dwUserId == dwUserId )
//		{
//			m_pPlayOfGaming.RemoveAt(i);
//
//			PT_MATCH_REMOVE_WAITLIST_INFO data;
//			data.dwUserId = dwUserId;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//			break;
//		}
//	}
//}
//void CBaseRoom::RemovePlayerFromMatch( unsigned int dwUserId )
//{
//	for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//	{
//		if( !m_pPlayOfMatching[i] )
//			continue;
//		if( m_pPlayOfMatching[i]->m_dwUserId == dwUserId )
//		{
//			m_pPlayOfMatching.RemoveAt(i);
//
//			PT_MATCH_REMOVE_WAITLIST_INFO data;
//			data.dwUserId = dwUserId;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//			break;
//		}
//	}
//}
//void CBaseRoom::RemoveGameToOut( unsigned int dwUserId )
//{
//	CUser **pp = m_pPlayOfGaming.GetData();
//
//	for( int i = 0; i < m_pPlayOfGaming.GetCount(); i++ )
//	{
//		if( !(*pp) )
//			continue;
//		if( (*pp)->m_dwUserId == dwUserId )
//		{
//			CUser *pUser = GetUser( dwUserId );
//			if( pUser )
//			{
//				pUser->m_bMatch = false;
//
//				if( m_iCurMatchMode != MATCH_SCORE )
//				{
//					PT_MATCH_FAIL_INFO data;
//					data.dwUserId = dwUserId;
//					data.bOutType = true;
//					g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex ,&data ,sizeof(data) );
//				}
//			}
//
//			PT_MATCH_REMOVE_WAITLIST_INFO data1;
//			data1.dwUserId = dwUserId;
//			g_ServerApp.SendToDataServer( &data1, sizeof(data1) );
//
//			PT_GAMESTATE_RESET_INFO data2;
//			data2.dwUserId = dwUserId;
//			data2.iState = US_FREE;
//			g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex, &data2, sizeof(data2) );
//
//
//			m_pPlayOfOut.Add( dwUserId );
//			m_pPlayOfGaming.RemoveAt(i);
//			break;
//		}
//
//		pp++;
//	}
//
//	RemovePlayerFromAllPlayer( dwUserId );
//}
//void CBaseRoom::RemoveMatchToOut( unsigned int	dwUserId )
//{
//	CUser **pp = m_pPlayOfMatching.GetData();
//
//	for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//	{
//		if( !(*pp) )
//			continue;
//		if( (*pp)->m_dwUserId == dwUserId )
//		{
//			CUser *pUser = GetUser( dwUserId );
//			if( pUser )
//			{
//				pUser->m_bMatch = false;
//
//				PT_MATCH_FAIL_INFO data;
//				data.dwUserId = dwUserId;
//				data.bOutType = false;
//				g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex ,&data ,sizeof(data) );
//			}
//
//			PT_MATCH_REMOVE_WAITLIST_INFO data;
//			data.dwUserId = dwUserId;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//
//			PT_GAMESTATE_RESET_INFO data2;
//			data2.dwUserId = dwUserId;
//			data2.iState = US_FREE;
//			g_ServerApp.SendToAgentServer(pUser->m_dwAgentIndex, &data2, sizeof(data2) );
//
//			m_pPlayOfOut.Add( dwUserId );
//			m_pPlayOfMatching.RemoveAt(i);
//			break;
//		}
//
//		pp++;
//	}
//
//	RemovePlayerFromAllPlayer( dwUserId );
//}
//CUser * CBaseRoom::GetUserFromGame( unsigned int dwUserId )
//{
//	for( int i = 0; i < m_pPlayOfGaming.GetCount(); i++ )
//	{
//		if( !m_pPlayOfGaming[i] )
//			continue;
//		if( m_pPlayOfGaming[i]->m_dwUserId == dwUserId )
//		{
//			return m_pPlayOfGaming[i];
//		}
//	}
//	return NULL;
//}
//int CBaseRoom::GetPlayerNumOfMatch()//获取所有人数，没有出局的，符合比赛条件的
//{
//	int num = 0;
//	//num = m_pPlayOfGaming.GetCount() + m_pPlayOfMatching.GetCount();
//	num = m_pAllPlayer.GetCount();
//	return num;
//}
//void CBaseRoom::AllotScore( int iScore )
//{
//	if( m_dwGameId == GAME_JS_ZLJ )
//	{
//		STeamInfo ** ppTeam = m_pReadyTeamList.GetData();
//		for( int i = 0; i < m_pReadyTeamList.GetCount(); i++ )
//		{
//			for( int j = 0; j < 3; j++ )
//			{
//				CUser * pUser = GetUser( (*ppTeam)->dwMemberId[j] );
//				if( pUser )
//					pUser->m_iMatchScore = iScore;
//			}
//			ppTeam++;
//		}
//	}
//	else
//	{
//		for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//		{
//			if( m_pPlayOfMatching[i] )
//				m_pPlayOfMatching[i]->m_iMatchScore = iScore;
//		}
//	}
//}

//void CBaseRoom::AutoAllotTable()
//{
//	g_strText.Format( L"===========autoallottable==================\n" );
//	Print( g_strText.GetBuffer() );
//
//
//	if(  m_pPlayOfMatching.GetCount() < m_iChairNum )
//	{
//		if( m_pPlayOfGaming.GetCount() == 0 )
//		{
//
//
//			m_iMatchTimeType = -1;
//			//比赛结束
//			SetMatchState( MATCH_STATE_END_MATCH );
//
//			if( m_pAllPlayer.GetCount() > 0 && m_pAllPlayer.GetAt(0) )
//			{
//
//				MatchAwardInfo * pMatchAward = GetMatchAward( 1 );
//				if( pMatchAward )
//				{
//					PT_MATCH_ADWARD_INFO data1;
//					data1.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//					data1.iMoney = pMatchAward->iAwardNum;
//					data1.iPlace = 0;
//					data1.iHonorNum = pMatchAward->iHonorNum;
//					_tcscpy( data1.szAward, pMatchAward->szAwardName );
//					g_ServerApp.SendToAgentServer( m_pAllPlayer.GetAt(0)->m_dwAgentIndex, &data1, sizeof(data1) );
//
//
//					PT_MATCH_UPDATE_BANK_MONEY_AND_HONOR_INFO data2;
//					data2.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//					data2.iHonor = pMatchAward->iHonorNum;
//					data2.iMoney = pMatchAward->iAwardNum;//===竞赛资金
//					g_ServerApp.SendToAgentServer( m_pAllPlayer.GetAt(0)->m_dwAgentIndex, &data2, sizeof(data2) );
//
//					m_pAllPlayer.GetAt(0)->m_dwHonor += pMatchAward->iHonorNum;///更新勋章数
//				}
//
//				PT_MATCH_CHAMPION_LIST_INFO data;
//				data.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//				data.iMatchPeopleNum = m_MathSignUpList.GetCount();
//				_tcscpy( data.szMatchName, m_szName );
//				_tcscpy( data.szMatchTime, m_MatchTime.ToStringEx() );
//				_tcscpy( data.szWinnerName, m_pAllPlayer.GetAt(0)->m_szUserName );
//				data.iGroupId = GetMatchBonusType();
//				data.iPlace = 1;//冠军
//				g_ServerApp.SendToDataServer( &data, sizeof(data) );
//
//				//mx
//				PT_MATCH_WIN_MSG_INFO data19;
//				::_tcscpy( data19.szGameName, GetName() );
//				::_tcscpy( data19.szUserName, m_pAllPlayer.GetAt(0)->m_szUserName );
//				data19.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//				data19.dwNumericAccount = m_pAllPlayer.GetAt(0)->m_dwNumericAccount;
//				for( int i = 0; i < AGENT_SERVER_NUM; ++ i )
//				{
//					g_ServerApp.SendToAgentServer( g_pServerManager->m_ServerList[i].dwConnectIndex, &data19, sizeof(data19) );
//				}
//
//				//SaveMatchPlace( m_pAllPlayer.GetAt(0)->m_dwUserId ,m_pAllPlayer.GetAt(0)->m_szUserName, 0 ,false);//wm add save place
//
//				PT_MATCH_CHAMPION_LIST_REQUEST_INFO data20;
//				g_ServerApp.SendToDataServer( &data20, sizeof(data20) );
//
//
//				PT_MATCH_REMOVE_WAITLIST_INFO data7;
//				data7.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//				g_ServerApp.SendToDataServer( &data7, sizeof(data7) );
//
//				m_pAllPlayer.GetAt(0)->m_bMatch = false;
//
//				PT_GAMESTATE_RESET_INFO data8;
//				data8.dwUserId = m_pAllPlayer.GetAt(0)->m_dwUserId;
//				data8.iState = US_FREE;
//				g_ServerApp.SendToAgentServer(m_pAllPlayer.GetAt(0)->m_dwAgentIndex, &data8, sizeof(data8) );
//
//
//
//				//===============================
//
//				m_pPlayOfOut.Add(m_pAllPlayer.GetAt(0)->m_dwUserId);
//				m_pAllPlayer.RemoveAt(0);
//
//				//===如果是大奖赛储存晋级名单====
//				if( m_iXmlMatchType == 1 )
//				{
//					SaveXmlInfo();
//				}
//
//				for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//				{
//					int iplace = GetPlace(m_pPlayOfOut[i]);
//					pMatchAward = GetMatchAward( iplace + 1 );
//					bool bRes = false;
//					if( pMatchAward && _tcslen( pMatchAward->szAwardName ) > 0 )
//						bRes =true;
//					SaveMatchPlace( m_pPlayOfOut[i], L"", iplace, bRes);
//				}
//
//				for( POS pos = m_pUserList->GetFirstPos(); pos; )
//				{
//					CUser * pUser = m_pUserList->GetNext( pos );
//					if( !pUser )
//						continue;
//
//					pUser->m_bMatch = false;
//
//					KickOut( pUser->m_dwUserId, ERR_FORCE_LEAVE_ROOM_MATCHEND );
//
//				}
//
//				m_pUserList->ClearAll();
//
//
//			}
//
//			m_bMatchStart = false;
//			m_MathSignUpList.RemoveAll();
//			m_pPlayOfMatching.RemoveAll();
//			m_pAllPlayer.RemoveAll();
//			m_pPlayOfOut.RemoveAll();
//			m_pPlayOfGaming.RemoveAll();
//			m_iLunNum = 0;
//			m_pTeamOut.RemoveAll();
//
//			switch( GetLoopMatch() )
//			{
//			case MATCH_FREE_LOOP:
//				{
//					m_MatchTime.GetDateTime();
//					m_MatchTime.AddMinute( 6 );
//
//					for( int i = 0; i < m_pTables.Num(); i++ )
//					{
//						m_pTables[i]->SetBout( 0 );
//						m_pTables[i]->m_iBaseScore = -1;
//					}
//
//					SetTimer( MATCH_TIME_COUNT ,MATCH_TIME_ID, false );
//				}
//				break;
//			case MATCH_WEEK_LOOP:
//			case MATCH_DAY_LOOP:
//			case MATCH_HOUR_LOOP:
//				{
//					for( int i = 0; i < m_pTables.Num(); i++ )
//					{
//						m_pTables[i]->SetBout( 0 );
//						m_pTables[i]->m_iBaseScore = -1;
//					}
//					m_MatchTime = GetNextMatchTime();
//					SetTimer( MATCH_TIME_COUNT ,MATCH_TIME_ID, false );
//					m_MatchTimes = m_MatchTime;
//				}
//				break;
//
//
//			}
//
//			PT_MATCH_END_INFO data1;
//			data1.dwGameId = m_dwGameId;
//			data1.dwRoomId = m_dwId;
//			_tcscpy( data1.szBeginTime, m_MatchTime.ToStringEx() );
//
//			for( int i = 0; i < AGENT_SERVER_NUM; ++ i )
//			{
//				g_ServerApp.SendToAgentServer( g_pServerManager->m_ServerList[i].dwConnectIndex, &data1, sizeof(data1) );
//			}
//
//			return;
//		}
//	}
//
//
//	SortAllPlayer();
//
//	g_strText.Format( L"=============whilebegin================\n" );
//	Print( g_strText.GetBuffer() );
//	int iTabId = 0;
//	while( m_pPlayOfMatching.GetCount() >= m_iChairNum )
//	{
//
//		iTabId = GetFreeTable();
//		if( iTabId == -1 )
//		{
//			Print( L"竞赛无法分配桌子\n" );
//			return;
//		}
//		CBaseTable * pTable = GetTable( iTabId );
//		//坐人
//		for( int i = 0; i < m_iChairNum; ++ i )
//		{
//			int num = rand() % ( int )m_pPlayOfMatching.GetCount();
//			CUser * pUser = m_pPlayOfMatching[num];
//			if( !pUser )
//			{
//				Print( L"竞赛分配座位出错\n" );
//				return;
//			}
//			pUser->m_bAllot = true;
//			pTable->m_pUsers[i] = pUser;
//			pUser->m_iTableId = iTabId;
//			pUser->m_iChairId = i;
//			pUser->m_iState = US_INTABLE;
//			RemoveMatchToGame( pUser->m_dwUserId );
//		}
//
//		PT_MATCH_TABLE_USERS_INFO data;
//		data.iInfoNum = m_iChairNum;
//		CUser * p;
//		for( int i = 0; i < m_iChairNum; ++ i )
//		{
//			p = pTable->m_pUsers[i];
//			data.info[i].bSex = p->m_bSex;
//			data.info[i].bVIP = p->m_bVIP;
//			data.info[i].dwDisconnect = p->m_iDisconnect;
//			data.info[i].dwDogfall = p->m_iDogfall;
//			data.info[i].dwEscape = p->m_iEscape;
//			data.info[i].dwFlower = p->m_dwFlower;
//			data.info[i].lHappyBean = p->m_lHappyBean;
//			data.info[i].dwHeadId = p->m_dwHeadId;
//			data.info[i].dwLost = p->m_iLost;
//			data.info[i].lMoney = p->m_lMoney;
//			data.info[i].dwNumericAccount = p->m_dwNumericAccount;
//			//			data.info[i].dwPropFlowerNum = p->m_dwPropFlowerNum;
//			data.info[i].dwPropHornBigNum = p->m_dwPropHornBigNum;
//			data.info[i].dwPropHornNum = p->m_dwPropHornNum;
//			//			data.info[i].dwPropVipBigNum = p->m_dwPropVipBigNum;
//			//			data.info[i].dwPropVipNum = p->m_dwPropVipNum;
//			//			data.info[i].dwPropVipSupperNum = p->m_dwPropVipSupperNum;
//			data.info[i].dwUserId = p->m_dwUserId;
//			data.info[i].dwWin = p->m_iWin;
//			data.info[i].iChairId = p->m_iChairId;
//			data.info[i].iCharm = p->m_iCharm;
//			data.info[i].iScore = p->m_iScore;
//			data.info[i].iTableId = p->m_iTableId;
//			data.info[i].wSubsidyNum = p->m_wSubsidyNum;
//			_tcscpy( data.info[i].szName, p->m_szUserName );
//			_tcscpy( data.info[i].szHeadImgName, p->m_szHeadImgName );//wz add upload new 333
//			data.info[i].iMatchScore = p->m_iMatchScore;
//			data.info[i].iMatchPlace = GetPlace( p->m_dwUserId );
//			data.info[i].dwHonor = p->m_dwHonor;
//			data.info[i].dwCountLoginTime = p->m_dwCountLoginTime;
//
//			CString str;
//			str.Format( L"%s->(%d)Table->(%d)Chair===<%d>\n", data.info[i].szName, data.info[i].iTableId, data.info[i].iChairId, m_iChairNum );
//			Print( str.GetBuffer() );
//
//			//add by mx 2009.9.24
//			data.info[i].bSuperCharm = p->m_bSuperCharm;
//			data.info[i].iRealSex = p->m_iRealSex;
//			data.info[i].bVidicon = p->m_bVidicon;
//
//		}
//		data.iCurrentPeopleNum = m_pAllPlayer.GetCount();
//		data.iCountPeopleNum = m_MathSignUpList.GetCount();
//		data.iMatchMode = m_iCurMatchMode;
//		pTable->SendToAllUser( &data, sizeof(data) );
//		CString str;
//		str.Format( L"=========%d====================\n", m_pPlayOfMatching.GetCount() );
//		Print( str.GetBuffer() );
//
//		pTable->SetTimer( 30000, WAIT_READY_ID, true );
//
//	}
//	CString str;
//	str.Format( L"=============whileend================\n" );
//	Print( str.GetBuffer() );
//	g_strText.Format(L"123456");
//	//==============================================end==================================================================
//}
//进入桌子(竞赛)
void CBaseRoom::EnterTableJS()
{

}
CDateTimeEx * CBaseRoom::GetTimeByDayOfWeek( CDateTimeEx time )
{
//	CDateTimeEx **ppTime = m_MatchTimeList.GetData();
//	for( int i = 0; i < m_MatchTimeList.GetCount(); i++ )
//	{
//		if( (*ppTime)->GetDayOfWeek() == time.GetDayOfWeek() )
//		{
//			if( time.CompareTime(*ppTime) == 2 || time.CompareTime(*ppTime) == 0)//小于列表中的时间
//			{
//				return (*ppTime);
//			}
//		}
//
//		ppTime++;
//	}

	return NULL;
}
CDateTimeEx CBaseRoom::GetNextMatchTime()
{
	CDateTimeEx time;
	time.GetDateTime();

	CDateTimeEx times;
	times.GetDateTime();



	switch( GetLoopMatch() )
	{
	case MATCH_FREE_LOOP:
		{
			time.AddMinute(10);
		}
		break;
	case MATCH_HOUR_LOOP:
	case MATCH_DAY_LOOP:
	case MATCH_WEEK_LOOP:
		{
			CDateTimeEx * pT = 0;
			do
			{
				pT = GetTimeByDayOfWeek( time );

				if( pT )
				{
					time.SetHour( pT->GetHour() );
					time.SetMinute( pT->GetMinute() );
					time.SetSecond( pT->GetSecond() );
				}
				else
				{
					time.AddDays();
					time.SetHour(0);
					time.SetMinute(0);
					time.SetSecond(0);

					pT = GetTimeByDayOfWeek( time );
					if( pT )
					{
						time.SetHour( pT->GetHour() );
						time.SetMinute( pT->GetMinute() );
						time.SetSecond( pT->GetSecond() );
					}
				}
			}
			while( !pT );

		}
		break;
	}
	return time;
}
//add by mx
void CBaseRoom::UpdateMoney( CUser * pUser )
{
	if( !pUser )
		return;

	for( int i = 0; i < m_pTables.Num(); i++ )
	{
		m_pTables[i]->UpdateMoney( pUser );
	}
}
//
//void CBaseRoom::LoadMathcTimeInfo()
//{
//
////	CDateTimeEx **ppTime = m_MatchTimeList.GetData();
////	for( int i = 0; i < m_MatchTimeList.GetCount(); i++ )
////	{
////		SAFE_DELETE( *ppTime );
////		ppTime++;
////	}
////	m_MatchTimeList.RemoveAll();
//
//	//=======
//	char floader[200];
//
//	char dir[20];
//	TiXmlDocument* m_xmlDoc;
//	TiXmlElement *xZone = 0;
//	TiXmlElement *xZoneEx = 0;
//
//	int iDayOfWeek = 0;
//	CDateTimeEx * pTime = 0;
//	wcstombs( dir, g_pGameManager->GetGame( m_dwGameId )->GetGameDir(), 20 );
//	/*switch( GetLoopMatch() )
//	{
//	case MATCH_FREE_LOOP:
//	{
//
//	break;
//	}
//	case MATCH_HOUR_LOOP:
//	{
//	sprintf(floader,"./js_config/%s/%s.xml", dir, "js_time_hour");
//	break;
//	}
//	case MATCH_DAY_LOOP:
//	{
//	sprintf(floader,"./js_config/%s/%s.xml", dir, "js_time_day");
//	break;
//	}
//	case MATCH_WEEK_LOOP:
//	{
//	sprintf(floader,"./js_config/%s/%s.xml", dir, "js_time_week");
//	break;
//	}
//	}*/
//
//	if( GetLoopMatch() != MATCH_FREE_LOOP )
//		sprintf(floader, "./js_config/%s/MatchTime%d.xml", dir, m_dwId );
//
//	m_xmlDoc = new TiXmlDocument(floader);
//
//	if (m_xmlDoc->LoadFile())
//	{
//
//		TiXmlElement *xPMathcTime = 0;
//
//		xPMathcTime = m_xmlDoc->FirstChildElement("matchtime");
//
//		//==============save==========
//		m_iXmlMatchId = atoi( xPMathcTime->Attribute("id"));
//		m_iXmlMatchType = atoi(xPMathcTime->Attribute("type"));
//		m_iXmlMatchPlace = atoi(xPMathcTime->Attribute("place"));
//		m_iXmlMatchPhase = atoi(xPMathcTime->Attribute("phase"));
//		m_iXmlMatchMoney = atoi(xPMathcTime->Attribute("money"));
//		//============================
//
//		if (xPMathcTime)
//		{
//			xZone = xPMathcTime->FirstChildElement("DayOfWeek");
//			if( !xZone )
//				return;
//			pTime = new CDateTimeEx;
//
//			iDayOfWeek = atoi(xZone->Attribute("id"));//周几
//			pTime->SetDayOfWeek( iDayOfWeek );
//
//			xZoneEx = xZone->FirstChildElement("Time");
//
//			int ihour = atoi(xZoneEx->Attribute("hour"));
//			int iminute = atoi(xZoneEx->Attribute("minute"));
//			int isecond = atoi(xZoneEx->Attribute("second"));
//			pTime->SetHour( ihour );
//			pTime->SetMinute( iminute );
//			pTime->SetSecond( isecond );
//
//			m_MatchTimeList.Add( pTime );
//
//			while( xZoneEx->NextSiblingElement() )
//			{
//				pTime = new CDateTimeEx;
//				pTime->SetDayOfWeek( iDayOfWeek );
//
//				//注意这里
//				xZoneEx = xZoneEx->NextSiblingElement();
//				ihour = atoi(xZoneEx->Attribute("hour"));
//				iminute = atoi(xZoneEx->Attribute("minute"));
//				isecond = atoi(xZoneEx->Attribute("second"));
//				pTime->SetHour( ihour );
//				pTime->SetMinute( iminute );
//				pTime->SetSecond( isecond );
//
//				m_MatchTimeList.Add( pTime );
//			}
//
//			while( xZone->NextSiblingElement() )
//			{
//				pTime = new CDateTimeEx;
//
//				xZone = xZone->NextSiblingElement();
//				iDayOfWeek = atoi(xZone->Attribute("id"));//周几
//				pTime->SetDayOfWeek( iDayOfWeek );
//
//				xZoneEx = xZone->FirstChildElement("Time");
//
//				int ihour = atoi(xZoneEx->Attribute("hour"));
//				int iminute = atoi(xZoneEx->Attribute("minute"));
//				int isecond = atoi(xZoneEx->Attribute("second"));
//				pTime->SetHour( ihour );
//				pTime->SetMinute( iminute );
//				pTime->SetSecond( isecond );
//
//				m_MatchTimeList.Add( pTime );
//
//				while( xZoneEx->NextSiblingElement() )
//				{
//					pTime = new CDateTimeEx;
//					pTime->SetDayOfWeek( iDayOfWeek );
//					//注意这里
//					xZoneEx = xZoneEx->NextSiblingElement();
//					ihour = atoi(xZoneEx->Attribute("hour"));
//					iminute = atoi(xZoneEx->Attribute("minute"));
//					isecond = atoi(xZoneEx->Attribute("second"));
//
//					pTime->SetHour( ihour );
//					pTime->SetMinute( iminute );
//					pTime->SetSecond( isecond );
//
//					m_MatchTimeList.Add( pTime );
//				}
//			}
//		}
//
//	}
//
//	delete m_xmlDoc;
//
//}
//void CBaseRoom::LoadMatchConfigInfo()
//{
//	m_MatchAwardList.RemoveAll();
//
//
//	char szDir[255];
//	_tcscpy( szDir , L"./js_config/" );
//	_tcscat( szDir, g_pGameManager->GetGame( m_dwGameId )->GetGameDir() );
//	//_tcscat( szDir, L"/" );
//
//	char Group[20];
//	_itow( m_iMatchBonusType , Group ,10 );
//	//_tcscat( szDir , L"js_committal.ini" );
//	CString dir;
//	dir.Format( L"%s/js_Award%d.ini",szDir,m_iMatchBonusType );
//
//	/*switch( m_iMatchBonusType )
//	{
//	case MATCH_BONUS_LOOP_FREE:
//	{
//	_tcscat( szDir , L"js_random.ini" );
//	break;
//	}
//	case MATCH_BONUS_LOOP_HOUR:
//	{
//	_tcscat( szDir , L"js_hour.ini" );
//	break;
//	}
//	case MATCH_BONUS_LOOP_DAY:
//	{
//	_tcscat( szDir , L"js_day.ini" );
//	break;
//	}
//	case MATCH_BONUS_LOOP_WEEK:
//	{
//	_tcscat( szDir , L"js_week.ini" );
//	break;
//	}
//	case MATCH_BONUS_COMMITTAL:
//	{
//	_tcscat( szDir , L"js_committal.ini" );
//	break;
//	}
//	}*/
//	CIniFileLoader randomIni( dir.GetBuffer() );
//
//	randomIni.SetAppName( L"GroupNum" );
//	WORD num = randomIni.GetValueInt( L"Num");
//	//随即循环赛配置文件读取
//	tstring awardname;
//	for( int i = 0 ; i< num ; i++ )
//	{
//		MatchAwardInfo randomInfo;
//		char group[20]=L"Group";
//		char num[5];
//		_itot( i , num ,10 );
//		_tcscat( group , num );
//
//		randomIni.SetAppName( group );
//		randomInfo.iMin = randomIni.GetValueInt( L"Min" );
//		randomInfo.iMax = randomIni.GetValueInt( L"Max" );
//		randomInfo.iAwardNum = randomIni.GetValueInt( L"Award" );
//		awardname = randomIni.GetValueString( L"AwardName" );
//		_tcscpy( randomInfo.szAwardName ,awardname.c_str() );
//		randomInfo.iHonorNum = randomIni.GetValueInt( L"HonorNum" );
//		m_MatchAwardList.Add( randomInfo );
//
//	}
//}

//MatchAwardInfo *  CBaseRoom::GetMatchAward( int iPlace )
//{
//	MatchAwardInfo * pp = m_MatchAwardList.GetData();
//	for( int i = 0; i < m_MatchAwardList.GetCount(); i++ )
//	{
//		if( (pp) && iPlace >= (pp)->iMin && iPlace <= (pp)->iMax )
//			return (pp);
//
//		pp++;
//	}
//	return NULL;
//}

//
//
//bool CBaseRoom::CreateTeam( CUser * pUser )
//{
//	if( pUser->m_bTeam || !pUser->m_bSign)
//		return false;
//	pUser->m_bTeam = true;
//
//	SMemberInfo * pMember = GetMember( pUser->m_dwUserId);
//	if( pMember )
//		pMember->dwTeamId = pUser->m_dwUserId;
//
//	STeamInfo * pTeam = new STeamInfo;
//	pTeam->dwMemberId[0]  = pUser->m_dwUserId;
//	pTeam->dwMemberId[1] = 0;
//	pTeam->dwMemberId[2] = 0;
//	InsertTeam( pTeam );
//
//	PT_LJJS_USER_CREATE_TEAM_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	SendToAllUser( &data, sizeof(data));
//	return true;
//}
//bool CBaseRoom::DelTeam( CUser * pUser )
//{
//	if( !pUser->m_bTeam )
//		return false;
//	pUser->m_bTeam = false;
//
//	STeamInfo * pTeam = GetTeam( pUser->m_dwUserId );
//	if( pTeam )
//	{
//		for( int i = 0; i < 3; i++ )
//		{
//			CUser * p =  GetUser( pTeam->dwMemberId[i] );
//			if( p )
//				p->m_bTeam = false;
//
//			SMemberInfo * pMember = GetMember( pTeam->dwMemberId[i] );
//			if(pMember)
//				pMember->dwTeamId = 0;
//		}
//
//		PT_MATCH_DEL_TEAM_INFO data;
//		data.dwTeamId = pTeam->dwMemberId[0];
//		data.dwTeamNum = m_pReadyTeamList.GetCount();
//		SendToAllUser( &data, sizeof(data) );
//
//		RemoveTeam( pUser->m_dwUserId );
//		SAFE_DELETE( pTeam );
//
//		return true;
//	}
//
//	return false;
//}
//bool CBaseRoom::InviteMember( CUser * pUser, unsigned int dwTeamId )
//{
//	return JoinTeam( pUser, dwTeamId );
//}
//void CBaseRoom::KickTeam( CUser * pUser, CUser * pOther )
//{
//	STeamInfo * pTeam = GetTeam( pUser->m_dwUserId );
//	if( !pTeam )
//		return;
//
//	if( pTeam->bReady )
//		return;
//
//	if( pUser->m_bMatch || pOther->m_bMatch )
//		return;
//
//	LeaveTeam( pOther, pTeam->dwMemberId[0] );
//}
//bool CBaseRoom::JoinTeam( CUser * pUser, unsigned int dwTeamId )
//{
//	SMemberInfo * pMember = GetMember( pUser->m_dwUserId );
//	if( !pMember || pMember->dwTeamId != 0 || !pUser->m_bSign)
//		return false;
//
//	STeamInfo * pTeam =  GetTeam(dwTeamId);
//	if( !pTeam || pUser->m_bTeam )
//		return false;
//
//	for( int i = 1; i < 3; i++ )
//	{
//		if( pTeam->dwMemberId[i] == 0 )
//		{
//			pTeam->dwMemberId[i] = pUser->m_dwUserId;
//			pUser->m_bTeam = true;
//
//			pMember->dwTeamId = dwTeamId;
//
//			PT_LJJS_USER_JOIN_TEAM_INFO data;
//			data.dwTeamId = dwTeamId;
//			data.dwUserId = pUser->m_dwUserId;
//			SendToAllUser( &data, sizeof(data) );
//			return true;
//		}
//	}
//	return false;
//}
//bool CBaseRoom::LeaveTeam( CUser * pUser, unsigned int dwTeamId )
//{
//	STeamInfo * pTeam =  GetTeam(dwTeamId);
//
//	if( !pTeam || !pUser->m_bTeam )//没有该队伍或这个人不是组队状态
//		return false;
//
//	if( pUser->m_bMatch )
//		return false;
//
//	RemovTeamFromReadyTeam( dwTeamId );
//
//	pTeam->bReady = false;
//	if( pUser->m_dwUserId == dwTeamId )//是队长
//	{
//		return DelTeam( pUser );
//	}
//	else
//	{
//		for( int i = 1; i < 3; i++ )
//		{
//			if( pTeam->dwMemberId[i] == pUser->m_dwUserId )
//			{
//				pTeam->dwMemberId[i] = 0;
//				pUser->m_bTeam = false;
//
//				PT_LJJS_USER_LEAVE_TEAM_INFO data;
//				data.dwUserId = pUser->m_dwUserId;
//				data.dwTeamId = dwTeamId;
//				data.dwTeamNum = m_pReadyTeamList.GetCount();
//				SendToAllUser( &data, sizeof(data));
//
//				SMemberInfo * pMember = GetMember( pUser->m_dwUserId);
//				if( pMember )
//					pMember->dwTeamId = 0;
//
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//void CBaseRoom::RemovTeamFromReadyTeam( unsigned int dwTeamId )
//{
//	STeamInfo ** ppTeam = m_pReadyTeamList.GetData();
//	for( int i = 0; i < m_pReadyTeamList.GetCount(); i++ )
//	{
//		if( (*ppTeam)->dwMemberId[0] == dwTeamId )
//		{
//			m_pReadyTeamList.RemoveAt( i );
//			break;
//		}
//		ppTeam++;
//	}
//
//	ppTeam = m_pAllTeamList.GetData();
//	for( int i = 0; i < m_pAllTeamList.GetCount(); i++ )
//	{
//		if( (*ppTeam)->dwMemberId[0] == dwTeamId )
//		{
//			m_pAllTeamList.RemoveAt(i);
//			break;
//		}
//		ppTeam++;
//	}
//}
//void CBaseRoom::ReadyTeam( CUser * pUser )
//{
//	STeamInfo * pTeam =  GetTeam(pUser->m_dwUserId);
//	if( !pTeam || !pUser->m_bTeam )//没有该队伍或这个人不是组队状态
//		return;
//
//	if( pTeam->dwMemberId[1] == 0 || pTeam->dwMemberId[2] == 0 || pTeam->bReady )//成员不足
//		return;
//
//	if( m_pReadyTeamList.GetCount() >= GetMatchMaxCount() )//队伍满
//		return;
//
//	pTeam->bReady = true;
//
//	m_pReadyTeamList.Add( pTeam );
//	m_pAllTeamList.Add( pTeam );
//
//
//	PT_LJJS_USER_READY_TEAM_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	data.dwTeamNum = m_pReadyTeamList.GetCount();
//	SendToAllUser( &data, sizeof(data) );
//}
//void CBaseRoom::AllotTeam( CUser * pUser )
//{
//	SMemberInfo * pMember = GetMember( pUser->m_dwUserId );
//	if( !pMember || pMember->dwTeamId != 0)
//		return;
//
//
//	STeamInfo * pTeam = 0;
//	for( POS pos = m_pTeamList->GetFirstPos(); pos; )
//	{
//		pTeam = m_pTeamList->GetNext( pos );
//		if( !pTeam )
//			continue;
//		for( int i = 1; i < 3; i++ )
//		{
//			if( pTeam->dwMemberId[i] == 0 )
//			{
//				pTeam->dwMemberId[i] = pUser->m_dwUserId;
//				pUser->m_bTeam = true;
//
//				pMember->dwTeamId = pTeam->dwMemberId[0];
//
//				PT_LJJS_USER_JOIN_TEAM_INFO data;
//				data.dwTeamId = pTeam->dwMemberId[0];
//				data.dwUserId = pUser->m_dwUserId;
//				SendToAllUser( &data, sizeof(data) );
//				return;
//			}
//		}
//
//	}
//
//
//	PT_LJJS_JOIN_TEAM_REVERT_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	SendToUser( &data, sizeof(data), pUser);
//
//
//	return;
//}
//bool CBaseRoom::IsHasAtXmlInfo( unsigned int dwUserId )
//{
//	if( m_iXmlMatchPhase == 0 )
//		return true;
//
//	char floader[200];
//
//	TiXmlDocument* m_xmlDoc;
//	TiXmlElement * xElement = 0;
//	TiXmlElement * XmlMatchInfo = 0;
//	TiXmlElement * XmlUser = 0;
//	int iReadPhase = m_iXmlMatchPhase - 1;
//
//	char dir[20];
//	wcstombs( dir, g_pGameManager->GetGame( m_dwGameId )->GetGameDir(), 20 );
//
//	sprintf(floader,"./js_config/%s/SuperMatch/%d.xml", dir,m_iXmlMatchId);
//
//	m_xmlDoc = new TiXmlDocument(floader);
//	if (m_xmlDoc->LoadFile())
//	{
//		xElement = m_xmlDoc->FirstChildElement("Match");
//
//		if (xElement)
//		{
//			XmlMatchInfo = xElement->FirstChildElement("MatchInfo");
//			if( XmlMatchInfo )
//			{
//				int iPhase = atoi(XmlMatchInfo->Attribute("Phase"));
//				if( iPhase == iReadPhase )
//				{
//					XmlUser = XmlMatchInfo->FirstChildElement("User");
//					if( XmlUser )
//					{
//						int id = atoi(XmlUser->Attribute("Id"));
//						if( id == dwUserId )
//						{
//							return true;
//						}
//						else
//						{
//							while( XmlUser->NextSiblingElement("User"))
//							{
//								XmlUser = XmlUser->NextSiblingElement("User");
//								int id = atoi(XmlUser->Attribute("Id"));
//								if( id == dwUserId )
//								{
//									return true;
//								}
//							}
//						}
//
//					}
//				}
//				else
//				{
//					while(XmlMatchInfo->NextSiblingElement("MatchInfo"))
//					{
//						XmlMatchInfo = XmlMatchInfo->NextSiblingElement("MatchInfo");
//
//						int iPhase = atoi(XmlMatchInfo->Attribute("Phase"));
//						if( iPhase == iReadPhase )
//						{
//							XmlUser = XmlMatchInfo->FirstChildElement("User");
//							if( XmlUser )
//							{
//								int id = atoi(XmlUser->Attribute("Id"));
//								if( id == dwUserId )
//								{
//									return true;
//								}
//								else
//								{
//									while( XmlUser->NextSiblingElement("User"))
//									{
//										XmlUser = XmlUser->NextSiblingElement("User");
//										int id = atoi(XmlUser->Attribute("Id"));
//										if( id == dwUserId )
//										{
//											return true;
//										}
//									}
//								}
//
//							}
//						}
//					}
//				}
//			}
//
//		}
//
//	}
//	SAFE_DELETE( m_xmlDoc );
//	return false;
//}
//void CBaseRoom::SaveXmlInfo()
//{
//	char floader[200];
//
//	TiXmlDocument* m_xmlDoc;
//	TiXmlElement *xZone = 0;
//	TiXmlElement *xZoneEx = 0;
//
//	char dir[20];
//	wcstombs( dir, g_pGameManager->GetGame( m_dwGameId )->GetGameDir(), 20 );
//
//	sprintf(floader,"./js_config/%s/SuperMatch/%d.xml", dir,m_iXmlMatchId);
//
//	m_xmlDoc = new TiXmlDocument(floader);
//
//
//
//	if (m_xmlDoc->LoadFile())
//	{
//		TiXmlElement * xElement = 0;
//		TiXmlElement * XmlMatchInfo = 0;
//		TiXmlElement * XmlUser = 0;
//
//		xElement = m_xmlDoc->FirstChildElement("Match");
//
//		if (xElement)
//		{
//			XmlMatchInfo = xElement->FirstChildElement("MatchInfo");
//			if( XmlMatchInfo )
//			{
//				int iPhase = atoi(XmlMatchInfo->Attribute("Phase"));
//				if( iPhase == m_iXmlMatchPhase )
//				{
//					for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//					{
//						unsigned int dwOutUserId = m_pPlayOfOut[i];
//						int iPlace = GetPlace(dwOutUserId );
//
//						if( iPlace >= m_iXmlMatchPlace )
//							continue;
//
//						XmlUser = XmlMatchInfo->FirstChildElement("User");
//						if( XmlUser )
//						{
//							int id = atoi(XmlUser->Attribute("Id"));
//							int place = atoi(XmlUser->Attribute("Place"));
//							if( id == m_pPlayOfOut[i] )
//							{
//								if( place > GetPlace(m_pPlayOfOut[i]) )
//								{
//									XmlUser->SetAttribute( "Place", GetPlace(m_pPlayOfOut[i]) );
//								}
//								else
//								{
//									XmlUser->SetAttribute( "Place", place );
//								}
//							}
//							else
//							{
//								bool b = false;
//								while( XmlUser->NextSiblingElement("User"))
//								{
//									XmlUser = XmlUser->NextSiblingElement("User");
//									int id = atoi(XmlUser->Attribute("Id"));
//									int place = atoi(XmlUser->Attribute("Place"));
//									if( id == m_pPlayOfOut[i] )
//									{
//										if( place > GetPlace(m_pPlayOfOut[i]) )
//										{
//											XmlUser->SetAttribute( "Place", GetPlace(m_pPlayOfOut[i]) );
//										}
//										else
//										{
//											XmlUser->SetAttribute( "Place", place );
//										}
//
//										b = true;
//									}
//								}
//
//								if( !b)
//								{
//									//create user
//									unsigned int dwUserId = m_pPlayOfOut[i];
//									TiXmlElement xUserElement("User");
//									xUserElement.SetAttribute("Id", dwUserId );
//									xUserElement.SetAttribute("Place", GetPlace(dwUserId ));
//									XmlMatchInfo->InsertEndChild(xUserElement);
//								}
//							}
//						}
//						else
//						{
//							//create user
//							unsigned int dwUserId = m_pPlayOfOut[i];
//							TiXmlElement xUserElement("User");
//							xUserElement.SetAttribute("Id", dwUserId );
//							xUserElement.SetAttribute("Place", GetPlace(dwUserId ));
//							XmlMatchInfo->InsertEndChild(xUserElement);
//						}
//					}
//				}
//				else
//				{
//					bool bb = false;
//					while(XmlMatchInfo->NextSiblingElement("MatchInfo"))
//					{
//						XmlMatchInfo = XmlMatchInfo->NextSiblingElement("MatchInfo");
//
//						int iPhase = atoi(XmlMatchInfo->Attribute("Phase"));
//						if( iPhase == m_iXmlMatchPhase )
//						{
//							bb = true;
//							for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//							{
//								unsigned int dwOutUserId = m_pPlayOfOut[i];
//								int iPlace = GetPlace(dwOutUserId );
//
//								if( iPlace >= m_iXmlMatchPlace )
//									continue;
//
//								XmlUser = XmlMatchInfo->FirstChildElement("User");
//								if( XmlUser )
//								{
//									int id = atoi(XmlUser->Attribute("Id"));
//									int place = atoi(XmlUser->Attribute("Place"));
//									if( id == m_pPlayOfOut[i] )
//									{
//										if( place > GetPlace(m_pPlayOfOut[i]) )
//										{
//											XmlUser->SetAttribute( "Place", GetPlace(m_pPlayOfOut[i]) );
//										}
//										else
//										{
//											XmlUser->SetAttribute( "Place", place );
//										}
//									}
//									else
//									{
//										bool b = false;
//										while( XmlUser->NextSiblingElement("User"))
//										{
//											XmlUser = XmlUser->NextSiblingElement("User");
//											int id = atoi(XmlUser->Attribute("Id"));
//											int place = atoi(XmlUser->Attribute("Place"));
//											if( id == m_pPlayOfOut[i] )
//											{
//												if( place > GetPlace(m_pPlayOfOut[i]) )
//												{
//													XmlUser->SetAttribute( "Place", GetPlace(m_pPlayOfOut[i]) );
//												}
//												else
//												{
//													XmlUser->SetAttribute( "Place", place );
//												}
//
//												b = true;
//											}
//										}
//
//										if( !b)
//										{
//											//create user
//											unsigned int dwUserId = m_pPlayOfOut[i];
//											TiXmlElement xUserElement("User");
//											xUserElement.SetAttribute("Id", dwUserId );
//											xUserElement.SetAttribute("Place", GetPlace(dwUserId ));
//											XmlMatchInfo->InsertEndChild(xUserElement);
//										}
//									}
//								}
//								else
//								{
//									//create user
//									unsigned int dwUserId = m_pPlayOfOut[i];
//									TiXmlElement xUserElement("User");
//									xUserElement.SetAttribute("Id", dwUserId );
//									xUserElement.SetAttribute("Place", GetPlace(dwUserId ));
//									XmlMatchInfo->InsertEndChild(xUserElement);
//								}
//							}
//						}
//					}
//
//					if(!bb)
//					{
//						TiXmlElement xElement1("MatchInfo");
//						xElement1.SetAttribute("Type", m_iXmlMatchType);
//						xElement1.SetAttribute("Phase", m_iXmlMatchPhase );
//
//						for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//						{
//							unsigned int dwUserId = m_pPlayOfOut[i];
//							int iPlace = GetPlace(dwUserId );
//
//							if( iPlace >= m_iXmlMatchPlace )
//							{
//								continue;
//							}
//							TiXmlElement xUserElement("User");
//							xUserElement.SetAttribute("Id", dwUserId );
//							xUserElement.SetAttribute("Place", iPlace);
//							xElement1.InsertEndChild(xUserElement);
//						}
//						xElement->InsertEndChild(xElement1);
//
//					}
//				}
//			}
//			else
//			{
//				int a = 0;
//			}
//
//		}
//		else
//		{
//			int a = 0;
//		}
//	}
//	else
//	{
//
//		TiXmlElement xEle("Match");
//
//		TiXmlElement xElement("MatchInfo");
//		xElement.SetAttribute("Type", m_iXmlMatchType);
//		xElement.SetAttribute("Phase", m_iXmlMatchPhase );
//
//		for( int i = 0; i < m_pPlayOfOut.GetCount(); i++ )
//		{
//			unsigned int dwUserId = m_pPlayOfOut[i];
//			int iPlace = GetPlace(dwUserId );
//
//			if( iPlace >= m_iXmlMatchPlace )
//			{
//				continue;
//			}
//
//			TiXmlElement xUserElement("User");
//			xUserElement.SetAttribute("Id", dwUserId );
//			xUserElement.SetAttribute("Place", GetPlace(dwUserId ));
//			xElement.InsertEndChild(xUserElement);
//		}
//
//		xEle.InsertEndChild(xElement);
//
//		m_xmlDoc->InsertEndChild(xEle);
//
//	}
//	m_xmlDoc->SaveFile(floader);
//	SAFE_DELETE( m_xmlDoc );
//}
//void CBaseRoom::MathcTimeOut()
//{
//	//清理没有进入比赛的玩家
//	CUser * pUser = 0;
//	for( POS pos = m_pUserList->GetFirstPos(); pos; )
//	{
//		pUser = m_pUserList->GetNext( pos );
//		if( !pUser->m_bMatch )
//		{
//			pUser->m_bExitMatch = true;
//
//			/*PT_USER_LEAVE_INFO data;
//			data.dwGameId = m_dwGameId;
//			data.dwRoomId = m_dwId;
//			data.dwUserId = pUser->m_dwUserId;
//			g_ServerApp.PostMsg( FORCE_MSG, &data, sizeof(data) );*/
//
//			LeaveRoom( pUser->m_dwUserId );
//
//
//		}
//		else
//		{
//			PT_MATCH_ADD_WAITLIST_INFO data;
//			data.dwUserId = pUser->m_dwUserId;
//			data.dwGameId = GetGameId();
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//		}
//
//	}
//
//}
