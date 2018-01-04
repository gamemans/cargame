/*
 * CNetApp.cpp
 *
 *  Created on: 2012-10-26
 *      Author: liyan
 */

#include "CNetApp.h"
//#include "brTankNetMessages.h"
#include "GetTime.h"
#include "Kbhit.h"
#include "Gets.h"
CNetApp g_NetApp;
CNetApp::CNetApp() {
	// TODO Auto-generated constructor stub
	m_bRun = true;

	m_CurId = 0;

}

CNetApp::~CNetApp() {
	// TODO Auto-generated destructor stub
}

int CNetApp::GetCurIdAndInc() {

	return m_CurId++;
}

int CNetApp::GetCurId() {
	return m_CurId;
}

bool CNetApp::Init() {

	srand(time(NULL));
	m_bRun = true;

	for (int i = 0; i < ROBOT_NUM; i++) {
		ARRAY_USERID[i] = 100000000 + i;
	}
	CUser * pUser = new CUser;

	pUser->m_nUserId = ARRAY_USERID[ROBOT_POINTER++];
	GetCurIdAndInc();
	//pUser->m_nUserId = 262117 + GetCurIdAndInc();
	//	pUser->m_nUserId = ROBOT_BEGIN_ID + i;
	if (!pUser->ConnectServer(SERVER_IP, SERVER_PORT)) {
		printf("connect server fail, %d\n", pUser->m_nUserId);
		return false;
	}

	AddUser(pUser);
	//}

	return true;

}

bool CNetApp::Run() {
	while (true) {
		for (map<unsigned int, CUser *>::iterator it = m_UserList.begin();
				it != m_UserList.end(); it++) {
			it->second->Run();
		}

		usleep(100000);

		char message[100];

		if (kbhit()) {
			// Notice what is not here: something to keep our network running.  It's
			// fine to block on gets or anything we want
			// Because the network engine was painstakingly written using threads.
			Gets(message, sizeof(message));
			if (strcmp(message, "quit") == 0) {

				puts("Quitting.");
				break;
			}

			if(strcmp(message, "list") == 0)
			{

			}
		}

		//printf("==========================\n");
	}

	return true;
}

//UidOrAll -1 send msg to all
bool CUser::SendtoOtherbyProxy(const char* pszData, int nDataLen,
		unsigned int UidOrAll) {
	RakNet::BitStream inPacket;
	inPacket.Write(pszData, nDataLen);

	RakNet::BitStream newbitStream;
	if (createProxyPacket(inPacket, &newbitStream, -1)) {
		SendData(&newbitStream, m_ServerAddr);

	}
	//delete newbitStream;

	return true;
}

bool CUser::createProxyPacket(RakNet::BitStream& inBitStream,
		RakNet::BitStream * outBitStream, int nUserIDorAll) {
	int nSendNums;
	if (nUserIDorAll > 0)
		nSendNums = 1;
	else
		nSendNums = m_HostUserList.size();

	if (nSendNums == 0)
		return false;

	outBitStream->Write((unsigned char) PT_SERVER_PROXY);
	outBitStream->Write((unsigned int) nSendNums);

	if (nUserIDorAll > 0) {
		outBitStream->Write((unsigned int) nUserIDorAll); //  写入userID

	} else {
		for (map<unsigned int, CUser *>::iterator it = m_HostUserList.begin();
				it != m_HostUserList.end(); ++it) {
			outBitStream->Write((unsigned int) it->first); //  写入userID
		}

	}

	//int length = inBitStream->GetNumberOfBitsUsed();
	outBitStream->Write(inBitStream);

	return true;
}

CUser::CUser() {
	m_peer = new CPeer(0, false);
	m_pTimer = new CTimer();

	m_bMaster = false;
	m_nIndex = -1;
	m_pHost = NULL;

	SMJUser m_mjuser[4];

	for (int i = 0; i < 4; i++) {
		m_mjuser[i].nIndex = -1;
		m_mjuser[i].nUserId = -1;
	}
	unsigned int m_nUserId = -1;
	unsigned int m_nIndex = -1;

	unsigned int m_nBankIndex = -1;
	unsigned int m_nBankId = -1;
}
CUser::~CUser() {
	delete m_peer;
	m_peer = NULL;

	delete m_pTimer;
	m_pTimer = NULL;
}
void CUser::SendData(const char * data, const int len, SystemAddress addr) {
	m_peer->Send(data, len, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr);
}

