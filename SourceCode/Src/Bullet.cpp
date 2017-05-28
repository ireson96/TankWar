#include "Bullet.h"

CBullet::CBullet(const char* szName):CSprite(szName)
{
    //ctor
    m_iDir = 0;
    m_iHp = 0;
    m_iOwner = 1;
    m_fSpeedX = 0.f;
    m_fSpeedY = 0.f;
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

