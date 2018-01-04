#ifndef __PACKDEFINE__H_
#define __PACKDEFINE__H_
enum GameMessages {
	PT_CHAT = ID_USER_PACKET_ENUM + 1, PT_NAT_PUNCHTROUGH_REQUEST,

	PT_NAT_HOST, PT_USER_LIST, PT_USER_ENTER,

	//进入Game信息
	PT_ENTER_GAME_REQUEST, 			///<进入房间申请135
	PT_ENTER_GAME_ACCEPT, 			///<进入房间成功
	PT_ENTER_GAME_FAILE, 			///<进入房间失败
	PT_USER_ENTER_GAME, 			///<有人进入房间

	//离开Game信息
	PT_LEAVE_GAME_REQUEST, 			///<离开房间申请139
	PT_LEAVE_GAME_ACCEPT, 			///<离开房间成功
	PT_LEAVE_GAME_FAILE, 			///<离开房间失败
	PT_USER_LEAVE_GAME, 			///<有人离开房间

	//进入房间信息
	PT_ENTER_ROOM_REQUEST, 			///<进入房间申请 143
	PT_ENTER_ROOM_ACCEPT, 			///<进入房间成功
	PT_ENTER_ROOM_FAILE, 			///<进入房间失败
	PT_USER_ENTER_ROOM, 			///<有人进入房间

	//离开房间信息
	PT_LEAVE_ROOM_REQUEST, 			///<离开房间申请147
	PT_LEAVE_ROOM_ACCEPT, 			///<离开房间成功
	PT_LEAVE_ROOM_FAILE, 			///<离开房间失败
	PT_USER_LEAVE_ROOM, 			///<有人离开房间

	//创建主机信息
	PT_CREATE_HOST_REQUEST, 		///<创建主机申请151
	PT_CREATE_HOST_ACCEPT, 			///<创建主机成功
	PT_CREATE_HOST_FAILE, 			///<创建主机失败
	PT_USER_CREATE_HOST, 			///<有人创建主机

	//加入主机信息
	PT_JOIN_HOST_REQUEST, 			///<加入主机申请155
	PT_JOIN_HOST_ACCEPT, 			///<加入主机成功
	PT_JOIN_HOST_FAILE, 			///<加入主机失败
	PT_USER_JOIN_HOST, 				///<有人加入主机

	//离开主机信息
	PT_LEAVE_HOST_REQUEST, 			///<加入主机申请159
	PT_LEAVE_HOST_ACCEPT, 			///<加入主机成功
	PT_LEAVE_HOST_FAILE, 			///<加入主机失败
	PT_USER_LEAVE_HOST, 			///<有人加入主机
	//游戏开始
	PT_GAME_START, 					///<游戏开始
	//游戏结束
	PT_GAME_END, 					///<游戏结束
	//游戏奖励
	PT_AWARD,						///<发送奖励给玩家
	PT_SERVER_CLOSE,				///<send to user when server will close
	PT_OPEN_SERVER,					///<leader tell gamecenter open a Roomserver
	PT_CLOSE_SERVER,				///<... close a Roomserver
	PT_SYSTEMINFO_REQUEST,			///<leader Get system info
	PT_SYSTEMINFO_RET,
	PT_ROOMSERVER_REGTO_GAMECENTER,
	PT_PROXY_TRANSMISSION,  		///<通过server代理转发的数据包
	PT_SYNCHRONOUSTIME, 			///<同步时间 该PT在PT_PROXY_TRANSMISSION后面
	PT_HOST_LIST,					///<主机列表
	PT_HOST_MESSAGE,				///<175
	PT_SERVER_PROXY,				///<服务转发
	PT_CHANGE_HOST,					///<while host id change;
	PT_ROOM_USER_LIST,				//<玩家列表
	PT_SERVER_IDENTIFY_NOTIFY,		///<服务器之间的身份声明
	PT_ROOM_TO_PROXY,  				///<180
	PT_USER_CONNECT,				///<玩家连接后，代理服务器通知房间服务器
	PT_USER_DISCONNECT,				///<玩家断线后，代理服务器通知房间服务器
	PT_USER_HEART_JUMP,				///<客户端心跳包
	PT_USER_RECONNECT,				///<玩家重连
	PT_USER_INGAME_MSG = 255,
};
enum SERVER_TYPE {
	SERVER_TYPE_UNKNOW = 0,			///<unknow server
	SERVER_TYPE_ROOMSERVER,			///<roomserver64
	SERVER_TYPE_PROXYSERVER,		///<proxyserver64
	SERVER_TYPE_DATASERVER,			///<dataserver64
	SERVER_TYPE_PUBSERVER,			///<pub
	SERVER_TYPE_ROUTERSERVER,		///<msgqueue
};
enum HOSTMSG {
	PT_HOST_USER_LIST = 0,			///<主机内人物列表。

