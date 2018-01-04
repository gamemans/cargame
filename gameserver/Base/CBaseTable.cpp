

#include "CBaseTable.h"



CBaseTable::CBaseTable( int iUserNum )
{
	m_pUsers = new CUser *[iUserNum];
	m_iUserNum = iUserNum;

	memset( m_pUsers, 0, sizeof(CUser *)*iUserNum );

	m_szPassword[0] = 0;
	m_pPasswordUser = NULL;

	m_iLookerNum = 0;
	m_dwForceUserId = 0;

	m_bSended = false;

	m_iBout = 0;
	m_iBaseScore = -1;

	m_bUse = true;
}

CBaseTable::~CBaseTable()
{
	delete[] m_pUsers;
	m_pUsers = NULL;
}

void CBaseTable::MatchStart()
{
//	int iCurBout;
//	iCurBout = GetBout();
//	iCurBout++;
//	SetBout( iCurBout );//设置当前回合数
//
//	if( m_pRoom->m_iCurMatchMode == MATCH_OUT )
//	{
//
//	}
//	else if( m_pRoom->m_iCurMatchMode == MATCH_SCORE )
//	{
//	}
//
//	ReSetCurBaseScore();//重置当前底分
}

void CBaseTable::SetTimer( unsigned int dwElapse, int iType, bool bOnce )
{
	m_Timer.SetTimer( dwElapse, bOnce );
	m_iTimerType = iType;
}
void CBaseTable::OnTimer()
{
	switch( m_iTimerType )
	{
	case WAIT_READY_ID:
		{/*
			PT_READY_CHECK_INFO data;
			data.dwGameId = m_pRoom->GetGameId();
			data.dwRoomId = m_pRoom->GetId();*/
			for( int i = 0; i < m_iUserNum; i++ )
			{
				if( !m_pUsers[i] )
				{
//					g_strText.Format( L"NULL准备出错----------------------------------------------------------------------->%d", i );
//					Print( g_strText.GetBuffer() );
				}

				if( m_pUsers[i] && m_pUsers[i]->m_iState != US_READY && !m_bInGame)
				{
				/*	data.dwUserId = m_pUsers[i]->m_dwUserId;
					g_ServerApp.PostMsg( FORCE_MSG, &data, sizeof(data) );*/

					m_pUsers[i]->m_bDrop = true;

//					g_strText.Format( L"%s准备%d\n",m_pUsers[i]->m_szUserName, i );
//					Print( g_strText.GetBuffer() );
//
//					m_pRoom->UserReady( m_pUsers[i] );

				/*	PT_USER_DROP_INFO data1;
					data1.dwUserId = m_pUsers[i]->m_dwUserId;
					SendToAllUser( &data1, sizeof( data1 ) );

					PT_MATCH_DISCONNECT_INFO data2;
					data2.dwUserId = m_pUsers[i]->m_dwUserId;
					g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data2, sizeof(data2) );*/
				}
			}
		}
		break;
	}
}
void CBaseTable::MatchOut()
{
}
void CBaseTable::MatchEnd()
{


}
bool CBaseTable::IsNoUser()
{
	for( int i = 0; i < m_iUserNum; ++ i )
	{
		if( m_pUsers[i] )
			return false;
	}
	return true;
}
int CBaseTable::GetBout()
{
	int t = 0;
	for( int i = 0; i < m_iUserNum; i++ )
	{
		if( m_pUsers[i] && m_pUsers[i]->m_iBout > t )
			t = m_pUsers[i]->m_iBout;
	}
	return t;
}
void CBaseTable::SetBout( int n )
{
	for( int i = 0; i < m_iUserNum; i++ )
	{
		if( m_pUsers[i] )
			m_pUsers[i]->m_iBout = n;
	}
	m_iBout = n;
}
/**
 *设置底分
 */
