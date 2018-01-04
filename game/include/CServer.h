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
//#include "CMysqlManager.h"

#include "CPlayer.h"
using namespace std;
using namespace RakNet;


//在STL中查找值，如果没有找到 reurn
#define FIND_LISTCONTENT(name,value,result)         \
	if(name.find(value) == name.end()){          \
		printf(":file:%s, line:%d\n", __FILE__, __LINE__);						\
		\
		result;										 \
	}



//class CPeer;
#define SetSend(data) (char *)&data, sizeof(data)

//copy src to des
#define cpy(des, src, num)\
	strncpy(des, src, num);\
des[num - 1] = 0;

namespace RakNet {
	class Packet;
}
class CBaseGame;
/**
  NTIMER_TANK_DISCONNECT
 * 代理服务器基本接口
 */
class CProxyServer {
	public:
		///代理服务器ＩＤ
		unsigned int m_nId;

		///代理服务器ＩＰ
		string m_strIp;

		///代理服务器端口
		unsigned int m_nPort;

		///代理服务器raknet唯一标识
		RakNet::RakNetGUID m_Guid;
};

class CServer:public CBase {

	public:
		CServer();

		virtual ~CServer();

		// 初始化
		virtual bool Init();
		// 运行
		virtual void Start(int argc, char ** argv);
		virtual void Exit();
		void ConnectProxyServer();
		bool Registertomysql();

	private:

		unsigned int m_ServerId;
		string m_strIp;
		int m_nPort;
		int m_nMaxClient;
		int m_nCurHostNum;
	private:
		///匹配需要时间
		unsigned long long m_llMatchCountTime;

		///上次自动区配时间
		unsigned long long m_llMatchTime;
		void OnTimeMatch();
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

		//CMysqlManager m_Mysql;

	public:

		std::vector<std::string> split(std::string str, std::string pattern);
		void ReadConfig(string strConfigPath);

		void HandlePacketCmd();

		void HandleRacknetCmd(unsigned char nCmdID, unsigned char * pData,
				Packet * packet);

		void OnKeyCmd(char* message);

		///发送消息到所有接收者
		void SendtoAll(char * data, int len, CPlayer * pOutUser);
		void SendtoAllByStream(BitStream * datastream, CPlayer * pOutUser = NULL);

		void SendBitStream2Myself(unsigned char msgid, unsigned int nUserId,
				RakNet::BitStream * data);

		void SendPack2Myself(unsigned char msgid, unsigned int nUserId,
				unsigned char * data, unsigned int len);
		/**
		 * 发送消息到指定接收者
		 * @param data 发送数据
		 * @param len 数据长度
		 * @param pUser 接收者
		 * @return 无
		 */
		void SendData(const char * data, const int len, CPlayer * pUser);

		/**
		 * 发送消息到指定接收者
		 * @param bitStream 发送数据
		 * @param pUser 接收者
		 * @return 无
		 */
		void SendData(BitStream * bitStream, CPlayer * pUser);
		/**
		 * 发送消息到指定接收者
		 * @param data 发送数据
		 * @param len 数据长度
		 * @param pUser 接收者
		 * @return 无
		 */
		void SendData(const char * data, const int len, RakNetGUID addr);

		/**
		 * 发送消息到指定接收者
		 * @param bitStream 发送数据
		 * @param addr 接收者
		 * @note 注意参数
		 * @return 无
		 */
		void SendData(BitStream * bitStream, RakNetGUID addr);

		void SendData(const char * data, const int len, unsigned int uid);
		void SendData(BitStream * bitStream, unsigned int uid);

		void SetClose();
		bool GetClose(CPlayer *);

		//unsigned long GetTickCount();
		unsigned long long GetTickCountEx();

		char * GetSystemTime(char * pbuf);

		void SetRunTime(int day = 1, int hour = 0, int minute = 0, int second = 0);

		bool ProHostMsg(CPlayer * pUser, unsigned char const * const data);


		bool ProHostMsgByStream(CPlayer * pUser, unsigned char * data,
				unsigned int len);
		void OnClientDisconnPro(RakNetGUID guid);

		CPlayer * GetUserById(unsigned int nUserId);

		bool ConnectProxyServer(const char * ip, const unsigned short port);

		void UserLeave(unsigned int uid);

		void DestroyGame(CBaseGame * pGame);
		void Add2Matchlist(unsigned int);
		void OnClientDisconnPro(unsigned int uid, bool = true);
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

		map<unsigned int, CPlayer *> m_UListByUid;
		map<unsigned int, CPlayer *> m_Matchlist;
		map<unsigned int, CBaseGame *>m_Gamelist;

		map<RakNetGUID, CProxyServer *>m_ProxyServerList;

		bool DelUser(RakNetGUID guid);
		bool AddUser(RakNetGUID guid);

		CBaseGame * CreateMJGame(unsigned int id);
		
		bool IsAllHostExit();

		bool OnMatch(CPlayer *p);

	private:

		unsigned long long m_llLogTime;

};
extern CServer g_Server;




#endif /* CSERVER_H_ */
