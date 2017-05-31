#include "Bullet.h"

CBullet::CBullet(const char* szName):CWeapon(szName)
{
    //ctor
    m_iOwner = 1;
    m_fMaxSpeed = 10;
}

CBullet::~CBullet()
{
    //dtor
}

void CBullet::OnMove(int iDir)
{
		SetDir(iDir);
		switch(GetDir())
		{
		case 0:
			SetSpeedX(0);
			SetSpeedY(-m_fMaxSpeed);
			break;
		case 1:
			SetSpeedX(m_fMaxSpeed);
			SetSpeedY(0);
			break;
		case 2:
			SetSpeedX(0);
			SetSpeedY(m_fMaxSpeed);
			break;
		case 3:
			SetSpeedX(-m_fMaxSpeed);
			SetSpeedY(0);
			break;
		}
		SetSpriteRotation(90*GetDir());
		SetSpriteLinearVelocity(GetSpeedX(),GetSpeedY());
}

void CBullet::OnSpriteColSprite(CWeapon* pSprite)
{
	if(pSprite == NULL)
	{
		return;
	}
	SetHp(0);
	if(GetOwner() == 1 && strstr(pSprite->GetName(),"aim_nor") != NULL)  //我方坦克子弹与军营发生碰撞
	{
		return;
	}
	if(GetOwner() == 0 && strstr(pSprite->GetName(),"enemy") != NULL) //敌方坦克子弹打中地方坦克
{
		return;
	}
pSprite->SetHp(0);
}