void CUser::SendData(BitStream * bitStream, SystemAddress addr) {
	m_peer->Send(bitStream, IMMEDIATE_PRIORITY, RELIABLE_ORDERED, addr, false);
}
bool CUser::ConnectServer(const char * ip, const unsigned short port) {
	int err = m_peer->Connect(ip, port, "", 0);
	if (0 != err)
		printf("the serve error code is: %d\n", err);

	return (0 == err);
}

void CUser::EnterGame(unsigned int nGameId) {

}

void CUser::EnterRoom(unsigned int nRoomId) {

}

void CUser::EnterHost(unsigned int nHostId) {

}

void CUser::CreateHost() {

}

void CUser::LeaveGame() {

}

void CUser::LeaveRoom() {

}

void CUser::LeaveHost() {

}
void CUser::OnTimer(int iTimerID) {

	switch (iTimerID) {

	case ON_ENTER_GAME_TIME: {
		printf("enter game request!\n");

		RakNet::BitStream ws;

		ws.Write((unsigned char) PT_ENTER_GAME_REQUEST);
		ws.Write((unsigned int) SERVER_ID);
		ws.Write((unsigned int) GAME_ID);
		ws.Write((unsigned int) m_nUserId);
		ws.Write((unsigned long long) 0);

		SendData(&ws, m_ServerAddr);

		printf("ontime===ON_ENTER_GAME_TIME===uid:%d\n", m_nUserId);

	}
		break;

	case ON_ZHUOZHUANG: {

		int zhuang = rand() % 3 + 1;
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_ZHUOZHUANG_REQ);
		bsData.Write((unsigned int) zhuang);
		SendData(&bsData, m_ServerAddr);

		printf("ontime===ON_ZHUOZHUANG===uid:%d, zhuang:%d\n", m_nUserId,
				zhuang);

	}
		break;
	case ON_LAZHUANG: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_LAZHUANG_REQ);
		bsData.Write((unsigned int) 1);
		SendData(&bsData, m_ServerAddr);
	}
		break;
	case ON_DASAIZI: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_DASAIZI_REQ);
		SendData(&bsData, m_ServerAddr);

		printf("ontime===ON_DASAIZI===uid:%d\n", m_nUserId);
	}
		break;
	case ON_DASAIZI_AG: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_DASAIZI_AG_REQ);
		SendData(&bsData, m_ServerAddr);

		printf("ontime===ON_DASAIZI_AG===uid:%d\n", m_nUserId);
	}
		break;

	case ON_DAPAI: {

		unsigned int card = m_nCard[0];

		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_DAPAI_REQ);
		bsData.Write((unsigned int) card);
		SendData(&bsData, m_ServerAddr);

		printf("ontime===dapai===paiid:%d===uid:%d\n", card, m_nUserId);
	}
		break;

	case ON_PENG: {

		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_PENG_PASS_REQ);

		SendData(&bsData, m_ServerAddr);
		printf("ontime===ON_PENG, uid:%d\n", m_nUserId);
	}
		break;

	case ON_GANG: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_GANG_PASS_REQ);

		SendData(&bsData, m_ServerAddr);
		printf("ontime===ON_GANG, uid:%d\n", m_nUserId);
	}
		break;

	case ON_MOPAI: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_MJ_MOPAI_REQ);

		SendData(&bsData, m_ServerAddr);
		printf("ontime===ON_MOPAI, uid:%d\n", m_nUserId);
	}
		break;

	case ON_LEAVE_GAME_TIME: {
		printf("leave game request!\n");

		PT_LEAVE_GAME_REQUEST_INFO data;
		SendData((char *) &data, sizeof(data), m_ServerAddr);
	}
		break;

	case ONTIMER_HEART_JUMP: {

		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_USER_HEART_JUMP);
		SendData(&bsData, m_ServerAddr);
	}
		break;

	case ONTIMER_READY: {
		RakNet::BitStream bsData;
		bsData.Write((unsigned char) PT_HOST_MESSAGE);
		bsData.Write((unsigned int) PT_HOST_READY_REQUEST);
		SendData(&bsData, m_ServerAddr);

		printf("ontimer====ready==uid:%d\n", m_nUserId);
	}
		break;

		if (iTimerID != 15) { //跳过心跳消息
			printf("myself:%d, ONTIME:%d\n", m_nUserId, iTimerID);
		}

	}
}
void CUser::SetTimer(int iTimeId, unsigned long ulElapse, bool bOnce) {
	m_pTimer->SetTimer(iTimeId, ulElapse, bOnce);
}
void CUser::KillTimer(int iTimeId) {
	m_pTimer->KillTimer(iTimeId);
}
bool CUser::ProHostMsg(Packet * packet) {

	return false;
}

