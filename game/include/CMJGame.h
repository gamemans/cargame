#ifndef CMJGame_H_
#define CMJGame_H_
#include "CBaseGame.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "BitStream.h"

#define INDEX_NUM 4

class SCard
{

	public:
		int id;
		int num;
		bool bUse;
		SCard()
		{
			bUse = false;
		}

		bool operator==(SCard &other)
		{
			if(this->num == other.num)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator==(int num)
		{
			return this->num == num;
		}

		int operator-(int num)
		{
			return this->num - num;
		}
		int operator+(int num)
		{
			return this->num + num;
		}
};
#define GetMyData(n) \
	if(data[n].bUse == true)\
continue;\
tmp[tmpnum++] = data[n];\
data[n].bUse = true;


struct SCardManager
{
	bool iske(SCard * data)
	{
		if(data[0] == data[1] && data[0] == data[2])
		{
			return true;
		}

		return false;

	}

	bool isshun(SCard * data)
	{
		if(data[0] == data[1] - 1 && data[0] == data[2] - 2)
		{
			return true;
		}
		return false;
	}
	bool isdui(SCard * data)
	{
		return data[0] == data[1];
	}


	void sort(SCard * data, int num)
	{
		int k = 0;
		for(int i = 0; i < num - 1; i++)
		{
			k = i;
			for(int j = i; j < num; j++)
			{
				if(data[k].num > data[j].num)
				{
					k = j;
				}
			}

			if(k != i)
			{
				SCard t = data[k];
				data[k] = data[i];
				data[i] = t;
			}
		}
	}

	bool hu(map<unsigned int, SCard *> * plist)
	{
		SCard card[14];

		int i = 0;
		for(map<unsigned int, SCard *>::iterator it = plist->begin();
				it != plist->end(); it++)
		{
			card[i++] = *(it->second); 
		}
	}
	bool hu(SCard * data, int num)
	{

		if(num == 0)
		{
			return true;
		}

		if(num == 2)
		{
			return isdui(data);
		}

		SCard tmp[14];
		int tmpnum = 0;
		for(int i = 0; i < num - 2; i++)
		{
			GetMyData(i)
				for(int j = i + 1; j < num - 1; j++)
				{
					GetMyData(j);
					for(int k = j + 1; k < num; k++)
					{
						GetMyData(k);

						if(iske(tmp)||isshun(tmp))
						{
							SCard ttt[14];
							int f = 0;
							for(int t = 0; t < num; t++)
							{
								if(data[t].bUse == false)
								{
									ttt[f++] = data[t];
								}
							}
							if(hu(ttt, f))
							{
								return true;
							}
							else
							{
								data[k].bUse = false;
								tmpnum--;
							}

						}
						else
						{
							data[k].bUse = false;
							tmpnum--;

						}

					}

					data[j].bUse = false;
					tmpnum--;

				}

			data[i].bUse = false;
			tmpnum--;

		}

		return false;
	}
};
class CMJGame:public CBaseGame
{
	public:
		CMJGame();
		~CMJGame();


		bool EnterGame(unsigned int uid, unsigned int &index);
		bool LeaveGame(unsigned int uid);

		void GameStart();
		void GameEnd();

	public:
		unsigned int AllocIndex(unsigned uid);
	public:

		void Net_ZhuoZhuang(unsigned int uid, unsigned int num);
		void Net_LaZhuang(unsigned int uid, unsigned int num);
		void Net_Dapai(unsigned int uid, unsigned int CardId);
		void Net_Hu(unsigned int uid, unsigned int CardId);
		void Net_Peng(unsigned int uid, unsigned int CardId);
		void Net_Gang(unsigned int uid, unsigned int CardId);
		void Net_MoPai(unsigned int uid);
		void Net_DaSaizi(unsigned int uid);
		void Net_DaSaiZiAG(unsigned int uid);	
		void Net_GangPass(unsigned int uid);
		void Net_PengPass(unsigned int uid);
		bool Net_Ready(unsigned int uid);


	public:
		void PrintCards();
		void InitCard();
		void FlushCard();
		void FaPai();

		SCard *  MoPai();
		SCard *  MoPai4back();

	protected:
		void OnTimer(int nTimerId);

		CBaseUser * GetUserByIndex(unsigned int index);

		void ResetBanker();
		void ResetCard();
		void ResetCurIndex(unsigned int = -1);

		bool IsAllLazhuang();
	protected:

		SCard	m_Cards[136];
		SCardManager m_CardManager;

	protected:
		unsigned int m_nSaiziA;
		unsigned int m_nSaiziB;
		unsigned int m_nSaiziA_ag;
		unsigned int m_nSaiziB_ag;

		unsigned int m_nIndexlist[INDEX_NUM];


		///当前操作对象索引
		unsigned int m_nCurIndex;
		///顺序情况下,下次操作索引
		unsigned int m_nNextIndex;

		///当前坐庄索引
		unsigned int m_nIndexBanker;

		///坐几庄,最多３庄,最少１庄
		unsigned int m_nBankNum;

		///记录下次牌位置
		unsigned int m_nNextCard;

		///从后面记录
		unsigned int m_nFrontCard;

		unsigned int m_nEndCard;

};

#endif
