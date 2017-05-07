#ifndef BALA_H
#define BALA_H

#include "GameObject.h"

class Bala{
    public:
        Bala(b2Vec2 pos, int tiempoVidaP, int velocidad, float deviacionP, int dir, int tipo = 0,  char *model = "BearEngine/res/arma.obj", char *texture = NULL);
        virtual ~Bala();
        void actualiza();
        void teletransportar();
        void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        void setDestruir(bool aux){ destruir = aux;}
        int getDestruir(){return destruir;}
        int GetId();
    private:
        GameObject m_gameObject;
        BearMngr *m_pBearMngr;
        int tiempoVida;
        float desviacion;
        uint32 time2Kill;
        b2Vec2 m_vel;
        b2Vec2 nextPos;
        int dir;
        int m_id;
        bool teletransportado;
		bool destruir;
};
#endif // BALA_H
