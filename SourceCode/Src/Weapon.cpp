#include "Weapon.h"

CWeapon::CWeapon(const char* szName):CSprite(szName)
{
    //ctor
    m_iDir=0;
    m_fSpeedX=0.f;
    m_fSpeedY=0.f;
    m_iHp=2;
    m_fMaxSpeed = 8;
}

CWeapon::~CWeapon()
{
    //dtor
}
bool CWeapon::IsDead()
{
	if(m_iHp == 0)
	{
		return true;
	}
	return false;
}
