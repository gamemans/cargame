/*
 * CServer.h
 *
 *  Created on: Feb 23, 2012
 *      Author: aaaa
 */

#ifndef CSERVER_H_
#define CSERVER_H_


#include "RakNetTypes.h"
#include <string>
#include "libxml/parser.h"
#include "libxml/tree.h"
#include "CPeer.h"
#include <map>
#include <vector>
#include "CMysqlManager.h"
using namespace std;
using namespace RakNet;


#pragma pack(push, 1)
struct PT_ENTER_GAME_REQUEST_INFO_EX
{
	int gameid;
	int uid;
	char buf[16];
	unsigned long long guid;
};


struct PT_ENTER_GAME_REQUEST_INFO_EX1
{
	int serverid;
	int gameid;
	int uid;
	unsigned long long guid;

};

#pragma pack(pop)
//class CPeer;
#define SetSend(data) (char *)&data, sizeof(data)

//copy src to des
#define cpy(des, src, num)\
strncpy(des, src, num);\
des[num - 1] = 0;

namespace RakNet {
class Packet;
}

class CBaseUser;

class CRoomServer;

class CServer {

public:
	CServer();

	virtual ~CServer();

	// 初始化
	virtual bool Init();
	// 运行
	virtual void Start(int argc, char ** argv);
	virtual void Exit();
	void ConnectRoomServer();
	bool Registertomysql();

	void ProUserHeartTime();
private:

	unsigned int m_ServerId;
	string m_strIp;
	int m_nPort;
	int m_nMaxClient;
	int m_nCurHostNum;

	unsigned long long m_HertSpanTime;//心跳间隔时间

private:
	//scribe ip and port from xml
	string m_strScribeIp;
	unsigned short int m_nScribePort;

private:
	//  <mysql ip="localhost" port="3306" uname="root" pwd="111111" DB="main"/>

	unsigned int m_nSqlPort;
	string m_strSqlIp;
	string m_strSqlUname;
	string m_strSqlPwd;
	string m_strSqlDB;

	CMysqlManager m_Mysql;

public:

	std::vector<std::string> split(std::string str, std::string pattern);
	void ReadConfig(string strConfigPath);

	void QuerUserInfo(unsigned int nUserId);
	void HandlePacketCmd();

	void HandleRacknetCmd(unsigned char nCmdID, unsigned char * pData,
			Packet * packet);

	void OnKeyCmd(char* message);

	void SendtoAll(char * data, int len, CBaseUser * pOutUser);
	void SendtoAllByStream(BitStream * datastream, CBaseUser * pOutUser = NULL);

	void SendData(const char * data, const int len, RakNetGUID addr);
	void SendData(BitStream * bitStream, RakNetGUID addr);
	void SetClose();
	bool GetClose(CBaseUser *);

	//unsigned long GetTickCount();
	unsigned long long GetTickCountEx();

	char * GetSystemTime(char * pbuf);

	void SetRunTime(int day = 1, int hour = 0, int minute = 0, int second = 0);

	bool ProHostMsg(CBaseUser * pUser, unsigned char const * const data);
	bool ProHostMsgByStream(CBaseUser * pUser,
			unsigned char const * const data);
	bool OnClientDisconnPro(RakNetGUID guid);

	CBaseUser * GetUserById(unsigned int nUserId);

	bool ConnectRoomServer(const char * ip, const unsigned short port);
public:

	CPeer * m_peer;
	//CPeer * m_pClient;

	bool m_bClose;

	unsigned long long m_lRuntime;

	unsigned long long m_lGameCounttime;

	bool Connection_Lost_Process(Packet * packet);

	struct timeval t_start;
public:


	Packet * packet;
	//Packet * packetClient;
	map<RakNetGUID, CBaseUser *> m_UList;

	//===2012.10.12 add
	map<unsigned int, CBaseUser *> m_UListByUid;

	map<unsigned int, CRoomServer *> m_Roomserverlist;

	vector<CBaseUser *> m_tmpList;
	bool DelUser(RakNetGUID guid);
	bool AddUser(RakNetGUID guid);

	bool AddGame(unsigned int id, char * name);

	bool IsAllHostExit();

	void CleanRoom(unsigned int);
private:

	unsigned long long m_llLogTime;

};
extern CServer g_Server;



class CRaknetNode
{
public:

	RakNet::RakNetGUID m_Guid;

};

class CRoomServer:public CRaknetNode
{
public:
	unsigned int m_nId;
	string m_strIp;
	unsigned int m_nPort;

};

class CBaseUser : public CRaknetNode{
public:
	CBaseUser() {
		m_pRoomServer = NULL;

		m_lljumptime  = g_Server.GetTickCountEx();
	}
public:

	unsigned int m_nUserId;
	CRoomServer * m_pRoomServer;
	unsigned long long m_lljumptime;

};


#endif /* CSERVER_H_ */
