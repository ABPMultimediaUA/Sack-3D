#ifndef METRALLA_H
#define METRALLA_H

#include "GameObject.h"

class Metralla{
    public:
        Metralla(b2Vec2 pos,b2Vec2 vel);
        virtual ~Metralla();
        void actualiza();
        void setDestruir(bool aux){ m_destruir = aux;}
        void SetLinearVelocity(b2Vec2 vel);
        int getDestruir(){return m_destruir;}
        int GetId();

    private:
        BearMngr     *m_pBearMngr;
        int 	     m_tiempoVida;
        uint32       m_time2Kill;
        GameObject   m_gameObject;
        int          m_id;
		bool 		 m_destruir;
};

#endif // METRALLA_H
