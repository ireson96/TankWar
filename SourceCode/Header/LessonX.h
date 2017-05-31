/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "CTankPlayer.h"
#include "Bullet.h"
#include "TankEnemy.h"
#include "Weapon.h"
#include<vector>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////
//
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
    int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������

    CSprite*		 m_pSplash;
    CSprite*		 m_pStart;

    CTankPlayer*     m_pTankPlayer;
    //CTankEnemy*      m_pTankEnemy;
    int m_iBulletNum;
    int g_iMap[11][13]=
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,0,0,1,0,1,0,0,0,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,1,0,1,0,1,0,1,0,0,0},
        {0,0,0,1,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,0,1,0,1,0,1,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,1,0,1,0,0,0,0,0,1,0,1,0},
        {0,0,0,0,0,1,1,1,0,0,0,0,0},
        {0,0,0,0,0,1,0,1,0,0,0,0,0}
    };
    vector<CWeapon*>	   m_vWeapon;
    float m_fTankEnemyTime;
    int m_iTankEnemyNumber;
    CWeapon* m_pAim_nor;

    CTextSprite*	 m_pScore; //��ʾ�������ı�����
    CTextSprite* 	m_pHight; //��ʾ��߷ֵ��ı�����
    CTextSprite*	 m_pEnemy;//��ʾ�����������ı�����
    int m_iScore;//����
    int m_iEnemy;//��������
    int m_iHight;//������߷�
    float  m_fDeltaTime;//��ʾ��Ϸʱ��


public:
    CGameMain();            //���캯��
    ~CGameMain();           //��������

    // Get����
    int				GetGameState()
    {
        return m_iGameState;
    }

    // Set����
    void			SetGameState( const int iState )
    {
        m_iGameState	=	iState;
    }

    // ��Ϸ��ѭ����
    void			GameMainLoop( float	fDeltaTime );
    void			GameInit();
    void			GameRun( float fDeltaTime );
    void			GameEnd();


    void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
    void OnKeyUp( const int iKey );
    void OnSpriteColWorldLimit( const char *szName, const int iColSide );
    void AddBullet( int iDir,float fPosX,float fPosY ,int iOwner);
    void LoadMap();

    CWeapon* FindWeaponByName(const char* szName);
    void DeleteWeaponByName(const char* szName);
    void AddTankEnemy(float fDeltaTime);
    void OnSpriteColSprite(const char *szSrcName, const char *szTarName);
    void DeleteAllSprite();
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
