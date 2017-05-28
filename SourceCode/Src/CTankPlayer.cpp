#include "CTankPlayer.h"

CTankPlayer::CTankPlayer(const char* szName):CSprite(szName) { //对构造函数进行实现
    m_iDir=0;
    m_fSpeedX=0.f;
    m_fSpeedY=0.f;
    m_iHp=2;
    m_iMaxSpeed = 8;
}

CTankPlayer::~CTankPlayer() {
    //dtor
}

void CTankPlayer::Init() {
    SetHp(2);
    SetSpritePosition(0.f,0.f);
    SetSpriteWorldLimit(WORLD_LIMIT_NULL, -26, -22, 26, 22);
    SetSpriteCollisionActive(1,1);//设置为可以接受和发生碰撞
    SetSpriteVisible(true);
}

void CTankPlayer::OnMove(int iKey, bool bPress) {
    if(bPress) {
        switch (iKey) {
        case KEY_W:
            SetDir(0);
            SetSpeedX(0);
            SetSpeedY(-m_iMaxSpeed);
            break;
        case KEY_D:
            SetDir(1);
            SetSpeedX(m_iMaxSpeed);
            SetSpeedY(0);
            break;
        case KEY_S:
            SetDir(2);
            SetSpeedX(0);
            SetSpeedY(m_iMaxSpeed);
            break;
        case KEY_A:
            SetDir(3);
            SetSpeedX(-m_iMaxSpeed);
            SetSpeedY(0);
            break;
        }
        SetSpriteRotation(float(90*GetDir())); //用方向值乘于90得到精灵旋转度数
        SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
    } else {
        if(iKey == KEY_W ||  iKey == KEY_S ) {
            //SetSpeedX(0);
            SetSpeedY(0);
            SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
        }
        else if(iKey == KEY_D || iKey == KEY_A){
            SetSpeedX(0);
            SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
        }
    }
}
