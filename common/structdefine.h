#ifndef STRUCT_DEFINE_H
#define STRUCT_DEFINE_H

#define MSG_GENERATE(name)\
	ROOM_TO_DATA_##name,\
	DATA_TO_ROOM_##name##_REP,

enum ZMQ_MSG {
//	ROOM_TO_DATA_GETUSER = 0,
//	DATA_TO_ROOM_GETUSER_REP,

	MSG_GENERATE(GETUSER)

//	ROOM_TO_DATA_REGSERVER,
//	DATA_TO_ROOM_REGSERVER_REP,

	MSG_GENERATE(REGSERVER)

//	ROOM_TO_DATA_LOGOUT,
//	DATA_TO_ROOM_LOGOUT_REP,

	MSG_GENERATE(LOGOUT)

//	ROOM_TO_DATA_CREATEHOST,		//主机创建
//	DATA_TO_ROOM_CREATEHOST_REP,

	MSG_GENERATE(CREATEHOST)

//	ROOM_TO_DATA_CHANGEHOST,		//主机改变，主机ID发生改变
//	DATA_TO_ROOM_CHANGEHOST_REP,

	MSG_GENERATE(CHANGEHOST)

//	ROOM_TO_DATA_UPDATEHOST,		//主机更新，当前人数改变
//	DATA_TO_ROOM_UPDATEHOST_REP,

	MSG_GENERATE(UPDATEHOST)

//	ROOM_TO_DATA_WORLDCHAT,			//世界聊天
//	DATA_TO_ROOM_WORLDCHAT_REP,

	MSG_GENERATE(WORLDCHAT)

	MSG_GENERATE(FRIEND_ENTER_GAME)//好友进入游戏
	MSG_GENERATE(FRIEND_LEAVE_GAME)
	MSG_GENERATE(FRIEND_ENTER_ROOM)
	MSG_GENERATE(FRIEND_LEAVE_ROOM)
	MSG_GENERATE(FRIEND_ENTER_HOST)
	MSG_GENERATE(FRIEND_LEAVE_HOST)
	MSG_GENERATE(FRIEND_CONNECT)
	MSG_GENERATE(FRIEND_DISCONNECT)

	MSG_GENERATE(FRIEND_CHANGE_HOST)//30

	PUB_TO_ROOM_PHP_BASEINFO,//32 php发送的基本信息(更新pb, rb, exp)

	MSG_GENERATE(GETMAPLIST)				//33,34获取地图列表

	ROOM_TO_DATA_UPDATE_BASEINFO,//35 更新基础信息

	PHP_TO_DATA_UPDATE_BASEINFO,			//php更新信息到dataserver

	ROOM_TO_DATA_GAMEEND, 					//37,游戏结束

	DATA_TO_ROOM_UNDEFIEN_REP,				///<38

	PUB_TO_ROOM_PHP_SELECTTANK, 			///<39 换坦克

	PUB_TO_ROOM_PHP_SELECTCOAT,				///<40 选择涂装

	PUB_TO_ROOM_PHP_POWER_USE,				///<41 体力消耗(PHP发往ROOM)

	PUB_TO_ROOM_BUYPOWER,					///<42购买体力

	ROOM_TO_DATA_POWER_USE, 				///<43 体力消耗(ROOM发往PHP)

	PUB_TO_ROOM_TANKFORCE,					///<44坦克强化

	PUB_TO_ROOM_TANKPARTLEVEL, 				///<45坦克部件升级
	PUB_TO_ROOM_TANKDEVELOP, 				///<46坦克研发

	PUB_TO_ROOM_ARMY_TEQ_UPLEVEL,			///<47军团技能升级

	PUB_TOROOM_ADD_HP, 						///<48加满血

	PUB_TO_ROOM_REBORN,						///<49重生

	PUB_SERVER_MSG,							///<50服务器公告

	ROOM_TO_DATA_SWAP_PLACE,				///<５１

};

