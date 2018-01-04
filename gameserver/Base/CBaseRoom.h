/*
 * CBaseRoom.h
 *
 *  Created on: 2017年4月9日
 *      Author: aaaa
 */

#ifndef BASE_CBASEROOM_H_
#define BASE_CBASEROOM_H_

#include <map>
#include <vector>
#include <string.h>
using namespace std;
#include "../include/CUser.h"
#include "CBaseTable.h"
#include "CDateTimeEx.h"

#include "Array.h"
#define WAIT_ALLOT_TIME				2000
#define WAIT_ALLOT_ID               100
#define MATCH_TIME_COUNT            1000
#define MATCH_TIME_ID               101


typedef map<unsigned int, CUser *> CUserHash;

typedef map<unsigned int, CBaseTable *> CTableHash;

typedef map<unsigned int, SMemberInfo *> CMemberHash;

typedef map<unsigned int, STeamInfo *> CTeamHash;


enum TIME_COMPARE
{
	TIME_OUT,//时间到了
	TIME_MINUTE_THREE,//离比赛还有三分钟
	TIME_MINUTE_ONE,//离比赛还有一分钟
	TIME_SECOND_THIRTY,//离比赛还有30秒
	TIME_SECOND_THIRTY_EX,
	TIME_NONE,//时间未到
	TIME_END,
	TIME_OVER_TEN_MINUTE,
};

//房间基类
class CBaseRoom
{
public:
	CBaseRoom();
	virtual ~CBaseRoom();

	Array<CBaseTable *>			m_pTables;
	CTableHash *				m_pAllotTables;				//动态分配的桌子，用于随机入坐
	unsigned int						m_dwAllotTableId;			//动态分配的桌子id号

	int							m_iMaxUserNum;				//房间正常容纳人数
	int							m_iCurUserNum;				//当前房间人数
	CUserHash *					m_pUserList;


	vector<CUser *>             m_pWaitGameUserList ;       //随即入座

	CTimer						m_Timer;					//记时器
	int							m_iTimerType;				//记时类型
	bool						m_bAllotTableLocked;

public:

	unsigned int						m_dwId;
	char						m_szName[MAX_ROOMNAME_LEN];

	unsigned int						m_dwGameId;					//所属游戏id

	int							m_iBaseScore;				//基数
	int							m_iBaseScores;				//基数copy

	int                         m_iForceExitBase;           //强退倍数

	int							m_iMinScore;				//能够进入房间的分数底线
	float						m_fTax;						//税率

	bool						m_bCanSeeOtherUser;			//用户进入后是否能看见其他用户
	bool						m_bCanEnterTable;			//用户是否能自行进入桌子

	int							m_iChairNum;				//桌子中的椅子数

	//add by mx ROOT模式
	bool						m_bEnterGameMode;			//是否是进入游戏模式 add by mx
	int						m_wLevelType;				//等级评价模式//0 score, 1 money, 2 HappyBean

	//add by mx 2009.9.15 邀请、旁观、不受欢迎、请他离开功能的开关
	bool						m_bCanInvite;				//是否能邀请
	bool						m_bCanLookAt;				//是否能旁观
	bool						m_bCanNoWelCome;			//是否有不受欢迎功能
	bool						m_bCanPleaseLeave;			//是否有请人离开功能

public:

	//===========================ww match variable==========================
	int							m_iMatchMoney;				//金币
	int							m_iMatchLeDou;				//乐豆
	int							m_iMatchRose;				//玫瑰
	int							m_iMatchHonor;				//勋章
	int							m_iMatchCharm;				//魅力

