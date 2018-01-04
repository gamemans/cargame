#include "CMJUser.h"

#include "CMJGame.h"

CMJUser::CMJUser() {
	m_nZhuang = 0;
}

CMJUser::~CMJUser() {

}
unsigned int CMJUser::GetZhuang() {
	return m_nZhuang;
}
void CMJUser::SetZhuang(unsigned int num) {
	m_nZhuang= num;
}


bool CMJUser::Peng(unsigned int cardid) {
	return true;
}
bool CMJUser::Gang(unsigned int cardid) {
	return true;
}
bool CMJUser::DaPai(unsigned int cardid) {
	if (m_Cardlist.find(cardid) == m_Cardlist.end()) {
		return false;
	} else {
		m_Cardlist.erase(cardid);
		return true;
	}
}

bool CMJUser::CanGang(unsigned int cardid) {
	return false;
}

bool CMJUser::CanPeng(unsigned int cardid) {
	return false;
}

void CMJUser::MoPai(SCard * pCard) {
	m_Cardlist[pCard->id] = pCard;
}