	PT_HOST_CHANGE_TEAM_REQUEST,	///<换队伍
	PT_HOST_CHANGE_TEAM_ACCEPT, 	///<换队伍成功
	PT_HOST_CHANGE_TEAM_FAILE, 		///<换队伍失败
	PT_HOST_USER_CHANGE_TEAM,		///<有人换队伍

	PT_HOST_USER_HOSTLIST_REQUEST,	///<获取主机列表请求
	PT_HOST_READY_REQUEST,			///<准备请求
	PT_HOST_USER_READY,				///<有人准备
	PT_HOST_READY_ACCEPT,			///<准备成功
	PT_HOST_GAME_START,				///<游戏开始

	PT_HOST_GAME_END,				///<游戏结束
	PT_CHAT_MSG,            		///<聊天发送
	PT_USER_CHAT_MSG,       		///<聊天接收
	PT_FRIEND_ENTER_GAME,   		///<好友进入游戏
	PT_FRIEND_LEAVE_GAME,   		///<好友退出游戏

	PT_FRIEND_ENTER_ROOM,   		///<好友进入大厅
	PT_FRIEND_LEAVE_ROOM,   		///<好友退出大厅
	PT_FRIEND_ENTER_HOST,   		///<好友进入房间
	PT_FRIEND_LEAVE_HOST,   		///<好友离开房间
	PT_FRIEND_CONNECT,      		///<好友连接

	PT_FRIEND_DISCONNECT,   		///<好友掉线
	PT_FRIEND_CHANGE_HOSTID,   		///<好友所在主机切换主机号
	PT_HOST_GAME_START_JOIN,   		///<中途加入
	PT_HOST_INGAME_START_REQUEST,   ///<通知服务器游戏中已加载完成
	PT_HOST_INGAME_START_ACCEPT,    ///<接收服务器游戏中已加载完成开始事件

	PT_HOST_EXIT_GAME_INROOM,     	///<游戏中退到房间
	PT_HOST_INGAME_CHANGE_REFEREE,	///<游戏中更换裁判
	PT_HOST_USER_EXIT_GAME,			///<有人离开了游戏(ingame)
	PT_HOST_USER_START,				///<有其它人开始加入，游戏没开始
	PT_HOST_INGAME_START_WAIT,		///<等待服务器通知开始

	PT_HOST_KICK_REQUEST,			///<踢人请求
	PT_HOST_KICK_ACCEPT,			///<踢人回复
	PT_HOST_USER_KICK,				///<踢人通知
	PT_HOST_HURT_HEATH_REQUEST,		///<伤害请求（受伤id, 伤害值，c2s）
	PT_HOST_UPDATE_HEATH,			///<更新当前生命值(userid, value, 广播到所有客户端)

	//	PT_HOST_RESTORE_HEATH_REQUEST,	///<回复生命值，战场道具（userid, value, c2s）
	PT_HOST_USE_ITEM_REQUEST,		///<使用道具回复生命（itemid, c2s）
	PT_HOST_USER_DEATH,				///<有人生命耗尽（killer, be killer, s2c）
	PT_HOST_USER_HURT,				///<有人被杀伤（userid, otherid, value, s2c）
	PT_HOST_WAR_PICK_ITEM,			///<战场拾取道具，战场道具（itemid, c2s）
	PT_HOST_USER_REBORN,            ///<有人复活