bool CUser::ProHostIngameMsgByStream(Packet * packet) {
	return true;
}
bool CUser::ProHostMsgByStream(Packet * packet) {
	RakNet::BitStream readPaket(packet->data, packet->length, false);
	readPaket.IgnoreBytes(1);

	unsigned int nHostMsgId;
	readPaket.Read(nHostMsgId);
	switch (nHostMsgId) {

	case PT_MJ_MATCH_ACCEPT: {
		unsigned int uid;
		unsigned int nIndex;

		unsigned int num;
		readPaket.Read(num);

		for (int i = 0; i < num; i++) {
			readPaket.Read(uid);
			readPaket.Read(nIndex);

			if (nIndex < 0 || nIndex > 3) {
				assert(0);
			}

			m_mjuser[nIndex].nIndex = nIndex;
			m_mjuser[nIndex].nUserId = uid;

			printf("match uid is %d, nIndex:%d\n", uid, nIndex);
			if (uid == m_nUserId) {
				m_nIndex = nIndex;
			}

		}

		printf("=============================\n");

		SetTimer(ONTIMER_READY, ONTIMER_READY_TIME + random() % 1000);
	}
		return true;

	case PT_MJ_END_GAME: {
		SetTimer(ON_ENTER_GAME_TIME, 1000 + random() % 1000);
	}
		return true;

	case PT_MJ_GAME_START: {

		unsigned int nBankerId;

		readPaket.Read(nBankerId);
		printf("=gamestart===BankerId:%d\n", nBankerId);

		if (nBankerId == this->m_nUserId) {
			SetTimer(ON_ZHUOZHUANG, ON_ZHUOZHUANG_TIME);
		}

		for (int i = 0; i < 4; i++) {
			m_nBankId = nBankerId;
			if (m_mjuser[i].nUserId == m_nBankId) {
				m_nBankIndex = m_mjuser[i].nIndex;
			}
		}

	}
		return true;

	case PT_MJ_USER_ZHUOZHUANG: {
		unsigned int uid;
		unsigned int nzhuang;

		readPaket.Read(uid);
		readPaket.Read(nzhuang);

		if (nzhuang < 3) {
			SetTimer(ON_LAZHUANG, ON_LAZHUANG_TIME);
		}

	}
		return true;

	case PT_MJ_USER_LAZHUANG: {
		unsigned int uid;
		unsigned int nzhuang;

		readPaket.Read(uid);
		readPaket.Read(nzhuang);

		printf("user lazhuang======>uid:%d, zhuang:%d\n", uid, nzhuang);
	}
		return true;

	case PT_MJ_DASAIZAI_START: {

		unsigned int nzhuang;
		readPaket.Read(nzhuang);
		if (this->m_nUserId == nzhuang) {
			SetTimer(ON_DASAIZI, ON_DASAIZI_TIME);
		}
	}
		return true;

	case PT_MJ_USER_DASAIZI: {

		unsigned int uid;
		unsigned int nA;
		unsigned int nB;

		readPaket.Read(uid);
		readPaket.Read(nA);
		readPaket.Read(nB);

		printf("user_dasaii,uid:%d, A:%d, B:%d\n", uid, nA, nB);

		if ((nA + nB - 1 + m_nBankIndex) % 4 == m_nIndex) {
			SetTimer(ON_DASAIZI_AG, ON_DASAIZI_AG_TIME);
		}
	}
		return true;

	case PT_MJ_USER_DASAIZI_AG: {
		unsigned int uid;
		unsigned int nA;
		unsigned int nB;

		readPaket.Read(uid);
		readPaket.Read(nA);
		readPaket.Read(nB);

		printf("user_dasaizi_ag,net_uid:%d, A:%d, B:%d\n", uid, nA, nB);

	}
		return true;

	case PT_MJ_FAPAI: {
		unsigned int num;
		readPaket.Read(num);

		printf("fapai===========begin=========uid:%d, num:%d====num\n",
				m_nUserId, num);
		for (int i = 0; i < num; i++) {
			readPaket.Read(m_nCard[i]);
			printf("%d,", m_nCard[i]);
		}

		printf("\nfapai===========end=========uid:%d\n", m_nUserId);

		if (m_nBankIndex == m_nIndex) {
			SetTimer(ON_DAPAI, ON_DAPAI_TIME);
		}
	}
		return true;

	case PT_MJ_USER_MOPAI: {
		unsigned int uid;
		unsigned int card;
		readPaket.Read(uid);
		readPaket.Read(card);
		m_nCard[0] = card;
		printf("PT_MJ_USER_MOPAI===net_uid:%d, card:%d, uid\n",uid, card, m_nUserId);

		if(uid == m_nUserId)
		{
			SetTimer(ON_DAPAI, ON_DAPAI_TIME);
		}
	}
		return true;

	case PT_MJ_USER_DAPAI: {
		unsigned int uid;
		unsigned int cardid;
		unsigned int optuid;
		unsigned int opttype;

		readPaket.Read(uid);
		readPaket.Read(cardid);
		readPaket.Read(optuid);
		readPaket.Read(opttype);

		printf(
				"PT_MJ_USER_DAPAI====net_uid:%d, cardid:%d, optuid:%d, opttype:%d\n",
				uid, cardid, optuid, opttype);

		if (optuid == m_nUserId) {
			switch (opttype) {
			case OPT_TYPE_DAPAI: {
				printf("error type:PT_MJ_USER_DAPAI\n");
			}
				break;
			case OPT_TYPE_GANG: {
				SetTimer(ON_GANG, ON_GANG_TIME);
			}
				break;
			case OPT_TYPE_PENG: {
				SetTimer(ON_PENG, ON_PENG_TIME);
			}
				break;
			case OPT_TYPE_MOPAI: {
				SetTimer(ON_MOPAI, ON_MOPAI_TIME);
			}
				break;

			}

		}

	}
		return true;

	case PT_HOST_GAME_START: {

		SetTimer(ONTIMER_TANK_ENTER_INGAME, 1000 + random() % 1000);

	}
		return true;

	case PT_HOST_INGAME_START_ACCEPT: {

		printf("game start==============\n");

		SetTimer(ONTIMER_EXIT_GAME_INROOM, 10 * 60 * 1000 + random() % 1000);
	}

		return true;

	}

	return false;
}
bool CUser::Run() {

	int iTimerId = m_pTimer->OnTimer();
	if (iTimerId != -1)
		OnTimer(iTimerId);

	unsigned char packetIdentifier;
	for (Packet * packet = m_peer->Receive(); packet;
			m_peer->DeallocatePacket(packet), packet = m_peer->Receive()) {

		packetIdentifier = CPeer::GetPacketIdentifier(packet);
		switch (packetIdentifier/*packet->data[0]*/) {
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			printf("Another client has dised.\n");
			break;
		case ID_REMOTE_CONNECTION_LOST:
			printf("Another client has lost the connection.\n");
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			printf("Another client has connected.\n");

			break;
		case ID_NEW_INCOMING_CONNECTION: {
			printf("A connection is incoming.\n");

		}
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS: {
			printf("The server is full.\n");
			break;
		}
		case ID_DISCONNECTION_NOTIFICATION: {
			printf("ID_DISCONNECTION_NOTIFICATION.\n");
		}
			break;

		case ID_CONNECTION_LOST: {
			printf("ID_CONNECTION_LOST.\n");
		}
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED: {
			printf("Our connection request has been accepted.\n");

			m_ServerAddr = packet->systemAddress;

			SetTimer(ON_ENTER_GAME_TIME, 1000 + random() % 1000);

			SetTimer(ONTIMER_HEART_JUMP, 3000, false);

			if (g_NetApp.GetCurIdAndInc() >= ROBOT_NUM)
				break;

			CUser * pUser = new CUser;

			pUser->m_nUserId = g_NetApp.ARRAY_USERID[g_NetApp.ROBOT_POINTER++];
//			pUser->m_nUserId = g_NetApp.getBeginId()

			if (!pUser->ConnectServer(SERVER_IP, SERVER_PORT)) {
				printf("connect server fail, %d\n", pUser->m_nUserId);
				break;
			} else {
				printf("connect server success, %d\n", pUser->m_nUserId);
			}
			g_NetApp.AddUser(pUser);

		}
			break;

		case PT_ENTER_GAME_ACCEPT: {
			printf("%d,PT_ENTER_GAME_ACCEPT\n", m_nUserId);

		}

			break;
		case PT_HOST_MESSAGE: {

			if (ProHostMsg(packet))
				break;

			if (ProHostMsgByStream(packet))
				break;

		}
			break;

		case PT_LEAVE_GAME_ACCEPT: {
			printf("myself:%d,PT_LEAVE_GAME_ACCEPT\n", m_nUserId);

			SetTimer(ON_ENTER_GAME_TIME, 1000 + random() % 1000);
		}
			break;
		case PT_LEAVE_ROOM_ACCEPT: {

			printf("myself:%d,PT_LEAVE_ROOM_ACCEPT\n", m_nUserId);

			if (m_pHost)	//自己所在的主机内，有人离开
			{
				for (map<unsigned int, CUser *>::iterator it =
						m_HostUserList.begin(); it != m_HostUserList.end();
						it++) {
					CUser *p = it->second;
					delete p;
					p = NULL;
				}

				m_HostUserList.clear();

				m_pHost = NULL;
			}

			for (map<unsigned int, CHostInfo *>::iterator it =
					m_HostList.begin(); it != m_HostList.end(); it++) {
				delete it->second;
				it->second = NULL;
			}
			m_HostList.clear();

			SetTimer(ON_ENTER_ROOM_TIME, 1000 + random() % 1000);
		}
			break;

		case PT_CHANGE_HOST: {

			printf("myself:%d, PT_CHANGE_HOST\n");

			//	PT_CHANGE_HOST_INFO * msg = (PT_CHANGE_HOST_INFO *)packet->data;

			unsigned int nHostId;
			unsigned int nOldHostId;
			RakNet::BitStream readPaket(packet->data, packet->length, false);
			readPaket.IgnoreBytes(1);
			readPaket.Read(nHostId);
			readPaket.Read(nOldHostId);
//			nHostId = msg->nHostId;
//			nOldHostId = msg->nOldHostId;

			printf("myself:%d, oldhostid:%d,newhostid:%d,PT_CHANGE_HOST\n",
					m_nUserId, nOldHostId, nHostId);

			if (m_HostList.find(nOldHostId) == m_HostList.end())
				assert(false);

			m_HostList[nHostId] = m_HostList[nOldHostId];
			m_HostList[nHostId]->nHostId = nHostId;
			m_HostList.erase(nOldHostId);

			if (m_pHost && m_pHost->nHostId == nOldHostId) {
				m_pHost->nHostId = nHostId;
			}
		}
			break;
		case PT_LEAVE_HOST_ACCEPT: {
			printf("myself:%d,PT_LEAVE_HOST_ACCEPT\n", m_nUserId);

			if (m_HostList.find(m_pHost->nHostId) == m_HostList.end()) {
				assert(false);
			}

			for (map<unsigned int, CUser *>::iterator it =
					m_HostUserList.begin(); it != m_HostUserList.end(); it++) {
				CUser *p = it->second;
				delete p;
				p = NULL;
			}

			m_HostUserList.clear();

			m_pHost = NULL;

			if (random() % 10 != 1)
				SetTimer(ON_ENTER_HOST_TIME, 1000 + random() % 1000);
			else
				SetTimer(ON_LEAVE_ROOM_TIME, 1000 + random() % 1000);
		}
			break;
		case PT_CREATE_HOST_ACCEPT: {

			PT_CREATE_HOST_ACCEPT_INFO * msg =
					(PT_CREATE_HOST_ACCEPT_INFO *) packet->data;

			m_pHost = new CHostInfo(tmpCreatehost);

			m_HostList[m_pHost->nHostId] = m_pHost;

			printf("myself:%d,PT_CREATE_HOST_ACCEPT, hostid:%d\n", m_nUserId,
					m_pHost->nHostId);

			SetTimer(ONTIMER_TANK_READY_INGAME, 6000 + random() % 6000);
		}
			break;

		case PT_USER_INGAME_MSG: {
			printf("myself:%d,PT_USER_INGAME_MSG\n", m_nUserId);
			ProHostIngameMsgByStream(packet);
		}
			break;
		default: {
			printf("unknow msg id %d\n", packetIdentifier);
		}
			break;
		}
	}

	return true;
}