enum ACHIEVEMENT_TYPE {
	ACHIEVEMENT_TYPE_HERT = 1,	//1, 累计输出伤害;
//	ACHIEVEMENT_TYPE_KILL,		//2, 累计击杀;
	ACHIEVEMENT_TYPE_BEHERT,	//3, 累计受到伤害;
	ACHIEVEMENT_TYPE_VIP,		//4, VIP身份,
	ACHIEVEMENT_TYPE_PROPS,		//5, 拥有道具(具体道体见achievement_needid),
	ACHIEVEMENT_TYPE_USE_TANK,	//6, 使用坦克击杀(具体坦克类型见achievement_needid),

	ACHIEVEMENT_TYPE_HERT_PERCENT = 9, 	//单场次总输出达到己方总伤害百分比
	ACHIEVEMENT_TYPE_KILL = 10,			//10,单场次击杀
	ACHIEVEMENT_TYPE_DEATH = 11,		//11,单场次死亡
	ACHIEVEMENT_TYPE_OVERTAKE = 12,		//反超(杀)
	ACHIEVEMENT_TYPE_MAX_KILL = 13,		//最大击杀
};

//enum ZMQ_MSG {
//
//	ROOM_TO_DATA_GETUSER = 0,
//	DATA_TO_ROOM_GETUSER_REP,
//
//	ROOM_TO_DATA_REGSERVER,
//	DATA_TO_ROOM_REGSERVER_REP,
//
//	ROOM_TO_DATA_LOGOUT,
//	DATA_TO_ROOM_LOGOUT_REP,
//
//	ROOM_TO_DATA_CREATEHOST,		//主机创建
//	DATA_TO_ROOM_CREATEHOST_REP,
//
//	ROOM_TO_DATA_CHANGEHOST,		//主机改变，主机ID发生改变
//	DATA_TO_ROOM_CHANGEHOST_REP,
//
//	ROOM_TO_DATA_UPDATEHOST,		//主机更新，当前人数改变
//	DATA_TO_ROOM_UPDATEHOST_REP,
//
//	ROOM_TO_DATA_WORLDCHAT,			//世界聊天
//	DATA_TO_ROOM_WORLDCHAT_REP,
//
//	DATA_TO_ROOM_UNDEFIEN_REP,
//
//};

#pragma pack(push, 1)
struct SHostInfo {
	unsigned int nHostId;
	unsigned int nMaxNum;
	unsigned int nCurNum;
	unsigned int nMode;
	unsigned int nHostState;
	char szPwd[6];
	bool bLock;

	unsigned int nSceneID;			//map or scene id
	unsigned int nTargetNum;

	unsigned int nLevel;

	unsigned int nBaseScore;			//底金

	unsigned int nBasePMoney;
	unsigned int nIndex;			//主机索引
	SHostInfo() {
		nBaseScore = 0;
		nBasePMoney = 0;
		nHostId = 0;
		nMaxNum = 32;
		nCurNum = 0;
		nMode = 0;
		szPwd[0] = 0;
		bLock = false;

		nHostState = 0;
		nLevel = 0;
		nTargetNum = 0;
		nSceneID = 0;
	}

};

struct SHostUserInfo {
	unsigned int nUserId;
	unsigned int nTeamId;
//	unsigned int		nPos;

	unsigned long long uUserGuid;

	char szIp[20];
	int nPort;
	SHostUserInfo() {
		szIp[0] = 0;
		//nPos = 0;
		uUserGuid = 0;
	}

};

struct SServer {
	unsigned int id;
	unsigned int nPort;
	char szIp[50];
};
struct SGame {
	unsigned int id;
	unsigned int nServerId;
	unsigned int nRoomNum;
	char szName[50];
};
struct SRoom {
	unsigned int id;
	unsigned int nServerId;
	unsigned int nGameId;
	unsigned int nMaxNum;
	char szName[50];
};
struct SUser {

	SUser()
	{
		m_nMaxPower = 200;
	}
	char m_szName[50];					///<昵称
	char m_szAccount[50];				///<账号名

	long long int m_llPMoney;			///<金币
	long long int m_llRMoney;			///<钻石

