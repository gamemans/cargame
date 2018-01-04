#include "CBaselist.h"
#include "CServer.h"
CBaselist::CBaselist()
{
}

CBaselist::~CBaselist()
{
}

void CBaselist::SendtoAll(char * data, int len, unsigned int outid) {
	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); ++it) {

		CBaseUser * pUser = it->second;
		if (outid != 0 && outid  == it->first)
			continue;

		g_Server.SendData(data, len, it->first);

	}   
}

void CBaselist::SendtoAllByStream(BitStream * datastream, unsigned int outid) {
	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); ++it) {

		CBaseUser * pUser = it->second;
		if (outid != 0 && outid == it->first)
			continue;

		g_Server.SendData(datastream, it->first);
	}   
}

void CBaselist::SendtoUser(char * data, int len, unsigned int uid)
{
	g_Server.SendData(data, len, uid);
}
void CBaselist::SendStreamtoUser(BitStream * datastream, unsigned int uid)
{
	g_Server.SendData(datastream, uid);
}

void CBaselist::SendBitStream2Myself(unsigned char msgid, unsigned int nUserId,
		RakNet::BitStream * data)
{
	g_Server.SendBitStream2Myself(msgid, nUserId, data);
}
void CBaselist::SendPack2Myself(unsigned char msgid, unsigned int nUserId,
		unsigned char * data, unsigned int len)
{
	g_Server.SendPack2Myself(msgid, nUserId, data, len);
}