void CBaseTable::ReSetCurBaseScore()
{

//	m_iBaseScore = m_pRoom->GetBaseScore();


//	PT_MATCH_BASESCORE_INFO data;
//	data.iBaseScore = m_iBaseScore;
//	SendToAllUser( &data, sizeof(data) );
}
int CBaseTable::CanEnter( CUser * pUser )
{
//	if( !m_pRoom->IsCanEnterTable() )
//		return ERR_ENTERTABLE_ACCEPT;

	//ip比较
	if( pUser->m_bSameIP )
	{
		for( int i = 0; i < m_iUserNum; ++ i )
		{
			if( m_pUsers[i] == NULL || m_pUsers[i] == pUser )
				continue;
			for( int j = i + 1; j < m_iUserNum; ++ j )
			{
				if( m_pUsers[j] == NULL )
					continue;
				if( strcmp( m_pUsers[i]->m_szIP, m_pUsers[j]->m_szIP ) == 0 )
					//return ERR_ENTERTABLE_HAVE_SAMEIP;
					return -1;
			}
		}
	}
	for( int i = 0; i < m_iUserNum; ++ i )
	{
		if( m_pUsers[i] == NULL || m_pUsers[i] == pUser )
			continue;
		if( m_pUsers[i]->m_bSameIP )
		{
			for( int j = 0; j < m_iUserNum; ++ j )
			{
				if( j == i || pUser == m_pUsers[j] || m_pUsers[j] == NULL )
					continue;
				if( strcmp( m_pUsers[j]->m_szIP, pUser->m_szIP ) == 0 )
					//return ERR_ENTERTABLE_NOWELCOME;
					return -1;
			}
			break;
		}
	}

	for( int i = 0; i < m_iUserNum; ++ i )
	{
		if( m_pUsers[i] == NULL || m_pUsers[i] == pUser )
			continue;
		if( m_pUsers[i]->m_bSameIP )
		{
			for( int j = 0; j < m_iUserNum; ++ j )
			{
				if( j == i || pUser == m_pUsers[j] || m_pUsers[j] == NULL )
					continue;
				if( strcmp( m_pUsers[j]->m_szIP, pUser->m_szIP ) == 0 )
//					return ERR_ENTERTABLE_NOWELCOME;
					return -1;
			}
			break;
		}
	}
//
//	float fUserDis = ( pUser->m_iDisconnect + pUser->m_iEscape ) / (float)( pUser->m_iWin + pUser->m_iLost + pUser->m_iDogfall + pUser->m_iEscape + pUser->m_iDisconnect ) * 100;
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( m_pUsers[i] == NULL || m_pUsers[i] == pUser )
//			continue;
//
//		//断线率比较
//		if( pUser->m_bDisconnect )
//		{
//			float dis = ( m_pUsers[i]->m_iDisconnect + m_pUsers[i]->m_iEscape ) /
//				(float)( m_pUsers[i]->m_iWin + m_pUsers[i]->m_iLost + m_pUsers[i]->m_iDogfall + m_pUsers[i]->m_iDisconnect + m_pUsers[i]->m_iEscape ) * 100;
//
//			if( dis > pUser->m_iDisconnectMin )
//				return ERR_ENTERTABLE_HAVE_DISCONNECT;
//		}
//		if( m_pUsers[i]->m_bDisconnect )
//		{
//			if( fUserDis > m_pUsers[i]->m_iDisconnectMin )
//				return ERR_ENTERTABLE_YOU_DISCONNECT;
//		}
//
//		//分差比较
//		if( pUser->m_bScoreDistance )
//		{
//			if( m_pRoom->GetScoreType() == SCORE_BEAN )
//			{
//				if( abs( (int)(pUser->m_lHappyBean - m_pUsers[i]->m_lHappyBean) ) > pUser->m_iScoreDistance )
//					return ERR_ENTERTABLE_HAVE_SCOREDIS;
//			}
//			else if( m_pRoom->GetScoreType() == SCORE_GOLD )
//			{
//				if( abs( (int)(pUser->m_lMoney - m_pUsers[i]->m_lMoney) ) > pUser->m_iScoreDistance )
//					return ERR_ENTERTABLE_HAVE_SCOREDIS;
//			}
//		}
//		if( m_pUsers[i]->m_bScoreDistance )
//		{
//			if( m_pRoom->GetScoreType() == SCORE_BEAN )
//			{
//				if( abs( (int)(pUser->m_lHappyBean - m_pUsers[i]->m_lHappyBean) ) > m_pUsers[i]->m_iScoreDistance )
//				return ERR_ENTERTABLE_YOU_SCOREDIS;
//			}
//			else if( m_pRoom->GetScoreType() == SCORE_GOLD )
//			{
//				if( abs( (int)(pUser->m_lMoney - m_pUsers[i]->m_lMoney) ) > m_pUsers[i]->m_iScoreDistance )
//				return ERR_ENTERTABLE_YOU_SCOREDIS;
//			}
//		}
//
//		//分数比较
//		if( pUser->m_bScoreMin )
//		{
//			if( m_pRoom->GetScoreType() == SCORE_BEAN )
//			{
//				if( m_pUsers[i]->m_lHappyBean < pUser->m_iScoreMin )
//				return ERR_ENTERTABLE_HAVE_SCOREMIN;
//			}
//			else if( m_pRoom->GetScoreType() == SCORE_GOLD )
//			{
//				if( m_pUsers[i]->m_lMoney < pUser->m_iScoreMin )
//				return ERR_ENTERTABLE_HAVE_SCOREMIN;
//			}
//		}
//		if( m_pUsers[i]->m_bScoreMin )
//		{
//			if( m_pRoom->GetScoreType() == SCORE_BEAN )
//			{
//				if( m_pUsers[i]->m_iScoreMin > pUser->m_lHappyBean )
//				return ERR_ENTERTABLE_YOU_SCOREMIN;
//			}
//			else if( m_pRoom->GetScoreType() == SCORE_GOLD )
//			{
//				if( m_pUsers[i]->m_iScoreMin > pUser->m_lMoney )
//				return ERR_ENTERTABLE_YOU_SCOREMIN;
//			}
//		}
//	}
//
//	//不受欢迎比较
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( !m_pUsers[i] || m_pUsers[i] == pUser )
//			continue;
//		for( int j = 0; j < m_pUsers[i]->m_NoWelcome.Num(); ++ j )
//		{
//			if( m_pUsers[i]->m_NoWelcome[j] == pUser->m_dwUserId )
//				return ERR_ENTERTABLE_NOWELCOME;
//		}
//	}
//
//	return ERR_ENTERTABLE_ACCEPT;

	return 0;
}

