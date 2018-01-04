/*
 * CServer.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: aaaa
 */

#include "CServer.h"

#include "structdefine.h"
#include "packdefine.h"

#include "Kbhit.h"
#include "Gets.h"
#include "libxml/parser.h"
#include "libxml/tree.h"

#include <time.h>

#include "BitStream.h"
//#include <jemalloc/jemalloc.h>
#include "GetTime.h"

//#include "RakPeer.h"
#define SERVER_AUTO_RUN

CServer g_Server;

CServer::CServer() {
	// TODO Auto-generated constructor stub

	gettimeofday(&t_start, NULL);

	m_peer = NULL;
	packet = NULL;

	m_bClose = false;

	m_lGameCounttime = 0;

	m_nCurHostNum = 0;

	m_nMaxClient = 200;

	m_llLogTime = GetTickCountEx();

	SetRunTime(300, 0, 1);

	m_HertSpanTime = 1000 * 30;
}

CServer::~CServer() {
	// TODO Auto-generated destructor stub

	map<RakNetGUID, CBaseUser *>::iterator it = m_UList.begin();
	while (it != m_UList.end()) {
		delete it->second;
		it->second = NULL;
		++it;
	}
	m_UList.clear();

	for (map<unsigned int, CRoomServer *>::iterator it =
			m_Roomserverlist.begin(); it != m_Roomserverlist.end(); it++) {
		//m_peer->CloseConnection(it->second->m_Addr);//这里不用断开了，因为642行已断了所有连m_peer->Disconnect();
		delete it->second;
		it->second = NULL;
	}
	m_Roomserverlist.clear();

}

void CServer::SendtoAll(char * data, int len, CBaseUser * pOutUser) {
	for (map<unsigned int, CBaseUser *>::iterator it = m_UListByUid.begin();
			it != m_UListByUid.end(); ++it) {

		CBaseUser * pUser = it->second;
		if (pOutUser != NULL && pOutUser->m_nUserId == pUser->m_nUserId)
			continue;

		g_Server.SendData(data, len, it->second->m_Guid);

	}
}

void CServer::SendtoAllByStream(BitStream * datastream, CBaseUser * pOutUser) {
	for (map<unsigned int, CBaseUser *>::iterator it = m_UListByUid.begin();
			it != m_UListByUid.end(); ++it) {

		CBaseUser * pUser = it->second;
		if (pOutUser != NULL && pOutUser->m_nUserId == pUser->m_nUserId)
			continue;

		g_Server.SendData(datastream, it->second->m_Guid);

	}

}

void CServer::SendData(const char * data, const int len, RakNetGUID addr) {
	m_peer->Send(data, len, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr);
}

void CServer::SendData(BitStream * bitStream, RakNetGUID addr) {
	m_peer->Send(bitStream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr, false);
}

bool CServer::DelUser(RakNetGUID guid) {

	if (m_UList.find(guid) != m_UList.end()) {
		delete m_UList[guid];
		m_UList.erase(guid);
	}

	return true;
}
bool CServer::AddUser(RakNetGUID guid) {
	if (m_UList.find(guid) != m_UList.end()) {
		m_UList[guid]->m_lljumptime = GetTickCountEx();
		return false;
	}
	CBaseUser * pUser = new CBaseUser;
	pUser->m_lljumptime = GetTickCountEx();
	m_UList[guid] = pUser;
	pUser->m_Guid = guid;

	return true;
}

bool CServer::AddGame(unsigned int id, char * name) {
	//CBaseGame * pGame = new CBaseGame;
	return true;
}
bool CServer::OnClientDisconnPro(RakNetGUID guid) {

	printf("OnClientDisconnPro--1\n");
	if (m_UList.find(guid) != m_UList.end()) {
		printf("OnClientDisconnPro--2\n");

		unsigned int nUserId = m_UList[guid]->m_nUserId;

		if (m_UList[guid]->m_pRoomServer) {
			RakNet::BitStream writePaket;
			writePaket.Write((unsigned char) PT_USER_DISCONNECT);
			writePaket.Write((unsigned int) nUserId);
			SendData(&writePaket, m_UList[guid]->m_pRoomServer->m_Guid);
		}

		m_UListByUid.erase(nUserId);

		DelUser(guid);

		m_peer->CloseConnection(guid);

		return true;

	}

	return false;

}