	int                         m_iMatchMode;				//当前房间竞赛模式
	int                         m_iLoopMatch;				//是否循环比赛
	bool						m_bMatchStart;				//是否已经开赛
	int							m_iMatchTimeType;
	char                       m_szMatchDate[20];			//比赛日期
	int                         m_iMatchTag;				//比赛标记
	int                         m_iMatchBouns;				//比赛总奖金
	int                         m_iMatchMinCount;			//比赛最小人数
	int                         m_iMatchMaxCount;			//比赛最大人数
	int                         m_iMatchSignUpNum;			//报名金额
	int                         m_iMatchSignUpNumType;		//报名费类型
	char                       m_szMatchInfoAddr[30];		//比赛网址
	int                         m_iMatchBonusType;			//比赛奖励类型

	CDateTimeEx                 m_MatchTime;				//开赛时间
	CDateTimeEx					m_MatchTimes;				//开赛时间备份

	int							m_iMinWaitUserNum;			//最小等待用户
	int							m_iMaxWaitUserNum;			//最大等待用户

	int							second;						//还有多长时间开赛

	int							m_iScoreType;				//记分类型
	int                         m_iCurMatchMode;			//当前比赛模式
	int							m_iBoutOfScore;				//定局积分模式用，几局
	int							m_iLunNum;					//定局积分的轮数（1轮＝3局）
	int							m_iPeopleNum;				//多少人开始定局积分
	int							m_iCurMatchPeopleNum;		//当前比赛需要的人数

	vector<unsigned int>				m_MathSignUpList;			//存储所有(报名该房间比赛)的(所有用户)的UserID
	vector<CUser *>				m_pAllPlayer;				//所有玩家＝比赛的玩家＋游戏中的玩家 主要用于排名
	vector<CUser *>				m_pPlayOfMatching;			//存储所有准备比赛的玩家
	vector<CUser *>				m_pPlayOfGaming;			//存储所有游戏中的玩家
	vector<unsigned int>				m_pPlayOfOut;				//按顺序存储所有出局玩家的UserId

	int                         m_iCurMatchCount;           //当前比赛报名人数
	int                         m_iCurMatchState;           //当前比赛状态

	int							m_iAddScore[9];				//每局增长的积分

	vector<MatchAwardInfo>		m_MatchAwardList;			//比赛奖励信息列表

	vector<CDateTimeEx *>		m_MatchTimeList;			//定点小时赛的开赛时间表

	int							m_iXmlMatchId;				//比赛ID
	int							m_iXmlMatchType;			//比赛Type(大奖赛 1or普通赛 0)
	int							m_iXmlMatchPlace;			//比赛前多少名晋级
	int							m_iXmlMatchPhase;			//比赛阶段(初赛，晋级赛，决赛 0,1,2)
	int							m_iXmlMatchMoney;			//资格不够所需的钱数

public:
	//=======六家组队竞赛========
	CMemberHash *				m_pMemberList;
	CTeamHash *					m_pTeamList;				//队伍列表
	vector<STeamInfo *>			m_pReadyTeamList;			//已经准备好的队伍列表
	vector<STeamInfo *>			m_pMatchTeamList;			//正在比赛中的队伍列表
	vector<unsigned int>				m_pTeamOut;

	vector<STeamInfo *>			m_pAllTeamList;			//所有队伍列表


public:

	bool CreateTeam( CUser * pUser );						//创建队伍
	bool InviteMember( CUser * pUser, unsigned int dwTeamId );		//邀请成员
	void KickTeam(CUser * pUser, CUser * pOther );			//踢出队伍
	bool JoinTeam( CUser * pUser, unsigned int dwTeamId );			//加入队伍
	bool LeaveTeam( CUser * pUser, unsigned int dwTeamId );		//离开队伍
	bool DelTeam( CUser * pUser );							//删除队伍

	void ReadyTeam( CUser * pUser );
	void AllotTeam( CUser * pUser );

	void RemovTeamFromReadyTeam( unsigned int dwTeamId );
	void RemoveReadyTeamToMatchTeam( unsigned int dwTeamId );
	void RemoveMatchTeamToReadyMatch( unsigned int dwTeamId );
	void RemoveMatchTeamToTeamOut( unsigned int dwTeamId );

public:

	//===================ww========================
	//===Member===
	SMemberInfo * GetMember( unsigned int dwUserId )
	{
//	if(m_pMemberList->find(dwUserId )==m_pMemberList->end());
//		return NULL;
//
//	return m_pMemberList[dwUserId];

		return NULL;
	}
	void InsertMember( SMemberInfo * pMember )
	{
//		if(pMember)
//		{
//			m_pMemberList[pMember->dwUserId] = pMember;
//		}

	}
	SMemberInfo * RemoveMember( unsigned int dwUserId )
	{

//		if(m_pMemberList->find(dwUserId) == m_pMemberList->end())
//		{
//			return NULL;
//		}
//		SMemberInfo * pMember = m_pMemberList[dwUserId];
//		m_pMemberList->erase(dwUserId);
//		return pMember;

		return NULL;
	}
	void ClearAllMember()
	{
//		SMemberInfo * pMember = 0;
//		for( POS pos = m_pMemberList->GetFirstPos(); pos; )
//		{
//			pMember = m_pMemberList->GetNext( pos );
//			if( pMember )
//				SAFE_DELETE( pMember );
//		}
//		m_pMemberList->ClearAll();
	}

	void SendAllMemberInfoToOne( SMemberInfo * pMember );

	//===team===
	STeamInfo * GetTeam( unsigned int dwUserId )
	{
//		POS pos = m_pTeamList->Find( dwUserId );
//		if( !pos )
//			return NULL;
//		return m_pTeamList->GetAt( pos );

		return NULL;
	}
	void InsertTeam( STeamInfo * pTeam )
	{
		//m_pTeamList->( pTeam->dwMemberId[0], pTeam );

	}
	STeamInfo * RemoveTeam( unsigned int dwUserId )
	{
//		POS pos = m_pTeamList->Find( dwUserId );
//		if( !pos )
//			return NULL;
//		STeamInfo * pTeam = m_pTeamList->GetAt( pos );
//		m_pTeamList->RemoveAt( pos );
//		return pTeam;
		return NULL;
	}
	void ClearAllTeam()
	{
//		STeamInfo * pTeam = 0;
//		for( POS pos = m_pTeamList->GetFirstPos(); pos; )
//		{
//			pTeam = m_pTeamList->GetNext( pos );
//			if( pTeam )
//				SAFE_DELETE( pTeam );
//		}
//		m_pTeamList->ClearAll();
	}

	//=================ww end=====================

	CUser * GetUser( unsigned int dwUserId )
	{
//		POS pos = m_pUserList->Find( dwUserId );
//		if( !pos )
//			return NULL;
//		return m_pUserList->GetAt( pos );
		return NULL;
	}
	CUser * GetUserFromNumericAccount( unsigned int dwNumericAccount )
	{
//		CUser * pp = NULL;
//		for( POS pos = m_pUserList->GetFirstPos(); pos; )
//		{
//			pp = m_pUserList->GetNext( pos );
//			if( pp->m_dwNumericAccount == dwNumericAccount )
//				return pp;
//		}
		return NULL;

	}
	void InsertUser( CUser * pUser )
	{
//		if(pUser)
//			m_pUserList[pUser->m_dwUserId] = pUser;
	}

	CUser * RemoveUser( unsigned int dwUserId )
	{
//		POS pos = m_pUserList->Find( dwUserId );
//		if( !pos )
//			return NULL;
//		CUser * pUser = m_pUserList->GetAt( pos );
//		m_pUserList->RemoveAt( pos );
//		return pUser;

		return NULL;
	}
	void RemoveUser( CUser * pUser )
	{
//		if( !pUser )
//			return;
//		POS pos = m_pUserList->Find( pUser->m_dwUserId );
//		//delete m_pUserList->GetAt( pos );
//		m_pUserList->RemoveAt( pos );
	}

