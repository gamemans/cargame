#include "CMJGame.h"
#include "CMJUser.h"
#include "MessageIdentifiers.h"
#include "structdefine.h"
#include "packdefine.h"
#define NET_USER_CHECK(uid) \
	if(m_Userlist.find(uid) == m_Userlist.end())			\
{														\
	printf("error:uid not find in userlist\n");			\
	return;												\
}														\
CMJUser * pUser = (CMJUser *)(m_Userlist[uid]);			\
if(!pUser)												\
{														\
	printf("error:pUser is NULL.\n");					\
	return;												\
}														\
if(pUser->GetIndex() != m_nCurIndex)					\
{														\
	printf("user index is:%d, cur index is:%d\n", pUser->GetIndex(), m_nCurIndex);\
	return;												\
}

#define SET_TIMER_ONCE(name)\
	SetTimer(name, name##_TIME, true);

#define SET_TIMER(name)\
	SetTimer(name, name##_TIME, false);

CMJGame::CMJGame() {
	InitCard();
	m_nSaiziA = 0;
	m_nSaiziB = 0;
	m_nCurIndex = -1;
	m_nNextIndex = -1;
	m_nIndexBanker = -1; ///<-１表示未设置

	m_nBankNum = 0;

	m_bDestroy = false;

	for (int i = 0; i < INDEX_NUM; i++) {
		m_nIndexlist[i] = 0;
	}
}
CMJGame::~CMJGame() {

	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); it++) {

		delete it->second;
		it->second = NULL;
	}
}

bool CMJGame::LeaveGame(unsigned int uid) {

	if (m_Userlist.find(uid) != m_Userlist.end()) {
		CBaseUser * pUser = m_Userlist[uid];
		if (pUser) {
			m_nIndexlist[pUser->GetIndex()] = 0; ///<清理位置

			delete pUser;
			pUser = NULL;
		}

		m_Userlist.erase(uid);
	}
	if (m_Userlist.size() <= 0) {
		GameEnd();
	}
	return true;
}

bool CMJGame::EnterGame(unsigned int uid, unsigned int &nIndex) {
	if (m_Userlist.find(uid) == m_Userlist.end()) {
		CBaseUser * pUser = new CMJUser();
		pUser->SetId(uid);
		m_Userlist[uid] = pUser;
		nIndex = AllocIndex(uid);
		if (nIndex == -1) {
			return false;
		}
		pUser->SetIndex(nIndex);

		SET_TIMER_ONCE(ONTIMER_WAIT_READY);

		return true;
	}

	return false;
}

unsigned int CMJGame::AllocIndex(unsigned int uid) {
	for (int i = 0; i < INDEX_NUM; i++) {
		if (m_nIndexlist[i] == 0) {
			m_nIndexlist[i] = uid;

			return i;
		}
	}

	return -1;
}

void CMJGame::OnTimer(int nTimerId) {
	switch (nTimerId) {
	case ONTIMER_WAIT_ZHUOZHUANG: {
		printf("zhuozhuang======>\n");
	}
		break;

	case ONTIMER_WAIT_LAZHUANG: {
	}
		break;
	case ONTIMER_WAIT_DASAIZI: {
	}
		break;
	case ONTIMER_WAIT_DASAIZI_AG: {
	}
		break;
	case ONTIMER_WAIT_GANG: {
	}
		break;
	case ONTIMER_WAIT_PENG: {
	}
		break;
	case ONTIMER_WAIT_DAPAI: {
	}
		break;
	case ONTIMER_WAIT_MOPAI: {
//		RakNet::BitStream bsData;
//		bsData.Write((unsigned char) PT_HOST_MESSAGE);
//		bsData.Write((unsigned int) PT_MJ_MOPAI_REQ);

		//	SendData(&bsData, m_ServerAddr);
	}
		break;
	case ONTIMER_WAIT_GANG_MOPAI: {

	}
		break;

	}
}