	PT_HOST_INGAME_END,				///<游戏结束

	///========================flag================================
	PT_HOST_FLAG_REQUEST,			///<抢旗消息。c2s
	PT_HOST_USER_FLAG,				///<有人抢到旗。s2c
	PT_HOST_FLAG_SUCCESS_REQUEST,	///<抢旗成功结束.c2s
	PT_HOST_USER_FLAG_SUCCESS,		///<有人成功夺旗 s2c
	PT_HOST_FLAG_RESET,				///<抢旗重新开始.s2c(５秒后发)

	//========================leader===============================
	PT_HOST_SET_LEADER,				///<s2c
	PT_HOST_USER_KILL_LEADER,		///<s2c，歼灭首领（５秒后重置）
	PT_HOST_LEADRE_RESET, 			///<s2c,

	//====================occupy占领=====================================
	PT_HOST_OCCUPY_REQUEST,			///<c2s	占领成功后发
	PT_HOST_USER_OCCUPY,			///<s2c	服务器通知其它人
	PT_HOST_OCCUPY_RESET,			///<s2c	占领重置
	PT_HOST_MIDWAY_ENTER_DATA,		///<游戏内数据
	PT_HOST_BEHURT_HEATH_REQUEST,	///<受到伤害消息（伤害者ＩＤ（不验证，可能是ＡＩ，数据不统计），　伤害量，　c2s）

	//=============================================================
	PT_MATCH_REQUEST,				///<匹配申请
	PT_MATCH_ACCEPT,				///<匹配成功
	PT_MATCH_OUTTIME,				///<匹配超时
	PT_MATCH_RESET_AI,				///<重置AI
	PT_MATCH_ADD_AI,				///<添加AI,暂时先不使用
	PT_MATCH_REMOVE_AI,				///<移除AI

	PT_MATCH_NO_POWER,				///<体力不足
	//=============================================

	PT_HOST_AI_ATTACK_REQUEST,

	PT_USER_LIGHTING_REQUEST,//点亮玩家,c2s
	PT_USER_LIGHTING_ACCEPT,//点亮成功,s2c
	PT_USER_LIGHTING_CANCEL,

	PT_ENTER_AURA_REQUEST,//进入光环,c2s
	PT_LEAVE_AURA_REQUEST,//离开光环,c2s

	//==============================================
	PT_ARENA_REQUEST,				///<挑战请求
	PT_ARENA_ACCEPT,				///<挑战请求成功
	PT_ARENA_FAIL,					///<挑战失败

	///=======================================
	PT_USER_ENTER_ARUA,				///<进入光环
	PT_USER_LEAVE_ARUA,				///<离开光环


	PT_MJ_OPT_FAIL,					///72 <operat fail look at fail id list

	PT_MJ_DAPAI_REQ,
	PT_MJ_USER_DAPAI,

	PT_MJ_DASAIZAI_START,
	PT_MJ_DASAIZI_REQ,
	PT_MJ_USER_DASAIZI,


	PT_MJ_DASAIZI_AG_REQ,
	PT_MJ_USER_DASAIZI_AG,

	PT_MJ_GANG_REQ,
	PT_MJ_GANG_PASS_REQ,
	PT_MJ_USER_GANG,

	PT_MJ_PENG_REQ,
	PT_MJ_PENG_PASS_REQ,
	PT_MJ_USER_PENG,

	PT_MJ_HU_REQ,
	PT_MJ_USER_HU,

	PT_MJ_MOPAI_REQ,
	PT_MJ_USER_MOPAI,//89

	PT_MJ_MATCH_ACCEPT,

	PT_MJ_GAME_START,

	PT_MJ_ZHUOZHUANG_REQ,	//<92
	PT_MJ_USER_ZHUOZHUANG,

	PT_MJ_LAZHUANG_REQ,
	PT_MJ_USER_LAZHUANG,

	PT_MJ_FAPAI,

	PT_MJ_WAIT_USER_OPT,
	PT_MJ_END_GAME,

	//=====ddz================
	PT_DDZ_CHUPAI = 200,
	PT_DDZ_JIAOFEN,
	PT_DDZ_PASS,