	bool IsFull()
	{
//		if( (int)m_pUserList->GetCount() >= m_iMaxUserNum )
//			return true;
//		else
			return false;
	}


	unsigned int GetId(){ return m_dwId; }
	char * GetName(){ return m_szName; }
	int GetTableNum(){ return m_pTables.Num(); }
	CBaseTable * GetTable( unsigned int dwId )
	{
		if( (int)dwId < m_pTables.Num() )
			return m_pTables[dwId];
		else
			return NULL;
	}

	int GetCurUserNum(){ return m_iCurUserNum; }
	int GetMaxUserNum(){ return m_iMaxUserNum; }


	virtual void UpdateAllUserInfo() = 0;
	virtual void Init( unsigned int dwId, char * szName, int iTableNum, int iMaxUserNum );
	virtual void Release();
	//virtual void Process();
	virtual int CanEnter( long long lMoney, long long lHappyBean );

	virtual void EnterRoom( CUser * pUser );
	virtual void LeaveRoom( unsigned int dwUserId );
	virtual void KickOut( unsigned int dwUserId, int iError );

	virtual void EnterTable( CUser * pUser, unsigned int dwTableId, unsigned int dwChairId,bool bCheckPass ,char *p = ""  );
	virtual void LeaveTable( CUser * pUser );
	virtual void UserReady( CUser * pUser );
	virtual void UserChat( CUser * pUser ){};
//	virtual void AutoAllotTable();
//	virtual void SetMatchMode();
//	virtual void MatchScore();
//	virtual void MatchOut();
//	virtual void SaveMatchPlace( unsigned int dwUserId ,char szUserName[20],int iPlace , bool bRes ){};//wm add
	//强退时的处理策略（米欣）
	virtual void ForceLeaveTable( CUser * pUser,float iPunishNum = 1 );
	//add by mx
	virtual void UpdateMoney( CUser * pUser );//更新钱时调用 add by mx

	//////////////////////////////////////////////////////////////////////
	/////2009.4.14

	virtual void SetTimer( unsigned int dwElapse, int iType ,bool bOnce = true );
	virtual void OnTimer();
	virtual void KillTimer();

	int GetWaitTableTime();								//获取等待时间（秒）

	void CheckAllot();
	virtual void NowAllot();							//立即分配

	void InsertWaitUser( CUser * pUser );				//插入等待用户
	void RemovePalyUser( CUser * pUser );				//删除已经分配的用户

	void SendToAllWaitUser( void * data, unsigned int size );


	//////////////////////////////////////////////////////////////////////

	virtual void SendAllUserInfoToOne( CUser * pUser );

	void SendToAllUser( void * data, unsigned int size, CUser * pExcept = NULL );

	void ChatToAllUser( void * data, unsigned int size );

	void SendToUser( void * data, unsigned int size, CUser * pOnly );


	void SetGameId( unsigned int dwGameId ){ m_dwGameId = dwGameId; }
	unsigned int GetGameId(){ return m_dwGameId; }

	void SetBaseScore( int iScore ){ m_iBaseScore = iScore, m_iBaseScores = iScore; }
	int GetBaseScore(){ return m_iBaseScore; }

	void SetScoreType( int iType ){ m_iScoreType = iType; }
	int GetScoreType(){ return m_iScoreType; }

	void SetMinScore( int iScore ){ m_iMinScore = iScore; }
	int GetMinScore(){ return m_iMinScore; }

	void SetTax( float fTax ){ m_fTax = fTax; }
	float GetTax(){ return m_fTax; }

//	virtual MatchAwardInfo * GetMatchAward( int iPlace );
	//virtual void SetMatchPeopleNum();
	void LoadMathcTimeInfo();
	bool IsOut( unsigned int dwUserId );
	bool IsAtMatch( CUser * pUser );
	bool IsAtMatchIng( CUser * pUser );
	void ReSetCurMatch();
	int GetFreeTable();
	int GetFreeChair( int iTableId );
	void ExitMatch( CUser * pUser );
	void SignUpMatch( CUser * pUser );
	void SortMatchList();
	int GetSignUpOrder( unsigned int dwUserId );