void CMJGame::FaPai() {
	m_nNextCard = 0;
	m_nFrontCard = 135;
	m_nEndCard = 130; ///??

	for (int i = 0; i < 4; i++) {
		unsigned int uid = m_nIndexlist[i];

		if (m_Userlist.find(uid) == m_Userlist.end()) {
			printf("error: fapai user not find, uid:%d\n", uid);

			return;
		}

		CMJUser * pUser = (CMJUser *) m_Userlist[uid];

		if (!pUser) {
			printf("error: fapai user is NULL\n");
			return;
		}

		BitStream streambuf;
		streambuf.Write((unsigned char) PT_HOST_MESSAGE);
		streambuf.Write((unsigned int) PT_MJ_FAPAI);

		printf("\n\n");
		if (i == m_nIndexBanker) {
			streambuf.Write((unsigned int) 14);
			for (int k = 0; k < 14; k++) {
				pUser->m_Cardlist[m_Cards[k + m_nNextCard].id] = &m_Cards[k
						+ m_nNextCard];
				streambuf.Write((unsigned int) m_Cards[k + m_nNextCard].id);

				printf("uid:%d===cardid:%d\n", uid,
						m_Cards[k + m_nNextCard].id);
			}

			m_nNextCard += 14;

		} else {
			streambuf.Write((unsigned int) 13);

			for (int k = 0; k < 13; k++) {
				pUser->m_Cardlist[m_Cards[k + m_nNextCard].id] = &m_Cards[k
						+ m_nNextCard];
				streambuf.Write((unsigned int) m_Cards[k + m_nNextCard].id);\
				printf("uid:%d===cardid:%d\n", uid,
						m_Cards[k + m_nNextCard].id);
			}
			m_nNextCard += 13;

		}
		SendStreamtoUser(&streambuf, uid);
	}

	ResetCurIndex(m_nIndexBanker);
	SET_TIMER_ONCE(ONTIMER_WAIT_DAPAI);
}

void CMJGame::ResetCard() {
}
void CMJGame::ResetBanker() {
	if (m_nIndexBanker == -1) {
		m_nIndexBanker = rand();
	} else {
		m_nIndexBanker++;
	}

	m_nIndexBanker %= 4;

	m_nBankNum = 1;
}

void CMJGame::ResetCurIndex(unsigned int index) {

	m_nNextIndex = (m_nCurIndex + 1) % 4;

	if (index != -1) {
		m_nCurIndex = index;
	} else {
		m_nCurIndex++;
	}

	m_nCurIndex %= 4;
}

void CMJGame::GameStart() {
	///	Reset cards;
	ResetCard();

	/// set banker 
	ResetBanker();

	/// set curl opt index
	ResetCurIndex(m_nIndexBanker);

	///send dasaizi msg 
	BitStream streambuf;
	streambuf.Write((unsigned char) PT_HOST_MESSAGE);
	streambuf.Write((unsigned int) PT_MJ_GAME_START);
	streambuf.Write((unsigned int) m_nIndexlist[m_nIndexBanker]); ///banker
	SendtoAllByStream(&streambuf);

	SET_TIMER_ONCE(ONTIMER_WAIT_ZHUOZHUANG)
}
SCard * CMJGame::MoPai4back() {
	if (m_nFrontCard > m_nEndCard) {
		return &m_Cards[m_nFrontCard--];
	}
	return NULL;
}
SCard * CMJGame::MoPai() {
	if (m_nNextCard < m_nEndCard) {
		return &m_Cards[m_nNextCard++];
	}

	return NULL;
}

bool CMJGame::Net_Ready(unsigned int uid) {
	if (m_Userlist.find(uid) == m_Userlist.end()) {
		return false;
	}

	CBaseUser * pUser = m_Userlist[uid];

	if (!pUser || pUser->GetReady()) {
		return false;
	}

	pUser->SetReady(true);

	bool flag = true;
	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); it++) {
		if (!it->second->GetReady()) {
			flag = false;
			break;
		}
	}

	if (flag) {
		GameStart();
	}

	return true;
}
void CMJGame::Net_GangPass(unsigned int uid) {
	NET_USER_CHECK(uid);

	ResetCurIndex(m_nNextIndex);
}