	PT_DDZ_USER_CHUPAI,
	PT_DDZ_USER_JIAOFEN,
	PT_DDZ_USER_PASS,

};
enum OPT_TYPE
{
	OPT_TYPE_DAPAI = 0,
	OPT_TYPE_GANG,
	OPT_TYPE_PENG,
	OPT_TYPE_MOPAI,

	OPT_TYPE_GMAEEND,
};
#pragma pack(push, 1)
struct PT_SERVER_CLOSE_INFO {
	unsigned char id;
	PT_SERVER_CLOSE_INFO() :
		id(PT_SERVER_CLOSE) {
		}
};
//write id
//write type
//if(type==0) wirte nUserId
//write nContentNum
//write szContent
struct PT_CHAT_MSG_INFO {
	unsigned char id;
	unsigned int nMsgid;

	unsigned int nType;				///<0 私聊， 1， 组内（HOST）， 2， 大厅（ROOM） ，3，世界
	unsigned int nUserId;			///<私聊有用，玩家ID
	unsigned int nContentNum;		///<聊天长度。
	unsigned char szContent[255];	///<聊天内容。最大255
	PT_CHAT_MSG_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_CHAT_MSG) {
		}
};
//有玩家聊天回复
struct PT_USER_CHAT_MSG_INFO {
	unsigned char id;
	unsigned int nMsgid;

	unsigned int nUserId;
	unsigned int nType;			///<聊天类型
	unsigned int nContentNum;	///<聊天长度。

	unsigned char szName[32];	///<玩家名称
	unsigned char szContent[255];	///<聊天内容。最大255

	PT_USER_CHAT_MSG_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_USER_CHAT_MSG) {
		}
};
//进入Game信息
struct PT_ENTER_GAME_REQUEST_INFO ///<进入Game申请
{
	unsigned char id;				///<消息ID
	unsigned int nUserId;			///<玩家ID
	unsigned int nGameId;			///<游戏ID,坦克为2

	unsigned long long uUserGuid;	///<玩家GUID

	PT_ENTER_GAME_REQUEST_INFO() :
		id(PT_ENTER_GAME_REQUEST) {
		}
};
struct PT_ENTER_GAME_ACCEPT_INFO ///<进入Game成功
{
	unsigned char id;				///<消息ID

	PT_ENTER_GAME_ACCEPT_INFO() :
		id(PT_ENTER_GAME_ACCEPT) {
		}
};
struct PT_ENTER_GAME_FAILE_INFO ///<进入Game失败
{
	unsigned char id;				///<消息ID
	unsigned int nFaileId;			///<错误ID
	PT_ENTER_GAME_FAILE_INFO() :
		id(PT_ENTER_GAME_FAILE) {
		}
};
struct PT_USER_ENTER_GAME_INFO ///<有人进入Game
{
	unsigned char id;				///<消息ID
	unsigned int nUserId;			///<玩家ID
	PT_USER_ENTER_GAME_INFO() :
		id(PT_USER_ENTER_GAME) {
		}
};

//离开Game信息
struct PT_LEAVE_GAME_REQUEST_INFO ///<离开Game申请
{
	unsigned char id;				///<消息ID

	PT_LEAVE_GAME_REQUEST_INFO() :
		id(PT_LEAVE_GAME_REQUEST) {
		}
};
struct PT_LEAVE_GAME_ACCEPT_INFO ///<离开Game成功
{
	unsigned char id;				///<消息ID

	PT_LEAVE_GAME_ACCEPT_INFO() :
		id(PT_LEAVE_GAME_ACCEPT) {
		}
};
struct PT_LEAVE_GAME_FAILE_INFO ///<离开Game失败
{
	unsigned char id;				///<消息ID
	unsigned int nFaileId;			///<错误ID
	PT_LEAVE_GAME_FAILE_INFO() :
		id(PT_LEAVE_GAME_FAILE) {
		}
};
struct PT_SERVER_IDENTIFY_NOTIFY_INFO {
	unsigned int id;				///<消息ID
	unsigned int nServerType; 		///<1, roomserver; 2, proxyserver
	PT_SERVER_IDENTIFY_NOTIFY_INFO() :
		id(PT_SERVER_IDENTIFY_NOTIFY) {
			nServerType = 1;
		}
};
struct PT_USER_LEAVE_GAME_INFO ///<有人离开游戏
{
	unsigned int id;				///<消息ID
	unsigned int nUserId;			///<玩家ID
	PT_USER_LEAVE_GAME_INFO() :
		id(PT_USER_LEAVE_GAME) {
		}
};

