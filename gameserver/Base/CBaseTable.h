/*
 * CBaseTable.h
 *
 *  Created on: 2017年4月7日
 *      Author: aaaa
 */

#ifndef SRC_CBASETABLE_H_
#define SRC_CBASETABLE_H_



#include "CUser.h"
#include "CTimer.h"
#include <string.h>
#define WAIT_READY_ID 5000


#include "commdefine.h"
class CBaseRoom;

class CBaseTable
{
public:

	CBaseTable( int iUserNum );
	virtual ~CBaseTable();

	CUser **	m_pUsers;
	int			m_iUserNum;										//每桌做几个人

	CUser *		m_pLookers[MAX_TABLEUSER_NUM];					//观看的玩家数组
	int			m_iLookerNum;									//已经有多少旁观者

	CTimer		m_Timer;
	int			m_iTimerType;

	char		m_szPassword[20];
	CUser *		m_pPasswordUser;
	unsigned int       m_dwForceUserId;                                 //当前强退用户ID

	bool		m_bSended;										//是否回复过不同意退出信息

	bool		m_bInGame;

	int			m_iBaseScore;									//底分

	bool		m_bUse;
protected:

	unsigned int		m_dwId;

	unsigned int		m_dwCurUser;									//当前活动玩家

	unsigned int		m_dwTime;										//记时

	CBaseRoom *	m_pRoom;										//属于哪个房间

	int			m_iBout;										//第几局


public:

	int	GetBout();
	void SetBout( int n );
	void ReSetCurBaseScore();


	void SetId( unsigned int dwId ){ m_dwId = dwId; }
	unsigned int GetId(){ return m_dwId; }

	void SetBaseRoom( CBaseRoom * pRoom ){ m_pRoom = pRoom; }
	CBaseRoom * GetBaseRoom(){ return m_pRoom; }

	CUser * GetUser(int dwChairId )
	{
		if( dwChairId >= m_iUserNum )
			return NULL;
		return m_pUsers[dwChairId];
	}

	void SendPlaceInfo();


	bool IsNoUser();

	void UserApplyExit( CUser * pUser );
	void UserApplyExitRevert( CUser * pUser, CUser * pOther );

	bool IsInTable( CUser * pUser );

	virtual int CanEnter( CUser * pUser );							//是否能进入桌子(判断设置冲突)

	virtual bool CanLookAt( int iChairId );							//是否能旁观
	virtual void LookAt( CUser * pLooker, int iChairId );			//旁观
	virtual void LookAtCancel( CUser * pLooker );					//取消旁观
	virtual void OnLookAt( CUser * pLooker );						//当有人旁观时被调用


	virtual bool StartGame();										//游戏开始
	virtual void EndGame();											//游戏结束
	virtual void SaveUserGameInfo() = 0;							//保存游戏信息(在一局游戏结束时调用)

	virtual void OnUserLeave( int iChairId );						//当用户离开桌子时被调用
	virtual void OnUserRejoin( CUser * pUser ){};						//当用户短线重连时被调用
	virtual float OnUserPunish( CUser * pUser ){ return 1;};                      //逃跑用户特殊惩罚。有特殊惩罚的游戏可重载此函数

	virtual void SendToAllUser( void * data, unsigned int size, CUser * pExcept = NULL, bool bToLooker = true );

	virtual void SetTimer( unsigned int dwElapse, int iType, bool bOnce = true );
	virtual void OnTimer();
	virtual void KillTimer(){m_Timer.KillAllTimer();}

	virtual void MatchOut();
	virtual void MatchStart();
	virtual void MatchEnd();


	void Bouns( float fTex );

	//add by mx
	virtual void UpdateMoney( CUser * pUser ){}//更新钱时调用 mx
	virtual void OnUserDrop( CUser * pUser ){}//add by mx 2009.9.2 掉线时调用
};

#endif /* SRC_CBASETABLE_H_ */