	void RemoveMatchToGame( unsigned int dwUserId );
	void RemoveGameToMatch( unsigned int dwUserId );

	void RemoveGameToOut( unsigned int	dwUserId );
	void RemoveMatchToOut( unsigned int dwUserId );
	void RemoveSignUpUser( unsigned int dwUserId );//wm

	void RemovePlayerFromGame( unsigned int dwUserId );
	void RemovePlayerFromMatch( unsigned int dwUserId );
	void RemovePlayerFromAllPlayer( unsigned int dwUserId );

	virtual void SortAllPlayer();//所有玩家排名
	virtual int GetPlace( unsigned int dwUserId );//获取排名
	CUser * GetUserFromGame( unsigned int dwUserId );

	void EnterTableJS();

	CDateTimeEx GetNextMatchTime();
	int GetPlayerNumOfMatch();
	CDateTimeEx * GetTimeByDayOfWeek( CDateTimeEx time );
	void SetMatchMode( int MatchMode )
	{
		m_iMatchMode = MatchMode ;
		if( m_iMatchMode == MATCH_ALL )
			m_iCurMatchMode = MATCH_OUT;
		else
            m_iCurMatchMode = MatchMode;
	}

	int  GetMatchMode(){ return m_iMatchMode; }

	void SetMatchState( int iMatchState ){ m_iCurMatchState = iMatchState; }
	int GetMatchState() {return m_iCurMatchState;}

	unsigned int GetSecondByDay( CDateTimeEx  time );

	void SetMatchDate( char *szMatchDate )
	{
//		_tcscpy( m_szMatchDate , szMatchDate );
//		////将时间字符转换成系统时间格式
//		CString str;
//		str.Format( L"%s",m_szMatchDate );
//		int index = 0 ,count = 0;
//		for( int i = 0 ; i < 5 ; i++ )
//		{
//			if( i==0 )
//			{
//				index = 0;
//				count = 4;
//			}
//			else
//			{
//				index = 5 + ( i-1 )*3;
//				count = 2 ;
//			}
//			CString temp = str.Mid( index ,count );
//			switch( i )
//			{
//			case 0:
//				{
//					m_MatchTime.wYear = _ttoi( temp.GetBuffer() );
//					break;
//				}
//			case 1:
//				{
//					m_MatchTime.wMonth = _ttoi( temp.GetBuffer() );
//					break;
//				}
//			case 2:
//				{
//					m_MatchTime.wDay = _ttoi( temp.GetBuffer() );
//					break;
//				}
//			case 3:
//				{
//					m_MatchTime.wHour = _ttoi( temp.GetBuffer() );
//					break;
//				}
//			case 4:
//				{
//					m_MatchTime.wMinute = _ttoi( temp.GetBuffer() );
//					break;
//				}
//			}
//		}
//		m_MatchTime.wSecond = 0;
//		m_MatchTime.wMilliseconds = 0 ;
//
//		//备份开赛时间
//		m_MatchTimes = m_MatchTime;

	}
	char * GetMatchDate(){ return m_szMatchDate; }

	void RandomMatchPeople();

	void AllotScore( int iScore );

	void SendPlaceList();
	void SetMatchTag( int MatchTag ){ m_iMatchTag = MatchTag ;}
	int  GetMatchTag(){ return m_iMatchTag; }

	void SetMatchBouns( int MatchBouns ){ m_iMatchBouns = MatchBouns ;}
	int  GetMatchBouns(){ return m_iMatchBouns; }

	void SetMatchMinCount( int MatchMinCount ){ m_iMatchMinCount = MatchMinCount ;}
	int  GetMatchMinCount(){ return m_iMatchMinCount; }

