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

#include "CMJGame.h"
#include "CDDZGame.h"
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
	m_llMatchCountTime = 10000;
	m_llMatchTime = m_llLogTime;
	SetRunTime(300, 0, 1);

}

CServer::~CServer() {
	// TODO Auto-generated destructor stub

	map<unsigned int, CPlayer *>::iterator it = m_UListByUid.begin();
	while (it != m_UListByUid.end()) {
		delete it->second;
		it->second = NULL;
		++it;
	}
	m_UListByUid.clear();

	/*
	 *
	 */
	map<unsigned int, CBaseGame *>::iterator it1 = m_Gamelist.begin();
	while (it1 != m_Gamelist.end()) {
		delete it1->second;
		it1->second = NULL;
		++it1;
	}
	m_Gamelist.clear();

	/*
	 * 清理代理服务器
	 *
	 */
	for (map<RakNetGUID, CProxyServer *>::iterator it =
			m_ProxyServerList.begin(); it != m_ProxyServerList.end(); it++) {
		delete it->second;
		it->second = NULL;
	}
	m_ProxyServerList.clear();

}

void CServer::SendtoAll(char * data, int len, CPlayer * pOutUser) {
	for (map<unsigned int, CPlayer *>::iterator it = m_UListByUid.begin();
			it != m_UListByUid.end(); ++it) {

		CPlayer * pUser = it->second;
		if (pOutUser != NULL && pOutUser->GetId() == pUser->GetId())
			continue;

		SendData(data, len, it->second);

	}
}

void CServer::SendBitStream2Myself(unsigned char msgid, unsigned int nUserId,
		RakNet::BitStream * data) {

	RakNet::BitStream writeStream;
	writeStream.Write((unsigned char) msgid);
	writeStream.Write(nUserId);
	writeStream.Write(data->GetNumberOfBitsUsed());
	writeStream.Write(data);

	g_Server.m_peer->m_pPeer->SendLoopback((char *) writeStream.GetData(),
			writeStream.GetNumberOfBitsUsed());
}

void CServer::SendPack2Myself(unsigned char msgid, unsigned int nUserId,
		unsigned char * data, unsigned int len) {
	RakNet::BitStream writeStream;
	writeStream.Write((unsigned char) msgid);
	writeStream.Write(nUserId);
	writeStream.Write(len);
	writeStream.Write((char *) data, len);

	g_Server.m_peer->m_pPeer->SendLoopback((char *) writeStream.GetData(),
			writeStream.GetNumberOfBitsUsed());
}


void CServer::SendtoAllByStream(BitStream * datastream, CPlayer * pOutUser) {
	for (map<unsigned int, CPlayer *>::iterator it = m_UListByUid.begin();
			it != m_UListByUid.end(); ++it) {

		CPlayer * pUser = it->second;
		if (pOutUser != NULL && pOutUser->GetId() == pUser->GetId())
			continue;

		SendData(datastream, it->second);

	}

}

void CServer::SendData(const char * data, const int len, RakNetGUID addr) {
	m_peer->Send(data, len, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr);
}
void CServer::SendData(BitStream * bitStream, RakNetGUID addr) {
	m_peer->Send(bitStream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr, false);
}
void CServer::SendData(const char * data, const int len, CPlayer* pUser) {

	unsigned int nUserId = pUser->GetId();
	BitStream streambuf;
	streambuf.Write((unsigned char) PT_ROOM_TO_PROXY);
	streambuf.Write((unsigned char) 0); //表示包的类型为结构体
	streambuf.Write((unsigned int) nUserId);
	streambuf.Write((unsigned int) len);
	streambuf.Write(data, len);

	m_peer->Send(&streambuf, IMMEDIATE_PRIORITY, RELIABLE_ORDERED,
			pUser->m_Guid, false);

}
void CServer::SendData(BitStream * bitStream, CPlayer * pUser) {

	bitStream->ResetReadPointer();
	unsigned int nUserId = pUser->GetId();

	BitStream streambuf;
	streambuf.Write((unsigned char) PT_ROOM_TO_PROXY);
	streambuf.Write((unsigned char) 1); //表示包的类型为流
	streambuf.Write((unsigned int) nUserId);
	streambuf.Write(bitStream);

	m_peer->Send(&streambuf, IMMEDIATE_PRIORITY, RELIABLE_ORDERED,
			pUser->m_Guid, false);
}

