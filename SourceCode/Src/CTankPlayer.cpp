#include "CTankPlayer.h"

CTankPlayer::CTankPlayer(const char* szName):CSprite(szName) //对构造函数进行实现
{
    m_iDir=0;
    m_fSpeedX=0.f;
    m_fSpeedY=0.f;
    m_iHp=2;
}

CTankPlayer::~CTankPlayer()
{
    //dtor
}

void CTankPlayer::Init()
{
    SetHp(2);
    SetSpritePosition(0.f,0.f);
    SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
    SetSpriteCollisionActive(1,1);//设置为可以接受和发生碰撞
    SetSpriteVisible(true);
}
