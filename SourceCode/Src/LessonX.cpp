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
    m_pScore = new CTextSprite("score");
    m_pHight = new CTextSprite("hight");
    m_pEnemy = new CTextSprite("enemyNum");
    m_iScore=0;//分数
    m_iEnemy=0;//敌人数量
    m_iHight = 0;
    m_fDeltaTime = 0.f;

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
        if(!m_pTankPlayer->IsDead() && !m_pAim_nor->IsDead() && m_fDeltaTime<30)
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
    m_vWeapon.push_back(m_pTankPlayer);
    m_iBulletNum = 0;
    //m_pTankEnemy = new CTankEnemy("enemy");
    //m_pTankEnemy->Init();
    LoadMap();
    m_pAim_nor = new CWeapon("myaim_nor");
    m_pAim_nor->CloneSprite("aim_nor");
    m_vWeapon.push_back(m_pAim_nor);
    m_pAim_nor->SetSpriteCollisionReceive(true);
    m_pAim_nor->SetSpritePosition(0.f,20.f);
    m_iBulletNum    =   0;
    m_iTankEnemyNumber  =  0;
    m_fTankEnemyTime = 4.f;
    m_iScore = 0;
    m_iHight = 0;
    m_iEnemy = 0;
    m_fDeltaTime = 0.f;

    FILE * fp =fopen("save.dat","r+");
    if(fp)
    {
        fread(&m_iHight,sizeof(int),1,fp);
        fclose(fp);
    }
    m_pHight = new CTextSprite("hight");
    m_pHight->SetTextValue(m_iHight);




}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    /*if(m_pTankEnemy)
    {
        m_pTankEnemy->OnMove(fDeltaTime);
        m_pTankEnemy->OnFire(fDeltaTime);
    }*/
    AddTankEnemy(fDeltaTime);
    for(int i=0; i<m_vWeapon.size(); i++)
    {
        if(!m_vWeapon[i]->IsDead())
        {

            m_vWeapon[i]->OnMove(fDeltaTime);
            m_vWeapon[i]->OnFire(fDeltaTime);
        }
        else
        {
            DeleteWeaponByName(m_vWeapon[i]->GetName());
        }
    }
    m_fDeltaTime += fDeltaTime;
    m_pScore->SetTextValue(m_iScore);
    m_pHight->SetTextValue(m_iHight);
    m_pEnemy->SetTextValue(m_iEnemy);


}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
    DeleteAllSprite();
    FILE * fp =fopen("save.dat","w+");
    if(m_iScore>m_iHight)
        fwrite(&m_iScore,sizeof(int),1,fp);
    fclose(fp);
    m_pSplash->SetSpriteVisible(true);
	m_pStart->SetSpriteVisible(true);
	SetGameState(0);

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
    else if(strstr(szName,"enemy") != NULL)
    {
        CWeapon* pEnemy = FindWeaponByName(szName);
        pEnemy->SetSpriteLinearVelocity(0.f,0.f);
        pEnemy->OnMove();
    }
    else if(strstr(szName,"bullet") != NULL)
    {
        CWeapon* pBullet = FindWeaponByName(szName);
        pBullet->SetHp(0);
    }

    /*if(m_pTankEnemy&&strcmp(m_pTankEnemy->GetName(),szName)==0)
    {
    	m_pTankEnemy->OnMove();
    }*/


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
    m_vWeapon.push_back(pBullet);
}
void CGameMain::LoadMap()
{
    char* szName;
    int i,j;
    float x,y;
    for(i=0; i<11; i++)
    {
        for(j=0; j<13; j++)
        {
            if(g_iMap[i][j]==1)
            {
                szName = CSystem::MakeSpriteName("wall",j+i*13+i);//重新起名
                CWeapon* pWall = new CWeapon(szName); //新建对象
                pWall->CloneSprite("wall"); //克隆墙块
                pWall->SetSpriteCollisionActive(0,1); //设置为接受碰撞
                pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
                x =float(-24+4*j);
                y =float(-20+4*i);
                pWall->SetSpritePosition(x,y);
                m_vWeapon.push_back(pWall);
            }
        }
    }

}

CWeapon* CGameMain::FindWeaponByName(const char* szName)//根据名字查找到对象
{
    for(int i=0; i<m_vWeapon.size(); i++)
    {
        if(strcmp(szName,m_vWeapon[i]->GetName()) == 0)
        {
            return m_vWeapon[i];
        }
    }
}

void CGameMain::DeleteWeaponByName(const char* szName)//根据名字把精灵从容器中删除
{
    for(vector<CWeapon*>::iterator it=m_vWeapon.begin(); it!=m_vWeapon.end();)
    {
        CWeapon* cw =*it;
        if(strcmp(szName,cw->GetName()) == 0)
        {
            m_vWeapon.erase(it);
            cw->DeleteSprite();
            delete cw;
            break;
        }
        else
        {
            it++;
        }
    }
}

void	CGameMain::AddTankEnemy(float fDeltaTime)
{
    m_fTankEnemyTime += fDeltaTime;
    if(m_fTankEnemyTime > 5)
    {
        char* szName = CSystem::MakeSpriteName("enemy",m_iTankEnemyNumber);
        CTankEnemy* m_pTankEnemy = new CTankEnemy(szName);
        m_pTankEnemy->CloneSprite("enemy");
        m_pTankEnemy->Init();
        m_iTankEnemyNumber++;
        m_vWeapon.push_back(m_pTankEnemy);  //把创建的敌方坦克插入到容器中
        m_fTankEnemyTime=0.f;
        m_iEnemy++;
    }
}

void	CGameMain::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
    CWeapon* tarSprite = FindWeaponByName(szTarName);
    if(strstr(szSrcName,"bullet") != NULL)//发送碰撞为子弹
    {
        CBullet *tmpBullet = (CBullet*)FindWeaponByName(szSrcName);
        tmpBullet->OnSpriteColSprite(tarSprite);
        if( tmpBullet->GetOwner()==1 && strstr(szTarName,"enemy") != NULL)
        {
            m_iScore++;
            m_iEnemy--;
        }
    }
    else if(strcmp(szSrcName,"myplayer")==0) //发送碰撞为我方坦克
    {
        m_pTankPlayer->OnSpriteColSprite(tarSprite);
    }
    else if(strstr(szSrcName,"enemy") != NULL)//发送碰撞为敌方坦克
    {
        CTankEnemy* tmpEnemy = (CTankEnemy*)FindWeaponByName(szSrcName);
        tmpEnemy->OnSpriteColSprite(tarSprite);


    }
}

void	CGameMain::DeleteAllSprite()
{
    int n=m_vWeapon.size();
    while(m_vWeapon.size()!=0)
    {
        vector<CWeapon*>::iterator itr=m_vWeapon.begin();
        CWeapon* cw = *itr;
        m_vWeapon.erase(itr);
        cw->DeleteSprite();
        delete cw;
    }
}

