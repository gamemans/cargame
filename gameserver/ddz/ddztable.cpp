/*
 * CDdz.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#include "ddztable.h"

#include "stdlib.h"
#include <assert.h>
CDDZ_Table::CDDZ_Table( int iUserNum ):CBaseTable( iUserNum )
{
	for( int i = 0; i < 54; ++ i )
		m_wPai[i] = i;
	//m_wPai[i] = 13 * (i % 4) + i / 4;
	//m_wPai[52] = 52;
	//m_wPai[53] = 53;

	m_iDiZhu = -1;
	//m_bFirst = true;
	m_bInGame = false;

	m_iNumOfBomb = 0;
	m_iNumOfRocket = 0;
	m_iChunTianOrFanChun = 1;


}

CDDZ_Table::~CDDZ_Table(void)
{
}

bool CDDZ_Table::StartGame()
{
	CBaseTable::StartGame();

#ifdef DDZ_DEBUG
	g_strText.Format( L"斗地主 %s 第 %d 桌 开局\n", m_pRoom->GetName(), m_dwId );
	Print( g_strText.GetBuffer() );
#endif

	ResetTablePai();
	//洗牌
	Shuffle();
	//玩家数据初始化
	for( int i = 0; i < 3; ++ i )
	{
		m_pUsers[i]->m_iState = US_INGAME;

		memcpy( m_UserInfo[i].m_wPai, &m_wPai[m_iNext], sizeof( int ) * 17 );
		m_iNext += 17;

		m_UserInfo[i].m_bIsDiZhu = false;
		m_UserInfo[i].m_wPaiNum = 17;
		m_UserInfo[i].m_iJiaoFen = -1;
		m_UserInfo[i].m_wDaPaiNum = 0;
		m_UserInfo[i].m_iChuPaiNum = 0;
	}
	//init
	m_iNumOfBomb = 0;
	m_iNumOfRocket = 0;
	m_iChunTianOrFanChun = 1;

	m_iPassCount = 2;

	m_iCurJiaoFen = -1;
	m_bHasDiZhu = false;

	//random
	int num = rand() % 3;
	m_dwCurUser = num;



	m_bInGame = true;
	//data statrt
//	PT_DDZ_GAME_START_INFO data;
//	data.wNum = num;
//	SendToAllUser( &data, sizeof(data) );

	//data1 pai
//	PT_DDZ_PAI_INFO data1;
//	for( int i = 0; i < 3; ++ i )
//	{
//		data1.dwUserId = m_pUsers[i]->m_dwUserId;
//		memcpy( data1.wPai, m_UserInfo[i].m_wPai, sizeof(int) * 17 );
//		g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data1, sizeof(data1) );
//	}
//
//	for( int i = 0; i < m_iLookerNum; ++ i )
//	{
//		data1.dwUserId = m_pLookers[i]->m_dwUserId;
//		memcpy( data1.wPai, m_UserInfo[m_pLookers[i]->m_pLookAt->m_iChairId].m_wPai, sizeof(int) * 17 );
//		g_ServerApp.SendToAgentServer( m_pUsers[i]->m_dwAgentIndex, &data1, sizeof(data1) );
//	}


	if( m_pUsers[m_dwCurUser]->m_bDrop )
		SetTimer( 1000, TIMER_WAIT_JIAOFEN );
	else
		SetTimer( WAIT_DDZ_JIAOFEN_TIME, TIMER_WAIT_JIAOFEN );

	return true;
}
void CDDZ_Table::OnTimer()
{
	CBaseTable::OnTimer();

	if( !m_bInGame )
		return;
	switch( m_iTimerType )
	{

	case TIMER_WAIT_JIAOFEN:
		{
//			PT_DDZ_JIAOPAI_CHECK_INFO data;
//			data.dwRoomId = m_pRoom->GetId();
//			if( m_pUsers[m_dwCurUser] )
//			{
//				data.dwTableId = m_pUsers[m_dwCurUser]->m_iTableId;
//				data.dwUserId = m_pUsers[m_dwCurUser]->m_dwUserId;
//			}
//			else
//				break;
//			data.wNum = 0;
//			g_ServerApp.PostMsg( FORCE_MSG, &data, sizeof(data) );
		}
		break;
	case TIMER_WAIT_DAPAI:
		{

			if( m_iPassCount == 2 )
			{
//				PT_DDZ_CHUPAI_CHECK_INFO data;
//				data.dwRoomId = m_pRoom->GetId();
//				if( m_pUsers[m_dwCurUser] )
//				{
//					data.dwTableId = m_pUsers[m_dwCurUser]->m_iTableId;
//					data.dwUserId = m_pUsers[m_dwCurUser]->m_dwUserId;
//				}
//				else
//					break;
//				data.wNum = 1;
//				data.wPai[0] = m_UserInfo[m_dwCurUser].m_wPai[0];
//				g_ServerApp.PostMsg( FORCE_MSG, &data, sizeof(data) );
			}
			else
			{
//				PT_DDZ_PASS_CHECK_INFO data;
//				data.dwRoomId = m_pRoom->GetId();
//				if( m_pUsers[m_dwCurUser] )
//				{
//					data.dwTableId = m_pUsers[m_dwCurUser]->m_iTableId;
//					data.dwUserId = m_pUsers[m_dwCurUser]->m_dwUserId;
//				}
//				else
//					break;
//				g_ServerApp.PostMsg( FORCE_MSG, &data, sizeof(data) );
			}

		}
		break;
	}
}
void CDDZ_Table::SetTimer( unsigned int dwElapse, int iType, bool bOnce )
{
	m_Timer.SetTimer( dwElapse, bOnce );
	m_iTimerType = iType;
}
void CDDZ_Table::KillTimer()
{
	//m_Timer.KillTimer();
}


void CDDZ_Table::MatchStart()
{


}
void CDDZ_Table::EndGame()
{
	CBaseTable::EndGame();


#ifdef DDZ_DEBUG
	g_strText.Format( L"斗地主 %s 第 %d 桌 结束\n", m_pRoom->GetName(), m_dwId );
	Print( g_strText.GetBuffer() );
#endif

	//PT_DDZ_GAME_END_INFO data;
	//data.dwTableId = m_dwId;
	//for( int i = 0; i < 3; i++ )
	//{
	//	data.wNum[i] = m_UserInfo[i].m_wPaiNum;
	//	memcpy( data.wPai[i], m_UserInfo[i].m_wPai, sizeof(int) * m_UserInfo[i].m_wPaiNum );
	//}
	//m_pRoom->SendToAllUser( &data, sizeof(data) );


//	PT_UPDATE_SCORE_INFO data3;
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( !m_pUsers[i] )
//			continue;
//		data3.lHappyBean = m_pUsers[i]->m_lHappyBean;
//		data3.lMoney = m_pUsers[i]->m_lMoney;
//		data3.iScore = m_pUsers[i]->m_iScore;
//		data3.dwUserId = m_pUsers[i]->m_dwUserId;
//		data3.dwWin = m_pUsers[i]->m_iWin;
//		data3.dwLost = m_pUsers[i]->m_iLost;
//		data3.dwDogfall = 0;
//
//		if( m_pRoom->IsCanSeeOtherUser() )
//			m_pRoom->SendToAllUser( &data3, sizeof(data3) );
//		else
//			SendToAllUser( &data3, sizeof(data3) );
//	}

	SaveUserGameInfo();

//	//不够分踢出
//	switch( m_pRoom->GetScoreType() )
//	{
//	case SCORE_BEAN:
//		{
//			for( int i = 0; i < m_iUserNum; ++ i )
//			{
//				if( m_pUsers[i]->m_lHappyBean < m_pRoom->GetMinScore() )
//					m_pRoom->KickOut( m_pUsers[i]->m_dwUserId, ERR_FORCE_LEAVE_ROOM_NOTENOUGHBEAN );
//			}
//		}
//		break;
//	case SCORE_GOLD:
//		{
//			for( int i = 0; i < m_iUserNum; ++ i )
//			{
//				if( m_pUsers[i]->m_lMoney < m_pRoom->GetMinScore() )
//					m_pRoom->KickOut( m_pUsers[i]->m_dwUserId, ERR_FORCE_LEAVE_ROOM_NOTENOUGHMONEY );
//			}
//		}
//		break;
//	}
//	//断线踢出
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		if( m_pUsers[i] && m_pUsers[i]->m_bDrop && m_pRoom->m_iScoreType != SCORE_MATCH )
//			m_pRoom->KickOut( m_pUsers[i]->m_dwUserId, ERR_FORCE_LEAVE_ROOM_DISCONNECT );
//	}
}

void CDDZ_Table::OnUserLeave( int iChairId )
{
	CBaseTable::OnUserLeave( iChairId );
}
void CDDZ_Table::OnLookAt( CUser * pLooker )
{
	CBaseTable::OnLookAt( pLooker );

//	//发送当前游戏信息给观看者
//	if( m_bInGame && pLooker->m_iState == US_LOOKAT )
//	{
//		PT_DDZ_LOOK_AT_INFO data;
//		data.iCurUser = m_dwCurUser;
//		for( int i = 0; i < 3; i++ )
//		{
//			data.wCardNum[i] = m_UserInfo[i].m_wPaiNum;
//
//			if( m_UserInfo[i].m_bIsDiZhu )
//				data.iDiZhu = i;
//		}
//		if( data.iDiZhu != -1 )
//		{
//			data.iFen = m_iCurJiaoFen;//如果已有地主，把地主叫的分 和　底牌发出去
//			memcpy( data.wDiZhuPai, &m_wPai[51], sizeof( int) * 3 );
//		}
//		else
//			data.iFen = -1;
//
//		memcpy( data.wPai, m_UserInfo[pLooker->m_pLookAt->m_iChairId].m_wPai, sizeof(int) * m_UserInfo[pLooker->m_pLookAt->m_iChairId].m_wPaiNum );
//
//		data.iBei = (int)pow( 2, m_iNumOfBomb + m_iNumOfRocket );
//
//		for( int j = 0; j < AGENT_SERVER_NUM; ++ j )
//		{
//			if( pLooker->m_dwAgentIndex == g_pServerManager->m_ServerList[j].dwConnectIndex )
//			{
//				g_ServerApp.m_PackedMsgInfo[j].SetMsg( (char *)(&data), sizeof(data) );
//				g_ServerApp.m_PackedMsgInfo[j].AddUser( pLooker->m_dwUserId );
//				g_ServerApp.SendToAgentServer( g_pServerManager->m_ServerList[j].dwConnectIndex, &g_ServerApp.m_PackedMsgInfo[j], g_ServerApp.m_PackedMsgInfo[j].GetSize() );
//				g_ServerApp.m_PackedMsgInfo[j].ResetMsg();
//				break;
//			}
//		}
//	}
}
void CDDZ_Table::OnUserRejoin( CUser * pUser )
{
//	PT_DDZ_REJOIN_DATA_INFO data;
//	data.iCurUser = m_dwCurUser;
//	for( int i = 0; i < 3; i++ )
//	{
//		data.wCardNum[i] = m_UserInfo[i].m_wPaiNum;
//
//		if( m_UserInfo[i].m_bIsDiZhu )
//			data.iDiZhu = i;
//	}
//	if( data.iDiZhu != -1 )
//	{
//		data.iFen = m_iCurJiaoFen;//如果已有地主，把地主叫的分 和　底牌发出去
//		memcpy( data.wDiZhuPai, &m_wPai[51], sizeof( int) * 3 );
//
//		data.wTabNum = m_iTabPaiNum;
//		memcpy( data.wTabPai, m_CurTabPai, sizeof( int ) * m_iTabPaiNum );
//		data.iChuPaiUser = m_iChuPaiUser;
//	}
//	else
//		data.iFen = -1;
//
//	memcpy( data.wPai, m_UserInfo[pUser->m_iChairId].m_wPai, sizeof(int) * m_UserInfo[pUser->m_iChairId].m_wPaiNum );
//
//	data.iBei = (int)pow( 2, m_iNumOfBomb + m_iNumOfRocket + m_iChunTianOrFanChun );
//
//	for( int j = 0; j < AGENT_SERVER_NUM; ++ j )
//	{
//		if( pUser->m_dwAgentIndex == g_pServerManager->m_ServerList[j].dwConnectIndex )
//		{
//			g_ServerApp.m_PackedMsgInfo[j].SetMsg( (char *)(&data), sizeof(data) );
//			g_ServerApp.m_PackedMsgInfo[j].AddUser( pUser->m_dwUserId );
//			g_ServerApp.SendToAgentServer( g_pServerManager->m_ServerList[j].dwConnectIndex, &g_ServerApp.m_PackedMsgInfo[j], g_ServerApp.m_PackedMsgInfo[j].GetSize() );
//			g_ServerApp.m_PackedMsgInfo[j].ResetMsg();
//			break;
//		}
//	}
}

void CDDZ_Table::SaveUserGameInfo()
{
	/*if( m_pRoom->GetScoreType() != SCORE_BEAN )
		return;*/

