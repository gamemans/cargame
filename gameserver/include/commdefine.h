/*
 * commdefine.h
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#ifndef INCLUDE_COMMDEFINE_H_
#define INCLUDE_COMMDEFINE_H_



#pragma once


#include <vector>
using namespace std;


//服务器类型
enum SERVER_TYPE
{
	UNKNOWN = 0,
	ST_LOGIN,
	ST_AGENT,
	ST_GAME,
	ST_DATA,
	ST_MATCH,
};


//服务器状态
enum SERVER_STATE
{
	SS_SERVER_OFF = 0,
	SS_SERVER_NORMAL,
	SS_SERVER_BUSY,
	SS_SERVER_FULL,
};

//登陆状态
enum LOGIN_STATE
{
	LS_LOGIN_LOGOUT,				//未登陆
	LS_LOGIN_ACCEPT,				//已经登陆(未与游戏服务器连接)
	LS_LOGIN_CONNECT,				//已经与游戏服务器连接
	LS_LOGIN_AGAIN,


	LS_MANAGER_LOCK,
};

//游戏状态(agent server)
enum GAME_STATE
{
	GS_CONNECTED,
	GS_ENTER_ROOM_WAIT,
	GS_INROOM,
	GS_ENTER_TABLE_WAIT,
	GS_INTABLE,
	GS_INGAME,
};

//游戏状态(game server)
enum USER_STATE
{
	US_FREE,
	US_INTABLE,
	US_READY,
	US_INGAME,
	US_LOOKAT,
	US_CONNECTED,
};




#define GAME_SERVER_NUM 3
#define AGENT_SERVER_NUM 2
#define SHOP_GOODS_NUM 8//wz add upload new 333 把shop_goos_num 7
#define GAME_ACTIVITY_NUM  5
#define GAME_MATCHSERVER_NUM 1


//const int MAX_MONEY_NUM	= 2000000000;		//最大值，包括所有涉及到数值的字段
const int FORCE_MSG	=	1000;


const int	MAX_SPEEK_LEN = 80;
const double CHAR_DATA_BACKUP_TIME = 600.0;


#define _PI 3.14159265358979f

#define	EXCHANGE_RATE		5				//兑换比（1：？）


const int	MAX_ID_LEN = 50;
const int	MAX_NICHENG_LEN = 50;
const int	MAX_PSW_LEN = 50;
const int	MAX_BUFF_SIZE = 10240;

const int   MAX_LABA_NUM = 999;
const int	MAX_ADDR_LEN = 16;


const int MAX_USER_NUM = 10000;
const int MAX_ROOMUSER_NUM = 300;
const int MAX_TABLEUSER_NUM = 100;
const int MAX_ROOMNAME_LEN = 20;

const int MAX_SEND_ROOM_NUM = 20;//wm 2009.10.15
const int MAX_SEND_GAME_NUM = 20;//mx 2009.12.10

const int MAX_USERNAME_LEN = 30;

const int MATCH_RES_BASE_TYPE = 1000;

struct SERVER_ADDR
{
	char	szAddr[MAX_ADDR_LEN];
	int	wPort;
};


const int LOGIN_VOER_TIME = 10;

const int BANK_PWD_LEN = 8;

const int FLOWER_PRICE = 1000;	//花 金币
const int BRICK_PRICE = 1200;	//砖
const int BUN_PRICE = 600;		//包子
const int BOMB_PRICE = 5000;

const int GAME_ACTIVE = 5000;	//游戏动作，亲一下，给一拳等　乐豆

const int CHARM_BRICK = 2;		//砖头减少的魅力
const int CHARM_BUN = 1;		//包子
const int CHARM_BOMB = 10;		//飞弹

const int BOYHEAD = 3;//默认男起始头像ID
const int GIRLHEAD = 0;//默认女起始头像ID

#define MAX_WAIT_TABLE_TIME				20

#define DEFAULT_VALUE			10000			//默认的值 gameid, tableid, roomid

enum ACTIVA_TYPE
{
	ACTIVE_KISS,			//亲一下
	ACTIVE_FIST,			//给一拳
	ACTIVE_EYE,				//抛媚眼
	ACTIVE_HUG,				//拥抱
	ACTIVE_PLAYKISS,		//飞吻
	ACTIVE_FOOT,			//踹一脚
};
enum FLOWER_TYPE
{
	FLOWER_UNDIVIDED_ATTENTION,				//一心一意		1
	FLOWER_TELESTHESIA,						//心心相印		5
	FLOWER_ILOVEYOU,						//我爱你		10
	FLOWER_TRUELOVE100,						//真爱百分百	20
	FLOWER_MISSYOUEVERY						//天天想你		99
};
enum BRICK_TYPE
{
	BRICK_BRICK,							//扔砖头
	BRICK_BUN,								//包子
	BRICK_BOMB,								//飞弹
};


enum BULLETIN_TYPE
{
	BULLETIN_HORN,
	BULLETIN_FLOWER,
};


enum FRIEND_ENTER_GAME
{
	FRIEND_ENTERGAME_UNLINE,					//不在线
	FRIEND_ENTERGAME_UNROOM,					//不在房间
	FRIEND_ENTERGAME_ACCESS,					//成功
};
enum GAME_TYPE
{
	GAME_TYPE_MJ,
	GAME_TYPE_PK,
	GAME_TYPE_XX,
	GAME_TYPE_JS,

};

//竞赛奖励
struct MatchAwardInfo
{
	int        iMin;//获得该奖励的名次范围 min为最小名次 max为最大名次
	int        iMax;
	int        iAwardNum;//获得奖励的金币数
	char      szAwardName[20];//获得奖励的名称
	int        iHonorNum;//获得奖励的乐呵勋章
    MatchAwardInfo()
	{
		iMin = iMax = iAwardNum = iHonorNum = 0;
		szAwardName[0]=0;
	}

};
//游戏等级
struct SGradeInfo
{
	int			iMin;
	int			iMax;
	char		szGradeName[50];
};

//mx 2009.12.10
struct GAMELIST_GAME_INFO
{
	unsigned int	dwGameId;
	int	wGameType;//麻将，扑克，休闲，竞赛
	unsigned int	dwCurUserNum;								//游戏当前人数
	char	szGameName[20];
	char	szDirName[20];
	char   szVersion[20];
};

// 游戏服务器信息
struct SERVER_INFO
{
	SERVER_ADDR	saForServer,								//连接server的端口
				saForClient;								//连接client的端口
	char		szAddr[MAX_ADDR_LEN];
	unsigned int		dwUserNum;									//服务器当前人数
	unsigned int		dwState;									//状态（关闭，正常，忙）
	unsigned int		dwConnectIndex;								//连接索引

	bool		bReceve;									//回复标志位,赠送道具用
	SERVER_INFO()
	{
		bReceve = false;
		dwUserNum = 0;
		dwState = SS_SERVER_OFF;
	}
};
// 树上的人数信息
struct TREE_INFO
{
	unsigned int		dwRoomId;
	unsigned int		dwCurUserNum;
};

// 游戏房间信息
struct ROOM_INFO
{
	unsigned int       dwGameId;                                   //该房间所在游戏ID
	unsigned int		dwRoomId;                                   //房间id
	char		szRoomName[MAX_ROOMNAME_LEN];				//房间名字
	unsigned int		dwMaxUserNum;								//房间容纳人数
	unsigned int		dwCurUserNum;								//房间当前人数

	int			iScoreType;									//积分类型（金币，乐豆）
	int			iMinScore;									//能够进入房间的分数底线

	//wm match
	int         iMatchMode;                                 //竞赛模式
	//end
    bool        bCanEnterTable;                             //wm 2009.10.13
	int			iMatchTag;

	char		szMatchDate[20];
	unsigned int		dwMatchBouns;							//金币总额

	int			iMatchState;

	int			iSignUpMoney;
	int			iSignUpMoneyType;
	unsigned int		dwSignPeopleNum;						//报名人数
	int			iMinPeopleCount;
	int		    iMaxPeopleCount;

	char		szMatchHttp[50];

	ROOM_INFO()
	{
		szRoomName[0] = 0;
		szMatchDate[0] = 0;
		szMatchHttp[0] = 0;
	}
};
enum SIGN_FEE_TYPE//报名费类型
{
	SIGN_BEAN,
	SIGN_GOLD,
	SIGN_TICKET,//赛券
};
enum SCORE_TYPE
{
	SCORE_BEAN,
	SCORE_GOLD,
	SCORE_MATCH,
};

struct GAME_INFO
{
	unsigned int dwGameId;
	int  wGameType;
	char szGameName[20];
	char szDirName[20];
	char szVersion[20];//wm7.1

	vector<ROOM_INFO *>	RoomInfoList;

	ROOM_INFO * GetRoomInfo( unsigned int dwRoomId )
	{
		vector<ROOM_INFO *>::iterator it = RoomInfoList.begin();
		for( ; it != RoomInfoList.end(); ++ it )
		{
			if( (*it)->dwRoomId == dwRoomId )
				return *it;
		}
		return NULL;
	}

	GAME_INFO()
	{
		szGameName[0] = 0;
		szDirName[0] = 0;
		szVersion[0] = 0;
	}

	int GetMatchRoomNum()
	{
		int sum = 0;
		vector<ROOM_INFO *>::iterator it = RoomInfoList.begin();
		for( ; it != RoomInfoList.end(); ++ it )
		{
			if( (*it)->iScoreType == SCORE_MATCH )
				sum++;
		}
		return sum;
	}
	virtual ~GAME_INFO()
	{
		vector<ROOM_INFO *>::iterator it = RoomInfoList.begin();
		for( ; it != RoomInfoList.end(); ++ it )
		{
			delete *it;
		}
	}
};
struct MATCH_CHAMPION_LIST
{
	char		szWinner[20];
	char		szMatchTime[20];
	char		szMatchName[50];
	int			iMatchPeopleNum;
};
//好友基本信息
struct SFRIEND_BASE
{
	unsigned int		dwUserId;
	unsigned int		dwHeadId;
	char		szHeadName[20];
	char		szUserName[20];
	unsigned int		dwGameId;
	unsigned int		dwRoomId;
	unsigned int		dwTableId;
	bool		bSex;
	bool		bOnline;
	unsigned int		dwNumericAccount;


	int		wAddFriend;	//添加好友
	int		wOnlineTip;	//上线提示
	int		wInviteGame;//邀请游戏

	SFRIEND_BASE()
	{
		szHeadName[0] = 0;
		szUserName[0] = 0;
		dwGameId = DEFAULT_VALUE;
		dwRoomId = DEFAULT_VALUE;
		dwTableId = DEFAULT_VALUE;
	}
};
struct SFRIEND_INFO
{
	unsigned int		dwMe;
	unsigned int		dwFriend;
};
struct SHOP_GOODS_INFO			//商城物品信息
{
	unsigned int		dwId;			//物品ID
	long long		lPrice;		//物品单价
	long long		lVIPPrice;		//会员价
};
struct GAME_ACTIVITY_INFO      //游戏活动信息
{
	unsigned int      dwID;     //活动ID
	char      szActivityName[30] ;//活动名
	char      szActivityInfoDir[50];//活动介绍网址
	GAME_ACTIVITY_INFO()
	{
		szActivityInfoDir[0] = 0;
		szActivityName[0] = 0;
	}

};
struct SPLACE_NAME
{
	char		szName[20];
	SPLACE_NAME()
	{
		szName[0] = 0;
	}
};
struct USER_INFO
{
	unsigned int	dwUserId;
	char	szName[MAX_USERNAME_LEN];
	int		iTableId;
	int		iChairId;
	int		iState;
	unsigned int	dwLookAt;
	unsigned int	dwWin;
	unsigned int	dwLost;
	unsigned int	dwDogfall;
	unsigned int	dwDisconnect;
	unsigned int	dwEscape;
	int		iScore;

	//char	szAccount[50];
	unsigned int	dwHeadId;
	bool	bVIP;
	bool	bSex;							//false女
	//char	szCity[20];
	//char	szQuestion[50];					//密码提示问题
	//char	szAnswer[50];					//提示问题答案
	//char	szEmail[50];					//邮件
	//char	szLove[50];						//爱好
	//char	szPerSigned[100];				//个性签名
	//char	szNominatePeople[30];			//推荐人
	//char	szIDCard[20];					//身份证号
	int		iCharm;							//魅力值
	unsigned int	dwNumericAccount;				//数字账号
	long long	lMoney;							//乐币
	long long	lHappyBean;
	unsigned int	dwFlower;
	unsigned int	dwCountLoginTime;				//游戏总时间

	int			iMatchScore;
	int			iMatchPlace;
	//int		iMatchHonor;
	unsigned int		dwHonor;					//竞赛勋章
	unsigned int		dwPropFlowerNum;			//花的数量
	//unsigned int		dwPropVipNum;				//VIP卡的数量
	unsigned int		dwPropHornNum;				//喇叭数
	unsigned int		dwPropHornBigNum;			//大嗽叭
	unsigned int       dwPropAwardNum;				//抽奖卷
	//unsigned int		dwPropVipBigNum;			//大ＶＩＰ
	//unsigned int		dwPropVipSupperNum;			//超级ＶＩＰ
	int		wSubsidyNum;				//低保次数
	//wz add upload 在struct USER_INFO中加入两个变量
	char       szHeadImgName[20];          //头像名称
	//char		szVIPTime[50];

	//add by mx 2009.9.24
	int			iRealSex;				//验证性别
	bool        bSuperCharm;          //魅力达人
	bool        bVidicon;             //摄象头

	USER_INFO()
	{
		szName[0] = 0;
		szHeadImgName[0] = 0;
		dwPropAwardNum = 0 ;
//		szVIPTime[0] = 0;
	}

};

//add by mx 用户重要信息
struct USER_IMPORTANT_INFO
{
	unsigned int		dwUserId;		//用户ID

	long long		lHappyBean;		//乐豆
	long long		lMoney;			//金币

	unsigned int		dwFlower;		//花
	int			iCharm;			//魅力

	unsigned int		dwHornBig;		//喇叭
	unsigned int       dwAward;		//奖券
	unsigned int       dwHonor;		//勋章
};

enum AUTO_EXIT_REASON
{
	AUTO_EXIT_SYSMANAGE,		//系统托管
	AUTO_EXIT_NOREADY,			//一定时间没准备
};
//wm match
enum MATCH_TYPE
{
	MATCH_ALL,//混合模式
    MATCH_OUT,//打立出局模式
	MATCH_SCORE//定局积分制

};
enum MATCH_TAG
{
	TAG_FREE,
	TAG_HOT,
	TAG_NEW,
};
enum MATCH_STATE
{
	MATCH_STATE_READY,//筹备中
	MATCH_STATE_SIGN_UP,//报名中状态
	MATCH_STATE_IN_MATCH,//正在比赛中
	MATCH_STATE_END_MATCH,//比赛已经结束
	MATCH_STATE_SIGN_UP_TRUE,//已报名
};
enum MATCH_MODE
{
	MATCH_FREE_LOOP,//自由循环赛
	MATCH_HOUR_LOOP,//定点循环赛
	MATCH_DAY_LOOP,//日循环赛
	MATCH_WEEK_LOOP,//周循环赛
	MATCH_COMMITTAL,//赞助赛
	MATCH_SUPER,//大奖赛
};
enum MATCH_BONUS_TYPE
{
	MATCH_BONUS_ZERO,///自由循环金币奖励
	MATCH_BONUS_ONE,//10QB奖励
	MATCH_BONUS_TWO,//50手机充值卡奖励
	MATCH_BONUS_THREE,//200元现金奖
	MATCH_BONUS_FOUR,//5QB奖励
	MATCH_BONUS_FIVE,//20手机充值卡奖励
	MATCH_BONUS_SIX,//节日金币奖励

};
//end
enum PROP_TYPE//道具
{
	PROP_FLOWER,	//只能使用

	PROP_VIP = 1,	//与库中ＩＤ相对应
	PROP_VIPBIG,
	PROP_VIPSUPPER,
	PROP_HORN,
	PROP_HORN10,
	PROP_HORNBIG,
	PROP_UPLOAD,//wz add upload new 333 道具上传图片
	PROP_AWARD//抽奖卷道具 wm7.31add
};

enum USE_FLOWER_RESULT_TYPE
{
	FLOWER_NOMONEY,
	FLOWER_NOPEOPLE,
	FLOWER_MYSELF,
	FLOWER_ACCESS,
	FLOWER_FREEZE_MONEY,//modify by mx 2009.11.27 冻结资金不足
};
enum USE_HORN_RESULT_TYPE
{
	USE_HORN_FAILE,
	USE_HORN_ACCESS,
};

enum DONATE_PROP_RESULT_TYPE
{
	DONATE_NOMONEY,
	DONATE_NOPEOPLE,
	DONATE_MYSELF,
	DONATE_ACCESS,
	DONATE_OUT_MAX,//modify by mx 2009.9.10 赠送道具上限
	DONATE_FREEZE_MONEY,//modify by mx 2009.11.27 冻结资金不足
};

enum SUBSIDY_RESULT_TYPE
{
};

enum BUY_PROP_REVERT
{
	BUY_FAIL,
	BUY_SUCCESS,
	BUY_OUT_MAX,
	BUY_FREEZE_MONEY,//modify by mx 2009.11.27 冻结资金不足
};

enum
{
	BONUS_ADD,				//奖金收集
	BONUS_TIMEUP_ADD,		//到抽奖时间但是需要继续收集奖金
	BONUS_ROLL,				//抽奖中
};

//add by mx
enum LEVEL_TYPE
{
	LEVEL_TYPE_SCORE = 0,	//积分
	LEVEL_TYPE_MONEY,		//金币
	LEVEL_TYPE_HEPPYBEAN,	//乐豆
};

#define	MULTI_INFO_NUM		100	//多人信息发送人数
////////////

//add by mx 2009.9.24
enum REAL_SEX
{
	REAL_SEX_NO_CHECK = 0, //未验证
	REAL_SEX_WOMAN = 1,    //已验证为女性玩家
};

#define UPTO_SUPER_CHARM_NUM       5000
#define DOWNTO_SUPER_CHARM_NUM     4500

/////////////////////////////////////////////////////////////////////////////////////////////////////
//games

enum GAME_ID
{
	GAME_TJMJ,
	GAME_ZJH,
	GAME_DDZ,
	GAME_TJMJ2,
	GAME_BJL,
	GAME_TGMJ,
	GAME_WZQ,
	GAME_BIE7,//wz add bie7
	GAME_BIE7SEC,//wz add bie7
	GAME_LHMJ,					//乐呵麻将
	GAME_LHMJ2,					//乐呵二人麻将
	GAME_WHNC,
	GAME_ZHY,					//砸红A
	GAME_TGM2,					//塘沽毛2
	GAME_TGM4,					//塘沽毛4
	GAME_ZLJ,					//砸六家
	GAME_PGJ,					//苹果机
	GAME_TSDC,					//唐山打储
	GAME_JS_DDZ,                /// wm add jsgame
	GAME_JS_TJMJ,
	GAME_JS_TGMJ,
	GAME_JS_ZLJ,
	GAME_GZ,
	GAME_CN,
	GAME_JS_TGM2,

	GAME_NUM,
};

//Operator State of TSDC
enum GAME_TSDC_OPERATOR_STATE
{
	TSDC_OPERATOR_STATE_CENGCHU,							//蹭储
	TSDC_OPERATOR_STATE_XIAN_NORMAL,						//闲家：包打，平踹，缴牌，平打
	TSDC_OPERATOR_STATE_ZHUANG_NORMAL,						//庄家：包打，反踹，缴牌，平打
	TSDC_OPERATOR_STATE_GENCHUAI_JIAOPAI,					//庄闲：跟踹，缴牌
	TSDC_OPERATOR_STATE_BAODA_JIAOPAI,						//庄闲：包打，缴牌
	TSDC_OPERATOR_STATE_BAODA_JIAOPAI_PINGDA,				//庄闲：包打，缴牌，平打
	TSDC_OPERATOR_STATE_ZHUANG_FANCHAUI_JIAOPAI_PINGDA,		//庄家：反踹，缴牌，平打

	TSDC_OPERATOR_STATE_BAODA_GENCHUAI_JIAOPAI,				//庄闲：包打，跟踹，缴牌
};

//The type of Chuai(梦踹，平踹，跟踹，反踹)
enum GAME_TSDC_CHUAI_TYPE
{
	TSDC_CHUAI_TYPE_MENG_CHUAI,
	TSDC_CHUAI_TYPE_PING_CHUAI,
	TSDC_CHUAI_TYPE_GEN_CHUAI,
	TSDC_CHUAI_TYPE_FAN_CHUAI,
};

typedef struct
{
	int wType;
	int wScore;
	char szName[20];
}STJMJHu,STGMJHu,SLHMJHu;


typedef struct
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
}STJMJUserData,STGMJUserData,SDDZUserData,SLHMJUserData,SZLJUserData,STSDCUserData;




///////////////////////////////////////////////////////////////////////////////////////////////////////

//麻将牌
struct SMJPai
{
	int id;
	int type;
	int num;

	bool operator == ( SMJPai & a )
	{
		if( type == a.type && num == a.num )
			return true;
		else
			return false;
	}

	bool operator != ( SMJPai & a )
	{
		if( type != a.type || num != a.num )
			return true;
		else
			return false;
	}
};

//麻将牌类型
enum MJ_PAI_TYPE
{
	MJ_BING,
	MJ_WAN,
	MJ_TIAO,
	MJ_FENG,
	MJ_HUA,
};


//胡牌类型
enum HU_TYPE
{
	HU_NONE,

	//天津麻将&塘沽麻将
	HU_HUNDIAO,
	HU_GANG_HUNDIAO,
	HU_SU_TI,
	HU_GANG_TI,
	HU_GANG_SU_TI,
	HU_ZHUO5,
	HU_SU_ZHUO5,
	HU_GANG_ZHUO5,
	HU_GANG_SU_ZHUO5,
	HU_SHUANG,
	HU_GANG_SHUANG,
	HU_LONG,
	HU_SU_LONG,
	HU_ZHUO5_LONG,
	HU_SU_ZHUO5_LONG,
	HU_HUNDIAO_LONG,
	HU_GANG_LONG,
	HU_GANG_SU_LONG,
	HU_GANG_SU_ZHUO5_LONG,
	HU_GANG_ZHUO5_LONG,
	HU_GANG_HUNDIAO_LONG,
	HU_BENHUN_LONG,
	HU_HUNDIAO_BENHUN_LONG,
	HU_BENHUN_ZHUO5_LONG,
	HU_GANG_BENHUN_LONG,
	HU_GANG_HUNDIAO_BENHUN_LONG,
	HU_SHUANG_LONG,
	HU_SHUANG_BENHUN_LONG,
	HU_GANG_BENHUN_ZHUO5_LONG,
	HU_TIANHU,


	HU_HUNDIAO_ZHUO5,
	HU_HUNDIAO_ZHUO5_LONG,
	HU_BAOCHENG,
	HU_BAOCHENG_ZHUO5,
	HU_BAOCHENG_LONG,
	HU_BAOCHENG_ZHUO5_LONG,
	HU_GANCHA,
	HU_GANCHA_ZHUO5,
	HU_GANCHA_LONG,
	HU_GANCHA_ZHUO5_LONG,
	HU_7D,
	HU_HUNDIAO_7D,
	HU_SU_7D,
	HU_ZHUO5_7D,
	HU_SU_ZHUO5_7D,
	HU_HUNDIAO_ZHUO5_7D,
	HU_BAOCHENG_7D,
	HU_BAOCHENG_ZHUO5_7D,
	HU_GANCHA_7D,
	HU_GANCHA_ZHUO5_7D,
	HU_MANGUAN,
	HU_SU_MANGUAN,
	HU_ZHUO5_MANGUAN,
	HU_SU_ZHUO5_MANGUAN,
	HU_HUNDIAO_MANGUAN,
	HU_HUNDIAO_ZHUO5_MANGUAN,
	HU_BAOCHENG_MANGUAN,
	HU_BAOCHENG_ZHUO5_MANGUAN,
	HU_GANCHA_MANGUAN,
	HU_GANCHA_ZHUO5_MANGUAN,
	HU_DATAI,
	HU_DATAI_7D,
	HU_DATAI_LONG,
	HU_DATAI_ZHUO5,
	HU_DATAI_ZHUO5_LONG,
	HU_DATAI_ZHUO5_7D,
	HU_DATAI_MANGUAN,
	HU_DATAI_ZHUO5_MANGUAN,
	HU_DATAI2,
	HU_DATAI2_7D,
	HU_DATAI2_LONG,
	HU_DATAI2_ZHUO5,
	HU_DATAI2_ZHUO5_LONG,
	HU_DATAI2_ZHUO5_7D,
	HU_DATAI2_MANGUAN,
	HU_DATAI2_ZHUO5_MANGUAN,


	//乐呵麻将

	//88翻
	HU_LH_DASIXI,				//大四喜
	HU_LH_DASANYUAN,			//大三元
	HU_LH_LVYISE,				//绿一色
	HU_LH_JIULIANBAODENG,		//九莲宝灯
	HU_LH_SIGANG,				//四杠
	HU_LH_LIANQIDUI,			//连7对
	HU_LH_SHISANYAO,			//十三幺

	//64翻
	HU_LH_QINGYAOJIU,			//清幺九
	HU_LH_XIAOSIXI,				//小四喜
	HU_LH_XIAOSANYUAN,			//小三元
	HU_LH_ZIYISE,				//字一色
	HU_LH_SIANKE,				//四暗刻
	HU_LH_YISESHUANGLONGHUI,	//一色双龙会

	//48翻
	HU_LH_YISESITONGSHUN,		//一色四同顺
	HU_LH_YISESIJIEGAO,			//一色四节高

	//32翻
	HU_LH_YISESIBUGAO,			//一色四步高
	HU_LH_SANGANG,				//三杠
	HU_LH_HUNYAOJIU,			//混幺九

	//24翻
	HU_LH_QIDUI,				//7对
	HU_LH_QIXINGBUKAO,			//7星不靠
	HU_LH_QUANSHUANGKE,			//全双刻
	HU_LH_QINGYISE,				//清一色
	HU_LH_YISESANTONGSHUN,		//一色三同顺
	HU_LH_YISESANJIEGAO,		//一色三节高
	HU_LH_QUANDA,				//全大
	HU_LH_QUANZHONG,			//全中
	HU_LH_QUANXIAO,				//全小

	//16翻
	HU_LH_QINGLONG,				//清龙
	HU_LH_SANSESHUANGLONGHUI,	//三色双龙会
	HU_LH_YISESANBUGAO,			//一色三步高
	HU_LH_QUANDAIWU,			//全带五
	HU_LH_SANTONGKE,			//三同刻
	HU_LH_SANANKE,				//三暗刻

	//12翻
	HU_LH_QUANBUKAO,			//全不靠
	HU_LH_ZUHELONG,				//组合龙
	HU_LH_DAYUWU,				//大于5
	HU_LH_XIAOYUWU,				//小于5
	HU_LH_SANFENGKE,			//三风刻

	//8翻
	HU_LH_HUALONG,				//花龙
	HU_LH_TUIBUDAO,				//推不倒
	HU_LH_SANSESANTONGSHUN,		//三色三同顺
	HU_LH_SANSESANJIEGAO,		//三色三节高
	HU_LH_WUFANHU,				//无翻胡
	HU_LH_MIAOSHOUHUICHUN,		//妙手回春
	HU_LH_HAIDILAOYUE,			//海底捞月
	HU_LH_GANGSHANGKAIHUA,		//杠上开花
	HU_LH_QIANGGANGHU,			//抢杠胡

	//6翻
	HU_LH_PENGPENGHU,			//碰碰胡
	HU_LH_HUNYISE,				//混一色
	HU_LH_SANSESANBUGAO,		//三色三步高
	HU_LH_WUMENQI,				//五门齐
	HU_LH_QUANQIUREN,			//全求人
	HU_LH_SHUANGANGANG,			//双暗杠
	HU_LH_SHUANGJIANKE,			//双箭刻

	//4翻
	HU_LH_QUANDAIYAO,			//全带幺
	HU_LH_BUQIUREN,				//不求人
	HU_LH_SHUANGMINGGANG,		//双明杠
	HU_LH_HUJUEZHANG,			//胡绝张

	//2翻
	HU_LH_JIANKE,				//箭刻
	HU_LH_QUANFENGKE,			//圈风刻
	HU_LH_MENFENGKE,			//门风刻
	HU_LH_MENQIANQING,			//门前清
	HU_LH_PINGHU,				//平胡
	HU_LH_SIGUIYI,				//四归一
	HU_LH_SHUANGTONGKE,			//双同刻
	HU_LH_SHUANGANKE,			//双暗刻
	HU_LH_ANGANG,				//暗杠
	HU_LH_DUANYAO,				//断幺

	//1翻
	HU_LH_YIBANGAO,				//一般高
	HU_LH_XIXIANGFENG,			//喜相逢
	HU_LH_LIULIAN,				//六连
	HU_LH_LAOSHAOFU,			//老少副
	HU_LH_YAOJIUKE,				//幺九刻
	HU_LH_MINGGANG,				//明杠
	HU_LH_QUEYIMEN,				//缺一门
	HU_LH_WUZI,					//无字
	HU_LH_BIANZHANG,			//边张
	HU_LH_KANZHANG,				//坎张
	HU_LH_DANDIAOJIANG,			//单钓将
	HU_LH_ZIMO,					//自摸
	HU_LH_TING,					//报听
	HU_LH_HUAPAI,				//花牌


	//

	HU_MAX,
};

//胡牌判断，副，刻
struct SMJFu
{
	SMJPai		pai[3];
	int			type;
};

//副，刻
enum MJ_FU_TYPE
{
	FU_12,
	FU_13,
	FU_123,
	KE_1,
	KE_12,
	KE_123,
	SHUANG_5,
};

//杠类型
enum MJ_GANG_TYPE
{
	GANG_MING,
	GANG_AN,
	GANG_JIN,
};

//===================================咂六家=========================================
struct SZLJPai
{
	int id;
	int value;
	int num;
	int type;
	bool bMate;				//是否能配

	SZLJPai()
	{
		bMate = false;
	}

	SZLJPai * operator = ( SZLJPai * pCard )
	{
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;
		this->bMate = pCard->bMate;

		return this;
	}
};
//===================================逗地主=========================================
struct SDDZPai
{
	int id;
	int value;
	int num;
	int type;

	SDDZPai * operator = ( SDDZPai * pCard )
	{
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}
};
//===================================唐山打储=========================================
struct STSDCPai
{
	int id;
	int value;
	int num;
	int type;

	STSDCPai * operator = ( STSDCPai * pCard )
	{
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}
};
//===================================诈金花=========================================
struct SZJHPai
{
	int id;
	int num;
	int type;

	SZJHPai * operator=( SZJHPai *pCard )
	{
		this->id   = pCard->id;
		this->num  = pCard->num;
		this->type = pCard->type;

		return this;
	}
};

enum PaiType
{
	ZJH_NONE,
	ZJH_BAOZI,
	ZJH_SHUNJIN,
	ZJH_JINHUA,
	ZJH_SHUNZI,
	ZJH_DUIZI,
	ZJH_TESHU,	//2，3，5
	ZJH_SANPAI,
};

struct SZJHUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};


struct SUserInfo_INGAME_ANSWER
{
	unsigned int dwUserID;
	bool bExist;
	bool bGiveUp;
	bool bFail;
	bool bKanPai;
};

struct SUserInfo_UPDATE_USER
{
	unsigned int dwUserID;
	int	nChairID;
	bool bExist;
};

//===================================百家乐=========================================
struct SBJLPai
{
	int id;
	int num;
	int type;

	SBJLPai * operator=( SBJLPai *pCard )
	{
		this->id   = pCard->id;
		this->num  = pCard->num;
		this->type = pCard->type;

		return this;
	}
};

//====================================组队===============================
struct SMemberInfo
{
	unsigned int	dwUserId;
	unsigned int	dwTeamId;
	char	szName[20];
	char	szHeadImgName[20];
	int		iScore;	//积分
	int		iDistinct;
	int		iSplace;
	SMemberInfo()
	{
		szName[0] = 0;
		dwTeamId = 0;
	}
};
struct STeamInfo
{
	unsigned int		dwMemberId[3];	//第０个无素为队长ID
	bool		bReady;			//队伍已准备
	STeamInfo()
	{
		bReady = false;
		dwMemberId[0] = 0;
		dwMemberId[1] = 0;
		dwMemberId[2] = 0;
	}
};


#define BJL_CARD_NUM		3			//庄/闲 最大牌数
#define BJL_MAX_WAIT_ZHUANG_NUM		5	//最大申请上庄人数
#define	BJL_MAX_TABLE_NUM		20			//一桌最大人数
#define MAX_ZHUANG_NUM		20			//坐庄最大局数
#define MIN_ZHUANG_MONEY	100000			//最小做庄钱数

//#define	XIAZHU_TIME		20			//下注时间(秒)

#define	XIAZHU_INFO_MAX_NUM_ONCE	100	//一次发送下注信息的最大数量

enum XaiZhuType
{
	ZHUANG=0,//押庄
	ZTIANWANG,//押庄天王
	ZDUI,///押庄对子
	XIAN,//押闲
	XTIANWANG,//押闲天王
	XDUI,//;押闲对子
	PING,//押平
	PTONGDIAN,//押同点平
};

struct SBJLXiaZhuInfo
{
	int	wType;//下注类型
	int	wJeton;//下注筹码
};

struct SBJL_SQZhuangInfo
{
	char	szUserName[MAX_USERNAME_LEN];
	long long	lMoney;

	SBJL_SQZhuangInfo()
	{
		::memset( szUserName, 0, sizeof(char) * MAX_USERNAME_LEN );
		lMoney = -1;
	}
};

struct SBJLUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};

enum BJL_XIAZHU_ERROR
{
	BJL_ERROR_XIAZHU_SUCCESS,//下注成功
	BJL_ERROR_XIAZHU_OVER_PLAYER_MONEY,//超过玩家自身的总金币
	BJL_ERROR_XIAZHU_OVER_KEXIA,//下注超过可下分
};

enum BJL_SQ_SHANGZHUANG_ERROR_MESSAGE
{
	BJL_SZ_ERROR_SUCCESS,//申请上庄成功
	BJL_SZ_ERROR_ZHUANG_SQ,//庄家不能申请上庄
	BJL_SZ_ERROR_SHANGZHUANG_MONEY_NOT_MIN,//上庄申请的钱不足10W
	BJL_SZ_ERROR_SHANGZHUANG_MONEY_NOT_ENOUGH,//上庄申请的钱超过自己的总值
	//BJL_SZ_ERROR_SHANGZHUANG_MONEY_LESS_THAN_LAST,//申请的钱数小于列表中前次申请的钱数
	BJL_SZ_ERROR_IN_SQLST,//已经在申请列表中
};

enum BJL_CANCEL_SQLST_ERROR_MESSAGE
{
	BJL_CANCEL_SQ_SUCCESS,//申请取消成功
	BJL_CANCEL_SQ_NOT_IN_SQLST,//不在申请列表中
};

enum BJL_XIAZHUANG_REASON
{
	BJL_COMPLETE_20 = 0,//完成20局庄，自动下庄
	BJL_REQUEST,//申请下庄
	BJL_NO_MONEY,//不足10W，自动下庄
	BJL_FORCE_LEAVE,//强制退出
	BJL_USER_DROP,//掉线
};

enum BJL_KICK_OUT_SQLIST_REASON
{
	BJL_KICK_SQLIST_NO_MONEY,         //当前金币少于申请上庄金币
	BJL_KICK_SQLIST_MONEY_LESS,       //当前列表中有5个比自己申请上庄金币数多，则被T出
	BJL_KICK_SQLIST_MONEY_LESS_B,     //申请的钱低于申请列表中的5个人的钱数时，则申请失败
};

//==============================好友============================
struct FRIEND_ROOM_INFO
{
	unsigned int		dwRoomId;                   //房间id
	char		szRoomName[20];				//房间名字

	FRIEND_ROOM_INFO()
	{
		dwRoomId = 1000;
		szRoomName[0] = 0;
	}
};

//====================五子棋=============================================

enum WZQ_GAME_TYPE
{
	NO_FORBIDDEN_MODE,						//无禁手模式
	FORBIDDEN_MODE,							//禁手模式
};

enum CHESSMAN_STATE							//棋盘中的棋子状态
{
	NONE_CHESSMAN,							//无子
	BLACK_CHESSMAN,							//黑子
	WHITE_CHESSMAN,							//白子
};
struct ChessmanInfo
{
	int x;
	int y;
	CHESSMAN_STATE chessmanState;

	void InitChessmanInfo()
	{
		this->x = -1;
		this->y = -1;
		this->chessmanState = NONE_CHESSMAN;
	}
};

#define CHESSBOARD_GRID_NUM		15			//棋盘横向或纵向的点数 N
#define CHESSBOARD_GRID_TITLE_NUM   (CHESSBOARD_GRID_NUM * CHESSBOARD_GRID_NUM)

enum CHESS_RES						//不能下棋的返回码
{
	NORMAL_RES,			           //返回正确，无禁手，无胜利
	FORBIDDEN_33,                   //先手方33禁手
	FORBIDDEN_44,                   //先手方44禁手
	FORBIDDEN_LONG,                 //先手方6子长连禁手
	BLACK_WIN,                      //黑方胜
	WHITE_WIN,                      //白方胜           r
	DEUCE,                          //棋盘下满，平手
	BLACK_GIVE_UP_WHITE_WIN,		//黑方认输，白方胜
	WHITE_GIVE_UP_BLACK_WIN,		//白方认输，黑方胜
	REQUEST_DEUCE_SUCCESS,			//求和成功，和棋
	BLACK_BOUT_TIME_OUT,			//黑方单回合超时
	WHITE_BOUT_TIME_OUT,			//白方单回合超时
	BLACK_TOTAL_TIME_OUT,			//黑方总时间超时
	WHITE_TOTAL_TIME_OUT,			//白方总时间超时
	FORCE_EXIT_GAME_OVER,			//强制退出
};

enum XIAQI_ERROR
{
	SETCM_BE_OUT,                   //摆放棋子的位置超出棋盘范围
	FIRST_SET_FORBIDDEN,			//第一步棋不能在棋盘中心8*8围成的正方形之外
	SETCM_BE_EXIST,                 //摆放棋子的位置已经存在棋子
	HUIQI_SET_FORBIDDEN,				//在对方申请悔棋的时候，不能下棋
};

struct SWZQUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};

//===================================憋七=========================================
struct SBIE7UserData//wz add bie7
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};
struct SBIE7Pai
{
	int id;
	int type;
	int num;
};
struct SBIE7Hu
{
	int wType;
	int wScore;
	char szName[20];
};

//====================我画你猜================================//
enum TIMEOUT
{
	TIMEOUT_20,
	TIMEOUT_99,
};
enum
{
	REDRAW,
	DRAWS,
	DRAWPOLYGON,
};
enum DRAW_COLOR
{
	BLACK,
	BLUE,
	PURPLE,
	GREEN,
	YELLOW,
	ORANGE,
	RED,
	PINK,
	WHITE,//橡皮擦
};
enum LINE_WIDTH
{
	L_NORMAL,
	L_WIDTH,
	L_EX_WIDTH,
};
//点，手绘，线，矩形，圆，橡皮
enum LINE_SHAPE
{
	LINE_NONE,
	POINT_EX,
	HANDWRIGHT,
	LINE,
	RECTANGLE,
	ELLIPSE,
	CIRCLE,
	POLYGON,
	ERASER,//橡皮擦
};
struct SWHNCUserInfo
{
	bool			bExist;
	unsigned int			dwUserID;
};
struct SWHNCUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};

struct POINT
{
	int x;
	int y;
};
struct DrawGroup
{
	POINT	pDown;
	POINT	pUp;
	int	wLineWidth;
	int	wColor;
	int	wLineStatus;
};
struct DrawGroupEx
{
	POINT	pDown;
	POINT	pUp;
	int	wLineWidth;
//	COLORREF	wColor;		//改进
	int	wLineStatus;

	bool	bClearImage;
};

////////////////////////////////////////////

//===================================砸红A=========================================
struct SZHYPai
{
	int index;
	int id;
	int value;
	int num;
	int type;

	SZHYPai * operator = ( SZHYPai * pCard )
	{
		this->index = pCard->index;
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}

	SZHYPai()
	{
		this->index = 0;
		this->id = 0;
		this->value = 0;
		this->num = 0;
		this->type = 0;
	}

	void InitPai()
	{
		this->index = 0;
		this->id = 0;
		this->value = 0;
		this->num = 0;
		this->type = 0;
	}
};

typedef struct
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
}SZHYUserData;

enum //叫牌提示种类
{
	ZHY_JIAO_TYPE_NONE,//无
	ZHY_JIAO_TYPE_TAN_XUAN_BAO,//摊宣报
	ZHY_JIAO_TYPE_TAN_XUAN,//摊宣
	ZHY_JIAO_TYPE_TANBAO,//摊报
	ZHY_JIAO_TYPE_SHE,//舍
	ZHY_JIAO_TYPE_SHE2,//再舍
	ZHY_JIAO_TYPE_CHUAI,//踹
	ZHY_JIAO_TYPE_CHUAI2,//跟踹
	ZHY_JIAO_TYPE_FAN_CHUAI,//反踹
	ZHY_JIAO_TYPE_FIND_FRIEND,//找朋友
	ZHY_JIAO_TYPE_FIND_FRIEND2,//跟亮
	ZHY_JIAO_TYPE_CHIBUZHU,//吃补助
	//ZHY_JIAO_TYPE_GUO,//过

	ZHY_JIAO_TYPE_SUM,//叫牌类型总数
};

enum //打牌提示种类
{
	ZHY_DA_TYPE_CHUPAI_GUO_TISHI,//出牌过提示
	ZHY_DA_TYPE_CHUPAI,
	//ZHY_DA_TYPE_GUO,//过

	ZHY_DA_TYPE_SUM,//打牌类型总数
};

enum //叫牌种类
{
	ZHY_JIAO_XUAN,//宣
	ZHY_JIAO_TAN,//摊
	ZHY_JIAO_BAO,//报
	ZHY_JIAO_TANBAO,//摊报
	ZHY_JIAO_SHE,//舍
	ZHY_JIAO_FINDFRIEND,//找朋友
	ZHY_JIAO_FINDFRIEND2,//跟亮（找朋友）
	ZHY_JIAO_CHUAI,//踹
	ZHY_JIAO_FAN_CHUAI,//反踹
	ZHY_JIAO_GUO,//过
	ZHY_JIAO_CHIBUZHU,//吃补助
};

enum
{
	ZHY_FAN_NONE,//未设置
	ZHY_FAN_XUAN,//宣
	ZHY_FAN_TAN,//摊
	ZHY_FAN_BAO,//报
	ZHY_FAN_TANBAO,//摊报
};

struct SZHYCountUserInfo
{
	char	szUserName[MAX_USERNAME_LEN];//呢称
	int	wJiapType;//叫牌类型（摊宣报）
	int	wShe;//舍的次数
	bool	bChuai;//踹
	bool	bFanChuai;//反踹
	bool	bShowFriend;//找朋友亮牌
	bool	bChiBuZhu;//吃补助
	bool	bDaNiEr;//打泥儿
	int	wFan;//番
	long long	lScore;//输赢的积分

	SZHYCountUserInfo()
	{
		::memset( this->szUserName, 0, sizeof(char) * MAX_USERNAME_LEN );
		this->wJiapType = ZHY_FAN_NONE;
		this->wShe = 0;
		this->bChuai = false;
		this->bFanChuai = false;
		this->bShowFriend = false;
		this->bChiBuZhu = false;
		this->bDaNiEr = false;
		this->wFan = 0;
		this->lScore = 0;
	}
};


struct STSDCCountUserInfo
{
	unsigned int	dwUserId;
	bool	bZhuang;
	bool	bCengChu;	//蹭储
	bool	bMengChuai;	//踹
	bool	bXuan;		//宣
	bool	bMengXuan;	//梦宣
	bool	bChuai;		//踹
	bool	bFanChuai;	//反踹
	bool	bGenChuai;	//跟踹
	bool	bBeiBaoDa;	//被包打
	bool	bJiaoPai;	//缴牌
	bool	bQuanBu;	//全捕
	int		iScore;		//输赢的积分

	int		iPlace;

	int	wPai[13];
	int	wNum;

	STSDCCountUserInfo()
	{
		iPlace = 0;
		bZhuang = false;
		bCengChu = false;	//蹭储
		bMengChuai = false;	//踹
		bXuan = false;;		//宣
		bMengXuan = false;	//梦宣
		bChuai = false;		//踹
		bFanChuai = false;	//反踹
		bGenChuai = false;	//跟踹
		bBeiBaoDa = false;	//被包打
		bJiaoPai = false;	//缴牌
		bQuanBu = false;	//全捕
		iScore = 0;			//输赢的积分
		memset( wPai, 0, sizeof(int) * 13);
		wNum = 0;
	}
};

struct SZHYPlayerInfo
{
	unsigned int	dwChairId;

	bool	bShowPai;
	int	wPai[6];
	int	wPaiNum;

	int	wJiapType;//叫牌类型（摊宣报）
	int	wShe;//舍的次数
	bool	bChuai;//踹
	bool	bFanChuai;//反踹
	bool	bShowFriend;//找朋友亮牌
};









///////////////////////////////////////////
//苹果机


enum PGJ_RUN_TYPE
{
	PRT_NORMAL,
	PRT_SECOND_OFF,				//加油站，熄火
	PRT_SECOND_ON,				//加油站，继续
	PRT_BAR,					//普通BAR
	PRT_BIG3,					//大三元
	PRT_SMALL3,					//小三元
	PRT_BAR3,					//BAR三个全中
	PRT_TRAIN,					//开火车
	PRT_DAJIALE,				//大家乐
	PRT_FOUR,					//四通
	PRT_TWO,					//对位
};

//=============== 塘沽毛2 毛4 ===========================

struct STGMPai
{
	int index;
	int id;
	int value;
	int num;
	int type;

	STGMPai * operator = ( STGMPai * pCard )
	{
		this->index = pCard->index;
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}

	STGMPai()
	{
		this->index = 0;
		this->id = 0;
		this->value = 0;
		this->num = 0;
		this->type = 0;
	}

	void InitPai()
	{
		this->index = 0;
		this->id = 0;
		this->value = 0;
		this->num = 0;
		this->type = 0;
	}
};

typedef struct
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
}STGM2UserData, STGM4UserData;

struct STGMPlayerInfo
{
	unsigned int	dwChairId;

	bool	bShowPai;
	int	wPai[22];
	int	wPaiNum;

	bool	bZhuang;
};

enum //打牌提示种类
{
	TGM_DA_TYPE_CHUPAI_GUO_TISHI,//出牌过提示
	TGM_DA_TYPE_CHUPAI,

	TGM_DA_TYPE_SUM,//打牌类型总数
};

enum //叫牌提示种类
{
	TGM_JIAO_TYPE_NONE,//无
	TGM_JIAO_TYPE_ZUOZHUANG_GUO,//坐庄 过
	TGM_JIAO_TYPE_QIANGZHUANG_GUO,//抢庄 过
	TGM_JIAO_TYPE_TIZHUANG_BUTI,//踢庄 不踢

	TGM_JIAO_TYPE_SUM,
};

enum //叫牌种类
{
	TGM_JIAO_ZUOZHUANG,//坐庄
	TGM_JIAO_QIANGZHUANG,//抢庄
	TGM_JIAO_TIZHUANG,//踢庄
	TGM_JIAO_BUTI,//不踢
	TGM_JIAO_GUO,//过
};

struct STGMCountUserInfo
{
	char	szUserName[MAX_USERNAME_LEN];//呢称
	bool	bJiaoZhuang;//庄
	bool	bTiZhuang;//踢庄
	int	wQiangZhuang;//抢庄
	int	wFan;//番
	long long	lScore;//输赢的积分

	STGMCountUserInfo()
	{
		::memset( this->szUserName, 0, sizeof(char) * MAX_USERNAME_LEN );
		this->bJiaoZhuang = false;
		this->bTiZhuang = false;
		this->wQiangZhuang = 0;
		this->wFan = 0;
		this->lScore = 0;
	}
};

//====================吹牛=============================================
struct SCNUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};

//===================================拱猪===================================//
enum GZ_GAME_TYPE
{
	FREEDOM_MODE,									//自由区模式
	CHUYANGQUANLIANG_MODE,							//除羊全亮模式
};

struct SGZPai
{
	int index;
	int id;
	int value;
	int num;
	int type;

	SGZPai * operator = ( SGZPai * pCard )
	{
		this->index = pCard->index;
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}
	SGZPai()
	{
		this->index = 0;
		this->id	= 0;
		this->value = 0;
		this->num	= 0;
		this->type	= 0;
	}
	void InitPai()
	{
		this->index = 0;
		this->id	= 0;
		this->value = 0;
		this->num	= 0;
		this->type	= 0;
	}
};

struct SGZUserData
{
	unsigned int dwUserId;
	unsigned int dwWin;
	unsigned int dwLost;
	unsigned int dwDogfall;
	unsigned int dwDisconnect;
	unsigned int dwEscape;
	int	  iScore;
};

struct SMaiType
{
	bool bZhu;
	bool bYang;
	bool bBian;
	bool bA;

	SMaiType * operator = ( SMaiType * pMaiCard )
	{
		this->bZhu	= pMaiCard->bZhu;
		this->bYang	= pMaiCard->bYang;
		this->bBian = pMaiCard->bBian;
		this->bA	= pMaiCard->bA;

		return this;
	}

	SMaiType()
	{
		this->bZhu	= false;
		this->bYang = false;
		this->bBian = false;
		this->bA	= false;
	}

	void InitMaiPai()
	{
		this->bZhu	= false;
		this->bYang = false;
		this->bBian = false;
		this->bA	= false;
	}
};

struct SGZPlayerInfo
{
	unsigned int		dwChairId;
	char		szName[MAX_USERNAME_LEN];

	bool		bShowPai;

	int		wPai[13];
	int		wPaiNum;

	SMaiType	sMaiPai;

	int		wScorePai[16];
	int		wScorePaiNum;

	SGZPlayerInfo()
	{
		wPaiNum = 0;
		wScorePaiNum = 0;
		sMaiPai.InitMaiPai();
	}
};

struct SGZUserAccountInfo
{
	char	szUserName[MAX_USERNAME_LEN];	//呢称
	long long	lScore;							//输赢的积分

	SGZUserAccountInfo()
	{
		::memset( this->szUserName, 0, sizeof(char) * MAX_USERNAME_LEN );
		this->lScore = 0;
	}
};

struct SGZCountUsersInfo					//结算信息
{
	SGZUserAccountInfo	sCountUserInfo[4];
};

//=================================拱猪 END=================================//


#endif /* INCLUDE_COMMDEFINE_H_ */
