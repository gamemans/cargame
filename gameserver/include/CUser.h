/*
 * CUser.h
 *
 *  Created on: 2017年4月7日
 *      Author: aaaa
 */

#ifndef INCLUDE_CUSER_H_
#define INCLUDE_CUSER_H_

#include <vector>
using namespace std;
#include <string.h>

#include "commdefine.h"
class CUser
{


public:
	CUser()
	{
		m_iRoomId = -1;
		m_iTableId = -1;
		m_iGameId = -1;
		m_iChairId = -1;
		m_iPlace = -1;
		m_iScore = 0;
		m_iWin = 0;
		m_iLost = 0;
		m_iDogfall = 0;

		m_szUserName[0] = 0;

		m_pLookAt = NULL;

		m_bAcceptExit = false;

		m_bDrop = false;

		m_bSign = false;

		m_bSuperMatchMoney = false;				//超级大奖赛（花钱进入的玩家）
		m_iBout = 0;

		m_bMatch = false;
		m_bAllot = false;
		m_bExitMatch = false;
		m_szAccount[0] = 0;
		m_szCity[0] = 0;
		m_szQuestion[0] = 0;					//密码提示问题
		m_szAnswer[0] = 0;						//提示问题答案
		m_szEmail[0] = 0;						//邮件
		m_szLove[0] = 0;						//爱好
		m_szPerSigned[0] = 0;					//个性签名
		m_szNominatePeople[0] = 0;				//推荐人
		m_szIDCard[0] = 0;						//身份证号

		szBirthday[0] = 0;            //生日
		szYearAttribute[0] = 0;       //生肖
		szBloodType[0] = 0;           //血型
		szConstellation[0] = 0;       //星座
		szSchool[0] = 0;              //学校 上面有
		szWork[0] = 0;                //职业
		szProvince[0] = 0;            //省份

		m_szIP[0] = 0;
		m_szVipTime[0] = 0;

		//add by mx 2009.9.24
		m_bVidicon = false;                     //摄象设备
		m_iRealSex = REAL_SEX_NO_CHECK;         //真实性别
		m_bSuperCharm = false;

		m_bTeam = false;

		//add by mx BJL
		m_bSysManage = false;
		m_lFreezeMoney = 0;
	}
	~CUser(){}


	vector<unsigned int>			m_NoWelcome;


	int			m_iBout;							//第几轮

	char		m_szUserName[50];
	unsigned	m_dwHeadId;
	bool		m_bVIP;

	bool		m_bSex;								//false女
	char		m_szAccount[50];
	char		m_szCity[20];
	char		m_szQuestion[50];					//密码提示问题
	char		m_szAnswer[50];						//提示问题答案
	char		m_szEmail[50];						//邮件
	char		m_szLove[50];						//爱好
	char		m_szPerSigned[100];					//个性签名
	char		m_szNominatePeople[30];				//推荐人
	char		m_szIDCard[20];						//身份证号
	int			m_iCharm;							//魅力值
	char		m_dwNumericAccount;					//数字账号
	long long		m_lMoney;							//乐币
	long long		m_lHappyBean;						//乐豆
	unsigned int	m_dwFlower;							//花的数量
	unsigned int	m_dwCountLoginTime;					//游戏总时间

	int			m_iMatchScore;						//竞赛用分
	bool		m_bSign;							//是否已报名
	int			m_iSignUp;							//第几个报名
	unsigned int		m_dwHonor;

//	DWORD		m_dwPropFlowerNum;					//花的数量
	unsigned int		m_dwPropVipNum;						//VIP卡的数量
	unsigned int		m_dwPropHornNum;					//喇叭数
	unsigned int		m_dwPropHornBigNum;					//大嗽叭
	unsigned int		m_dwPropVipBigNum;					//大ＶＩＰ
	unsigned int		m_dwPropVipSupperNum;				//超级ＶＩＰ
	unsigned int       m_dwPropAwardNum;                   //抽奖卷
	unsigned int		m_wSubsidyNum;						//低保次数
	char       m_szVipTime[64];///wm add VIP到期时间
		//wz add upload 在CUser类中加入两个变量
	char       m_szHeadImgName[20];   //头像名称

	unsigned int       dwAge;                      //年龄
	char       szBirthday[20];            //生日
	char       szYearAttribute[20];       //生肖
	char       szBloodType[20];           //血型
	char       szConstellation[20];       //星座
	char       szSchool[50];              //学校 上面有
	char       szWork[30];                //职业
	char       szProvince[20];            //省份

	char		m_szIP[16];

	//大厅设置
	bool		m_bSameIP;
	bool		m_bDisconnect;
	bool		m_bScoreDistance;
	bool		m_bScoreMin;
	int			m_iDisconnectMin;
	int			m_iScoreDistance;
	int			m_iScoreMin;


	//DWORD		m_dwAgentId;
	unsigned int		m_dwUserId;			//数据库唯一标识
	unsigned int		m_dwAgentIndex;

	int			m_iGameId;
	int			m_iRoomId;
	int			m_iTableId;
	int			m_iChairId;		//桌子中的第几个人

	int			m_iScore;
	int			m_iWin;					//输
	int			m_iLost;				//赢
	int			m_iDogfall;				//平

	int			m_iDisconnect;			//断线
	int			m_iEscape;				//逃跑

	CUser *		m_pLookAt;				//旁观谁
	unsigned int		m_dwLookAtId;			//旁观别人的id

	int			m_iState;

	bool		m_bAcceptLookAt;		//允许别人旁观

	bool		m_bAcceptExit;

	bool		m_bDrop;				//是否掉线

	unsigned int		m_dwMatchRoomId;		//报名的比赛房间

	bool		m_bServerLeave;			//是否是服务器离座（竞赛有效）

	bool		m_bMatch;				//是否正在比赛
	bool		m_bAllot;				//是否已分配座位

	bool		m_bExitMatch;			//是否可以退赛
	//add by mx 2009.9.24
	bool		m_bVidicon;             //是否有摄像设备
	int			m_iRealSex;				//验证性别
	bool        m_bSuperCharm;          //魅力达人

	//add by mx BJL
	bool		m_bSysManage;
	bool		m_bSysManageInRoom;

	long long		m_lFreezeMoney;			//冻结资金

	bool		m_bTeam;				//已有队伍
	int			m_iPlace;				//最好名次
	bool		m_bSuperMatchMoney;
};





#endif /* INCLUDE_CUSER_H_ */