//	PT_DDZ_UPDATE_ONE_USER_DATA_INFO data;
//
//	CUser * pUser;
//	for( int i = 0; i < m_iUserNum; ++ i )
//	{
//		pUser = m_pUsers[i];
//		if( pUser )
//		{
//			data.data.dwDisconnect = pUser->m_iDisconnect;
//			data.data.dwDogfall = 0;
//			data.data.dwEscape = pUser->m_iEscape;
//			data.data.dwLost = pUser->m_iLost;
//			data.data.dwUserId = pUser->m_dwUserId;
//			data.data.dwWin = pUser->m_iWin;
//			data.data.iScore = pUser->m_iScore;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//		}
//	}
}



// 发牌
bool CDDZ_Table::SendCard(void)
{



	return false;
}
// 洗牌
void CDDZ_Table::Shuffle( int num )
{
	int index;
	for( int i = 0; i < 54; i++ )
	{
		index  = rand() % 54;
		if( index == i )
			continue;
		m_wPai[i] ^= m_wPai[index];
		m_wPai[index] ^= m_wPai[i];
		m_wPai[i] ^= m_wPai[index];
	}

	//勿删

	//====测试用，a,b,c 分别为三家要的牌Ｉｄ，不要的牌用－１，系统自动填充
	/*int a[20] = {6, 19, 32, 7, 20, 33, 5, 18, 8, 21, -1, -1, -1, -1, -1, -1, -1  }, b[20] = { 9, 10, 22, 23, 35, 36, 3, 16, 12, 25, -1, -1, -1, -1, -1, -1, -1 }, c[20] = {};

	{
		int i, j;
		for( int k = 0; k < 17; k ++ )
		{
			if( a[k] == -1 )
			{

				bool bb;

				for( j = 0; j < 54; j++ )
				{
					bb = false;
					for( i = 0; i < 17; i ++ )
					{
						if( a[i] == m_wPai[j] && a[i] !=-1 || b[i] == m_wPai[j] && b[i] != -1 )
						{
							bb = true;
							break;
						}
					}
					if( !bb )
						break;
				}
				if( !bb )
				{
					a[k] = m_wPai[j];
				}
			}
		}
		for( int k = 0; k < 17; k ++ )
		{
			if( b[k] == -1 )
			{
				bool bb;
				for( j = 0; j < 54; j++ )
				{
					bb = false;
					for( i = 0; i < 17; i ++ )
					{
						if( a[i] == m_wPai[j] && a[i] !=-1 || b[i] == m_wPai[j] && b[i] != -1 )
						{
							bb = true;
							break;
						}

					}
					if( !bb )
						break;
				}
				if( !bb )
				{
					b[k] = m_wPai[j];
				}
			}
		}
		for( int k = 0; k < 17; k ++ )
		{

			bool bb;

			for( j = 0; j < 54; j++ )
			{
				bb = false;
				for( i = 0; i < 17; i ++ )
				{
					if( a[i] == m_wPai[j] && a[i] !=-1 || b[i] == m_wPai[j] && b[i] != -1 || c[i] == m_wPai[j])
					{
						bb = true;
						break;
					}

				}

				if( !bb )
					break;
			}
			if( !bb )
			{
				c[k] = m_wPai[j];
			}

		}

		for( int i = 0; i < 17; i++ )
		{
			m_wPai[i] = a[i];
			m_wPai[i+17] = b[i];
			m_wPai[i+34] = c[i];

		}
	}*/

	m_iNext = 0;
	m_iLast = 54;

	memset( m_CurTabPai, 0, sizeof( int ) * 20 );
	m_iTabPaiNum = 0;
	m_iChuPaiUser = -1;
}
void CDDZ_Table::ResetTablePai()
{
	memset( m_CurTabPai, 0, sizeof( int ) * 20 );
	m_iTabPaiNum = 0;
	m_iChuPaiUser = -1;
}
void CDDZ_Table::PassPai( CUser * pUser )
{
	if( !m_bInGame || !m_bHasDiZhu)
		return;
	if( m_iPassCount == 2 )
		return;

	if( pUser != m_pUsers[m_dwCurUser] )
		return;

//	PT_DDZ_USER_PASS_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	SendToAllUser( &data, sizeof( data ) );

	/*CString str;
	str.Format( L"%s过牌\n",pUser->m_szUserName );
	Print( str.GetBuffer() );*/

	m_iPassCount++;
	MoveCurPointer();

	if( m_pUsers[m_dwCurUser]->m_bDrop )
		SetTimer( 1000, TIMER_WAIT_DAPAI );
	else
		SetTimer( WAIT_DDZ_DAPAI_TIME, TIMER_WAIT_DAPAI );

	if( m_iPassCount == 2 )
	{
		ResetTablePai();
	}
}
//打立出局
void CDDZ_Table::MatchOut()
{

}
void CDDZ_Table::MoveAbandonCardToArrayLast( CUser * pUser, int AbandonPai[], int AbandonNum )
{
	int id = pUser->m_iChairId;

	for( int j = 0; j < AbandonNum; j ++ )
	{
		for( int i = 0; i < m_UserInfo[id].m_wPaiNum; i++ )
		{
			if( m_UserInfo[id].m_wPai[i] == AbandonPai[j] )
			{
				m_UserInfo[id].m_wPai[i] = 99;
				break;
			}
		}
	}

	for( int i = 0; i < m_UserInfo[id].m_wPaiNum - 1; i++ )
	{
		int k = i;
		for( int j = i + 1; j < m_UserInfo[id].m_wPaiNum; j++ )
		{
			if( m_UserInfo[id].m_wPai[k] > m_UserInfo[id].m_wPai[j] )
				k = j;
		}
		if( k != i )
		{
			int tmp = m_UserInfo[id].m_wPai[k];
			m_UserInfo[id].m_wPai[k] = m_UserInfo[id].m_wPai[i];
			m_UserInfo[id].m_wPai[i] = tmp;
		}
	}

	m_UserInfo[pUser->m_iChairId].m_wPaiNum -= AbandonNum;
}
void CDDZ_Table::ChuPai( CUser * pUser, int pai[], int num )
{
	if( !m_bInGame || !m_bHasDiZhu )
		return;
	if( pUser != m_pUsers[m_dwCurUser] )
		return;

assert(num>0);

	if( ChuPaiCheck( pUser, pai, num ) )
	{
		MoveCurPointer();

		//==
		MoveAbandonCardToArrayLast( pUser, pai, num );

//		PT_DDZ_USER_CHUPAI_INFO data;
//		data.wNum = num;
//		data.dwUserId = pUser->m_dwUserId;
//		memcpy( data.wPai, pai, sizeof( int ) * num );
//
//		for( int i = 0; i < num; i++ )
//		{
//			SDDZPai * p = GetDDZPaiInfo( pai[i] );
//
//
//		}
//
//		SendToAllUser( &data, sizeof( data ) );

		/*CString str;
		str.Format( L"%s出牌\n",pUser->m_szUserName );
		Print( str.GetBuffer() );*/

		if( m_pUsers[m_dwCurUser]->m_bDrop )
			SetTimer( 1000, TIMER_WAIT_DAPAI );
		else
			SetTimer( WAIT_DDZ_DAPAI_TIME, TIMER_WAIT_DAPAI );


		m_UserInfo[pUser->m_iChairId].m_iChuPaiNum++;

		m_iPassCount = 0;

		if( m_UserInfo[pUser->m_iChairId].m_wPaiNum == 0 )
		{
			if( m_UserInfo[pUser->m_iChairId].m_bIsDiZhu  )
			{
				//地主胜
				for( int i = 0; i < 3; i++ )
				{
					if( pUser->m_iChairId == i )
						continue;

					if( m_UserInfo[i].m_iChuPaiNum > 0 )
					{
						m_iChunTianOrFanChun = 0;
						break;
					}
				}
			}
			else
			{
				//农民胜
				for( int i = 0; i < 3; i++ )
				{
					if( pUser->m_iChairId == i || !m_UserInfo[i].m_bIsDiZhu )
						continue;

					if( m_UserInfo[i].m_iChuPaiNum > 1 )
					{
						m_iChunTianOrFanChun = 0;
						break;
					}
				}
			}

			WinBalance( m_UserInfo[pUser->m_iChairId].m_bIsDiZhu );
			EndGame();
		}

	}
	else
	{
//		PT_DDZ_CHUPAI_REVERT_INFO data;
//		data.dwUserId = pUser->m_dwUserId;
//		memcpy( data.wPai, pai, sizeof(int) * num );
//		data.wNum = num;
//		g_ServerApp.SendToAgentServer( pUser->m_dwAgentIndex, &data, sizeof(data) );

		return;
	}
}
void CDDZ_Table::WinBalance( bool bIsDiZhu )
{
//	int iNumOfBombPlusRocketPlusChunTian = m_iNumOfBomb + m_iNumOfRocket + m_iChunTianOrFanChun;
//	//int iBaseScore = ((CDDZ_Room *)m_pRoom)->GetBaseScore();
//	int iBaseScore = 0;
//	if( m_pRoom->m_iScoreType == SCORE_MATCH )
//	{
//		iBaseScore = m_iBaseScore;
//	}
//	else
//	{
//		iBaseScore = ((CDDZ_Room *)m_pRoom)->GetBaseScore();
//	}
//	double dTax = ((CDDZ_Room *)m_pRoom)->GetTax() / 100.0;//税率
//	int iScoreType = ((CDDZ_Room *)m_pRoom)->GetScoreType();
//
//	__int64 iDiZhuMoney = 0;
//	__int64 iNongMinMoney = 0;
//
//	__int64 LostMoney[3];
//
//	int iFinallyScore = m_iCurJiaoFen * (int)pow( 2, iNumOfBombPlusRocketPlusChunTian ) * iBaseScore;
//	for( int i = 0; i < 3; i++ )
//	{
//		m_UserInfo[i].m_dCountScore = 0;
//		if( m_UserInfo[i].m_bIsDiZhu )
//		{
//			if( iScoreType == SCORE_BEAN )
//			{
//				LostMoney[i] = m_pUsers[i]->m_lHappyBean >=  2 * iFinallyScore ? 2 * iFinallyScore : m_pUsers[i]->m_lHappyBean;
//			}
//			else if( iScoreType == SCORE_GOLD )
//			{
//				LostMoney[i] = m_pUsers[i]->m_lMoney >=  2 * iFinallyScore ? 2 * iFinallyScore : m_pUsers[i]->m_lMoney;
//			}
//			else if( iScoreType == SCORE_MATCH )
//			{
//				LostMoney[i] = 2 * iFinallyScore;
//			}
//		}
//		else
//		{
//			if( iScoreType == SCORE_BEAN )
//			{
//				LostMoney[i] = m_pUsers[i]->m_lHappyBean >= iFinallyScore ? iFinallyScore : m_pUsers[i]->m_lHappyBean;
//			}
//			else if( iScoreType == SCORE_GOLD )
//			{
//				LostMoney[i] = m_pUsers[i]->m_lMoney >=  iFinallyScore ? iFinallyScore : m_pUsers[i]->m_lMoney;
//			}
//			else if( iScoreType == SCORE_MATCH )
//			{
//				LostMoney[i] = iFinallyScore ;
//			}
//		}
//	}
//
//
//	PT_DDZ_BALANCE_INFO data;
//	data.iMultiple = (int)pow( 2, iNumOfBombPlusRocketPlusChunTian );
//	data.iScoreType = iScoreType;
//	data.iTax = (int)( dTax * 100 );
//	data.wBombNum = m_iNumOfBomb;
//	data.wRocketNum = m_iNumOfRocket;
//	data.wSpriteNum = m_iChunTianOrFanChun;
//	if( bIsDiZhu )
//		data.bWin = true;//表示地主ＷＩＮ
//	else
//		data.bWin = false;
//	for( int i = 0; i < 3; i++ )
//	{
//		if( m_UserInfo[i].m_bIsDiZhu )
//		{
//			if( bIsDiZhu )
//			{
//				for( int j = 0; j < 3; j ++ )
//				{
//					if( i == j )
//						continue;
//
//					m_UserInfo[i].m_dCountScore += LostMoney[j];
//				}
//				m_UserInfo[i].m_dCountScore *= ( 1 - dTax );
//
//
//				if( m_pRoom->GetScoreType() == SCORE_GOLD )
//					Bouns( m_UserInfo[i].m_dCountScore * ( dTax ));
//
//				if( m_pRoom->GetScoreType() != SCORE_MATCH )
//				{
//					m_pUsers[i]->m_iWin++;
//					m_pUsers[i]->m_iScore += 2 * m_iCurJiaoFen* (int)pow( 2, iNumOfBombPlusRocketPlusChunTian ) * iBaseScore;
//				}
//			}
//			else
//			{
//				m_UserInfo[i].m_dCountScore = -LostMoney[i];
//
//				if( m_pRoom->GetScoreType() != SCORE_MATCH )
//				{
//					m_pUsers[i]->m_iLost++;
//					m_pUsers[i]->m_iScore += 2 * m_iCurJiaoFen* (int)pow( 2, iNumOfBombPlusRocketPlusChunTian  ) * -1 * iBaseScore;
//				}
//			}
//		}
//		else
//		{
//			if( !bIsDiZhu )
//			{
//				for( int j = 0; j < 3; j++ )
//				{
//					if( m_UserInfo[j].m_bIsDiZhu )
//					{
//						m_UserInfo[i].m_dCountScore = LostMoney[j] / 2;
//						break;
//					}
//				}
//
//				m_UserInfo[i].m_dCountScore *= ( 1 - dTax );
//
//
//				//将税金放入奖池
//				if( m_pRoom->GetScoreType() == SCORE_GOLD )
//					Bouns( m_UserInfo[i].m_dCountScore * ( dTax ));
//
//				if( m_pRoom->GetScoreType() != SCORE_MATCH )
//				{
//					m_pUsers[i]->m_iWin++;
//					m_pUsers[i]->m_iScore += (int)pow( 2, iNumOfBombPlusRocketPlusChunTian ) * m_iCurJiaoFen* iBaseScore;
//				}
//			}
//			else
//			{
//				m_UserInfo[i].m_dCountScore = -LostMoney[i];
//
//				if( m_pRoom->GetScoreType() != SCORE_MATCH )
//				{
//					m_pUsers[i]->m_iLost++;
//					m_pUsers[i]->m_iScore += (int)pow( 2, iNumOfBombPlusRocketPlusChunTian ) * m_iCurJiaoFen* -1 * iBaseScore;
//				}
//			}
//		}
//
//		data.iScore[i] = int( m_UserInfo[i].m_dCountScore > 0 ?  m_UserInfo[i].m_dCountScore + 0.5 : m_UserInfo[i].m_dCountScore );
//		if( iScoreType == SCORE_BEAN )
//		{
//			m_pUsers[i]->m_lHappyBean += data.iScore[i];
//
//			if( m_pUsers[i]->m_lHappyBean < 0 )
//				m_pUsers[i]->m_lHappyBean = 0;
//
//		}
//		else if( iScoreType == SCORE_GOLD )
//		{
//			m_pUsers[i]->m_lMoney += data.iScore[i];
//
//			if( m_pUsers[i]->m_lMoney < 0 )
//				m_pUsers[i]->m_lMoney = 0;
//
//		}
//		else if( iScoreType == SCORE_MATCH )
//		{
//			m_pUsers[i]->m_iMatchScore += data.iScore[i];
//
//			/*if( m_pUsers[i]->m_iMatchScore < 0 )
//				m_pUsers[i]->m_iMatchScore = 0;*/
//		}
//
//		data.wNum[i] = m_UserInfo[i].m_wPaiNum;
//		memcpy( data.wPai[i], m_UserInfo[i].m_wPai, sizeof(int) * m_UserInfo[i].m_wPaiNum );
//	}
//
//	SendToAllUser( &data, sizeof(data) );

}
bool CDDZ_Table::HaveTheCard( CUser * pUser, int pai )
{
	int id = pUser->m_iChairId;
	for( int i = 0; i < m_UserInfo[id].m_wPaiNum; i++ )
	{
		if( m_UserInfo[id].m_wPai[i] == pai )
			return true;
	}
	return false;
}
// 出牌检测
bool CDDZ_Table::ChuPaiCheck( CUser * pUser, int pai[], int num )
{
	if( num != m_iTabPaiNum && num != 4 && num != 2 && m_iTabPaiNum != 0 )
	{
		return false;
	}

	for( int i = 0; i < num; i ++ )
	{
		if( !HaveTheCard( pUser, pai[i] ))
			return false;
	}

	memcpy( m_UserInfo[pUser->m_iChairId].m_DaPai, pai, sizeof( int ) * num );

	SDDZPai Card[20];
	for( int i = 0; i < num; i++ )
	{
		Card[i] = * GetDDZPaiInfo( m_UserInfo[pUser->m_iChairId].m_DaPai[i] );
	}


	SDDZPai TCard[20];
	for( int i = 0; i < m_iTabPaiNum; i++ )
	{
		TCard[i] = * GetDDZPaiInfo( m_CurTabPai[i] );
	}

	int iPaiSize, iTabPaiSize;//手中牌和桌面上的牌最小的牌（有效牌）值
	int iType = CheckPaiType( Card, num, iPaiSize );
	int iTabPaiType = CheckPaiType( TCard, m_iTabPaiNum, iTabPaiSize );

	if( iType != PAI_TYPE_NONE && m_iTabPaiNum == 0 )
	{
		memcpy( m_CurTabPai,  m_UserInfo[pUser->m_iChairId].m_DaPai, sizeof( int ) * num );//将当前桌面上的牌替换为手中牌
		m_iTabPaiNum = num;
		m_iChuPaiUser = pUser->m_iChairId;

		if( iType == PAI_TYPE_ROCKET )
		{
			m_iNumOfRocket = 1;
		}
		if( iType == PAI_TYPE_BOMB )
		{
			m_iNumOfBomb++;
		}
		return true;
	}
	if( iType == PAI_TYPE_ROCKET )
	{
		m_iNumOfRocket = 1;

		return true;
	}
	if( iTabPaiType == PAI_TYPE_ROCKET )
		return false;

	if( num == m_iTabPaiNum )
	{
		if( iType != iTabPaiType && iType != PAI_TYPE_BOMB )
			return false;
		else if( iType != iTabPaiType && iType == PAI_TYPE_BOMB )
		{
			m_iNumOfBomb++;
			return true;
		}
		else
		{
			if( iPaiSize > iTabPaiSize )
			{
				if( iType == PAI_TYPE_BOMB )
				{
					m_iNumOfBomb++;
				}
				memcpy( m_CurTabPai,  m_UserInfo[pUser->m_iChairId].m_DaPai, sizeof( int ) * num );//将当前桌面上的牌替换为手中牌
				m_iTabPaiNum = num;
				m_iChuPaiUser = pUser->m_iChairId;
				return true;
			}
		}
	}
	else
	{
		if( (iType == PAI_TYPE_ROCKET || iType == PAI_TYPE_BOMB) && iTabPaiType != PAI_TYPE_ROCKET )
		{
			if( iType == PAI_TYPE_BOMB )
			{
				m_iNumOfBomb++;
				memcpy( m_CurTabPai,  m_UserInfo[pUser->m_iChairId].m_DaPai, sizeof( int ) * num );//将当前桌面上的牌替换为手中牌
				m_iTabPaiNum = num;
				m_iChuPaiUser = pUser->m_iChairId;
			}
			return true;
		}
	}

	return false;
}