void CServer::SendData(const char * data, const int len, unsigned int uid) {
	if (m_UListByUid.find(uid) == m_UListByUid.end())

	{
		return;
	}

	CPlayer * pPlayer = m_UListByUid[uid];
	if (!pPlayer) {
		return;
	}

	SendData(data, len, pPlayer);
}

void CServer::SendData(BitStream * bitStream, unsigned int uid) {
	if (m_UListByUid.find(uid) == m_UListByUid.end()) {
		return;
	}

	CPlayer * pPlayer = m_UListByUid[uid];
	if (!pPlayer) {
		return;
	}

	SendData(bitStream, pPlayer);

}
void CServer::OnClientDisconnPro(RakNetGUID guid) {

}
void CServer::Add2Matchlist(unsigned int uid) {
	if (m_Matchlist.find(uid) != m_Matchlist.end()) {
		return;
	}

	if (m_UListByUid.find(uid) == m_UListByUid.end()) {
		return;
	}

	m_Matchlist[uid] = m_UListByUid[uid];
}

void CServer::UserLeave(unsigned int uid) {
	FIND_LISTCONTENT(m_UListByUid, uid, return);

	CPlayer * pUser = m_UListByUid[uid];

	if (pUser->m_nGameId != -1) {

		if (m_Gamelist.find(pUser->m_nGameId) != m_Gamelist.end()) {
			CBaseGame * pGame = m_Gamelist[pUser->m_nGameId];

			if (pGame) {
				pGame->LeaveGame(uid);
			}
		}
	}

	pUser->m_nGameId = -1;
	m_UListByUid.erase(uid);

	delete pUser;
	pUser = NULL;

}
void CServer::OnClientDisconnPro(unsigned int uid, bool b) {
	FIND_LISTCONTENT(m_UListByUid, uid, return);

	CPlayer * pUser = m_UListByUid[uid];

	if (!pUser) {
		return;
	}

	if (pUser->m_nGameId != -1) {
//		pUser->m_bDisconnect = true; ///<断线重连
//		pUser->SetTimer(ONTIMER_WAIT_RECONNECT, ONTIMER_WAIT_RECONNECT_TIME,
//				true);

		UserLeave(uid);

	} else {

		printf("uid:%d is reconnecting\n", uid);
		UserLeave(uid);

		//		CStream stream;
		//		stream.WriteInt(ROOM_TO_DATA_LOGOUT);
		//		stream.WriteInt(uid);
		//		m_zmq.Send(stream);

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
		//				CPlayer * pUser = m_UList[packet->guid];
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
			writePaket.Write((unsigned int) SERVER_TYPE_ROOMSERVER);
			writePaket.Write((unsigned int) m_ServerId);
			SendData(&writePaket, packet->guid);

		}
			break;

		case ID_NEW_INCOMING_CONNECTION: {
			printf("A connection is incoming.\n");
			//	char* tempIP = (char*) packet->guid.ToString();

		}
			break;

		case PT_SERVER_IDENTIFY_NOTIFY: {
			unsigned int nServerId = -1;
			unsigned int nServerType;
			RakNet::BitStream rs(packet->data, packet->length, false);
			rs.IgnoreBytes(1);
			rs.Read(nServerType);
			if (nServerType != SERVER_TYPE_PROXYSERVER)
				break;

			rs.Read(nServerId);

			if (m_ProxyServerList.find(packet->guid)
					!= m_ProxyServerList.end()) {
				m_ProxyServerList[packet->guid]->m_nId = nServerId;
			} else {

				CProxyServer * pServer = new CProxyServer;
				pServer->m_nId = nServerId;
				pServer->m_Guid = packet->guid;
				m_ProxyServerList[packet->guid] = pServer;
			}
		}
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS: {
			printf("The server is full.\n");
			break;
		}
		case ID_DISCONNECTION_NOTIFICATION: {

			printf("%s has disconnected.\n", packet->guid.ToString());

		}
			break;

		case ID_ALREADY_CONNECTED: {
		}
			break;
		case ID_CONNECTION_LOST: {
			printf("%s lost the connection.\n", packet->guid.ToString());

		}
			break;
		case PT_NAT_PUNCHTROUGH_REQUEST: {

		}
			break;
		case PT_USER_DISCONNECT: {
			unsigned int nUserId;
			RakNet::BitStream rs(packet->data, packet->length, false);
			rs.IgnoreBytes(1);
			rs.Read(nUserId);
			OnClientDisconnPro(nUserId, false);
		}
			break;
		case PT_ENTER_GAME_REQUEST: { //客户端第一次连入，确定roomserver.

			unsigned int nUserId;
			unsigned int nGameId;
			unsigned int nPort;
			unsigned long long llUserguid;
			char szIp[50];

			RakNet::BitStream rs(packet->data, packet->length, false);
			rs.IgnoreBytes(1);
			rs.Read(nUserId);
			rs.Read(nGameId);
			rs.Read(llUserguid);
			rs.Read(nPort);
			rs.Read(szIp, 50);

			CPlayer * pPlayer = NULL;
			//此人存在
			if (m_UListByUid.find(nUserId) != m_UListByUid.end()) {
				pPlayer = m_UListByUid[nUserId];
				if (pPlayer->m_nGameId != -1) {
					if (m_Gamelist.find(pPlayer->m_nGameId)
							!= m_Gamelist.end()) {
						CBaseGame * pGame = m_Gamelist[pPlayer->m_nGameId];
						pGame->LeaveGame(nUserId);
					}
				}
				pPlayer->Reset();
				pPlayer->m_Guid = packet->guid;

			} else {
				//新登录用户
				pPlayer = new CPlayer;
				pPlayer->SetId(nUserId);
				pPlayer->m_Guid = packet->guid;
				m_UListByUid[nUserId] = pPlayer;

				PT_ENTER_GAME_ACCEPT_INFO data;
				SendData((char *) &data, sizeof(data), pPlayer);
			}
			Add2Matchlist(nUserId);
		}
			break;
		case PT_HOST_MESSAGE: {
			unsigned int nUserId = 0;
			int len = 0;

			RakNet::BitStream rs(packet->data, packet->length, false);
			rs.IgnoreBytes(1);
			rs.Read(nUserId);
			rs.Read(len);

			FIND_LISTCONTENT(m_UListByUid, nUserId, break);

			char * buf = (char *) malloc(len);

			rs.Read(buf, len);

			CPlayer * pUser = m_UListByUid[nUserId];

			if (!pUser) {
				free(buf);
				break;
			}
			// if (ProHostMsg(pUser, (unsigned char *) buf)) {
			//	  free(buf);
			//	  break;
			// }
			if (ProHostMsgByStream(pUser, (unsigned char *) buf, len)) {
				free(buf);
				break;
			}
			//===ww need modify===test
			free(buf);
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
bool CServer::ProHostMsgByStream(CPlayer * pUser, unsigned char * data,
		unsigned int len) {

	unsigned int nMsgId = 0;
	int datalen = len;
	RakNet::BitStream readPaket(data, datalen, false);
	readPaket.IgnoreBytes(1);

	readPaket.Read(nMsgId);

	//================================================================
	printf("msg id is:%d\n", nMsgId);
	if (pUser->m_nGameId == -1) {

		printf("1,gameid is %d, msgid:%d, uid:%d\n", pUser->m_nGameId, nMsgId,
				pUser->GetId());
		return false;
	}

	if (m_Gamelist.find(pUser->m_nGameId) == m_Gamelist.end()) {
		printf("2,gameid is %d, msgid:%d, uid:%d\n", pUser->m_nGameId, nMsgId,
				pUser->GetId());
		return false;
	}

	CBaseGame * pGame = m_Gamelist[pUser->m_nGameId];

	if (!pGame) {
		printf("error:pGame is null\n");
		return false;
	}

	//================================================================
	if (pGame->ProHostMsgByStream(pUser->GetId(), data, len))
		return true;

	switch (nMsgId) {
	case PT_HOST_USER_HOSTLIST_REQUEST: {
	}
		return true;

	case PT_HOST_READY_REQUEST: {
		pGame->Net_Ready(pUser->GetId());
	}
		return true;
	case PT_MJ_DAPAI_REQ: {

		unsigned int nCardId = 0;
		readPaket.Read(nCardId);

		((CMJGame *) pGame)->Net_Dapai(pUser->GetId(), nCardId);
	}
		return true;
	case PT_MJ_DASAIZI_REQ: {
		((CMJGame *) pGame)->Net_DaSaizi(pUser->GetId());
	}
		return true;
	case PT_MJ_DASAIZI_AG_REQ: {
		((CMJGame *) pGame)->Net_DaSaiZiAG(pUser->GetId());
	}
		return true;
	case PT_MJ_GANG_REQ: {
		unsigned int nCardId = 0;
		readPaket.Read(nCardId);

		((CMJGame *) pGame)->Net_Gang(pUser->GetId(), nCardId);

	}
		return true;
	case PT_MJ_GANG_PASS_REQ: {
		((CMJGame *) pGame)->Net_GangPass(pUser->GetId());
	}
		return true;
	case PT_MJ_ZHUOZHUANG_REQ: {
		unsigned int nZhuangnum;
		readPaket.Read(nZhuangnum);
		((CMJGame *) pGame)->Net_ZhuoZhuang(pUser->GetId(), nZhuangnum);
	}
		return true;
	case PT_MJ_LAZHUANG_REQ: {
		unsigned int nlazhuang;
		readPaket.Read(nlazhuang);
		((CMJGame *) pGame)->Net_LaZhuang(pUser->GetId(), nlazhuang);
	}
		return true;
	case PT_MJ_PENG_REQ: {
		unsigned int nCardId = 0;
		readPaket.Read(nCardId);

		((CMJGame *) pGame)->Net_Peng(pUser->GetId(), nCardId);

	}
		return true;
	case PT_MJ_PENG_PASS_REQ: {
		((CMJGame *) pGame)->Net_PengPass(pUser->GetId());
	}
		return true;
	case PT_MJ_HU_REQ: {
		unsigned int nCardId = 0;
		readPaket.Read(nCardId);

		((CMJGame *) pGame)->Net_Hu(pUser->GetId(), nCardId);

	}
		return true;
	case PT_MJ_MOPAI_REQ: {
		((CMJGame *) pGame)->Net_MoPai(pUser->GetId());
	}
		return true;


	case PT_DDZ_CHUPAI: {

		int pai[20];
		int painum = 0;
		((CDDZGame *)pGame)->ChuPai(pUser, pai, painum);
	}
		return true;
	case PT_DDZ_JIAOFEN: {

		int fen = 1;
		((CDDZGame *)pGame)->JiaoPai(pUser, fen);
	}
		return true;
	case PT_DDZ_PASS: {
		((CDDZGame *)pGame)->PassPai(pUser);
	}
		return true;
	}


	return false;
}



//void CServerApp::OnMsgProc(CThreadCommand * pCmd)
//{
//	WORD id = *(WORD *)pCmd->m_Data;
//	switch( id )
//	{
//	case PT_UPDATE_ROOM_USER_DATA:
//		{
//			PT_UPDATE_ROOM_USER_DATA_INFO * msg = (PT_UPDATE_ROOM_USER_DATA_INFO *)pCmd->m_Data;
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			CBaseRoom * pRoom;
//			int iRoomNum = pGame->GetRoomNum();
//			for( int i = 0; i < iRoomNum; ++ i )
//			{
//				pRoom = pGame->GetRoom( i );
//				if( !pRoom )
//					continue;
//				pRoom->UpdateAllUserInfo();
//			}
//		}
//		return;
//	case PT_CHECK_ALLOT:
//		{
//			PT_CHECK_ALLOT_INFO * msg = (PT_CHECK_ALLOT_INFO *)pCmd->m_Data;
//
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			if( !pGame )
//				return;
//			CBaseRoom * pRoom = pGame->GetRoom( msg->dwRoomId );
//			if( !pRoom )
//				return;
//			pRoom->CheckAllot();
//		}
//		return;
//	case PT_USER_LEAVE:
//		{
//			PT_USER_LEAVE_INFO * msg = (PT_USER_LEAVE_INFO *)pCmd->m_Data;
//
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			if( !pGame )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法GameId: %d\n", msg->dwGameId );
//				return;
//			}
//			CBaseRoom * pRoom = pGame->GetRoom( msg->dwRoomId );
//			if( !pRoom )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法RoomId: %d,%d\n", msg->dwGameId, msg->dwRoomId );
//				return;
//			}
//			pRoom->LeaveRoom( msg->dwUserId );
//
//
//		}
//		return;
//	case PT_ENTER_TABLE_CHECK:
//		{
//			PT_ENTER_TABLE_CHECK_INFO * msg = (PT_ENTER_TABLE_CHECK_INFO *)pCmd->m_Data;
//
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			if( !pGame )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法GameId: %d\n", msg->dwGameId );
//				return;
//			}
//			CBaseRoom * pRoom = pGame->GetRoom( msg->dwRoomId );
//			if( !pRoom )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法RoomId: %d,%d\n", msg->dwGameId, msg->dwRoomId );
//				return;
//			}
//			CUser * pUser = pRoom->GetUser( msg->dwUserId );
//			if( !pUser )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"未找到用户: %d\n", msg->dwUserId );
//				return;
//			}
//
//			pUser->m_bAcceptLookAt = msg->bAcceptLookAt;
//			pRoom->EnterTable( pUser, msg->dwTableId, msg->dwChairId ,msg->bCheckPass , msg->szPassWord);
//		}
//		return;
//	case PT_LEAVE_TABLE_CHECK:
//		{
//			PT_LEAVE_TABLE_CHECK_INFO * msg = (PT_LEAVE_TABLE_CHECK_INFO *)pCmd->m_Data;
//
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			if( !pGame )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法GameId: %d\n", msg->dwGameId );
//				return;
//			}
//			CBaseRoom * pRoom = pGame->GetRoom( msg->dwRoomId );
//			if( !pRoom )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法RoomId: %d,%d\n", msg->dwGameId, msg->dwRoomId );
//				return;
//			}
//			CUser * pUser = pRoom->GetUser( msg->dwUserId );
//			if( !pUser )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"未找到用户: %d\n", msg->dwUserId );
//				return;
//			}
//			CBaseTable * pTable = NULL;
//			if( pRoom->IsCanEnterTable() || pRoom->m_iScoreType == SCORE_MATCH)
//				pTable = pRoom->GetTable( pUser->m_iTableId );
//			else if( !pRoom->IsCanEnterTable() )
//				pRoom->m_pAllotTables->GetData( pUser->m_iTableId, pTable );
//			if( !pTable )
//				return;
//
//			if( !pTable->IsInTable( pUser ) )
//				return;
//
//			pRoom->LeaveTable( pUser );
//		}
//		return;
//	case PT_READY_CHECK:
//		{
//			PT_READY_CHECK_INFO * msg = (PT_READY_CHECK_INFO *)pCmd->m_Data;
//
//			CBaseGame * pGame = g_pGameManager->GetGame( msg->dwGameId );
//			if( !pGame )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法GameId: %d\n", msg->dwGameId );
//				return;
//			}
//			CBaseRoom * pRoom = pGame->GetRoom( msg->dwRoomId );
//			if( !pRoom )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"非法RoomId: %d,%d\n", msg->dwGameId, msg->dwRoomId );
//				return;
//			}
//			CUser * pUser = pRoom->GetUser( msg->dwUserId );
//			/*if( !pUser )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"未找到用户: %d\n", msg->dwUserId );
//				return;
//			}*/
//			if( !pUser )
//			{
//				_ftprintf( g_ErrLog.m_pFile, L"未找到用户: %d\n", msg->dwUserId );
//
//				g_strText = "";
//				g_strText.Format( L" 未找到用户 %d\n", msg->dwUserId );
//				Print( g_strText.GetBuffer() );
//				g_strText = "";
//				return;
//			}
//			else
//			{
//				g_strText = "";
//				g_strText.Format( L"%s 准备1\n", pUser->m_szUserName );
//				Print( g_strText.GetBuffer() );
//				g_strText = "";
//			}
//
//			pRoom->UserReady( pUser );
//		}
//		return;
//	}
//
//	if( TJMJGameMsg( pCmd ) )
//		return;
//
//	if( TJMJ2GameMsg( pCmd ) )
//		return;
//
//	if( DDZGameMsg( pCmd ))
//		return;
//
//	if( WZQGameMsg( pCmd ) )
//		return;
//
//	if( TGMJGameMsg( pCmd ) )
//		return;
//
//	if( BIE7GameMsg( pCmd ))
//		return;
//	if( BIE7SECGameMsg( pCmd ))
//		return;
//
//	if ( BJLGameMsg( pCmd ) )
//		return;
//	if ( WHNCGameMsg( pCmd ) )
//		return;
//
//	if( LHMJGameMsg( pCmd ) )
//		return;
//
//	if( LHMJ2GameMsg( pCmd ) )
//		return;
//
//	if ( ZJHGameMsg(pCmd) )
//		return;
//
//	if ( ZHYGameMsg( pCmd ) )
//		return;
//	if ( ZLJGameMsg( pCmd ) )
//		return;
//	if( JSZLJGameMsg( pCmd ) )
//		return;
//	if ( TSDCGameMsg( pCmd ) )
//		return;
//
//	if ( TGM2GameMsg( pCmd ) )
//		return;
//
//	if( JSTGM2GameMsg( pCmd ) )
//		return;
//
//	if ( TGM4GameMsg( pCmd ) )
//		return;
//
//	if ( ZJHServerMsg( pCmd ) )
//		return;
//	if ( WHNCServerMsg( pCmd ) )
//		return;
//	if ( BJLServerMsg( pCmd ) )
//		return;
//
//	if ( ZHYServerMsg( pCmd ) )
//		return;
//	if ( GZServerMsg( pCmd ) )
//		return;
//
//	if ( TGM2ServerMsg( pCmd ) )
//		return;
//	if ( JSTGM2ServerMsg( pCmd ) )
//		return;
//
//	if ( TGM4ServerMsg( pCmd ) )
//		return;
//
//	if( PGJGameMsg( pCmd ) )
//		return;
//	if( GZGameMsg( pCmd ) )
//		return;
//
//	if( JSDDZGameMsg( pCmd ))
//		return;
//
//	if( JSTJMJGameMsg( pCmd ) )
//		return;
//	if( JSTGMJGameMsg( pCmd ) )
//		return;
//
//    if( CNGameMsg( pCmd ) )
//		return;
//}
//


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

	xmlFreeDoc(doc);
}

bool CServer::ConnectProxyServer(const char * ip, const unsigned short port) {

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
void CServer::ConnectProxyServer() {
	//=====================================================
	ConnectProxyServer("localhost", 61000);
}

bool CServer::Init() {

	ReadConfig("RackNetConfig.xml");

	m_peer = new CPeer(m_nPort, true);

	StartupResult result = m_peer->Startup(m_nMaxClient, m_nPort);
	if (result != RAKNET_STARTED)
		perror("Startup");

	//m_Mysql.ConnMySQL(m_strSqlIp.c_str(), m_nSqlPort, m_strSqlDB.c_str(),
	//		m_strSqlUname.c_str(), m_strSqlPwd.c_str(), NULL);

	//注册到数据库
	//	if (!Registertomysql()) {
	//		return false;
	//	}

	//连接其它房间服务器
	ConnectProxyServer();

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

void CServer::DestroyGame(CBaseGame * pGame) {
	for (map<unsigned int, CBaseUser *>::iterator ituser =
			pGame->m_Userlist.begin(); ituser != pGame->m_Userlist.end();
			ituser++) {
		unsigned int nUserId = ituser->first;
		if (m_UListByUid.find(nUserId) != m_UListByUid.end()) {
			CPlayer * pPlayer = m_UListByUid[nUserId];
			if (pPlayer) {
				pPlayer->m_nGameId = -1;
			}
		}
	}

	delete pGame;
	pGame = NULL;
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

		if (m_lGameCounttime - m_llMatchTime > m_llMatchCountTime) {

			OnTimeMatch();

			m_llMatchTime = m_lGameCounttime;
		}

		for (map<unsigned int, CBaseGame *>::iterator it = m_Gamelist.begin();
				it != m_Gamelist.end();) {
			CBaseGame * pGame = it->second;

			if (pGame->m_bDestroy) {

				m_Gamelist.erase(it++);
				DestroyGame(pGame);

				continue;
			} else {
				it++;
			}

			int nTimerId = pGame->GetTimerId();

			if (nTimerId != -1) {
				pGame->OnTimer(nTimerId);
			}

		}

	}

	m_peer->Disconnect();
	delete m_peer;
	m_peer = NULL;
}

bool CServer::OnMatch(CPlayer * pPlayer) {
	if (pPlayer->m_nGameId != -1)
		return false;
	return true;
}
void CServer::OnTimeMatch() {
	printf("on time match, machlist size:%d\n", m_Matchlist.size());
	if (m_Matchlist.size() == 0) {
		return;
	}

	///匹配已有游戏

	CPlayer * tmp[4];
	memset(tmp, 0, sizeof(CPlayer *) * 4);
	int num = 0;
	if (m_Matchlist.size() >= 4) {

		for (map<unsigned int, CPlayer *>::iterator it = m_Matchlist.begin();
				it != m_Matchlist.end();) {
			tmp[num] = it->second;

		if (OnMatch(tmp[num])) {
				m_Matchlist.erase(it++);
			} else {
				it++;
				continue;
			}

			//m_Matchlist.erase(tmp[num]->GetId());

			num++;

			if (num >= 4) {
				break;
			}

		}

		if (num < 4)			///<人数不够
				{
			return;
		}

		///创建一个游戏
		CBaseGame * pGame = CreateMJGame(tmp[0]->GetId());
		if (!pGame) {
			return;
		}

		RakNet::BitStream ds;
		ds.Write((unsigned char) PT_HOST_MESSAGE);
		ds.Write((unsigned int) PT_MJ_MATCH_ACCEPT);
		ds.Write((unsigned int) 4);			//write size

		for (int i = 0; i < 4; i++) {
			unsigned int index = -1;
			pGame->EnterGame(tmp[i]->GetId(), index);

			ds.Write((unsigned int) tmp[i]->GetId());			///<写入玩家ＩＤ
			ds.Write((unsigned int) index);

			tmp[i]->m_nGameId = pGame->GetId();

			printf("match success.%d\n", tmp[i]->GetId());

		}

		pGame->SendtoAllByStream(&ds);
	}

}

CBaseGame * CServer::CreateMJGame(unsigned int id) {
	CBaseGame * pGame = new CMJGame();
	m_Gamelist[id] = pGame;
	pGame->SetId(id);

	return pGame;

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