void CBaseTable::OnUserLeave( int iChairId )
{
	//如果有人旁观此座，则退出旁观
//	for( int i = 0; i < m_iLookerNum; ++ i )
//	{
//		if( m_pLookers[i]->m_pLookAt->m_iChairId == iChairId )
//		{
//			PT_GAMESTATE_RESET_INFO data;
//			data.dwUserId = m_pLookers[i]->m_dwUserId;
//			data.iState = US_FREE;
//			g_ServerApp.SendToAgentServer( m_pLookers[i]->m_dwAgentIndex, &data, sizeof(data) );
//
//			PT_USER_LEAVE_TABLE_INFO data2;
//			data2.dwUserId = m_pLookers[i]->m_dwUserId;
//			data2.iChairId = m_pLookers[i]->m_iChairId;
//			if( m_pRoom->IsCanEnterTable() )
//				m_pRoom->SendToAllUser( &data2, sizeof(data2) );
//			else
//				SendToAllUser( &data2, sizeof(data2) );
//
//			m_pLookers[i]->m_iState = US_FREE;
//			m_pLookers[i]->m_iTableId = -1;///////解决旁观对象退出 导致客户端在该位置有用户信息存在的问题
//			memcpy( &m_pLookers[i], &m_pLookers[i+1], 4*( m_iLookerNum - i - 1 ) );
//			-- m_iLookerNum;
//			-- i;
//
//
//		}
//	}
}