void CServer::CleanRoom(unsigned int roomid) {
	if (m_Roomserverlist.find(roomid) != m_Roomserverlist.end()) {

		for (map<unsigned int, CBaseUser *>::iterator it = m_UListByUid.begin();
				it != m_UListByUid.end();) {

			if (it->second->m_pRoomServer
					&& it->second->m_pRoomServer->m_nId == roomid) {
				RakNetGUID guid = it->second->m_Guid;
				m_UListByUid.erase(it++);

				DelUser (guid);

				m_peer->CloseConnection(guid);
			}
			else
			{
				it++;
			}
		}
	}
}
void CServer::HandlePacketCmd() {

	unsigned char packetIdentifier;

	for (packet = m_peer->Receive(); packet;
			m_peer->DeallocatePacket(packet), packet = m_peer->Receive()) {
		packetIdentifier = CPeer::GetPacketIdentifier(packet);

//		if (packetIdentifier != PT_SERVER_PROXY
//				&& PT_SERVER_PROXY != PT_PROXY_TRANSMISSION) {
//			if (m_UList.find(packet->guid) != m_UList.end()) {
//				CBaseUser * pUser = m_UList[packet->guid];
//				printf("MSG ID:%d, ip:%s, uid:%d\n", packetIdentifier,
//						pUser->m_Addr.ToString(), pUser->m_nUserId);
//			} else {
//				printf("MSG ID:%d, ip:%s\n", packetIdentifier,
//						packet->guid.ToString());
//			}
//		}

		switch (packetIdentifier/*packet->data[0]*/) {

		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf("Another client has disconnected.\n");
			break;
		case ID_REMOTE_CONNECTION_LOST:
			printf("Another client has lost the connection.\n");
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf("Another client has connected.\n");
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED: {
			printf("Our connection request has been accepted m_ServerId:%d.\n",
					m_ServerId);

//			CRoomServer * pRoom = new CRoomServer;
//			pRoom->m_Addr = packet->guid;
//			m_Roomserverlist[10] = pRoom;

			RakNet::BitStream writePaket;
			writePaket.Write((unsigned char) PT_SERVER_IDENTIFY_NOTIFY);
			writePaket.Write((unsigned int) SERVER_TYPE_PROXYSERVER);
			writePaket.Write((unsigned int) m_ServerId);
			SendData(&writePaket, packet->guid);

		}
			break;

		case ID_NEW_INCOMING_CONNECTION: {
			printf("A connection is incoming.\n");
			//	char* tempIP = (char*) packet->guid.ToString();

			this->AddUser(packet->guid);

			RakNet::BitStream writePaket;
			writePaket.Write((unsigned char) PT_SERVER_IDENTIFY_NOTIFY);
			writePaket.Write((unsigned int) SERVER_TYPE_PROXYSERVER);
			writePaket.Write((unsigned int) m_ServerId);
			SendData(&writePaket, packet->guid);

		}
			break;

		case PT_SERVER_IDENTIFY_NOTIFY: {

			unsigned int nServerId = -1;
			unsigned int nServerType;
			RakNet::BitStream rs(packet->data, packet->length, false);
			rs.IgnoreBytes(1);
			rs.Read(nServerType);
			if (nServerType != SERVER_TYPE_ROOMSERVER)
				break;

			rs.Read(nServerId);

			DelUser(packet->guid); //因为所有连入服务器的都存入了User列表，所以要去掉服务器的部分

			if (m_Roomserverlist.find(nServerId) != m_Roomserverlist.end()) {
				m_Roomserverlist[nServerId]->m_Guid = packet->guid;
			} else {

				CRoomServer * pServer = new CRoomServer;
				pServer->m_nId = nServerId;
				pServer->m_Guid = packet->guid;
				m_Roomserverlist[nServerId] = pServer;
			}

		}
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS: {
			printf("The server is full.\n");
			break;
		}
		case ID_DISCONNECTION_NOTIFICATION: {

			printf("%s has disconnected.\n", packet->guid.ToString());

			bool flag = false;
			for (map<unsigned int, CRoomServer *>::iterator it =
					m_Roomserverlist.begin(); it != m_Roomserverlist.end();
					it++) {
				if (it->second->m_Guid == packet->guid) {

					CleanRoom(it->first);

					delete it->second;
					it->second = NULL;
					m_Roomserverlist.erase(it);

					flag = true;
					break;
				}
			}

			if (!flag) { //是玩家断开

				this->OnClientDisconnPro(packet->guid);
			}

		}
			break;

		case ID_ALREADY_CONNECTED: {
//			RakNet::BitStream writePaket;
//			writePaket.Write((unsigned char) PT_SERVER_IDENTIFY_NOTIFY);
//			writePaket.Write((unsigned int) SERVER_TYPE_PROXYSERVER);
//			writePaket.Write((unsigned int) m_ServerId);
//			SendData(&writePaket, packet->guid);
//			m_peer->CloseConnection(packet->guid);
//			printf("%s\n", packet->guid.ToString(true));
		}

			break;
		case ID_CONNECTION_LOST: {
			printf("%s lost the connection.\n", packet->guid.ToString());

			bool flag = false;
			for (map<unsigned int, CRoomServer *>::iterator it =
					m_Roomserverlist.begin(); it != m_Roomserverlist.end();
					it++) {
				if (it->second->m_Guid == packet->guid) {
					delete it->second;
					it->second = NULL;
					m_Roomserverlist.erase(it);

					flag = true;
					break;
				}
			}

			if (!flag) { //是玩家断开

				this->OnClientDisconnPro(packet->guid);
			}

		}
			break;
		case PT_USER_HEART_JUMP: {

			if (m_UList.find(packet->guid) == m_UList.end()) {
				break;
			}

			CBaseUser * pUser = m_UList[packet->guid];
			if (pUser && pUser->m_lljumptime) {
				pUser->m_lljumptime = GetTickCountEx();
			}

		}
			break;
		case PT_NAT_PUNCHTROUGH_REQUEST: {

		}
			break;
		case PT_ENTER_GAME_REQUEST: { //客户端第一次连入，确定roomserver.

			printf("PT_ENTER_GAME_REQUEST\n");
			int datalen = packet->length;
			RakNet::BitStream readPaket(packet->data, datalen, false);

			unsigned int nServerId;
			unsigned int nGameId;
			unsigned int nUserId;
			unsigned long long nUserGuid;

			readPaket.IgnoreBytes(1);

//			//===================unity da kai=========================
//
//			PT_ENTER_GAME_REQUEST_INFO_EX info;
//			readPaket.Read((char *)&info, sizeof(info));


			PT_ENTER_GAME_REQUEST_INFO_EX1 info;
			readPaket.Read((char *)&info, sizeof(info));


			nServerId = info.serverid;
			nGameId = info.gameid;
			nUserId = info.uid;
			nUserGuid = info.guid;
//			//====================unity zhu diao xia mian==========================
//			readPaket.Read(nServerId);
//			readPaket.Read(nGameId);
//			readPaket.Read(nUserId);
//			readPaket.Read(nUserGuid);


			//=============================================
//			PT_ENTER_GAME_REQUEST_INFO_EX info;
//
//			info.gameid = 1009;
//			info.guid = 10000000098;
//			info.uid=200009;
//			strcpy(info.buf, "hello world!");
//			RakNet::BitStream data11;
//			data11.Write((unsigned char) 255);
//
//			data11.Write((char *)&info, sizeof(info));
//
//			SendData(&data11, packet->guid);


			if (m_Roomserverlist.find(nServerId) == m_Roomserverlist.end()) {
				printf(
						"PT_ENTER_GAME_REQUEST error no roomserver id : %d====\n",
						nServerId);
				break;
			}

			if (m_UListByUid.find(nUserId) != m_UListByUid.end()) {
				CBaseUser * pUser = m_UListByUid[nUserId];
				if (pUser && pUser->m_Guid != packet->guid) {	//断线重连

				//将之前的用户清理
				//必须手动处理断开情况，然后进入，如果直接掉用m_peer->CloseConnection(guid),断线处理消息将晚于当前消息发送至roomserver
					this->OnClientDisconnPro(pUser->m_Guid);
					printf("aaa warning====dis=======uid:%d\n", nUserId);

					//			break;
				}
			}
			if (m_UList.find(packet->guid) == m_UList.end()) {
				printf("aaa warning===========uid:%d\n", nUserId);
				return;

			}
			m_UList[packet->guid]->m_pRoomServer = m_Roomserverlist[nServerId];
			m_UList[packet->guid]->m_nUserId = nUserId;

			m_UListByUid[nUserId] = m_UList[packet->guid];

			//==========================

			RakNet::BitStream data;
			data.Write((unsigned char) PT_ENTER_GAME_REQUEST);
			data.Write((unsigned int) nUserId);
			data.Write((unsigned int) nGameId);
			data.Write((unsigned long long) nUserGuid);
			data.Write((unsigned int) packet->systemAddress.GetPort());
			data.Write(packet->systemAddress.ToString(true), 50);

//			PT_ENTER_GAME_REQUEST_INFO data;
//			data.nGameId = nGameId;
//			data.nUserId = nUserId;
//			data.uUserGuid = nUserGuid;
			SendData(&data, m_Roomserverlist[nServerId]->m_Guid);

			printf("PT_ENTER_GAME_REQUEST====end\n");

		}
			break;

		case PT_ROOM_TO_PROXY: { //roomserver发给客户端消息

			int datalen = packet->length;
			RakNet::BitStream readPaket(packet->data, datalen, false);
			unsigned int nUserId;
			unsigned char msgtype;
			readPaket.IgnoreBytes(1);
			readPaket.Read(msgtype);
			readPaket.Read(nUserId);

			if (m_UListByUid.find(nUserId) != m_UListByUid.end()) {

				if (msgtype == 1) { //以流形式发送
					RakNet::BitStream writePaket;
					writePaket.Write(readPaket);

					SendData(&writePaket, m_UListByUid[nUserId]->m_Guid);

				} else { //以包形式发送到客户端

					int len;
					readPaket.Read(len);

					//char * buf = (char *)malloc(sizeof(char) * len);
					char * buf = (char *) malloc(len);
					readPaket.Read(buf, len);
					SendData(buf, len, m_UListByUid[nUserId]->m_Guid);

					free(buf);
				}

			}
		}
			break;

		case PT_SERVER_PROXY: { //客户端之间转发

			/*
			 * packet struct
			 *
			 * ID_TIMESTAMP;									unsigned char
			 * GetTime();											int64
			 * PT_SERVER_PROXY;							unsigned char
			 * username;											unsigned int
			 * userid[username];						unsigned int * (username)
			 * base data;											packet->length - (sum of up);
			 * * */

			//unsigned char id1;
			unsigned int nUserNum;

			unsigned char msgid;

			RakNet::Time timestamp;
			//pack head size
			//int headsize = 0;

			int datalen = packet->length;
			RakNet::BitStream readPaket(packet->data, datalen, false);

			readPaket.Read(msgid);
			if (msgid == ID_TIMESTAMP) {
				readPaket.Read(timestamp);

				printf("%lu-----%lu\n", timestamp, RakNet::GetTime());
				readPaket.IgnoreBytes(1);			//ignore PT_SERVER_PROXY
			}

			readPaket.Read(nUserNum);

			//PT_SERVER_PROXY, 	nUserNum,		nUserNum * UserId
			//			headsize = 1 + sizeof(unsigned int) + nUserNum
			//					* sizeof(unsigned int);

			unsigned int * pUserid = new unsigned int[nUserNum];

			//	unsigned int nUserId;
			for (int i = 0; i < (int) nUserNum; i++) {
				readPaket.Read(pUserid[i]);
			}

			RakNet::BitStream datastream;
			if (msgid == ID_TIMESTAMP) {
				datastream.Write((unsigned char) ID_TIMESTAMP);
				datastream.Write(timestamp);
			}
			datastream.Write(readPaket);

			for (int i = 0; i < (int) nUserNum; i++) {

				if (m_UListByUid.find(pUserid[i]) != m_UListByUid.end()) {
					CBaseUser * pUser = m_UListByUid[pUserid[i]];

					SendData(&datastream, pUser->m_Guid);
				}

			}
			delete[] pUserid;
			pUserid = NULL;

		}
			break;

		case PT_LEAVE_GAME_REQUEST:
		case PT_ENTER_ROOM_REQUEST:
		case PT_LEAVE_ROOM_REQUEST:
		case PT_CREATE_HOST_REQUEST:
		case PT_JOIN_HOST_REQUEST:
		case PT_LEAVE_HOST_REQUEST: //加入主机申请
		case PT_GAME_START: //游戏开始
		case PT_GAME_END: //游戏结束
		case PT_HOST_MESSAGE: {
			if (m_UList.find(packet->guid) != m_UList.end()) {
				CBaseUser * pUser = m_UList[packet->guid];
				if (!pUser || !pUser->m_pRoomServer) {
					printf("the user is not normal! msg id is:%d\n",
							packetIdentifier);
					break;
				}

				RakNet::BitStream writeStream;
				writeStream.Write((unsigned char) packetIdentifier);
				writeStream.Write(pUser->m_nUserId);
				writeStream.Write(packet->length);
				writeStream.Write((char *) packet->data, packet->length);
				SendData(&writeStream, pUser->m_pRoomServer->m_Guid);

			}
		}
			break;

		default:
			//客户端发来的消息，除了上面处理过的，直接转发到roomserver
		{

			printf("unknow msg %d\n", packetIdentifier);

		}
			break;
		}
	}
}