int CDDZ_Table::CheckPaiType( SDDZPai pai[], int num, int &PaiSize )
{
	if( num == 0 )
		return PAI_TYPE_NONE;

	SortCard( pai, num );
	if( num == 1 )
	{
		PaiSize = pai[0].value;
		return PAI_TYPE_SINGLE;
	}
	if( _IsRocket( pai, num ) )
		return PAI_TYPE_ROCKET;

	PaiSize = _Is2( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_DOUBLE;

	PaiSize = _Is3( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_THREE;

	PaiSize = _IsBomb( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_BOMB;

	PaiSize = _IsSanDaiYiSingle( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SANDAIYISINGLE;

	PaiSize = _IsSanDaiYiDouble( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SANDAIYIDOUBLE;

	PaiSize = _IsDanShun( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_DANSHUN;

	PaiSize = _IsShuangShun( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SHUANGSHUN;

	PaiSize = _IsSanShun( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SANSHUN;

	PaiSize = _IsPlaneSingle( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_PLANESINGLE;

	PaiSize = _IsPlaneDouble( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_PLANEDOUBLE;

	PaiSize = _IsSiDaiErSingle( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SIDAIERSINGLE;

	PaiSize = _IsSiDaiErDouble( pai, num );
	if( PaiSize != -1 )
		return PAI_TYPE_SIDAIERDOUBLE;

	return PAI_TYPE_NONE;
}
// 检测是否为火箭牌型
bool CDDZ_Table::_IsRocket( SDDZPai pai[], int num )
{
	if( num != 2)
		return false;

	if( pai[0].type == 4 && pai[1].type == 4 )
		return true;

	return false;
}

int CDDZ_Table::_Is2( SDDZPai pai[], int num )
{
	if( num != 2 )
		return -1;

	if( pai[0].value == pai[1].value )
		return pai[0].value;

	return -1;
}

int CDDZ_Table::_Is3( SDDZPai pai[], int num )
{
	if( num == 3 )
	{
		if( pai[0].value == pai[1].value && pai[0].value == pai[2].value )
			return pai[0].value;
	}

	return -1;
}

// 检测是否为炸弹牌型
int CDDZ_Table::_IsBomb( SDDZPai pai[], int num )
{
	if( num != 4 )
		return -1;

	int iPaiNum = pai[0].value;
	for( int i = 1; i < 4; i++ )
	{
		if( pai[i].value != iPaiNum )
			return -1;
    }
	return pai[0].value;
}

// 检测是否为单顺牌型
int CDDZ_Table::_IsDanShun( SDDZPai pai[], int num )
{
	if( num < 5 )
		return -1;

	int iPaiNum = pai[0].value;
	for( int i = 1; i < num; i ++ )
	{
			if( pai[i].value != (iPaiNum + i)%13 )
		{
			return -1;
		}
	}
	return pai[0].value;
}

// 检测是否为双顺牌型
int CDDZ_Table::_IsShuangShun( SDDZPai pai[], int num )
{
	if( num < 6 || num % 2 != 0 )
		return -1;

	if( pai[0].value != pai[1].value )
		return -1;

	int k = 0;
	int iPaiNum = pai[0].value;
	for( int i = 2; i < num; i += 2 )
	{
		k++;
	if( pai[i].value != (iPaiNum + k) % 13 )
			return -1;
	}
	iPaiNum = pai[1].value;
	k = 0;
	for( int i = 3; i < num; i += 2 )
	{
		k++;
		if( pai[i].value != (iPaiNum + k)%13 )
			return -1;
	}
	return pai[0].value;
}

// 检测是否为三顺牌型
int CDDZ_Table::_IsSanShun( SDDZPai pai[], int num )
{
	if( num < 6 || num % 3 != 0 )
		return -1;

	int iPaiNum = pai[0].value;
	for( int i = 0; i < num; i += 3 )
	{
		if( iPaiNum == pai[i+1].value && iPaiNum == pai[i+2].value && iPaiNum == pai[i].value)
			iPaiNum++; //需要判断　PaiNum == pai[i].num
		else
			return -1;
	}
	return pai[0].value;
}

// 检测是否为三带一牌型(单张)
int CDDZ_Table::_IsSanDaiYiSingle( SDDZPai pai[], int num )
{
	if( num != 4 )
		return -1;

	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 3 )
		return pai[0].value;
	else
		if( GetCardCountByCardNum( pai, num, pai[0].num ) == 1 )
			if( GetCardCountByCardNum( pai, num, pai[1].num ) == 3  )
				return pai[1].value;

	return -1;
}
// 检测是否为三带一牌型(对儿)
int CDDZ_Table::_IsSanDaiYiDouble( SDDZPai pai[], int num )
{
	if( num != 5 )
		return -1;

	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 3 )
	{
		if(  GetCardCountByCardNum( pai, num, pai[3].num ) == 2 && pai[3].type != 4 )//不能带一对儿王
			return pai[0].value;
	}
	else
	{
		if(  GetCardCountByCardNum( pai, num, pai[0].num ) == 2 && pai[0].type != 4 )
			if(  GetCardCountByCardNum( pai, num, pai[2].num ) == 3 )
				return pai[2].value;
	}

	return -1;
}

// 检测是否为飞机带翅膀牌型(单张)
int CDDZ_Table::_IsPlaneSingle( SDDZPai pai[], int num )
{
	if( num % 4 != 0 || num < 8 )
		return -1;

	int iLian = num / 4;	//记录一共可以连几次
	int iBegin = -1;		//三张牌开始的位置

	// 查找第一个三张牌的位置
	for( int i = 0; i < num; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) == 3 )
		{
			iBegin = i;
			break;
		}
	}

	if( iBegin == -1 )
		return -1;

	// 检测连牌是否全为３张,并且是否连续
	//int iPaiValue = pai[iBegin].value;
	//for( int i = iBegin + 3; i < iLian * 3 + iBegin; i += 3 )
	//{
	//	if( GetCardCountByCardNum( pai, num, pai[i].num ) != 3 )
	//		return -1;
	//	if( iPaiValue + 1 != pai[i].value )
	//		return -1;
	//	else
	//		iPaiValue++;
	//}

	for( int i = iBegin; i < iBegin + iLian * 3; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 3 )
		{
			return -1;
		}
	}

	for( int i = 0; i < iLian; i++ )
	{
		if( pai[iBegin].value + i != pai[iBegin + 3 * i].value )
			return  -1;
	}

	// 检测连牌的前面是否全为单张
	for( int i = 0; i < iBegin; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 1 )
			return -1;
	}
	// 检测连牌的后面是否全为单张
	for( int i = iBegin + iLian * 3; i < num; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 1 )
			return -1;
	}

	return pai[iBegin].value;
}
// 检测是否为飞机带翅膀牌型(对儿)
int CDDZ_Table::_IsPlaneDouble( SDDZPai pai[], int num )
{
	if( num % 5 != 0 || num < 10 )
		return -1;

	int iLian = num / 5;	//记录一共可以连几次
	int iBegin = -1;		//三张牌开始的位置

	for( int i = 0; i < num; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) == 3 )
		{
			iBegin = i;
			break;
		}
    }

	if( iBegin == -1 )
		return -1;

	for( int i = iBegin; i < iBegin + iLian * 3; i++ )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 3 )
		{
			return -1;
		}
	}

	for( int i = 0; i < iLian; i++ )
	{
		if( pai[iBegin].value + i != pai[iBegin + 3 * i].value )
			return  -1;

	}

	for( int i = 0; i < iBegin; i += 2 )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 2 )
			return -1;
	}

	for( int i = iBegin + iLian * 3; i < num; i += 2 )
	{
		if( GetCardCountByCardNum( pai, num, pai[i].num ) != 2 )
			return -1;
	}

	return pai[iBegin].value;
}

