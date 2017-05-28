#ifndef BULLET_H
#define BULLET_H

#include <CommonClass.h>


class CBullet : public CSprite
{
    public:
        CBullet(const char* szName);
        virtual ~CBullet();

        void SetDir(int dir)    {m_iDir = dir;}
        void SetHp(int hp)      {m_iHp = hp;}
        void SetOwner(int owner){m_iOwner = owner;}
        void SetSpeedX(int x)   {m_fSpeedX = x;}
        void SetSpeedY(int y)   {m_fSpeedY = y;}
        int GetDir()            {return m_iDir;}
        int GetHp()             {return m_iHp;}
        int GetOwner()          {return m_iOwner;}
        float GetSpeedX()       {return m_fSpeedX;}
        float GetSpeedY()       {return m_fSpeedY;}
        void OnMove(int iDir);

    protected:
    private:
        int m_iDir,m_iHp,m_iOwner;
        float m_fSpeedX,m_fSpeedY,m_fMaxSpeed;
};

#endif // BULLET_H