	unsigned int m_nExe;				///<经验
	unsigned int m_nAccount_id;			///<账号ID
	unsigned int m_nLevel;				///<等级
	unsigned int m_nMaxContinueKill;	///<最大连杀

	unsigned int m_nMaxPower;	///<最大体力
	unsigned int m_nCurPower;	///<当前体力
	unsigned int m_nTimePower;	///<房间服务器没有使用此变量,房间服务器用的是ontimer

	unsigned int m_nVip;		///<vip

	unsigned int m_nWP_AP;	///<洗点所加的生命值

};
/**
 * 坦克结构
 */
struct STank {
	int ID;				///<坦克ID,唯一标识
	int tankid;			///<坦克ID, itemtype id
	int keeperId;		///<该值为UID表示已装备, 0表示未装备.
	int tanktype;		///<坦克类型
	int tankexp;		///<坦克经验
	int tanklevel;		///<坦克等级
	int attacklevel;	///<攻击等级
	int defenselevel;	///<防御等级
	int speedlevel;		///<移动速度等级
	int aplevel;		///<血量等级
	int tankcoat1;		///<涂装1
	int tankcoat2;		///<涂装2
	int tank_wuxun;		///<当前武勋值
	int tank_use_wuxun;	///<已使用武勋值
	int tank_status;	///<坦克状态,1,已解锁,2,已获得
	int tank_win_num;	///<当日获胜次数,目前主要用于首胜判断
	int tank_money_type;	///<1,金币车(其实是只能使用钻石购买的车);  0, 普通车
	int tank_exp_coefficient;	///<经验加成系数
	int tank_money_coefficient;	///<金币加成系数
	int tank_repair_fee;		///<维修费

	int tank_match_score;		///<坦克自动匹配基础分数
	int tank_match_bonus;		///<坦克自动匹配加成系数(范围1-1000),需除1000.

	unsigned int m_nEngine;				///<引擎
	unsigned int m_nCannon;				///<主炮
	unsigned int m_nArmor;				///<甲板
	unsigned int m_nTracks;				///<履带

	STank() {
		ID = 0;				///<坦克ID,唯一标识
		tankid = 0;			///<坦克ID, itemtype id
		keeperId = 0;		///<该值为UID表示已装备, 0表示未装备.
		tanktype = 0;		///<坦克类型
		tankexp = 0;		///<坦克经验
		tanklevel = 0;		///<坦克等级
		attacklevel = 0;	///<攻击等级
		defenselevel = 0;	///<防御等级
		speedlevel = 0;		///<移动速度等级
		aplevel = 0;		///<血量等级
		tankcoat1 = 0;		///<涂装1
		tankcoat2 = 0;		///<涂装2
		tank_wuxun = 0;		///<当前武勋值
		tank_use_wuxun = 0;	///<已使用武勋值
		tank_status = 0;	///<坦克状态,1,已解锁,2,已获得
		tank_win_num = 0;	///<当日获胜次数,目前主要用于首胜判断
		tank_money_type = 0;	///<1,金币车(其实是只能使用钻石购买的车) = 0;  0, 普通车
		tank_exp_coefficient = 0;	///<经验加成系数
		tank_money_coefficient = 0;	///<金币加成系数
		tank_repair_fee = 0;		///<维修费

		tank_match_score = 0;		///<坦克自动匹配基础分数
		tank_match_bonus = 0;		///<坦克自动匹配加成系数(范围1-1000),需除1000.

		m_nEngine = 0;				///<引擎
		m_nCannon = 0;				///<主炮
		m_nArmor = 0;				///<甲板
		m_nTracks = 0;				///<履带
	}
};

/**
 *　玩家军团信息
 */
struct SUserArmy {
	int nArmyId;
	int nDefenselevel;	///<防御等级
	int nMovelevel;		///<移动等级
	int nRotatelevel;	///<炮塔转速等级
	int nAttacklevel;	///<攻击等级

