#ifndef CBaselist_H_
#define CBaselist_H_
#include "CBaseUser.h"
#include "BitStream.h"
using namespace RakNet;
class CBaselist:public CBase
{
	public:
		CBaselist();
		~CBaselist();

	public:
		map<unsigned int, CBaseUser *> m_Userlist;

	public:

		void SendtoAll(char * data, int len, unsigned int outid = 0);

		void SendtoAllByStream(BitStream * datastream, unsigned int outid = 0); 

		void SendtoUser(char * data, int len, unsigned int uid);
		void SendStreamtoUser(BitStream * datastream, unsigned int uid);

		void SendBitStream2Myself(unsigned char msgid, unsigned int nUserId,
				RakNet::BitStream * data);
		void SendPack2Myself(unsigned char msgid, unsigned int nUserId,
				unsigned char * data, unsigned int len);
};


#endif
