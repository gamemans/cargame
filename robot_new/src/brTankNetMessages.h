//
//  brTankNetMessages.h
//  OGRE
//
//  Created by obuil on 12-6-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef OGRE_brTankNetMessages_h
#define OGRE_brTankNetMessages_h
//#include"brNetMessagesCommon.h"
#include "RakNetTypes.h"

#define DEBUG_PRINTF(format,...) printf("["__FILE__", Line: %04d]: \n"format"\n", __LINE__, ##__VA_ARGS__)
//#define DEBUG_PRINTF(format,...)

// 当前游戏玩法模式
enum eGameRunMode 
{


	
	// 1:单人游戏
	// 弹出创建房间列表,选择默认选择为单人游戏.然后选择人数以及模式
  SINGLE_GAME_MODE = 0,
	
	// 3:游戏大厅
	// 进入房间列表.并且增加选项:创建房间.
  COMMON_LOBBY_MODE ,
	

	
	// 以下两者作为快速对战的后续使用变量，
	QUICK_CREATE_MODE,
	QUICK_JOIN_MODE,
	
	// 2:快速对战
	// 有网络规则
	// 快速加入一个有位置并且正在准备的房间
	// 快速加入一个有位置并正在比赛的房间
	// 如果没可用房间,直接进入创建房间界面.
	// 无网络
	// 点击任何选项都提示:当前没有发现可用网络.可以进入单机训练模式.
	
	// 快速对战 是统称，可以是下面的 快速创建和快速加入的任何一种
	QUICK_MATCH_MODE= 10,

};

#pragma pack(push, 1)


// 游戏模式信息
struct  stGameMode 
{
	int sceneID;
	int game_mode;
	int game_minute;  // 游戏时间
	int player_num;
	int target_num;
	char szPwd[6];
	
	
	void operator = (const stGameMode& other)
  {
		this->sceneID = other.sceneID;
		this->game_mode = other.game_mode;
		this->game_minute = other.game_minute;
		this->player_num = other.player_num;
		 this->target_num = other.target_num;
		strcpy(this->szPwd,other.szPwd) ;
  }
	
};

// 用户装备信息
struct stUserItemsInfo
{
	unsigned int keyID;
	unsigned int userID;  // 玩家ID
	unsigned int nItemID;  // 装备ID
	unsigned int nKeeperID;  // 装备的上层绑定ID
	
	void operator = (const stUserItemsInfo& other)
  {
		this->keyID = other.keyID;
		this->userID = other.userID;
		this->nItemID = other.nItemID;
		this->nKeeperID = other.nKeeperID;

  }

};
// 支付方式
enum  ePayMode
{
	Pay_ITurns=0,   //ITurns内购
	Pay_91,  // 91 支付

	
};

// 充值产品列表
struct stRechargeItemInfo
{
	unsigned int    nID;  // 装备ID
	unsigned int    nType;
	unsigned int    nRealMoney;
	unsigned int    nMoney1;
	unsigned int    nMoney2;
	unsigned int    nExtraValue;
	unsigned int    nItemType;
	std::string     sProductID;
	std::string     sProductName;
	
	void operator = (const stRechargeItemInfo& other)
  {
		this->nID = other.nID;
		this->nType = other.nType;
		this->nRealMoney = other.nRealMoney;
		this->nMoney1 = other.nMoney1;
		this->nMoney2 = other.nMoney2;
		this->nExtraValue = other.nExtraValue;
		this->nItemType = other.nItemType;
		this->sProductID = other.sProductID;
		this->sProductName = other.sProductName;
		
  }
	
};

// 商品购买结果返回信息
struct stUserBuyInfo
{
  unsigned int keyID;
  
};

