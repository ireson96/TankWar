/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain() {
    m_iGameState			=	0;
    m_pSplash	= new CSprite("splash");
    m_pStart	= new CSprite("start");
}
//==============================================================================
//
// ��������
CGameMain::~CGameMain() {
    delete m_pSplash;
    delete m_pStart;

}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime ) {
    switch( GetGameState() ) {
    // ��ʼ����Ϸ�������һ���������
    case 1: {
        GameInit();
        SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
    }
    break;

    // ��Ϸ�����У����������Ϸ�߼�
    case 2: {
        // TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
        if( true ) {
            GameRun( fDeltaTime );
        } else { // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
            SetGameState(0);
            GameEnd();
        }
    }
    break;

    // ��Ϸ����/�ȴ����ո����ʼ
    case 0:
    default:
        break;
    };
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit() {
    m_pSplash->SetSpriteVisible(false);
    m_pStart->SetSpriteVisible(false);

    m_pTankPlayer = new CTankPlayer("myplayer");
    m_pTankPlayer->CloneSprite("player");
    m_pTankPlayer->Init();

}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime ) {
}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd() {
}


void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress ) {
    if( 0 ==GetGameState() ) {
        if(iKey ==	KEY_SPACE) {
            m_iGameState = 1;
        }
    }
    if(m_iGameState == 2) {
        m_pTankPlayer->OnMove(iKey, true);
    }


}

void CGameMain::OnKeyUp( const int iKey ) {
    if(m_iGameState == 2) {
        m_pTankPlayer->OnMove(iKey, false);
    }
}

void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide ) {
    if(strstr(szName,"player") != NULL) { //�ж���������߽��̹���Ƿ�Ϊ�ҷ�̹��
        if(iColSide==0||iColSide==1){
            m_pTankPlayer->SetSpriteLinearVelocityX(0);

        }else if(iColSide==2||iColSide==3){
            m_pTankPlayer->SetSpriteLinearVelocityY(0);
        }
    }

}
