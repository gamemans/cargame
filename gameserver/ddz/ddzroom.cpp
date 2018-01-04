/*
 * ddzroom.cpp
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#include "ddzroom.h"


#include "ddzroom.h"


CDDZ_Room::CDDZ_Room(void)
{

}

CDDZ_Room::~CDDZ_Room(void)
{

}


void CDDZ_Room::UpdateAllUserInfo()
{
//	PT_DDZ_UPDATE_USER_DATA_INFO data;
//	int iNumLast = m_iCurUserNum;
//	int iNum = 0;
//	CUser * pUser = NULL;
//	for( POS pos = m_pUserList->GetFirstPos(); pos; )
//	{
//		pUser = m_pUserList->GetNext( pos );
//		if( !pUser )
//			continue;
//
//		SDDZUserData * pData = &data.data[iNum];
//		pData->dwDisconnect = pUser->m_iDisconnect;
//		pData->dwDogfall = pUser->m_iDogfall;
//		pData->dwEscape = pUser->m_iEscape;
//		pData->dwLost = pUser->m_iLost;
//		pData->dwWin = pUser->m_iWin;
//		pData->iScore = pUser->m_iScore;
//		pData->dwUserId = pUser->m_dwUserId;
//
//		++ iNum;
//		-- iNumLast;
//
//		if( iNum == 500 || iNumLast == 0 )
//		{
//			data.iNum = iNum;
//			g_ServerApp.SendToDataServer( &data, sizeof(data) );
//		}
//		if( iNum == 500 )
//			iNum = 0;
//		if( iNumLast == 0 )
//			break;
//	}
}





void CDDZ_Room::Init( unsigned int dwId, char * szName, int iTableNum, int iMaxUserNum )
{
	CBaseRoom::Init( dwId, szName, iTableNum, iMaxUserNum );

	SetChairNum( 3 );
	m_iForceExitBase = 25;

	for( int i = 0; i < iTableNum; i++ )
	{
		CBaseTable * p = new CDDZ_Table( 3 );
		p->SetId( i );
		p->SetBaseRoom( this );
		m_pTables.AddItem( p );
	}


}
//
//void CDDZ_Room::SetMatchPeopleNum()
//{
////	if( m_pPlayOfMatching.GetCount() > 36 )
////	{
////		m_iPeopleNum = 36;
////	}
////	else
////	{
////		m_iPeopleNum = 24;
////	}
//}
//


////打立出局
//void CDDZ_Room::MatchOut()
//{
//	if( m_iMatchMode == MATCH_ALL )
//	{
//		if( GetPlayerNumOfMatch() > m_iPeopleNum )
//		{
//			AutoAllotTable();//分配座位
//		}
//		else if( m_pPlayOfGaming.GetCount() == 0 )//所有人都玩完了
//		{
//			m_iCurMatchMode = MATCH_SCORE;
//
//			PT_MATCH_UPDATE_MODE_INFO data;
//			data.iMode = MATCH_SCORE;
//			SendToAllUser( &data, sizeof(data) );
//
//			m_iLunNum = 0;
//
//
//			SortMatchList();
//
//			SendPlaceList();
//
//			//将24名以后的出局
//			for( int i = m_pPlayOfMatching.GetCount() - 1; i >= 24; i-- )
//			{
//
//				MatchAwardInfo * pMatchAward = GetMatchAward( i+1 );
//				if( pMatchAward )
//				{
//					PT_MATCH_ADWARD_INFO data1;
//					data1.dwUserId = m_pPlayOfMatching[i]->m_dwUserId;
//					data1.iMoney = pMatchAward->iAwardNum;
//					data1.iPlace = i;
//					data1.iHonorNum = pMatchAward->iHonorNum;
//					_tcscpy( data1.szAward, pMatchAward->szAwardName );
//					g_ServerApp.SendToAgentServer( m_pPlayOfMatching[i]->m_dwAgentIndex, &data1, sizeof(data1) );
//
//					g_strText = "";
//					g_strText.Format( L"24之后%d--->%d\n", data1.dwUserId, data1.iPlace );
//					Print( g_strText.GetBuffer() );
//
//					PT_MATCH_UPDATE_BANK_MONEY_AND_HONOR_INFO data;
//					data.iHonor = pMatchAward->iHonorNum;
//					data.dwUserId = m_pPlayOfMatching[i]->m_dwUserId;
//					data.iMoney = pMatchAward->iAwardNum;//===竞赛资金
//					g_ServerApp.SendToAgentServer( m_pPlayOfMatching[i]->m_dwAgentIndex, &data, sizeof(data) );
//
//					m_pPlayOfMatching[i]->m_dwHonor += pMatchAward->iHonorNum;///更新勋章数
//				}
//					RemoveMatchToOut( m_pPlayOfMatching[i]->m_dwUserId );
//			}
//
//			m_iCurMatchPeopleNum = 24;
//
//			for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//			{
//				m_pPlayOfMatching[i]->m_iBout = 0;
//				if( m_pPlayOfMatching[i]->m_iMatchScore < 0 )
//				{
//					 m_pPlayOfMatching[i]->m_iMatchScore = 0;
//				}
//			}
//			ReSetCurMatch();
//		}
//		else
//		{
//			//等待所有人都玩完
//			return;
//		}
//	}
//	else
//		AutoAllotTable();//分配座位
//}
////定局积分
//void CDDZ_Room::MatchScore()
//{
//	if( m_iLunNum == 0 )
//	{
//		if( m_iMatchMode == MATCH_ALL )//经过了预赛
//		{
//			for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//			{
//				if( m_pPlayOfMatching[i]->m_iMatchScore <= 0 )
//				{
//					m_pPlayOfMatching[i]->m_iMatchScore = 0;
//				}
//				else
//				{
//					m_pPlayOfMatching[i]->m_iMatchScore = (int)sqrt( (float)(m_pPlayOfMatching[i]->m_iMatchScore * 12) );//折算积分
//				}
//			}
//
//			m_iBaseScore = 100;
//		}
//		AutoAllotTable();//分配座位
//		m_iLunNum++;
//	}
//	else
//	{
//		if( m_pPlayOfGaming.GetCount() == 0 )//游戏列表为空，说明所有人都结束了游戏
//		{
//			SortMatchList();
//
//			SendPlaceList();
//			int n = 0;
//			switch( m_iLunNum )
//			{
//			case 1://第一轮结束后
//				{
//					n = 12;
//				}
//				break;
//			case 2:
//				{
//					n = 6;
//				}
//				break;
//			case 3:
//				{
//					n = 1;
//				}
//				break;
//
//			}
//
//			m_iCurMatchPeopleNum = n;
//
//			//将n名以后的出局
//			for( int i = m_pPlayOfMatching.GetCount() - 1; i >= n; i-- )
//			{
//				MatchAwardInfo * pMatchAward = GetMatchAward( i+1 );
//				if( pMatchAward )
//				{
//					PT_MATCH_ADWARD_INFO data1;
//					data1.dwUserId = m_pPlayOfMatching[i]->m_dwUserId;
//					data1.iMoney = pMatchAward->iAwardNum;
//					data1.iPlace = i;
//					data1.iHonorNum = pMatchAward->iHonorNum;
//					_tcscpy( data1.szAward, pMatchAward->szAwardName );
//					g_ServerApp.SendToAgentServer( m_pPlayOfMatching[i]->m_dwAgentIndex, &data1, sizeof(data1) );
//
//					g_strText = "";
//					g_strText.Format( L"n之后%d--->%d\n", data1.dwUserId, data1.iPlace );
//					Print( g_strText.GetBuffer() );
//
//					PT_MATCH_UPDATE_BANK_MONEY_AND_HONOR_INFO data;
//					data.dwUserId = m_pPlayOfMatching[i]->m_dwUserId;
//					data.iHonor = pMatchAward->iHonorNum;
//					data.iMoney = pMatchAward->iAwardNum;//===竞赛资金
//					g_ServerApp.SendToAgentServer( m_pPlayOfMatching[i]->m_dwAgentIndex, &data, sizeof(data) );
//
//					m_pPlayOfMatching[i]->m_dwHonor += pMatchAward->iHonorNum;///更新勋章数
//
//				}
//				RemoveMatchToOut( m_pPlayOfMatching[i]->m_dwUserId );
//			}
//
//			for( int i = 0; i < m_pPlayOfMatching.GetCount(); i++ )
//			{
//				if( m_pPlayOfMatching[i]->m_iMatchScore <=0 )
//				{
//					m_pPlayOfMatching[i]->m_iMatchScore = 0;
//				}
//				else
//				{
//					m_pPlayOfMatching[i]->m_iMatchScore = m_pPlayOfMatching[i]->m_iMatchScore * 3 / 10;//折算积分
//				}
//			}
//
//			//重新分配并开始
//			AutoAllotTable();
//
//			m_iLunNum++;
//
//
//		}
//	}
//}
void CDDZ_Room::NowAllot()
{
//	while( m_pWaitGameUserList.GetCount() >= 3 )
//	{
//		//创建桌子
//		CDDZ_Table * pTable = new CDDZ_Table( 3 );
//		pTable->SetId( m_dwAllotTableId );
//		pTable->SetBaseRoom( this );
//		m_pAllotTables->Insert( m_dwAllotTableId, pTable );
//		++ m_dwAllotTableId;
//
//		//坐人
//		for( int i = 0; i < 3; ++ i )
//		{
//			int num = rand()%(int)m_pWaitGameUserList.GetCount();
//			CUser * pUser = m_pWaitGameUserList[num];
//			pTable->m_pUsers[i] = pUser;
//			pUser->m_iTableId = pTable->GetId();
//			pUser->m_iChairId = i;
//			pUser->m_iState = US_INTABLE;
//			m_pWaitGameUserList.RemoveAt( num );
//		}
//
//		PT_GAMESTATE_RESET_INFO data2;///解决随即金币区游戏开始后开始按钮还在的问题
//		for( int i = 0; i < 3; ++ i )
//		{
//			data2.dwUserId = pTable->m_pUsers[i]->m_dwUserId;
//			data2.iState = US_INTABLE;
//			g_ServerApp.SendToAgentServer( pTable->m_pUsers[i]->m_dwAgentIndex, &data2, sizeof(data2) );
//		}
//
//		PT_ALLOT_TABLE_USERS_INFO data;
//		data.iInfoNum = 3;
//		CUser * p;
//		for( int i = 0; i < 3; ++ i )
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
////			data.info[i].dwPropFlowerNum = p->m_dwPropFlowerNum;
//			data.info[i].dwPropHornBigNum = p->m_dwPropHornBigNum;
//			data.info[i].dwPropHornNum = p->m_dwPropHornNum;
////			data.info[i].dwPropVipBigNum = p->m_dwPropVipBigNum;
////			data.info[i].dwPropVipNum = p->m_dwPropVipNum;
////			data.info[i].dwPropVipSupperNum = p->m_dwPropVipSupperNum;
//			data.info[i].dwUserId = p->m_dwUserId;
//			data.info[i].dwWin = p->m_iWin;
//			data.info[i].iChairId = p->m_iChairId;
//			data.info[i].iCharm = p->m_iCharm;
//			data.info[i].iScore = p->m_iScore;
//			data.info[i].iTableId = p->m_iTableId;
//			data.info[i].wSubsidyNum = p->m_wSubsidyNum;
//			data.info[i].dwHonor = p->m_dwHonor;
//			_tcscpy( data.info[i].szName, p->m_szUserName );
//			_tcscpy( data.info[i].szHeadImgName, p->m_szHeadImgName );//wz add upload new 333
//			data.info[i].dwCountLoginTime = p->m_dwCountLoginTime;
//
//			//add by mx 2009.9.24
//			data.info[i].iRealSex = p->m_iRealSex;
//			data.info[i].bSuperCharm = p->m_bSuperCharm;
//			data.info[i].bVidicon = p->m_bVidicon;
//		}
//		pTable->SendToAllUser( &data, sizeof(data) );
//
//
//	}
//
//	//剩余人继续等待
//	CheckAllot();
}


void CDDZ_Room::LeaveRoom( unsigned int dwUserId )
{
	CUser * pUser = GetUser( dwUserId );
	if( !pUser )
		return;

//	//更新用户数据
//	PT_DDZ_UPDATE_ONE_USER_DATA_INFO data2;
//	data2.data.dwDisconnect = pUser->m_iDisconnect;
//	data2.data.dwDogfall = pUser->m_iDogfall;
//	data2.data.dwEscape = pUser->m_iEscape;
//	data2.data.dwLost = pUser->m_iLost;
//	data2.data.dwWin = pUser->m_iWin;
//	data2.data.iScore = pUser->m_iScore;
//	data2.data.dwUserId = pUser->m_dwUserId;
//	g_ServerApp.SendToDataServer( &data2, sizeof(data2) );

	CBaseRoom::LeaveRoom( dwUserId );
}