// 组当前状态
enum  enHostState
{
	ROOM_STATE=0,
	INGAME_STATE,
		
};
// 房间内主机信息
struct stHostInRoomInfo
{
	unsigned int nHostId;  // 组ID
	unsigned int nMaxNum;  // 最大人数
	unsigned int nCurNum;  // 当前人数 或更新人数（－1 or ＋1）
	int mode;     // 组比赛模式
  enHostState  state;
	bool			bLock;
	unsigned int 			nSceneID;			//map or scene id
	unsigned int			nTargetNum;
	unsigned int			nLevel;
	int     update_flag;  // =0:不作为；＝1 增加；＝－1 删除； ＝2：更新
	
	void operator = (const stHostInRoomInfo& other)
  {
		this->nHostId = other.nHostId;
		this->nMaxNum = other.nMaxNum;
		this->nCurNum = other.nCurNum;
		this->mode = other.mode;
		this->state = other.state;
		this->bLock = other.bLock;
		this->nSceneID = other.nSceneID;
		this->nTargetNum = other.nTargetNum;
		this->update_flag = other.update_flag;
		
  }
	
	stHostInRoomInfo()
	:nHostId(0)
	,nMaxNum(12)
	,nCurNum(0)
	,mode(0)
	,state(ROOM_STATE)
	,bLock(false)
	{
	}
	
};

// 玩家信息
struct stPlayerInGameInfo
{
	unsigned int userID;
	unsigned int tank_id;
	unsigned int muzzle_id;
	unsigned int posIdx;
	unsigned int group;
	unsigned int bReferee;
	
	// 以下信息不通过网络共享
	std::string  name;
	int money1;
	int money2;
	int level;
	int exp;
	int winNum;  // 胜数
	std::string  model;  // 机型
	
	void operator = (const stPlayerInGameInfo& other)
  {
		this->userID  = other.userID;
		this->tank_id = other.tank_id;
		this->muzzle_id = other.muzzle_id;
		this->posIdx    = other.posIdx;
		this->group  = other.group;
		this->bReferee  = other.bReferee;
		
		this->name  = other.name;
		this->money1  = other.money1;
		this->money2  = other.money2;
		this->level  = other.level;
		this->exp  = other.exp;
		this->winNum  = other.winNum;
		this->model  = other.model;
  }
	
	stPlayerInGameInfo()
	:userID(0)
	,name("")
	,tank_id(0)
	,muzzle_id(0)
	,posIdx(0)
	,group(0)
	,bReferee(1)
	,money1(0)
	,money2(0)
	,level(0)
	,exp(0)
	,winNum(0)
	{
	}

};


// 上传游戏结束后统计信息
struct stGamneEndStateInfo
{
	int nKillNum;  //  成就数目
	int nScore;  // 得分
	int nVictory;  // 是否获胜
	int nMvp;     // 是否MVP

	void operator = (const stGamneEndStateInfo& other)
  {
		this->nKillNum = other.nKillNum;
		this->nScore = other.nScore;
		this->nVictory = other.nVictory;
		this->nMvp = other.nMvp;		
  }
	
};


// 游戏结束后服务器反馈奖励
struct stGamneEndRewardInfo
{
	int nMoney1;      // 货币1
	int nMoney2;      // 货币2
	int nExperience;  // 经验数
	int nItemID;      // 奖励物品ID
	
	void operator = (const stGamneEndRewardInfo& other)
  {
		this->nMoney1 = other.nMoney1;
		this->nMoney2 = other.nMoney2;
		this->nExperience = other.nExperience;
		this->nItemID = other.nItemID;		
  }
	
};


	// 充值确认反馈奖励
struct stRechargeRewardInfo
{
	int itemid;
	int uitemid;

	void operator = (const stRechargeRewardInfo& other)
	{
		this->itemid = other.itemid;
		this->uitemid = other.uitemid;

	}
	
};



enum MultiThreadState
{
	THREAD_STOP = 0,
	THREAD_SLEEP,
	THREAD_INIT,
	THREAD_LOGIN,
	THREAD_ALLROOMLIST,
  THREAD_ROOM,
	THREAD_INGAME_BUY,
	THREAD_INGAME_UPDATE,
	
	
};

