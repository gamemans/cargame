#ifndef CMJUser_H_
#define CMJUser_H_
#include "CBaseUser.h"

class SCard;
class CMJUser:public CBaseUser
{
	public:
		CMJUser();
		~CMJUser();

	public:

		unsigned int GetZhuang();
		void SetZhuang(unsigned int num);

		std::map<unsigned int, SCard *> m_Cardlist;

		bool	DaPai(unsigned int cardid);

		bool	CanPeng(unsigned int cardid);
		bool	CanGang(unsigned int cardid);
		
		bool	Peng(unsigned int cardid);
		bool	Gang(unsigned int cardid);

		void	MoPai(SCard * pCard);
	protected:

		unsigned int m_nZhuang;

	
};

#endif
