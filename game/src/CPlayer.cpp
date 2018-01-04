#include "CPlayer.h"
CPlayer::CPlayer()
{
	m_nGameId = -1;
	m_bReady = false;
	m_nChairId = -1;
	m_bDisconnect = false;
	m_nProxyServerId = -1;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Reset()
{
	m_nGameId = -1;
	m_bReady = false;
	m_nChairId = -1;
	m_bDisconnect = false;
}