// 二级消息头
// 一级消息头为：PT_USER_INGAME_MSG
enum TankGameMessages
{
	// 通知clientMaster我slaver端准备完毕
	INGAME_PRE_TANK_READY = 1,//非房主发
	// 通知所有clientslavers 开始游戏
	INGAME_PRE_TANK_START,//房主发开始
	// 开始游戏计时
	INGAME_TANK_START,//互发
	// 更新自己的tank参数
	INGAME_STATE_TANK_POSITION,//位置参数，炮管角度。
	// 更新自己的ap
	INGAME_STATE_TANK_AP,//更新血量
	// 通知开火事件
	INGAME_EVENT_TANK_FIRE,//我开火，目标，
	// 通知重生事件
	INGAME_EVENT_TANK_REBORN,//主机通知，有人复活
	// 通知吃道具事件
	INGAME_EVENT_TANK_PROPS,//不一定自己吃到
	// 通知炸毁事件
	INGAME_EVENT_TANK_DESTORY,//主机通知。
	// INGAME内购买事件
	INGAME_EVENT_BUY,
	// gameover
	INGAME_TANK_GAMEOVER,//主机通知
	// 通知退出游戏，但不退出host
	INGAME_EXIT_INGAME_NOTIFY,//通知其它人自己退出
	// 聊天消息
	INGAME_MESSAGES,
	// 赛后统计互传事件
	INGAME_END2OTHERS_STATEINFO,
	// 房主改变通知
	INGAME_HOSTMASTER_CHANGE,
	// 中途有palyer加入
	INGAME_MIDWAY_NEW_COMING=101,
	// 通知中途加入的玩家ingame已有统计信息
	INGAME_MIDWAY_DATA_NOTIFY,
	

	


};

// INGAME内购买事件
struct PT_INGAME_EVENT_BUY_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int nUserId;
	unsigned int nItemId;
	PT_INGAME_EVENT_BUY_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EVENT_BUY)
	{

	}
};

	
// 赛后统计互传事件
struct PT_GAME_END2OTHERS_INFO
{
	unsigned char id;
	unsigned int in_id;
	
	unsigned int userId;
	
	unsigned int pMoney;
	int nExperience;  // 经验数
	int nItemID;      // 奖励物品ID
	int nMvp;     // 是否MVP
	
	PT_GAME_END2OTHERS_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_END2OTHERS_STATEINFO)
	{
		pMoney = 0;
		nExperience = 0;
		nItemID = 0;
		nMvp = 0;
		
	}
};

	
//聊天信息
struct	PT_INGAME_MESSAGES_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int nUserId;
	char     szchat[128];
	PT_INGAME_MESSAGES_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_MESSAGES)
	{
		szchat[0] = 0;
	}
};
	

// 准备事件READY
struct PT_INGAME_STATE_TANK_READY_INFO
{
	unsigned char id;
	unsigned int in_id;
	stPlayerInGameInfo  playerInfo;  // 本机Player的装备信息
	PT_INGAME_STATE_TANK_READY_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_PRE_TANK_READY){}
};

// 准备事件START
struct PT_INGAME_STATE_TANK_START_INFO
{
	unsigned char id;
	unsigned int in_id;
	int game_mode;
	int game_minute;  // 游戏时间
	int player_num;
	PT_INGAME_STATE_TANK_START_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_PRE_TANK_START){}
};

// 开始计时，游戏正式开始
struct PT_INGAME_STATE_TANK_TIME_START_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	PT_INGAME_STATE_TANK_TIME_START_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_TANK_START){}
};

// 游戏结束
struct PT_INGAME_STATE_TANK_GAMEOVER_INFO
{
	unsigned char id;
	unsigned int in_id;
	PT_INGAME_STATE_TANK_GAMEOVER_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_TANK_GAMEOVER){}
};