string GetXmlValue(xmlNodePtr node, unsigned char * value = 0) {
	string strRet;

	if (value == NULL)
		value = BAD_CAST "value";
	xmlAttrPtr attrPtr = node->properties;
	do {
		if (xmlStrcmp(attrPtr->name, value) == 0) {
			xmlChar* szAttr = xmlGetProp(node, attrPtr->name);
			strRet = (char *) szAttr;
			xmlFree(szAttr);

			return strRet;
		}
		attrPtr = attrPtr->next;
	} while (attrPtr != NULL);

	return strRet;
}
void CServer::ReadConfig(string strConfigPath) {
	xmlDocPtr doc; //定义解析文档指针
	xmlNodePtr rootNode, childNode;

	doc = xmlReadFile(strConfigPath.c_str(), "UTF-8", XML_PARSE_RECOVER);
	if (doc != NULL) {
		rootNode = xmlDocGetRootElement(doc);
		printf("%s\n", rootNode->name);
		childNode = rootNode->xmlChildrenNode;
		string strT;
		while (childNode != NULL) {
			printf("%s\n", childNode->name);

			if (xmlStrcmp(childNode->name, BAD_CAST "ServerId") == 0) {
				strT = GetXmlValue(childNode);
				m_ServerId = atoi(strT.c_str());

			} else if (xmlStrcmp(childNode->name, BAD_CAST "ServerIp") == 0) {
				m_strIp = GetXmlValue(childNode);

			} else if (xmlStrcmp(childNode->name, BAD_CAST "ServerPort") == 0) {
				strT = GetXmlValue(childNode);
				m_nPort = atoi(strT.c_str());

			} else if (xmlStrcmp(childNode->name, BAD_CAST "MaxClient") == 0) {
				strT = GetXmlValue(childNode);
				m_nMaxClient = atoi(strT.c_str());

			} else if (xmlStrcmp(childNode->name, BAD_CAST "mysql") == 0) {

				m_strSqlIp = GetXmlValue(childNode, BAD_CAST "ip");
				m_strSqlUname = GetXmlValue(childNode, BAD_CAST "uname");
				m_strSqlPwd = GetXmlValue(childNode, BAD_CAST "pwd");
				m_strSqlDB = GetXmlValue(childNode, BAD_CAST "DB");

				strT = GetXmlValue(childNode, BAD_CAST "port");
				m_nSqlPort = atoi(strT.c_str());

			} else if (xmlStrcmp(childNode->name, BAD_CAST "ScribeLog") == 0) {

			} else if (xmlStrcmp(childNode->name, BAD_CAST "webserver") == 0) { //webserver

			} else if (xmlStrcmp(childNode->name, BAD_CAST "ZMQRouter") == 0) {

			} else if (xmlStrcmp(childNode->name, BAD_CAST "Game") == 0) {
//				strT = GetXmlValue(childNode, BAD_CAST "id");
//				unsigned int gameid = (unsigned int) atoi(strT.c_str());
//				pGame = m_pGameFactory->CreateGame(gameid);
//				if (pGame == NULL)
//					continue;
//
//				pGame->SetId(gameid);
//				strT = GetXmlValue(childNode, BAD_CAST "name");
//				pGame->SetName(strT.c_str());
//
//				m_GameList[gameid] = pGame;
//
//				xmlNodePtr roomNode = childNode->children;
//				while (roomNode != NULL) {
//					if (roomNode->type == XML_ELEMENT_NODE) {
//
//						unsigned int nRoomId;
//						string strName;
//						unsigned int nMaxNum;
//
//						strT = GetXmlValue(roomNode, BAD_CAST "id");
//						nRoomId = atoi(strT.c_str());
//
//						strName = GetXmlValue(roomNode, BAD_CAST "name");
//
//						strT = GetXmlValue(roomNode, BAD_CAST "userNumLimit");
//						nMaxNum = atoi(strT.c_str());
//
//						pGame->AddRoom(nRoomId, (char *) strName.c_str(),
//								nMaxNum);
//					}
//					roomNode = roomNode->next;
//				}

			}
			childNode = childNode->next;
		}

	} else
		printf("打开配置文件失败。\n");
}