void CMJGame::Net_PengPass(unsigned int uid) {
	NET_USER_CHECK(uid);
}
void CMJGame::Net_Dapai(unsigned int uid, unsigned int CardId) {
	printf("=net_dapai===uid:%d, cardid:%d====\n", uid, CardId);
	NET_USER_CHECK(uid);

	if (pUser->DaPai(CardId)) {
		BitStream streambuf;
		streambuf.Write((unsigned char) PT_HOST_MESSAGE);
		streambuf.Write((unsigned int) PT_MJ_USER_DAPAI);
		streambuf.Write((unsigned int) uid); ///谁操作的
		streambuf.Write((unsigned int) CardId);

		///check other user gang peng
		for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
				it != m_Userlist.end(); it++) {
			if (((CMJUser *) (it->second))->CanGang(CardId)) {

				printf("wait user gang, uid:%d, card:%d\n", it->first, CardId);

				streambuf.Write((unsigned int) it->first); ///<轮到谁操作
				streambuf.Write((unsigned int) OPT_TYPE_GANG);

				SET_TIMER_ONCE(ONTIMER_WAIT_PENG);
				ResetCurIndex(it->second->GetIndex());
				return;
			}

			if (((CMJUser*) (it->second))->CanPeng(CardId)) {

				printf("wait user peng, uid:%d, card:%d\n", it->first, CardId);

				streambuf.Write((unsigned int) it->first); ///<轮到谁操作
				streambuf.Write((unsigned int) OPT_TYPE_PENG);

				SET_TIMER_ONCE(ONTIMER_WAIT_PENG);
				ResetCurIndex(it->second->GetIndex());
				return;
			}

		}

		ResetCurIndex();

		CMJUser * pNextUser = (CMJUser *) GetUserByIndex(m_nCurIndex);
		if (!pNextUser) {
			printf("error: 376 row,index is:%d\n", m_nCurIndex);
			return;
		}

		streambuf.Write((unsigned int) pNextUser->GetId()); ///<轮到谁操作
		streambuf.Write((unsigned int) OPT_TYPE_MOPAI);

		SendtoAllByStream(&streambuf);

		SET_TIMER_ONCE(ONTIMER_WAIT_MOPAI);
	} else {
		printf("=net_dapai=is fail=uid:%d, cardid:%d====\n", uid, CardId);
	}

}

void CMJGame::Net_Hu(unsigned int uid, unsigned int CardId) {
	printf("=net_hu===uid:%d, cardid:%d====\n", uid, CardId);
	NET_USER_CHECK(uid);

	if (m_CardManager.hu(&pUser->m_Cardlist)) {

		GameEnd();
	}
}

void CMJGame::Net_Peng(unsigned int uid, unsigned int CardId) {
	printf("=net_peng==uid:%d, cardid:%d====\n", uid, CardId);
	NET_USER_CHECK(uid);

	bool ret = pUser->Peng(CardId);

	if (!ret) {
		return;
	} else {
		BitStream ds;
		ds.Write((unsigned char) PT_HOST_MESSAGE);
		ds.Write((unsigned int) PT_MJ_USER_PENG);
		ds.Write((unsigned int) uid);
		ds.Write((unsigned int) CardId);
		SendtoAllByStream(&ds);

		SET_TIMER_ONCE(ONTIMER_WAIT_DAPAI);
	}
}