bool CBaseTable::CanLookAt( int iChairId )
{
	//return false;//不允许旁观 禁止所有人

	/*if( !m_pRoom->IsCanEnterTable() )
		return false;*/

//	if( !m_pUsers[iChairId] )
//		return false;
//
//	return m_pUsers[iChairId]->m_bAcceptLookAt;

	return true;
}

void CBaseTable::LookAt( CUser * pLooker, int iChairId )
{

}

void CBaseTable::OnLookAt( CUser * pLooker )
{
//	if( m_bInGame && pLooker->m_dwLookAtId == m_pUsers[pLooker->m_iChairId]->m_dwUserId )
//	{
//		PT_USER_LOOK_AT_INFO data;
//		data.dwLookerId = pLooker->m_dwUserId;
//		data.dwUserId = pLooker->m_dwLookAtId;
//		m_pRoom->SendToAllUser( &data, sizeof(data), pLooker );
//
//		pLooker->m_pLookAt = m_pUsers[pLooker->m_iChairId];
//		m_pLookers[m_iLookerNum] = pLooker;
//		++ m_iLookerNum;
//	}
//	else
//	{
//		pLooker->m_iState = US_FREE;
//		pLooker->m_iTableId = -1;
//		pLooker->m_iChairId = -1;
//	}
}

void CBaseTable::LookAtCancel( CUser * pLooker )
{
//	for( int i = 0; i < m_iLookerNum; ++ i )
//	{
//		if( m_pLookers[i] == pLooker )
//		{
//			PT_GAMESTATE_RESET_INFO data;
//			data.dwUserId = m_pLookers[i]->m_dwUserId;
//			data.iState = US_FREE;
//			g_ServerApp.SendToAgentServer( m_pLookers[i]->m_dwAgentIndex, &data, sizeof(data) );
//
//			memcpy( &m_pLookers[i], &m_pLookers[i+1], ( m_iLookerNum - i - 1 )*4 );
//			-- m_iLookerNum;
//			break;
//		}
//	}
}

void CBaseTable::SendToAllUser( void * data, unsigned int size, CUser * pExcept, bool bToLooker )
{

}

void CBaseTable::UserApplyExit( CUser * pUser )
{
//	m_bSended = false;
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( !m_pUsers[i] )
//			continue;
//
//		/*if(m_pUsers[i]->m_dwUserId == pUser->m_dwUserId )
//			m_pUsers[i]->m_bAcceptExit = true;
//		else
//			m_pUsers[i]->m_bAcceptExit = false;*/
//	}
//
//	PT_USER_APPLY_EXIT_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	SendToAllUser(  &data, sizeof(data), pUser );
}

void CBaseTable::SendPlaceInfo()
{
//	PT_MATCH_PLACE_INFO data;
//	for( int i = 0; i < m_iUserNum; i++ )
//	{
//		if( !m_pUsers[i] )
//			continue;
//		data.iPlace = m_pRoom->GetPlace( m_pUsers[i]->m_dwUserId );
//		data.dwUserId = m_pUsers[i]->m_dwUserId;
//		data.iMatchScore = m_pUsers[i]->m_iMatchScore;
//		SendToAllUser( &data, sizeof(data) );
//	}
}
void CBaseTable::UserApplyExitRevert( CUser * pUser, CUser * pOther )
{
	pUser->m_bAcceptExit = true;
	bool flag = true;
	for( int i = 0; i < m_iUserNum; i++ )
	{
		if( !m_pUsers[i] )
			continue;
		if( m_pUsers[i]->m_dwUserId == pOther->m_dwUserId )
			continue;
		if( m_pUsers[i] &&  m_pUsers[i]->m_bAcceptExit == false )
			flag = false;
	}
	if( flag )
	{
		pOther->m_bAcceptExit = true ;
//		PT_APPLY_EXIT_REVERT_INFO data;
//		data.bAccess = true;
//		data.dwUserId = pOther->m_dwUserId;
//		g_ServerApp.PostSend( pOther->m_dwAgentIndex,  &data, sizeof(data) );
	}
}