// 检测是否为四带二牌型(单张)
int CDDZ_Table::_IsSiDaiErSingle( SDDZPai pai[], int num)
{
	if( num != 6 )
		return -1;

	// 判断一张是单张并有四张相同时，即为是
	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 1
		&& GetCardCountByCardNum( pai, num, pai[2].num ) == 4 )
	{
		return pai[2].value;
	}
	if ( GetCardCountByCardNum( pai, num, pai[0].num ) == 4
		&& GetCardCountByCardNum( pai, num, pai[4].num ) == 1 )
	{
		return pai[0].value;
	}

	return -1;
}
// 检测是否为四带二牌型(对儿)
int CDDZ_Table::_IsSiDaiErDouble( SDDZPai pai[], int num)
{
	if ( num != 8 )
		return -1;

	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 2
		&& GetCardCountByCardNum( pai, num, pai[2].num ) == 2
		&& GetCardCountByCardNum( pai, num, pai[4].num ) == 4)
	{
		return pai[4].value;
	}

	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 2
		&& GetCardCountByCardNum( pai, num, pai[2].num ) == 4
		&& GetCardCountByCardNum( pai, num, pai[6].num ) == 2)
	{
		return pai[2].value;
	}

	if( GetCardCountByCardNum( pai, num, pai[0].num ) == 4
		&& GetCardCountByCardNum( pai, num, pai[4].num ) == 2
		&& GetCardCountByCardNum( pai, num, pai[6].num ) == 2 )
	{
		return pai[0].value;
	}

	return -1;
}

