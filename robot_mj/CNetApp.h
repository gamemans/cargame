/*
 * CNetApp.h
 *
 *  Created on: 2012-10-26
 *      Author: liyan
 */

#ifndef CNETAPP_H_
#define CNETAPP_H_
#include <map>
#include "RakNetTypes.h"
#include<stdlib.h>

#include <string>

#include "CPeer.h"

#include "CTimer.h"
#include "structdefine.h"
#include "packdefine.h"

#include "BitStream.h"

#if 1
const char SERVER_IP[20] = "localhost";
const unsigned short SERVER_PORT = 61000;//(200-202)
const int ROBOT_NUM = 4;
const int ROOM_ID = 100;
const int SERVER_ID=101;//(300-302)
const int GAME_ID = 2;
#else
const char SERVER_IP[20] = "tankweb.bluerox.cn";
const unsigned short SERVER_PORT = 40001; //60050 roomid 3
const int ROBOT_NUM = 10;
const int ROOM_ID = 10;
const int SERVER_ID=42;//(300-302)
const int GAME_ID = 2;
#endif


using namespace std;

enum {
	ON_ENTER_GAME_TIME,

	ON_ENTER_ROOM_TIME,

	ON_ENTER_HOST_TIME,

	ON_LEAVE_GAME_TIME,

	ON_LEAVE_ROOM_TIME,

	ON_LEAVE_HOST_TIME,

	ON_CREATE_HOST_TIME,

	ON_INGAME_PRE_TANK_START,

	ON_INGAME_PRE_TANK_READY,

	ON_INGAME_TANK_START,

	ON_INGAME_TANK_FIRE,

	ON_INGAME_TANK_MOVE,


	ONTIMER_TANK_READY_INGAME,

	ONTIMER_TANK_ENTER_INGAME,

	ONTIMER_EXIT_GAME_INROOM,

	ONTIMER_HEART_JUMP,

	ONTIMER_MATCH,


	ONTIMER_READY,

	ON_ZHUOZHUANG,

	ON_LAZHUANG,

	ON_DASAIZI,

	ON_DASAIZI_AG,

	ON_DAPAI,

	ON_PENG,

	ON_GANG,

	ON_MOPAI,

};
const int ONTIMER_READY_TIME = 1000;

const int ON_ZHUOZHUANG_TIME = 1000;

const int ON_LAZHUANG_TIME = 1000;

const int ON_DASAIZI_TIME = 1000;

const int ON_DASAIZI_AG_TIME = 1000;

const int ON_DAPAI_TIME = 1000;

const int ON_PENG_TIME = 1000;

const int ON_GANG_TIME = 1000;

const int ON_MOPAI_TIME = 1000;

class CHostInfo {
public:
	unsigned int nHostId;
	unsigned int nMaxNum;
	unsigned int nCurNum;
	unsigned int nMode;
	bool bLock;
	unsigned int nTeamId;
	char szPwd[6];

	CHostInfo(CHostInfo & other) {
		this->nHostId = other.nHostId;
		this->nMaxNum = other.nMaxNum;
		this->nCurNum = other.nCurNum;
		this->nMode = other.nMode;
		this->bLock = other.bLock;
		this->nTeamId = other.nTeamId;
		strcpy(szPwd, other.szPwd);
	}

	CHostInfo() {
		nHostId = 0;
		nMaxNum = 0;
		nCurNum = 0;
		nMode = 0;
		bLock = false;
		nTeamId = 0;
		szPwd[0] = 0;
	}

	void operator =(CHostInfo & other) {
		this->nHostId = other.nHostId;
		this->nMaxNum = other.nMaxNum;
		this->nCurNum = other.nCurNum;
		this->nMode = other.nMode;
		this->bLock = other.bLock;
		this->nTeamId = other.nTeamId;
		strcpy(szPwd, other.szPwd);
	}

};


struct SMJUser
{
	unsigned int nUserId;
	unsigned int nIndex;

};

class CUser {
public:
	CUser();
	~CUser();

	map<unsigned int, CHostInfo *> m_HostList;


	map<unsigned int, CUser *> m_HostUserList;
	bool createProxyPacket(RakNet::BitStream& inBitStream,
			RakNet::BitStream * outBitStream, int nUserIDorAll = -1);

	void SendData(const char * data, const int len, SystemAddress addr);

	void SendData(BitStream * bitStream, SystemAddress addr);

	void SendLaZhuang(unsigned int ZhuangNum);
	void SendZuoZhuang(unsigned int ZhuangNum);
	void SendDasaizi();
	void SendDasaiziag();
	void SendEntergame(unsigned serverid, unsigned int gameid, unsigned int uid);
	void SendDapai(unsigned int card);
	void SendGangpass();
	void SendGangreq();
	void SendMopai();
	void SendHeartjump();
	void SendReady();
	bool ConnectServer(const char * ip, const unsigned short port);

	void EnterGame(unsigned int nGameId);

	void EnterRoom(unsigned int nRoomId);

	void EnterHost(unsigned int nHostId);

	void CreateHost();

	void LeaveGame();

	void LeaveRoom();

	void LeaveHost();

	bool ProHostMsg(Packet * packet);
	bool ProHostMsgByStream(Packet * packet);
	bool ProHostIngameMsgByStream(Packet * packet);
	bool SendtoOtherbyProxy(const char* pszData, int nDataLen,
			unsigned int UidOrAll);
	void OnTimer(int iTimerID);
	void SetTimer(int iTimeId, unsigned long ulElapse, bool bOnce = true);
	void KillTimer(int iTimeId);

	bool Run();

public:

	SMJUser m_mjuser[4];
	unsigned int m_nUserId;
	unsigned int m_nIndex;

	unsigned int m_nBankIndex;
	unsigned int m_nBankId;

	unsigned int m_nCard[14];

	CPeer * m_peer;

	CTimer * m_pTimer;

	SystemAddress m_ServerAddr;

	bool		m_bMaster;//房主
	CHostInfo * m_pHost;
	CHostInfo tmpCreatehost;//创建主机时，临时存放数据，等服务器返回成功后，加入主机列表。
	CHostInfo tmpJoinhost;//tme join host
};

class CNetApp {
public:
	CNetApp();

	virtual ~CNetApp();

	int GetCurId();
	int GetCurIdAndInc();
	bool Init();

	bool Run();

	map<unsigned int, CUser *> m_UserList;

	CUser * GetUser(unsigned int nUserId) {
		if (m_UserList.find(nUserId) != m_UserList.end()) {
			return m_UserList[nUserId];
		}
		return NULL;
	}

	bool AddUser(CUser * pUser) {
		if (pUser != NULL) {
			m_UserList[pUser->m_nUserId] = pUser;
			return true;
		}
		return false;
	}


	unsigned int ARRAY_USERID[ROBOT_NUM];
	unsigned int ROBOT_POINTER;

private:
	bool m_bRun;
	int m_CurId;

};
extern CNetApp g_NetApp;
#endif /* CNETAPP_H_ */
