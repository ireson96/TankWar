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
    int m_iBulletNum;


public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();


	void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void OnKeyUp( const int iKey );
	void OnSpriteColWorldLimit( const char *szName, const int iColSide );
	void AddBullet( int iDir,float fPosX,float fPosY ,int iOwner);

};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