void CMJGame::Net_Gang(unsigned int uid, unsigned int CardId) {
	printf("=net_gang===uid:%d, cardid:%d====\n", uid, CardId);
	NET_USER_CHECK(uid);

	bool ret = pUser->Gang(CardId);

	if (!ret) {
		return;
	} else {
		BitStream ds;
		ds.Write((unsigned char) PT_HOST_MESSAGE);
		ds.Write((unsigned int) PT_MJ_USER_GANG);
		ds.Write((unsigned int) uid);
		ds.Write((unsigned int) CardId);
		SendtoAllByStream(&ds);

		SET_TIMER_ONCE(ONTIMER_WAIT_GANG_MOPAI);

//		SCard * pCard = MoPai4back();
//
//		if (pCard != NULL) {
//			pUser->MoPai(pCard);
//		} else {
//			printf("error:mo pai is error\n");
//			return;
//		}
//
//		BitStream ds1;
//		ds1.Write((unsigned char) PT_HOST_MESSAGE);
//		ds1.Write((unsigned int) PT_MJ_USER_MOPAI);
//		ds1.Write((unsigned int) uid);
//		ds1.Write((unsigned int) pCard->id);
//		SendtoAllByStream(&ds1);
//
//		SET_TIMER_ONCE(ONTIMER_WAIT_DAPAI);

	}
}
void CMJGame::Net_MoPai(unsigned int uid) {
	printf("=net_mopai===uid:%d====\n", uid);
	NET_USER_CHECK(uid);

	SCard * pCard = MoPai();

	if (pCard != NULL) {
		pUser->MoPai(pCard);
	} else {
		GameEnd();
		printf("error:mo pai is error\n");
		return;
	}

	BitStream ds1;
	ds1.Write((unsigned char) PT_HOST_MESSAGE);
	ds1.Write((unsigned int) PT_MJ_USER_MOPAI);
	ds1.Write((unsigned int) uid);
	ds1.Write((unsigned int) pCard->id);
	SendtoAllByStream(&ds1);

	SET_TIMER_ONCE(ONTIMER_WAIT_DAPAI);
}

void CMJGame::Net_DaSaizi(unsigned int uid) {
	NET_USER_CHECK(uid);

	m_nSaiziA = rand() % 6 + 1;
	m_nSaiziB = rand() % 6 + 1;

	///send saizi msg

	BitStream streambuf;
	streambuf.Write((unsigned char) PT_HOST_MESSAGE);
	streambuf.Write((unsigned int) PT_MJ_USER_DASAIZI);
	streambuf.Write((unsigned int) uid);
	streambuf.Write((unsigned int) m_nSaiziA);
	streambuf.Write((unsigned int) m_nSaiziB);
	SendtoAllByStream(&streambuf);

	ResetCurIndex((m_nIndexBanker + m_nSaiziA + m_nSaiziB - 1) % 4);

	SET_TIMER_ONCE(ONTIMER_WAIT_DASAIZI_AG);

}
void CMJGame::Net_DaSaiZiAG(unsigned int uid) {
	NET_USER_CHECK(uid);
	m_nSaiziA_ag = rand() % 6 + 1;
	m_nSaiziB_ag = rand() % 6 + 1;

	BitStream streambuf;
	streambuf.Write((unsigned char) PT_HOST_MESSAGE);
	streambuf.Write((unsigned int) PT_MJ_USER_DASAIZI_AG);
	streambuf.Write((unsigned int) uid);
	streambuf.Write((unsigned int) m_nSaiziA_ag);
	streambuf.Write((unsigned int) m_nSaiziB_ag);
	SendtoAllByStream(&streambuf);

	FaPai();

	SET_TIMER_ONCE(ONTIMER_WAIT_DAPAI);
}
void CMJGame::Net_ZhuoZhuang(unsigned int uid, unsigned int num) {
	/*	
	 if(m_Userlist.find(uid) == m_Userlist.end())
	 {
	 return;
	 }
	 CMJUser * pUser = m_Userlist[uid];
	 if(!pUser)
	 return;

	 if(pUser->GetIndex != m_nCurIndex)
	 {
	 return;
	 }
	 */
	NET_USER_CHECK(uid);

	if (num < 1 || num > 3) {
		return;
	}

	m_nBankNum = num;

	///send banker info
	BitStream streambuf;
	streambuf.Write((unsigned char) PT_HOST_MESSAGE);
	streambuf.Write((unsigned int) PT_MJ_USER_ZHUOZHUANG);
	streambuf.Write((unsigned int) uid);
	streambuf.Write((unsigned int) m_nBankNum);
	SendtoAllByStream(&streambuf);

	pUser->SetZhuang(num);

	if (m_nBankNum < 3) {
		///wait la zhuang
		SET_TIMER_ONCE(ONTIMER_WAIT_LAZHUANG)

	} else {
		///wait da sai zi

		BitStream streambuf;
		streambuf.Write((unsigned char) PT_HOST_MESSAGE);
		streambuf.Write((unsigned int) PT_MJ_DASAIZAI_START);
		streambuf.Write((unsigned int) m_nIndexlist[m_nIndexBanker]);
		SendtoAllByStream(&streambuf);

		SET_TIMER_ONCE(ONTIMER_WAIT_DASAIZI);

	}

}
///所有人都lazhuang
bool CMJGame::IsAllLazhuang() {
	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); it++) {
		CMJUser * pUser = (CMJUser *) m_Userlist[it->first];
		if (pUser->GetZhuang() <= 0) {
			return false;
		}
	}

	return true;
}
void CMJGame::Net_LaZhuang(unsigned int uid, unsigned int num) {
	if (m_Userlist.find(uid) == m_Userlist.end()) {
		return;
	}
	CMJUser * pUser = (CMJUser *) m_Userlist[uid];
	if (!pUser)
		return;

	///已操作过
	if (pUser->GetZhuang() > 0) {
		return;
	}

	unsigned nTmp = num;
	if (m_nBankNum + num > 3) {
		pUser->SetZhuang(3 - m_nBankNum);
		nTmp = 3 - m_nBankNum;
	} else {
		pUser->SetZhuang(num);

	}

	BitStream streambuf;
	streambuf.Write((unsigned char) PT_HOST_MESSAGE);
	streambuf.Write((unsigned int) PT_MJ_USER_LAZHUANG);
	streambuf.Write((unsigned int) uid);
	streambuf.Write((unsigned int) nTmp);
	SendtoAllByStream(&streambuf);

	if (IsAllLazhuang()) {

		BitStream streambuf;
		streambuf.Write((unsigned char) PT_HOST_MESSAGE);
		streambuf.Write((unsigned int) PT_MJ_DASAIZAI_START);
		streambuf.Write((unsigned int) m_nIndexlist[m_nIndexBanker]);
		SendtoAllByStream(&streambuf);

		SET_TIMER_ONCE(ONTIMER_WAIT_DASAIZI);
	}
}