//进入房间信息
struct PT_ENTER_ROOM_REQUEST_INFO				///<进入房间申请
{
	unsigned char id;				///<消息ID
	unsigned int nRoomId;			///<房间ID

	PT_ENTER_ROOM_REQUEST_INFO() :
		id(PT_ENTER_ROOM_REQUEST) {
			nRoomId = -1;
		}
};

struct PT_ENTER_ROOM_ACCEPT_INFO				///<进入房间成功
{
	unsigned char id;				///<消息ID
	PT_ENTER_ROOM_ACCEPT_INFO() :
		id(PT_ENTER_ROOM_ACCEPT) {
		}
};

struct PT_ENTER_ROOM_FAILE_INFO					///<进入房间失败
{
	unsigned char id;				///<消息ID
	unsigned int nFaileId;			///<失败ID
	PT_ENTER_ROOM_FAILE_INFO() :
		id(PT_ENTER_ROOM_FAILE) {
		}
};

struct PT_USER_ENTER_ROOM_INFO					///<有人进入房间
{
	unsigned char id;				///<消息ID
	unsigned int nUserId;			///<玩家ID
	PT_USER_ENTER_ROOM_INFO() :
		id(PT_USER_ENTER_ROOM) {
		}
};

//离开房间信息
struct PT_LEAVE_ROOM_REQUEST_INFO				///<离开房间申请
{
	unsigned char id;				///<消息ID
	PT_LEAVE_ROOM_REQUEST_INFO() :
		id(PT_LEAVE_ROOM_REQUEST) {
		}
};

struct PT_LEAVE_ROOM_ACCEPT_INFO				///<离开房间成功
{
	unsigned char id;				///<消息ID
	PT_LEAVE_ROOM_ACCEPT_INFO() :
		id(PT_LEAVE_ROOM_ACCEPT) {
		}
};

struct PT_LEAVE_ROOM_FAILE_INFO				///<离开房间失败
{
	unsigned char id;				///<消息ID
	unsigned int nFaileId;			///<失败ID
	PT_LEAVE_ROOM_FAILE_INFO() :
		id(PT_LEAVE_ROOM_FAILE) {
		}
};

struct PT_USER_LEAVE_ROOM_INFO				///<有人离开房间
{
	unsigned char id;				///<消息ID
	unsigned int nUserId;			///<离开房间的User
	PT_USER_LEAVE_ROOM_INFO() :
		id(PT_USER_LEAVE_ROOM) {
		}
};

/**
 * 主机改变消息
 */
struct PT_CHANGE_HOST_INFO {
	unsigned char id;				///<消息ID
	unsigned int nHostId;			///<新主机ID
	unsigned int nOldHostId;		///<老主机ID
	PT_CHANGE_HOST_INFO() :
		id(PT_CHANGE_HOST) {
		}
};
/**
 * 主机列表消息
 */
struct PT_HOST_LIST_INFO {
	unsigned char id;				///<消息ID
	unsigned int nHostNum;			///<主机数
	SHostInfo HostList[50];			///<主机列表
	PT_HOST_LIST_INFO() :
		id(PT_HOST_LIST), nHostNum(0) {
		}
};
/**
 * 主机内玩家列表
 */
struct PT_HOST_USER_LIST_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID
	unsigned int nHostUserNum;		///<玩家数
	SHostUserInfo UserList[50];		///<玩家列表
	PT_HOST_USER_LIST_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_USER_LIST), nHostUserNum(0) {
		}
};
/**
 * 更改队伍请求消息,客户端发给服务器
 */
