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
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
    m_iGameState			=	0;
    m_pSplash	= new CSprite("splash");
    m_pStart	= new CSprite("start");
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
    delete m_pSplash;
    delete m_pStart;

}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
    switch( GetGameState() )
    {
        // 初始化游戏，清空上一局相关数据
    case 1:
    {
        GameInit();
        SetGameState(2); // 初始化之后，将游戏状态设置为进行中
    }
    break;

    // 游戏进行中，处理各种游戏逻辑
    case 2:
    {
        // TODO 修改此处游戏循环条件，完成正确游戏逻辑
        if( true )
        {
            GameRun( fDeltaTime );
        }
        else     // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
        {
            SetGameState(0);
            GameEnd();
        }
    }
    break;

    // 游戏结束/等待按空格键开始
    case 0:
    default:
        break;
    };
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
    m_pSplash->SetSpriteVisible(false);
    m_pStart->SetSpriteVisible(false);

    m_pTankPlayer = new CTankPlayer("myplayer");
    m_pTankPlayer->CloneSprite("player");
    m_pTankPlayer->Init();
    m_iBulletNum = 0;
    m_pTankEnemy = new CTankEnemy("enemy");
    m_pTankEnemy->Init();
    LoadMap();

}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    if(m_pTankEnemy)
    {
        m_pTankEnemy->OnMove(fDeltaTime);
        m_pTankEnemy->OnFire(fDeltaTime);
    }

}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
}


void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
    if( 0 ==GetGameState() )
    {
        if(iKey ==	KEY_SPACE)
        {
            m_iGameState = 1;
        }
    }
    if(m_iGameState == 2)
    {
        m_pTankPlayer->OnMove(iKey, true);
        if(iKey == KEY_J)   //判断按下键是够为J键
        {
            m_pTankPlayer->OnFire();
        }

    }


}

void CGameMain::OnKeyUp( const int iKey )
{
    if(m_iGameState == 2)
    {
        m_pTankPlayer->OnMove(iKey, false);

    }
}

void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
    if(strstr(szName,"player") != NULL)   //判断碰到世界边界的坦克是否为我方坦克
    {
        if(iColSide==0||iColSide==1)
        {
            m_pTankPlayer->SetSpriteLinearVelocityX(0);

        }
        else if(iColSide==2||iColSide==3)
        {
            m_pTankPlayer->SetSpriteLinearVelocityY(0);
        }
    }
    if(m_pTankEnemy&&strcmp(m_pTankEnemy->GetName(),szName)==0)
	{
		m_pTankEnemy->OnMove();
	}


}

void CGameMain::AddBullet( int iDir,float fPosX,float fPosY ,int iOwner)
{
    char* szName = CSystem::MakeSpriteName("bullet",m_iBulletNum);//创建坦克名字
    CBullet* pBullet = new CBullet(szName);
    pBullet->CloneSprite("bullet");
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,-26, -22, 26, 22); //设置世界边界
    pBullet->SetSpritePosition(fPosX,fPosY);
    pBullet->SetSpriteCollisionSend(true); //设置接收碰撞
    pBullet->OnMove(iDir);
    m_iBulletNum++; //子弹个数加1
    if(iOwner == 1)
    {
        pBullet->SetOwner(1);//1表示我方坦克发射的子弹
    }
    else
    {
        pBullet->SetOwner(0); //0表示地方坦克发射的子弹
    }
}
void CGameMain::LoadMap()
{
		char* szName;
		int i,j;
		float x,y;
		for(i=0;i<11;i++)
		{
			for(j=0;j<13;j++)
			{
                if(g_iMap[i][j]==1)
				{
					szName = CSystem::MakeSpriteName("wall",j+i*13+i);//重新起名
					CSprite* pWall = new CSprite(szName); //新建对象
					pWall->CloneSprite("wall"); //克隆墙块
					pWall->SetSpriteCollisionActive(0,1); //设置为接受碰撞
					pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
					x =float(-24+4*j);
					y =float(-20+4*i);
					pWall->SetSpritePosition(x,y);
				}
			}
		}
}


