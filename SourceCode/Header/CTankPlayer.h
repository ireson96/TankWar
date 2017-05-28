#ifndef CTANKPLAYER_H
#define CTANKPLAYER_H

#include <CommonClass.h>


class CTankPlayer : public CSprite
{
    public:
        CTankPlayer(const char* szName);
        virtual ~CTankPlayer();
        void SetHp(int hp)									             {m_iHp = hp;}
        void SetDir(int dir)             								{m_iDir = dir;}
        void SetSpeedX(float speedX)    						{m_fSpeedX = speedX;}
        void SetSpeedY(float speedY)    						{m_fSpeedY = speedY;}
        //get·½·¨
        int GetHp()                   										{return m_iHp;}
        int GetDir()                 										{return m_iDir;}
        float GetSpeedX()            								{return m_fSpeedX;}
        float GetSpeedY()								            {return m_fSpeedY;}
        void Init();
        void OnMove(int iKey,bool bPress);

        void OnFire();
    protected:
    private:
    int m_iDir,m_iHp;
    float m_fSpeedX,m_fSpeedY,m_fMaxSpeed;
};

#endif // CTANKPLAYER_H