struct PT_HOST_CHANGE_TEAM_REQUEST_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID
	unsigned int nTeamId;			///<队伍ID
	unsigned int nPos;				///<位置
	PT_HOST_CHANGE_TEAM_REQUEST_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_CHANGE_TEAM_REQUEST) {
		}
};
/**
 * 更改队伍成功消息,由服务器返回给客户端
 */
struct PT_HOST_CHANGE_TEAM_ACCEPT_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID
	PT_HOST_CHANGE_TEAM_ACCEPT_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_CHANGE_TEAM_ACCEPT) {
		}
};
struct PT_HOST_CHANGE_TEAM_FAILE_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID
	PT_HOST_CHANGE_TEAM_FAILE_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_CHANGE_TEAM_FAILE) {
		}
};

/**
 * 其它玩家更新队伍信息
 */
struct PT_HOST_USER_CHANGE_TEAM_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID
	unsigned int nUserId;			///<玩家ID
	unsigned int nTeamId;			///<队伍ID
	PT_HOST_USER_CHANGE_TEAM_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_USER_CHANGE_TEAM) {
		}
};

/**
 * 主机列表请求(已停用)
 */
struct PT_HOST_USER_HOSTLIST_REQUEST_INFO {
	unsigned char id;				///<消息ID
	unsigned int nMsgid;			///<子消息ID

	PT_HOST_USER_HOSTLIST_REQUEST_INFO() :
		id(PT_HOST_MESSAGE), nMsgid(PT_HOST_USER_HOSTLIST_REQUEST) {
		}
};
//===================================

/**
 * 创建主机请求
 *
 */
struct PT_CREATE_HOST_REQUEST_INFO
{
	unsigned char id;				///<消息ID
	unsigned int nUserId;			///<玩家ID
	unsigned int nMode;				///<游戏模式
	unsigned int nSceneId;			///<场景ID
	unsigned int nTargetNum;		///<目标数
	unsigned int nMaxUserNum;		///<最大人数
	char szPwd[6];					///<密码
	unsigned int nBaseScore;		///<钻石
	unsigned int nBasePMoney;			///<金币
	PT_CREATE_HOST_REQUEST_INFO() :
		id(PT_CREATE_HOST_REQUEST) {
			nMode = 0;
			szPwd[0] = 0;
			nSceneId = 1;
			nTargetNum = 10;
			nMaxUserNum = 2;
			nBaseScore = 0;
			nBasePMoney = 0;
		}
};
/**
 * 创建主机成功
 */
struct PT_CREATE_HOST_ACCEPT_INFO			///<创建主机成功
{
	unsigned char id;						///<消息ID
	unsigned int nTeamId;					///<队伍ID
	unsigned int nIndex;					///<队伍索引,客户端显示用
	SHostInfo hostinfo;						///<主机信息
	PT_CREATE_HOST_ACCEPT_INFO() :
		id(PT_CREATE_HOST_ACCEPT) {
		}
};
/**
 * 创建主机失败
 */
struct PT_CREATE_HOST_FAILE_INFO			///<创建主机失败
{
	unsigned char id;						///<消息ID
	unsigned int nFaileId;					///<错误ID
	PT_CREATE_HOST_FAILE_INFO() :
		id(PT_CREATE_HOST_FAILE) {
		}
};

/**
 * 其它玩家创建主机
 */
struct PT_USER_CREATE_HOST_INFO				///<有人创建主机
{
	unsigned char id;						///<消息ID
	unsigned int nUserId;					///<玩家ID
	SHostInfo hostinfo;						///<主机信息
	PT_USER_CREATE_HOST_INFO() :
		id(PT_USER_CREATE_HOST) {
		}
};

/**
 * 加入主机请求信息
 */
struct PT_JOIN_HOST_REQUEST_INFO			///<加入主机申请
{
	unsigned char id;						///<消息ID
	unsigned int nHostId;					///<主机ID
	//	unsigned int 	nTeamId;
	char szPwd[6];							///<密码
	PT_JOIN_HOST_REQUEST_INFO() :
		id(PT_JOIN_HOST_REQUEST) {
		}
};
/**
 * 进入主机成功
 */