	void SetMatchMaxCount( int MatchMaxCount ){ m_iMatchMaxCount = MatchMaxCount ;}
	int  GetMatchMaxCount(){ return m_iMatchMaxCount; }

	int  GetMatchSignUpNum(){ return m_MathSignUpList.size(); }

	void SetMatchSignUpFree( int MatchSignUpNum ){ m_iMatchSignUpNum = MatchSignUpNum ;}
	int GetMatchSignUpFree(){ return m_iMatchSignUpNum; }
	void SetMatchSignUpNumType( int MatchSignUpNumType ){ m_iMatchSignUpNumType = MatchSignUpNumType ;}
	int  GetMatchSignUpNumType(){ return m_iMatchSignUpNumType; }

	void SetMatchInfoAddr( char *szMatchInfoAddr ){ strcpy( m_szMatchInfoAddr , szMatchInfoAddr ); }
	char * GetMatchInfoAddr(){ return m_szMatchInfoAddr; }

	void SignUpMatchEx( CUser * pUser );
	void SetMatchBonusType( int iType ){ m_iMatchBonusType = iType ;}
	int  GetMatchBonusType(){ return m_iMatchBonusType ;}
	void SetLoopMatch( int iLoop ){ m_iLoopMatch = iLoop ;}
	int GetLoopMatch(){ return m_iLoopMatch ;}

//	virtual void LoadMatchConfigInfo();
//	virtual void MathcTimeOut();

//	virtual void SaveXmlInfo();
	bool IsHasAtXmlInfo( unsigned int dwUserId );
	//end

	void SetCanSeeOtherUser( bool bCan ){ m_bCanSeeOtherUser = bCan; }
	bool IsCanSeeOtherUser(){ return m_bCanSeeOtherUser; }

	void SetCanEnterTable( bool bCan );
	bool IsCanEnterTable(){ return m_bCanEnterTable; }

	void SetMinWaitUserNum( int iMin ){ m_iMinWaitUserNum = iMin; }
	int GetMinWaitUserNum(){ return m_iMinWaitUserNum; }

	void SetMaxWaitUserNum( int iMax ){ m_iMaxWaitUserNum = iMax; }
	int GetMaxWaitUserNum(){ return m_iMaxWaitUserNum; }

	void SetChairNum( int iChairNum ){ m_iChairNum = iChairNum; }
	int GetChairNum(){ return m_iChairNum; }
	int CompareTime( CDateTimeEx match );
//////////////////add by mx 2009.7.30
	void SetEnterGameMode( bool bEnterGameMode ){ m_bEnterGameMode = bEnterGameMode; }
	int IsEnterGameMode(){ return m_bEnterGameMode; }

	void SetLevelType( int wLevelType ){ m_wLevelType = wLevelType; }//0 score, 1 money, 2 HappyBean
	int GetLevelType(){ return m_wLevelType; }
//////////////////////////////////////////
//add by mx 2009.9.15 邀请、旁观、不受欢迎、请人离开的开关功能
	void SetCanInvite( bool bCanInvite ){ m_bCanInvite = bCanInvite; }
	int IsCanInvite(){ return m_bCanInvite; }

	void SetCanLookAt( bool bCanLookAt ){ m_bCanLookAt = bCanLookAt; }
	bool IsCanLookAt(){ return m_bCanLookAt; }

	void SetCanNoWelCome( bool bCanNoWelCome ){ m_bCanNoWelCome = bCanNoWelCome; }
	bool IsCanNoWelCome(){ return m_bCanNoWelCome; }

	void SetCanPleaseLeave( bool bCanPleaseLeave ){ m_bCanPleaseLeave = bCanPleaseLeave; }
	bool IsCanPleaseLeave(){ return m_bCanPleaseLeave; }
};

#endif /* BASE_CBASEROOM_H_ */
