#ifndef BALA_H
#define BALA_H

#include "GameObject.h"

class Bala{
    public:
        Bala(b2Vec2 pos, int tiempoVidaP, int velocidad, float deviacionP, int dir, int tipo = 0);
        virtual ~Bala();
        void actualiza();
        void teletransportar();
        void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        void setDestruir(bool aux){ destruir = aux;}
        int getDestruir(){return destruir;}
        int GetId();
    private:
        GameObject m_gameObject;
        IrrMngr *m_pIrrMngr;
        int tiempoVida;
        float desviacion;
        irr::f32 time2Kill;
        irr::ITimer* timer2Kill;
        b2Fixture* balaFixture;
        b2Vec2 m_vel;
        b2Vec2 nextPos;
        int dir;
        int m_id;
        bool teletransportado;
		bool destruir;
};
#endif // BALA_H
