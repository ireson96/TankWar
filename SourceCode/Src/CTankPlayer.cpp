#include "CTankPlayer.h"
#include "LessonX.h"
CTankPlayer::CTankPlayer(const char* szName):CWeapon(szName) { //对构造函数进行实现

    m_fMaxSpeed = 8;
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
            SetSpeedY(-m_fMaxSpeed);
            break;
        case KEY_D:
            SetDir(1);
            SetSpeedX(m_fMaxSpeed);
            SetSpeedY(0);
            break;
        case KEY_S:
            SetDir(2);
            SetSpeedX(0);
            SetSpeedY(m_fMaxSpeed);
            break;
        case KEY_A:
            SetDir(3);
            SetSpeedX(-m_fMaxSpeed);
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

void CTankPlayer::OnFire()
{
		float x,y;
		x = GetSpritePositionX();
		y = GetSpritePositionY();
		switch(GetDir())
		{
		case 0:
			y=y-GetSpriteHeight()/2-1;
			break;
		case 1:
			x=x+GetSpriteWidth()/2+1;
			break;
		case 2:
			y=y+GetSpriteHeight()/2+1;
			break;
		case 3:
			x=x-GetSpriteWidth()/2-1;
			break;
		}
		g_GameMain.AddBullet(GetDir(),x,y,1);
}

void CTankPlayer::OnSpriteColSprite(CWeapon* pSprite)
{
	if(pSprite == NULL)
	{
		return;
	}
	else if(strstr(pSprite->GetName(),"bullet") != NULL)
	{
		SetHp(0);
	}
	else if(strstr(pSprite->GetName(),"wall") != NULL)
	{
		SetSpeedX(0);
		SetSpeedY(0);
		SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
	}
}