int CDDZ_Table::GetCardCountByCardNum( SDDZPai pai[], int num, int PaiNum )
{
	int wCount = 0;
	for( int i = 0; i < num; i++ )
	{
		if( pai[i].num == PaiNum )
			wCount++;
	}
	return wCount;
}

void CDDZ_Table::SortCard( SDDZPai Card[], int num )
{
	for( int i = 0; i < num - 1; i++ )
	{
		int k = i;
		for( int j = i + 1; j < num; j++ )
		{
			if( Card[k].value > Card[j].value )
				k = j;
		}
		if( k != i )
		{
			SDDZPai tmp = Card[k];
			Card[k] = Card[i];
			Card[i] = tmp;
		}
	}
}
void CDDZ_Table::MoveCurPointer()
{
	m_dwCurUser++;
	if( m_dwCurUser == 3 )
		m_dwCurUser = 0;
}
// 叫牌
void CDDZ_Table::JiaoPai( CUser * pUser, int num )
{
	if( m_bHasDiZhu || pUser->m_iChairId != m_dwCurUser )
		return;
	if( num <= m_iCurJiaoFen && num != 0 && m_iCurJiaoFen != -1)
		return;

	m_iCurJiaoFen = num;

//	PT_DDZ_USER_JIAOPAI_INFO data;
//	data.dwUserId = pUser->m_dwUserId;
//	data.wNum	  = num;
//
//	SendToAllUser( &data, sizeof(data) );


	MoveCurPointer();

	if( num == 3 )
	{
		SetDiZhu( pUser, num );
		return;
	}
	else
	{

	}
	m_UserInfo[pUser->m_iChairId].m_iJiaoFen = num;

	//检测有没有没叫过牌的玩家
	for( int i = 0; i < 3; i++ )
	{
		if( m_UserInfo[i].m_iJiaoFen == -1 )//有没叫分的玩家
		{
			if( m_pUsers[m_dwCurUser]->m_bDrop )
				SetTimer( 1000, TIMER_WAIT_JIAOFEN );
			else
				SetTimer( WAIT_DDZ_JIAOFEN_TIME, TIMER_WAIT_JIAOFEN );
			return;
		}
	}


	//检测是否所有玩家都叫的是０分（过）
	int itmp = 0;
	int k = 0;
	for( int i = 0; i < 3; i++ )
	{
		if( m_UserInfo[i].m_iJiaoFen > itmp )
		{
			itmp = m_UserInfo[i].m_iJiaoFen;
			k = i;
		}
	}

	//查找最高分的玩家
	CUser *pTmp;
	for( int i = 0; i < 3; i++ )
	{
		if( m_pUsers[i]->m_iChairId == k )
		{
			pTmp = m_pUsers[i];
			break;
		}
	}


	if (itmp == 0)		//全是０分则从重新开始
		StartGame();
	else
		SetDiZhu(pTmp, itmp);

}

