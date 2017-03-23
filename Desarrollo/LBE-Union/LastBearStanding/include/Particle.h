#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"

class Particle{
    public:
        Particle(PhysicBody *physicBody, b2Vec2 pos, irr::core::vector3df tam,  irr::video::SColor color,  int tiempoVida);
        virtual ~Particle();
        void actualiza();
        void setDestruir(bool aux){ m_destruir = aux;}
        int getDestruir(){return m_destruir;}
        int GetId();
    private:
        IrrMngr     *m_pIrrMngr;
        int 	     m_tiempoVida;
        irr::f32     m_time2Kill;
        irr::ITimer* m_timer2Kill;
        GameObject   m_gameObject;
        int          m_id;
		bool 		 m_destruir;

};

#endif // PARTICLE_H
