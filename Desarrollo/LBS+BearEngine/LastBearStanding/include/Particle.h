#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"

class Particle{
    public:
        Particle(PhysicBody *physicBody, b2Vec2 pos, glm::vec3 tam,  int tiempoVida = 5000,  char *model = "BearEngine/res/arma.obj", char *texture = NULL);
        virtual ~Particle();
        void actualiza();
        void SetAngularVelocity(float imp);
        void SetLinearVelocity(b2Vec2 vel);
        void
        SetGravity(float gravity);
        void setDestruir(bool aux){ m_destruir = aux;}
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

#endif // PARTICLE_H
