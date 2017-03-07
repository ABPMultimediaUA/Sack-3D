#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

class Usable : public Cogible{
    public:
        Usable(Spawner* expo, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color);
        virtual ~Usable();
        virtual void usar();
        virtual void actualiza();
        virtual void CompruebaVida();
        virtual int getUsos();
    protected:
        bool usando;
	    int usos;
        int cadencia;
        bool killCountDown;
        irr::f32 time2Kill;
        irr::f32 timeCadencia;
        irr::ITimer* timer2Kill;
        irr::ITimer* timerCadencia;
};

#endif
