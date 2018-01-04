/*
 * CDDZGame.h
 *
 *  Created on: 2017年4月11日
 *      Author: aaaa
 */

#ifndef CDDZGAME_H_
#define CDDZGAME_H_

#include "../Base/CBaseGame.h"



class CPlayer;

struct SDDZPai
{
	int id;
	int value;
	int num;
	int type;

	SDDZPai * operator = ( SDDZPai * pCard )
	{
		this->id	= pCard->id;
		this->value = pCard->value;
		this->num	= pCard->num;
		this->type	= pCard->type;

		return this;
	}
};
class CDDZGame: public CBaseGame {
public:

	bool ProHostMsgByStream(unsigned int uid, unsigned char * data, unsigned int len);

	CDDZGame();
	virtual ~CDDZGame();
	bool Net_Ready(unsigned int uid);

public:
	void ChuPai(CPlayer * pUser, int pai[], int len);
	void PassPai(CPlayer * pUser);
	void JiaoPai(CPlayer * pUser, int num);
};
extern SDDZPai g_DDZPaiInfo[54];
extern SDDZPai * GetDDZPaiInfo(int wId);
#endif /* CDDZGAME_H_ */
