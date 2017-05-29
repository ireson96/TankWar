#ifndef TANKENEMY_H
#define TANKENEMY_H

#include <CommonClass.h>


class CTankEnemy : public CSprite
{
    public:
        CTankEnemy(const char* szName);
        virtual ~CTankEnemy();
        void Init();
        void OnMove();

        void SetHp(int hp)									             {m_iHp = hp;}
        void SetDir(int dir)             								{m_iDir = dir;}
        void SetSpeedX(float speedX)    						{m_fSpeedX = speedX;}
        void SetSpeedY(float speedY)    						{m_fSpeedY = speedY;}
        void SetChangeDirTime(float changeDirTime)              {m_fChangeDirTime = changeDirTime;}
        void SetBulletCreateTime(float bulletCreateTime)        {m_fBulletCreateTime = bulletCreateTime;}
        int GetHp()                   										{return m_iHp;}
        int GetDir()                 										{return m_iDir;}
        float GetSpeedX()            								{return m_fSpeedX;}
        float GetSpeedY()								            {return m_fSpeedY;}
        float GetChangeDirTime()                                    {return m_fChangeDirTime;}
        float GetBulletCreateTime()                                 {return m_fBulletCreateTime;}
        void OnMove(float fDeltaTime);
        void OnFire(float fDeltaTime);



    protected:
    private:
        int m_iDir,m_iHp;
        float m_fSpeedX,m_fSpeedY,m_fChangeDirTime,m_fBulletCreateTime;
};

#endif // TANKENEMY_H
