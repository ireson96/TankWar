#ifndef CTANKPLAYER_H
#define CTANKPLAYER_H

#include <Weapon.h>


class CTankPlayer : public CWeapon
{
    public:
        CTankPlayer(const char* szName);
        virtual ~CTankPlayer();
        void Init();
        void OnMove(int iKey,bool bPress);

        void OnFire();
        void OnSpriteColSprite(CWeapon* pSprite);
    protected:
    private:
    float m_fMaxSpeed;
};

#endif // CTANKPLAYER_H