struct PT_JOIN_HOST_ACCEPT_INFO				///<加入主机成功
{
	unsigned char id;						///<消息ID
	unsigned int nTeamId;					///<队伍ID
	unsigned int nHostId;					///<主机ID

	//RakNetGUID		guid;
	char hostIp[20];						///<主机IP
	unsigned int nPort;						///<主机端口

	PT_JOIN_HOST_ACCEPT_INFO() :
		id(PT_JOIN_HOST_ACCEPT) {
		}
};

/**
 * 加入主机失败
 */
struct PT_JOIN_HOST_FAILE_INFO				///<加入主机失败
{
	unsigned char id;						///<消息ID
	unsigned int nFaileId;					///<失败ID
	PT_JOIN_HOST_FAILE_INFO() :
		id(PT_JOIN_HOST_FAILE) {
		}
};

/**
 * 其它玩家加入主机
 */
struct PT_USER_JOIN_HOST_INFO				///<有人加入主机
{
	unsigned char id;						///<消息ID
	unsigned int nUserId;					///<玩家ID
	unsigned int nTeamId;					///<队伍ID
	unsigned long long uUserGuid;			///<玩家GUID
	char szIp[20];							///<玩家IP
	int nPort;								///<玩家PORT
	unsigned int nHostId;					///<主机ID
	PT_USER_JOIN_HOST_INFO() :
		id(PT_USER_JOIN_HOST) {
		}
};
/**
 *离开主机信息
 */
struct PT_LEAVE_HOST_REQUEST_INFO			///<离开主机申请
{
	unsigned char id;						///<消息ID
	PT_LEAVE_HOST_REQUEST_INFO() :
		id(PT_LEAVE_HOST_REQUEST) {
		}
};
/**
 * 离开主机成功
 */
struct PT_LEAVE_HOST_ACCEPT_INFO			///<离开主机成功
{
	unsigned char id;						///<消息ID
	PT_LEAVE_HOST_ACCEPT_INFO() :
		id(PT_LEAVE_HOST_ACCEPT) {
		}
};
/**
 * 离开主机失败
 */
struct PT_LEAVE_HOST_FAILE_INFO				///<离开主机失败
{
	unsigned char id;						///<消息ID
	unsigned int nFaileId;					///<失败ID
	PT_LEAVE_HOST_FAILE_INFO() :
		id(PT_LEAVE_HOST_FAILE) {
		}
};

/**
 * 其它玩家离开主机
 */
struct PT_USER_LEAVE_HOST_INFO				///<有人离开主机
{
	unsigned char id;						///<消息ID
	unsigned int UserId;					///<玩家ID
	unsigned int nHostId;					///<主机ID
	PT_USER_LEAVE_HOST_INFO() :
		id(PT_USER_LEAVE_HOST) {
		}
};

/**
 * 游戏开始
 */
struct PT_GAME_START_INFO					///<游戏开始
{
	unsigned char id;						///<消息ID

	PT_GAME_START_INFO() :
		id(PT_GAME_START) {
		}
};

//游戏结束
struct PT_GAME_END_INFO							///<游戏结束
{
	unsigned char id;
	PT_GAME_END_INFO() :
		id(PT_GAME_END) {
		}
};

//游戏奖励
struct PT_AWARD_INFO								///<发送奖励给玩家
{
	unsigned char id;

	unsigned int nUserId;
	int iPMoney;
	int iRmoney;
	int iExp;
	PT_AWARD_INFO() :
		id(PT_AWARD) {
		}
};

//==============================================
//struct PT_USER_LIST_INFO
//{
//	unsigned char 	id;
//
//	SUserInfo		User[50];
//	int				iUserNum;
//
//	PT_USER_LIST_INFO():id(PT_USER_LIST)
//	{
//		iUserNum = 0;
//	}
//};
//struct PT_USER_ENTER_INFO
//{
//	unsigned char 	id;
//
//	SUserInfo		User;
//
//	PT_USER_ENTER_INFO():id(PT_USER_ENTER){}
//};
struct PT_NAT_HOST_INFO {
	unsigned char id;