struct PT_INGAME_STATE_TANK_POSITION_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	float x;
	float y;
	float z;
	float qw;
	float qx;
	float qy;
	float qz;
	float turret_yaw;
	float muzzle_pitch;
	
	PT_INGAME_STATE_TANK_POSITION_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_STATE_TANK_POSITION),player_id(0){}
	
	
	void operator = (const PT_INGAME_STATE_TANK_POSITION_INFO& other)
  {
		this->id  = other.id;
		this->in_id = other.in_id;
		this->player_id = other.player_id;
		this->x    = other.x;
		this->y  = other.y;
		this->z  = other.z;
		this->qw  = other.qw;
		this->qx  = other.qx;
		this->qy  = other.qy;
		this->qz  = other.qz;
		this->turret_yaw  = other.turret_yaw;
		this->muzzle_pitch  = other.muzzle_pitch;
  }
	
};


struct PT_INGAME_STATE_TANK_AP_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	float ap;
	
	PT_INGAME_STATE_TANK_AP_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_STATE_TANK_AP){}
};


struct PT_INGAME_EVENT_TANK_FIRE_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	unsigned int des_player_id;   // 瞄准的目标ID
	int acc;   // 准度
	int crit;   // 暴击率

	float x;    // 炮弹落地点
	float y;
	float z;
//	
//	int num
//	
//	for ()
//	{
//		 tankID +  dis
//		
//	}
	PT_INGAME_EVENT_TANK_FIRE_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EVENT_TANK_FIRE)
	{
		x =0;y=0;z=0;
	}
};
	
struct stFireStateinfo
{
	unsigned int player_id;
	int     dis;           //距离

};

struct PT_INGAME_STATE_TANK_REBORN_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	float    acc;
	PT_INGAME_STATE_TANK_REBORN_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EVENT_TANK_REBORN){}
};
struct PT_INGAME_STATE_TANK_PROPS_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	int trig_id;
	int values;
	int type;
	PT_INGAME_STATE_TANK_PROPS_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EVENT_TANK_PROPS){}
};
struct PT_INGAME_EVENT_TANK_DESTORY_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int player_id;
	unsigned int des_player_id;
	unsigned int kill_type;
	
	PT_INGAME_EVENT_TANK_DESTORY_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EVENT_TANK_DESTORY){}
};

// 通知退出游戏，但不退出host
struct PT_INGAME_EXIT_INGAME_NOTIFY_INFO
{
		unsigned char id;
		unsigned int in_id;
		unsigned int player_id;
		PT_INGAME_EXIT_INGAME_NOTIFY_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_EXIT_INGAME_NOTIFY){}
};
	
// 中途有palyer加入
struct PT_INGAME_MIDWAY_NEW_COMING
{
	unsigned char id;
	unsigned int in_id;
	stPlayerInGameInfo playerInfo;
	PT_INGAME_MIDWAY_NEW_COMING():id(PT_USER_INGAME_MSG),in_id(INGAME_MIDWAY_NEW_COMING){}
};
	
// 房主改变通知
struct PT_INGAME_HOSTMASTER_CHANGE_INFO
{
	unsigned char id;
	unsigned int in_id;
	unsigned int hostID;
	PT_INGAME_HOSTMASTER_CHANGE_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_HOSTMASTER_CHANGE){}
};
	
struct stPlayer_Stateinfo
{
	unsigned int player_id;
	int     killNum;        //杀人数
	int     killedNum;      //被杀数
	int     bannerNum;      //抢旗数
	int     score;          //得分
	int     ap;          //得分
	int     repeatKillNum;  //当前连击数
	int     x;
	int     y;
	int     z;
};
	
struct PT_INGAME_MIDWAY_DATA_NOTIFY_INFO
{
	unsigned char id;
	unsigned int in_id;
	int cur_time_num;
	int   palyer_num;
	
	// stPlayer_Stateinfo
	
	
	PT_INGAME_MIDWAY_DATA_NOTIFY_INFO():id(PT_USER_INGAME_MSG),in_id(INGAME_MIDWAY_DATA_NOTIFY){}
};
	
#pragma pack(pop)

#endif