	SUserArmy() {
		nArmyId = 0;		///<军团ID
		nDefenselevel = 0;	///<防御等级 对应itemtype 中legion_type 1
		nRotatelevel = 0;	///<炮塔转速等级 ... 3
		nAttacklevel = 0;	///<攻击等级 ... 4
		nMovelevel = 0;		///<移动等级  ... 2
	}
};

/**
 * 坦克部件
 */
struct STankUnit
{
	int	nId;
	int nType1;
	int nValue1;
	STankUnit()
	{
		nId = 0;
		nType1 = 0;
		nValue1 = 0;
	}
};
struct SItem {
	int ID;
	int Item_type;
	int Keeper_id;
	int Player_id;
	int item_count;
	int item_time_type;
	int item_endtime;
	int item_packet;
	int item_exp;
	int attack_level;
	int defense_level;
	int movespeed_level;
	int loadbulletspeed_level;
	int ap_level;
	int crit_level;
	int Main_type;
	char Name[50];
	int sub_type;
	int Type_tank;			///<坦克类型,突击, 重型, 远程
	int tank_level;			///<坦克等级
	int itemscore;			///<坦克自动匹配基础分数
	int itemlevelbonus;		///<坦克自动匹配加成系数(范围1-1000),需除1000.

	int coat1;				///<涂装1
	int coat2;				///<涂装2

	SItem() {
		ID = 0;
		Item_type = 0;
		Keeper_id = 0;
		Player_id = 0;
		item_count = 0;
		item_time_type = 0;
		item_endtime = 0;
		item_packet = 0;
		item_exp = 0;
		attack_level = 0;
		defense_level = 0;
		movespeed_level = 0;
		loadbulletspeed_level = 0;
		ap_level = 0;
		crit_level = 0;
		Main_type = 0;
		Name[0] = 0;
		sub_type = 0;
		Type_tank = 0;
		coat1 = 0;				///<涂装1
		coat2 = 0;				///<涂装2
	}
};

struct SUserAchievement {
	int achievement_id;			///<成就ID
	int achievement_num;		///<成就进度
	int achievement_achieve;	///<成就完成, 1 完成, 0 未完成

	SUserAchievement() {
		achievement_id = 0;			///<成就ID
		achievement_num = 0;		///<成就进度
		achievement_achieve = 0;	///<成就完成, 1 完成, 0 未完成
	}
};

///地图信息
struct SMap {
	int id;
	int nMaxnum;
};

///全局配置信息
struct SWorldConfig {
	int ID;					///<ID
	int Basephase;			///<基础改造段位
	int Basecost;			///<改造基础费用
	int Phasetime;			///<段位倍率
	int RDdivisor;			///<研发等级比率
	int Hthptime;			///<重战车HP费用倍率
	int Htatktime;			///<重战车攻击费用倍率
	int Htdeftime;			///<重战车防御用倍率
	int Htspdtime;			///<重战车移动速度费用倍率
	int Lthptime;			///<轻战车HP费用倍率
	int Ltatktime;			///<轻战车攻击费用倍率
	int Ltdeftime;			///<轻战车防御费用倍率
	int Ltspdtime;			///<轻战车移动费用倍率
	int Mahptime;			///<自走炮HP
	int Maatktime;			///<自走炮攻击
	int Madeftime;			///<自走炮防御
	int Maspdtime;			///<自走炮移动
	int Wiresu;				///<胜利常数(0-1000)使用时需除1000
	int Loresu;				///<失败常数(0-1000)使用时需除1000
	int Kafall;				///<击坠常数
	int KaDPS;				///<伤害常数(0-1000)使用时需除1000
	int Cosoexp;			///<个人经验系数(0-1000)使用时需除1000
	int CotaExp;			///<战车经验系数(0-1000)使用时需除1000
};

//位置信息
struct SMappos {
	int id;

	int nMapid;
	int nTeam;			//１，１队位置；　２，２队位置
	int nType;			//０非组队，　１组队

	unsigned int nUserId;			//谁在这个位置

	SMappos() {
		id = 0;
		nMapid = 0;
		nType = 0;
		nUserId = 0;
	}
};

