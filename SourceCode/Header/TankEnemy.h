#ifndef TANKENEMY_H
#define TANKENEMY_H

#include <Weapon.h>



class CTankEnemy : public CWeapon
{
    public:
        CTankEnemy(const char* szName);
        virtual ~CTankEnemy();
        void Init();
        void OnMove();

        void SetChangeDirTime(float changeDirTime)              {m_fChangeDirTime = changeDirTime;}
        void SetBulletCreateTime(float bulletCreateTime)        {m_fBulletCreateTime = bulletCreateTime;}
        float GetChangeDirTime()                                    {return m_fChangeDirTime;}
        float GetBulletCreateTime()                                 {return m_fBulletCreateTime;}
        void OnMove(float fDeltaTime);
        void OnFire(float fDeltaTime);
        void OnSpriteColSprite(CWeapon* pSprite);



    protected:
    private:
        float m_fChangeDirTime,m_fBulletCreateTime;
};

#endif // TANKENEMY_H