bool CBaseTable::StartGame()
{
	/*m_bSended = false;
	PT_GAMESTATE_RESET_INFO data;
	for( int i = 0; i < m_iUserNum; ++ i )
	{
		if( !m_pUsers[i] )
			continue;
		m_pUsers[i]->m_iState = US_INGAME;
		m_pUsers[i]->m_bAcceptExit = false;
		data.iState = US_INGAME;
		data.dwUserId = m_pUsers[i]->m_dwUserId;
		g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data, sizeof(data) );
	}*/

//	PT_GAME_START_INFO data2;
//	data2.dwTableId = m_dwId;
//	if( m_pRoom->IsCanSeeOtherUser() )
//		m_pRoom->SendToAllUser( &data2, sizeof(data2) );
//
//	m_dwTime = GetTickCount();

//	if( m_pRoom->GetScoreType() == SCORE_MATCH )
//	{
//		CBaseTable::MatchStart();
//	}

	return true;
}



void CBaseTable::EndGame()
{

//	m_dwTime = GetTickCount() - m_dwTime;
//
//	if( m_pRoom->GetScoreType() != SCORE_MATCH )///比赛不计游戏时间
//	{
//		PT_UPDATE_GAMETIME_INFO data9;
//		data9.dwTime = m_dwTime;
//		if( m_pRoom->GetScoreType() == SCORE_GOLD )
//			data9.bMoneyType = true;
//		else
//			data9.bMoneyType = false;
//
//		for( int i = 0; i < m_iUserNum; ++ i )
//		{
//			if( !m_pUsers[i] )
//				continue;
//
//			data9.dwUserId = m_pUsers[i]->m_dwUserId;
//
//			g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data9, sizeof(data9) );
//		}
//	}
//
//
//
//	PT_GAMESTATE_RESET_INFO data2;
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( !m_pUsers[i] )
//			continue;
//		m_pUsers[i]->m_bAcceptExit = false;
//		if( m_dwForceUserId > 0 && m_pUsers[i]->m_dwUserId == m_dwForceUserId )
//		{
//			m_pUsers[i]->m_iState = US_FREE;
//			data2.iState = US_FREE;
//		}
//		else
//		{
//			m_pUsers[i]->m_iState = US_INTABLE;
//			data2.iState = US_INTABLE;
//		}
//		data2.dwUserId = m_pUsers[i]->m_dwUserId;
//		g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data2, sizeof(data2) );
//	}
//
//
//	m_bInGame = false;
//
//	PT_GAME_END_INFO data;
//	data.dwTableId = m_dwId;
//	if( m_pRoom->IsCanSeeOtherUser() )
//		m_pRoom->SendToAllUser( &data, sizeof(data) );
//	else
//		SendToAllUser( &data, sizeof(data) );
//
//	//update Agent and save login
//	for( int i = 0; i < m_iUserNum; i++ )
//	{
//		PT_UPDATE_USER_COMMON_DATA_INFO data3;
//		data3.dwUserId = m_pUsers[i]->m_dwUserId;
//		data3.dwFlower = m_pUsers[i]->m_dwFlower;
//		data3.lHappyBean = m_pUsers[i]->m_lHappyBean;
//		data3.lMoney = m_pUsers[i]->m_lMoney;
//		g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data3, sizeof(data3) );
//	}

	KillTimer();

}

bool CBaseTable::IsInTable( CUser * pUser )
{
	if( !pUser )
		return false;

	for( int i = 0; i < m_iUserNum; ++ i )
	{
		if( pUser == m_pUsers[i] )
			return true;
	}

	for( int i = 0; i < m_iLookerNum; ++ i )
	{
		if( pUser == m_pLookers[i] )
			return true;
	}

	return false;
}
//收税后调用
void CBaseTable::Bouns( float fTex )
{
//	if( !g_pGameManager->m_bBounsIsOpen )
//		return;
//
//	PT_ADD_BONUS_INFO data;
//	data.fBonus = fTex / 100 * g_pGameManager->m_fTex;
//	g_ServerApp.SendToDataServer( &data, sizeof(data) );
}