void CMJGame::GameEnd() {

	this->m_bDestroy = true;

	for (map<unsigned int, CBaseUser *>::iterator it = m_Userlist.begin();
			it != m_Userlist.end(); it++) {

		BitStream streambuf;
		streambuf.Write((unsigned char) PT_HOST_MESSAGE);
		streambuf.Write((unsigned int) PT_MJ_END_GAME);
		SendStreamtoUser(&streambuf, it->first);

	}
}

void CMJGame::InitCard() {
	for (int i = 0; i < 136; i++) {
		m_Cards[i].id = i;
		m_Cards[i].num = (i / 4 % 9 + 1) + i / 36 * 10;
	}
	///==================================================

	PrintCards();

}

void CMJGame::FlushCard() {
	printf("==============flush card===========================\n");

	for (int i = 0; i < 136; i++) {
		int n = rand() % 136;
		int m = rand() % 136;

		if (m != n) {
			SCard t = m_Cards[m];
			m_Cards[m] = m_Cards[n];
			m_Cards[n] = t;

		}
	}
	PrintCards();

}

void CMJGame::PrintCards() {
	printf("==============build card==========================\n");
	for (int i = 0; i < 136; i++) {
		if (i % 4 == 0) {
			printf("\n");
		}
		printf("id:%3d,num:%2d\t", m_Cards[i].id, m_Cards[i].num);
	}

	printf("\n");

}

CBaseUser * CMJGame::GetUserByIndex(unsigned int index) {
	unsigned int uid = m_nIndexlist[index];

	if (m_Userlist.find(uid) == m_Userlist.end()) {
		return NULL;
	}

	return m_Userlist[uid];
}