/**
 * 装备
 */
struct SEquipment {
	int id;
	int nMaxHp;			//最大血
};


/**
 * 光环
 */
struct SAura
{
	SAura()
	{
		nCount = 0;
	}
	int nId;
	int param1; //攻击力增强
	int param2; //防御力增强
	int param3; //回血间隔
	int param4; //回血百分比
	int param5; //持续伤害间隔
	int param6; //持续伤害量
	int param7; //持续伤害时间

	int nCount;
};
struct SItemtype {
	int id;
	int nMain_type;		///<主要类型
	int nAp_max;
	int nEp_max;
	int nLegion_type;	///<军团附属技能
	int nLegion_level;	///<军团附属技能等级
	int nLegion_num;	///<技能相对应的附加值
	SItemtype() {
		nMain_type = 0;
		id = 0;
		nAp_max = 0;
		nEp_max = 0;
		nLegion_type = 0;	///<军团附属技能
		nLegion_level = 0;	///<军团附属技能等级
		nLegion_num = 0;	///<技能相对应的附加值
	}
};
struct SEquipbase {
	int nValue;
	int nPmoney;
	int nRmoney;
};

struct SIntensify {
	int nId;

	int nhplevel;
	int nspeedlevel;
	int ndeflevel;
	int nattacklevel;

	double fhpup;
	double fspeedup;
	double fdefup;
	double fattackup;
};

/**
 * 坦克默认的炮管
 * 两个ＩＤ都是item_type
 */
struct STankmuzzle {
	int nTankId;			//坦克ＩＤ
	int nMuzzleId;			//炮管ＩＤ
};

/**
 * 按等级奖励信息
 */
struct SAwardbylevel {
	int nLevelId;
	int nExplost;
	int nExpwin;
	int nPmoneylost;
	int nPmoneywin;
};

struct SAchievement {
	int id;
	int achievement_needtype;
	int achievement_needid;
	int achievement_neednum;
	int achievement_awardid;
	int achievement_awardnum;
};

#pragma pack(pop)
//struct SUserInfo
//{
//	unsigned int  	uUserID;
//
//	char			szIp[30];
//	int				iPort;
//
//	RakNetGUID		guid;
//	SUserInfo()
//	{
//		iPort = 0;
//		szIp[0] = 0;
//	}
//
//	SUserInfo& operator = ( const SUserInfo& input )
//	{
//		uUserID = input.uUserID;
//		iPort = input.iPort;
//		guid = input.guid;
//		strcpy(szIp, input.szIp);
//		return *this;
//	}
//};
//class CUserList
//{
//public:
//	vector<SUserInfo *> m_UserList;
//
//public:
//	void AddUser(SUserInfo * pUser)
//	{
//		m_UserList.push_back(pUser);
//	}
//
//	void DelUser(unsigned int id)
//	{
//		for(vector<SUserInfo *>::iterator i =  m_UserList.begin(); i != m_UserList.end(); i++)
//		{
//			if((*i)->uUserID == id)
//			{
//				delete (*i);
//				m_UserList.erase(i);
//			}
//		}
//	}
//
//	//guid
//
//	void DelUser(RakNetGUID id)
//	{
//		for(vector<SUserInfo *>::iterator i =  m_UserList.begin(); i != m_UserList.end(); i++)
//		{
//			if((*i)->guid == id)
//			{
//				delete (*i);
//				m_UserList.erase(i);
//				break;
//			}
//		}
//	}
//
//	SUserInfo * FindUser(unsigned int id)
//	{
//		for(vector<SUserInfo *>::iterator i =  m_UserList.begin(); i != m_UserList.end(); i++)
//		{
//			if((*i)->uUserID == id)
//				return (*i);
//		}
//		return NULL;
//	}
//
//	~CUserList()
//	{
//		for(vector<SUserInfo *>::iterator i =  m_UserList.begin(); i != m_UserList.end(); i++)
//		{
//			delete (*i);
//			(*i) = NULL;
//		}
//	}
//
//};

#endif
