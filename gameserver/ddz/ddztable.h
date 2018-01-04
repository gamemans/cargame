/*
 * CDdz.h
 *
 *  Created on: 2017年4月8日
 *      Author: aaaa
 */

#ifndef DDZ_DDZTABLE_
#define DDZ_DDZTABLE_



#include "../Base/CBaseTable.h"


//#define DDZ_DEBUG

#define WAIT_DDZ_JIAOFEN_TIME				40000
#define WAIT_DDZ_DAPAI_TIME					45000

#define WAIT_MATCH_DDZ_JIAOFEN_TIME			40000
#define WAIT_MATCH_DDZ_DAPAI_TIME			20000

enum DDZ_PAI_TYPE
{
	PAI_TYPE_NONE,
	PAI_TYPE_ROCKET,
	PAI_TYPE_BOMB,
	PAI_TYPE_DANSHUN,
	PAI_TYPE_SHUANGSHUN,
	PAI_TYPE_SANSHUN,
	PAI_TYPE_SANDAIYISINGLE,
	PAI_TYPE_SANDAIYIDOUBLE,
	PAI_TYPE_PLANESINGLE,
	PAI_TYPE_PLANEDOUBLE,
	PAI_TYPE_SIDAIERSINGLE,
	PAI_TYPE_SIDAIERDOUBLE,
	PAI_TYPE_THREE,
	PAI_TYPE_DOUBLE,
	PAI_TYPE_SINGLE,
};
class CDDZ_Table : public CBaseTable
{
public:
	CDDZ_Table( int iUserNum );
	~CDDZ_Table();

public:
	bool StartGame();
	void EndGame();
	void SaveUserGameInfo();

	void MatchStart();

	void MatchOut();

	void SetTimer( unsigned int dwElapse, int iType, bool bOnce = true );
	void OnTimer();
	void KillTimer();
protected:
	struct SUserInfo
	{
		SUserInfo()
		{
			m_bIsDiZhu = false;
			m_iJiaoFen = -1;
			m_wPaiNum  = 17;
			m_iChuPaiNum = 0;
		}
		int			m_wPai[20];					//玩家手里的牌
		int				m_wPaiNum;					//牌的数量

		int			m_DaPai[20];				//玩家出的牌
		int				m_wDaPaiNum;				//出牌数量

		bool			m_bIsDiZhu;					//是否地主
		int				m_iJiaoFen;					//叫牌（-1,没叫过牌　　0,不叫　　　1,叫１分　　　2,叫２分　　　3,叫３分）

		double			m_dCountScore;				//总成绩

		int				m_iChuPaiNum;				//出牌次数

	};
	enum TIMER_TYPE
	{
		TIMER_WAIT_JIAOFEN,
		TIMER_WAIT_DAPAI,
	};
public:
	int				m_iNext;					//下张牌
	int				m_iLast;					//最后张牌


	int				m_iDiZhu;					//地主
	int			m_wDiPai[3];				//三张底牌
	int			m_wPai[54];
	SUserInfo		m_UserInfo[3];

	int				m_iNumOfBomb;				//炸弹的数量
	int				m_iNumOfRocket;				//火箭的数量,最多１个
	int				m_iChunTianOrFanChun;		//春天或反春,最多１个

	int			m_CurTabPai[20];			//当前桌面上已出的牌型
	int				m_iTabPaiNum;
	int				m_iChuPaiUser;				//出牌人（座位号）

	int				m_iPassCount;				//连续过牌次数

	bool			m_bHasDiZhu;				//已有地主
	int				m_iCurJiaoFen;				//当前叫的分

	// 发牌
	bool SendCard(void);
	// 洗牌
	void Shuffle( int num = 20 );
	// 出牌检测
	bool ChuPaiCheck( CUser * pUser, int pai[], int num );
	// 检测是否为火箭牌型
	bool _IsRocket( SDDZPai pai[], int num );
	// 检测是否为炸弹牌型
	int _IsBomb( SDDZPai pai[], int num );
	// 检测是否为单顺牌型
	int _IsDanShun( SDDZPai pai[], int num );
	// 检测是否为双顺牌型
	int _IsShuangShun( SDDZPai pai[], int num );
	// 检测是否为三顺牌型
	int _IsSanShun( SDDZPai pai[], int num );
	// 检测是否为三带一牌型(单张)
	int _IsSanDaiYiSingle( SDDZPai pai[], int num );
	// 检测是否为三带一牌型(对儿)
	int _IsSanDaiYiDouble( SDDZPai pai[], int num );
	// 检测是否为飞机带翅膀牌型(单张)
	int _IsPlaneSingle( SDDZPai pia[], int num );
	// 检测是否为飞机带翅膀牌型(对儿)
	int _IsPlaneDouble( SDDZPai pia[], int num );
	// 检测是否为四带二牌型(单张)
	int _IsSiDaiErSingle( SDDZPai pai[], int num );
	// 检测是否为四带二牌型(对儿)
	int _IsSiDaiErDouble( SDDZPai pai[], int num );
	// 检测是否为对儿
	int _Is2( SDDZPai pai[], int num );
	// 栓测是否为三张牌
	int _Is3( SDDZPai pai[], int num );
	// 检测牌的类型
	int CheckPaiType( SDDZPai pai[], int num, int &PaiSize );
	// 获得相同牌的个数
	int GetCardCountByCardNum( SDDZPai pai[], int num, int PaiNum );

	// 排序
	void SortCard( SDDZPai Card[], int num );
	// 叫牌
	void JiaoPai( CUser * pUser, int num );
	// 设置地主
	void SetDiZhu( CUser * pUser, int num );

	void ChuPai( CUser * pUser, int pai[], int num );

	void PassPai( CUser * pUser );

	void MoveCurPointer();
	// 清理桌面的牌
	void ResetTablePai();
	// 胜利（游戏币）结算
	void WinBalance( bool bIsDiZhu );
	// 手中是否拥有这张牌
	bool HaveTheCard( CUser * pUser, int pai );
	// 将已出过的牌放到数组最后
	void MoveAbandonCardToArrayLast( CUser * pUser, int AbandonPai[], int AbandonNum );

	void OnUserLeave( int iChairId );
	void OnLookAt( CUser * pLooker );
	void OnUserRejoin( CUser * pUser );

};
extern SDDZPai g_DDZPaiInfo[54];
extern SDDZPai * GetDDZPaiInfo( int wId );
#endif /* DDZ_DDZTABLE_ */