	char szIp[20];
	unsigned int uPort;

	PT_NAT_HOST_INFO() :
		id(PT_NAT_HOST) {
			szIp[0] = 0;
		}
};

struct PT_CHAT_INFO {
	unsigned char id;

	char str[100];

	PT_CHAT_INFO() :
		id(PT_CHAT) {
		}
};

struct PT_NAT_PUNCHTROUGH_REQUEST_INFO {
	unsigned char id;

	unsigned int iHostID;

	PT_NAT_PUNCHTROUGH_REQUEST_INFO() :
		id(PT_NAT_PUNCHTROUGH_REQUEST) {
		}

};

//===============================GameCenter====================================

struct PT_OPEN_SERVER_INFO {
	unsigned int id;
	unsigned int nServerId;
	int nPort;

	PT_OPEN_SERVER_INFO() :
		id(PT_OPEN_SERVER) {
		}
};
struct PT_CLOSE_SERVER_INFO {
	unsigned int id;

	unsigned int ServerId;

	PT_CLOSE_SERVER_INFO() :
		id(PT_CLOSE_SERVER) {
		}
};
struct PT_SYSTEMINFO_REQUEST_INFO {
	unsigned int id;

	PT_SYSTEMINFO_REQUEST_INFO() :
		id(PT_SYSTEMINFO_REQUEST) {
		}
};
struct PT_SYSTEMINFO_RET_INFO {
	unsigned int id;

	unsigned int nServerid;
	int nCpu;
	int nMem;
	int nUserNum;
	int nMaxUserNum;

	int nCurHostNum;
	PT_SYSTEMINFO_RET_INFO() :
		id(PT_SYSTEMINFO_RET) {
			nCpu = 0;
			nMem = 0;
			nUserNum = 0;
			nMaxUserNum = 0;

			nCurHostNum = 0;
		}
};
struct PT_ROOMSERVER_REGTO_GAMECENTER_INFO {
	unsigned int id;
	unsigned int nServerId;
	int nPort;
	PT_ROOMSERVER_REGTO_GAMECENTER_INFO() :
		id(PT_ROOMSERVER_REGTO_GAMECENTER) {
		}
};

//struct PT_SERVER_PROXY_INFO
//{
//	unsigned int 	id;
//	unsigned int 	nNum;
//	unsigned int 	nUserId[nNum];
//
//	char data[]
//
//};



const int ONTIMER_HURT_AURA_UPDATE_TIME = 1 * 1000;
const int ONTIMER_WAIT_READY_TIME = 3 * 1000;
const int ONTIMER_WAIT_ZHUOZHUANG_TIME = 3 * 1000;
const int ONTIMER_WAIT_LAZHUANG_TIME = 3 * 1000;
const int ONTIMER_WAIT_DASAIZI_TIME = 3 * 1000;
const int ONTIMER_WAIT_DASAIZI_AG_TIME = 3 * 1000;
const int ONTIMER_WAIT_GANG_TIME = 3 * 1000;
const int ONTIMER_WAIT_PENG_TIME = 3 * 1000;
const int ONTIMER_WAIT_DAPAI_TIME = 3 * 1000;
const int ONTIMER_WAIT_RECONNECT_TIME = 10 *1000;
const int ONTIMER_WAIT_MOPAI_TIME = 3 * 1000;
const int ONTIMER_WAIT_GANG_MOPAI_TIME = 2 * 1000;

enum UserOnTimerID {
	ONTIMER_WAIT_READY,
	ONTIMER_WAIT_ZHUOZHUANG,
	ONTIMER_WAIT_LAZHUANG,
	ONTIMER_WAIT_DASAIZI,
	ONTIMER_WAIT_DASAIZI_AG,
	ONTIMER_WAIT_GANG,
	ONTIMER_WAIT_PENG,
	ONTIMER_WAIT_DAPAI,
	ONTIMER_WAIT_RECONNECT,
	ONTIMER_WAIT_MOPAI,
	ONTIMER_WAIT_GANG_MOPAI,
};



#pragma pack(pop)
#endif /*__PACKDEFINE__H_*/