bool CServer::ConnectRoomServer(const char * ip, const unsigned short port) {

	int err = m_peer->Connect(ip, port, "", 0);

	printf("the serve error code is: %d, ip:%s, port:%d\n", err, ip, port);

	return (0 == err);
}
std::vector<std::string> CServer::split(std::string str, std::string pattern) {

	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern; //扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if (pos < size) {
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
void CServer::ConnectRoomServer() {
	//=====================================================
	int recordnum = 0;
	char szSql[1024];
	sprintf(szSql, "select * from user_service_list");
	string strData = m_Mysql.SelectData(szSql, 4, ",", ";", recordnum);
	/**
	 +--------+---------------+-------+----------+
	 | ID     | ip            | port  | serverid |
	 +--------+---------------+-------+----------+
	 | 292001 | 192.168.1.209 | 60101 |        2 |
	 +--------+---------------+-------+----------+
	 */

	if (recordnum > 0) {
		vector<string> rowlist = split(strData, ";");

		for (vector<string>::iterator it = rowlist.begin(); it != rowlist.end();
				it++) {

			vector<string> itemlist = split(*it, ",");
			if (itemlist.size() > 0) {

				ConnectRoomServer(itemlist[1].c_str(),
						atoi(itemlist[2].c_str()));
			}
		}

	}

}

bool CServer::Registertomysql() {

	int recordnum = 0;
	char szSql[1024];
	sprintf(szSql, "select id from user_proxy_list where id = %d", m_ServerId);
	string strData = m_Mysql.SelectData(szSql, 1, ",", ";", recordnum);

	if (recordnum > 0) {

		sprintf(szSql,
				"update user_proxy_list set ip=\'%s\', port = %d where id = %d",
				m_strIp.c_str(), m_nPort, m_ServerId);

		int ret = m_Mysql.UpdateData(szSql);

		if (ret)
			return false;

	} else {

		sprintf(szSql,
				"insert into user_proxy_list(id, ip, port) values(%d, \'%s\', %d)",
				m_ServerId, m_strIp.c_str(), m_nPort);
		if (!m_Mysql.InsertData(szSql)) {
			printf("error:Registertomysql is fail, serverid:%d, ip:%s, port:%d",
					m_ServerId, m_strIp.c_str(), m_nPort);
			return false;
		}
	}

	return true;
}

bool CServer::Init() {

	ReadConfig("RackNetConfig.xml");

	m_peer = new CPeer(m_nPort, true);

	StartupResult result = m_peer->Startup(m_nMaxClient, m_nPort);
	if (result != RAKNET_STARTED)
		perror("Startup");

	m_Mysql.ConnMySQL(m_strSqlIp.c_str(), m_nSqlPort, m_strSqlDB.c_str(),
			m_strSqlUname.c_str(), m_strSqlPwd.c_str(), NULL);

	//注册到数据库
	if (!Registertomysql()) {
		return false;
	}

	//连接其它房间服务器
	ConnectRoomServer();

	return true;
}

unsigned long long CServer::GetTickCountEx() {
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return ((unsigned long long) ts.tv_sec * 1000
			+ (unsigned long long) ts.tv_nsec / 1000000);
}
char * CServer::GetSystemTime(char * pbuf) {

	time_t t = time(0);

	strftime(pbuf, 64, "%Y-%m-%d %X", localtime(&t));

	return pbuf;
}
void CServer::Exit() {

}

void CServer::Start(int argc, char ** argv) {

	char message[100];
	for (;;) {

		usleep(1000);

		m_lGameCounttime = GetTickCountEx();

		if (kbhit()) {
			// Notice what is not here: something to keep our network running.  It's
			// fine to block on gets or anything we want
			// Because the network engine was painstakingly written using threads.
			Gets(message, sizeof(message));
			if (strcmp(message, "quit") == 0) {
				puts("Quitting.");
				break;
			} else
				OnKeyCmd(message);
		}

		HandlePacketCmd();

		ProUserHeartTime();
	}

	m_peer->Disconnect();
	delete m_peer;
	m_peer = NULL;
}
void CServer::ProUserHeartTime() {

	map<RakNetGUID, CBaseUser *>::iterator it = m_UList.begin();
	unsigned long long curtime = GetTickCountEx();
	while (it != m_UList.end()) {

		if (curtime - it->second->m_lljumptime > m_HertSpanTime) {
			printf("==>>>proUserHearttime is %d\n",
					curtime - it->second->m_lljumptime);
			this->OnClientDisconnPro(it++->first);
		} else {
			it++;
		}
	}
}
void CServer::SetRunTime(int day, int hour, int minute, int second) {
	if (day > 10)			//max 10 day
		day = 10;
	m_lRuntime = (((day * 24 + hour) * 60 + minute) * 60 + second) * 1000
			+ GetTickCountEx();
}
void CServer::OnKeyCmd(char* message) {
	if (strcmp(message, "kick") == 0) {
		return;
	} else if (strcmp(message, "getconnectionlist") == 0) {
		return;
	} else if (strcmp(message, "ban") == 0) {
		return;
	}
}