void CDDZ_Table::SetDiZhu( CUser * pUser, int num )
{
	if( m_bHasDiZhu )
		return;
	m_iCurJiaoFen = num;


	m_bHasDiZhu = true;

	m_UserInfo[pUser->m_iChairId].m_bIsDiZhu = true;

	for( int i = 0; i < 3; i++ )
		m_UserInfo[i].m_iJiaoFen = num;

//	PT_DDZ_DZPAI_INFO data1;
//	data1.wScore = num;
//	data1.dwUserId = pUser->m_dwUserId;
//	memcpy( data1.wPai, &m_wPai[m_iNext], sizeof( int) * 3 );
//	SendToAllUser( &data1, sizeof( data1 ));

	m_dwCurUser = pUser->m_iChairId;

	memcpy( &m_UserInfo[pUser->m_iChairId].m_wPai[17], &m_wPai[m_iNext], sizeof( int) * 3  );
	m_iNext += 3;
	m_UserInfo[pUser->m_iChairId].m_wPaiNum = 20;

	if( m_pUsers[m_dwCurUser]->m_bDrop )
		SetTimer( 1000, TIMER_WAIT_DAPAI );
	else
		SetTimer( WAIT_DDZ_DAPAI_TIME, TIMER_WAIT_DAPAI );


}
//
//SDDZPai g_DDZPaiInfo[54];
//SDDZPai * GetDDZPaiInfo( int wId )
//{
//	for( int i = 0; i < 54; i++ )
//	{
//		if( g_DDZPaiInfo[i].id == wId )
//			return &g_DDZPaiInfo[i];
//	}
//	return NULL;
//}
